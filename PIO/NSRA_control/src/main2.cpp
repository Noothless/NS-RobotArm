/*****************************************************************************
*  BSD 3-Clause License
* 
*  Copyright (c) 2020, Noa Sendlhofer
*  All rights reserved.
* 
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions are met:
* 
*  1. Redistributions of source code must retain the above copyright notice, this
*     list of conditions and the following disclaimer.
* 
*  2. Redistributions in binary form must reproduce the above copyright notice,
*     this list of conditions and the following disclaimer in the documentation
*     and/or other materials provided with the distribution.
* 
*  3. Neither the name of the copyright holder nor the names of its
*     contributors may be used to endorse or promote products derived from
*     this software without specific prior written permission.
* 
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
*  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
*  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
*  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
*  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
*  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
*  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
****************************************************************************/

/* Author: Noa Sendlhofer
   Desc:   Part of the NSRA Control stack. Teensy step/direction signal generator.
*/

#include <Arduino.h>
#include <AccelStepper.h>
#include <ArduinoQueue.h>
#include <ros.h>
#include <TeensyThreads.h>
#include <Wire.h>
#include <CRC32.h>
#include <Base64.h>

#define QUEUE_SIZE 10
#define ACCELERATION 5000
#define FRQ 20
#define PULSE_WIDTH 50
#define VEL_DIFF 500

Threads::Mutex pos_lock;

volatile bool serialFlag = true;

AccelStepper axis1(1, 0, 1);
AccelStepper axis2(1, 2, 3);
AccelStepper axis3(1, 4, 5);
AccelStepper axis4(1, 6, 7);
AccelStepper axis5(1, 8, 9);
AccelStepper axis6(1,10,11);

IntervalTimer ctrl_loop_timer;

bool queueFlag = false;
bool controlFlag = false;

struct pos {
    volatile int axis1;
    volatile int axis2;
    volatile int axis3;
    volatile int axis4;
    volatile int axis5;
    volatile int axis6;
    pos(): axis1(0), axis2(0), axis3(0), axis4(0), axis5(0), axis6(0) {}
};
ArduinoQueue<pos> queue(50);

pos last;

void update() {
  if(queueFlag && controlFlag)
  {
    
    pos_lock.lock(1);
    pos now = queue.dequeue();
    pos next = queue.getHead();
    pos_lock.unlock();

    /*
    Wire.beginTransmission(8);
    Wire.write(((uint16_t)(now.axis1 + 32000) >> 8) & 0xFF);
    Wire.write(((uint16_t)(now.axis1 + 32000) >> 0) & 0xFF);
    Wire.endTransmission();
    */

    axis1.setMaxSpeed((int)round((abs(last.axis1 - now.axis1) + abs(now.axis1 - next.axis1))/2)*FRQ + VEL_DIFF);
    axis2.setMaxSpeed((int)round((abs(last.axis2 - now.axis2) + abs(now.axis2 - next.axis2))/2)*FRQ + VEL_DIFF);
    axis3.setMaxSpeed((int)round((abs(last.axis3 - now.axis3) + abs(now.axis3 - next.axis3))/2)*FRQ + VEL_DIFF);
    axis4.setMaxSpeed((int)round((abs(last.axis4 - now.axis4) + abs(now.axis4 - next.axis4))/2)*FRQ + VEL_DIFF);
    axis5.setMaxSpeed((int)round((abs(last.axis5 - now.axis5) + abs(now.axis5 - next.axis5))/2)*FRQ + VEL_DIFF);
    axis6.setMaxSpeed((int)round((abs(last.axis6 - now.axis6) + abs(now.axis6 - next.axis6))/2)*FRQ + VEL_DIFF);
    
    axis1.moveTo(now.axis1);
    axis2.moveTo(now.axis2);
    axis3.moveTo(now.axis3);
    axis4.moveTo(now.axis4);
    axis5.moveTo(now.axis5);
    axis6.moveTo(now.axis6);

    last = now;
    
  } else if(queue.itemCount() >= QUEUE_SIZE && !queueFlag){
    queueFlag = true;
  }
  
  if(queue.itemCount() == 0){
    queueFlag = false;
  }
  
}

void serial_interrupt() {

  char in_bytes[24];
  CRC32 crc;
  
  while (Serial.available())
  {
    in_bytes[0] = Serial.read();
    if (in_bytes[0] == 10) { break; }
  }

  for (int n = 0; n < 24; n++)
  {
    in_bytes[n] = Serial.read();
  }

  char dec_string[16];

  Base64.decode(dec_string, in_bytes, 24);

  uint32_t checksum = crc.calculate(dec_string, 12);

  uint32_t rec_checksum;

  rec_checksum = dec_string[15];
  rec_checksum = rec_checksum << 8;
  rec_checksum = rec_checksum | dec_string[14];
  rec_checksum = rec_checksum << 8;
  rec_checksum = rec_checksum | dec_string[13];
  rec_checksum = rec_checksum << 8;
  rec_checksum = rec_checksum | dec_string[12];

  if(rec_checksum == checksum) {

    if(!controlFlag) {
      axis1.enableOutputs();
      axis2.enableOutputs();
      axis3.enableOutputs();
      axis4.enableOutputs();
      axis5.enableOutputs();
      axis6.enableOutputs();

      axis1.setCurrentPosition(0);
      axis2.setCurrentPosition(0);
      axis3.setCurrentPosition(0);
      axis4.setCurrentPosition(0);
      axis5.setCurrentPosition(0);
      axis6.setCurrentPosition(0);

      controlFlag = true;
      digitalWrite(LED_BUILTIN, HIGH);
    }
    
    pos n;
  
    n.axis1 = (uint16_t)((dec_string[1] << 8) | dec_string[0]) - 32000;
    n.axis2 = (uint16_t)((dec_string[3] << 8) | dec_string[2]) - 32000;
    n.axis3 = (uint16_t)((dec_string[5] << 8) | dec_string[4]) - 32000;
    n.axis4 = (uint16_t)((dec_string[7] << 8) | dec_string[6]) - 32000;
    n.axis5 = (uint16_t)((dec_string[9] << 8) | dec_string[8]) - 32000;
    n.axis6 = (uint16_t)((dec_string[11] << 8) | dec_string[10]) - 32000;
  
    pos_lock.lock(1);
    queue.enqueue(n);
    pos_lock.unlock();

  } else if(controlFlag) {

    axis1.disableOutputs();
    axis2.disableOutputs();
    axis3.disableOutputs();
    axis4.disableOutputs();
    axis5.disableOutputs();
    axis6.disableOutputs();

    controlFlag = false;
    digitalWrite(LED_BUILTIN, LOW);
     
  }
  
  serialFlag = true;
}

void setup() {
  Serial.begin(115200);

  while (!Serial) {
    delay(1);
  }

  pinMode(LED_BUILTIN, OUTPUT);
  //Wire.begin();
  axis1.setAcceleration(ACCELERATION);
  axis2.setAcceleration(ACCELERATION);
  axis3.setAcceleration(ACCELERATION);
  axis4.setAcceleration(ACCELERATION);
  axis5.setAcceleration(ACCELERATION);
  axis6.setAcceleration(ACCELERATION);

  axis1.setMinPulseWidth(PULSE_WIDTH);
  axis2.setMinPulseWidth(PULSE_WIDTH);
  axis3.setMinPulseWidth(PULSE_WIDTH);
  axis4.setMinPulseWidth(PULSE_WIDTH);
  axis5.setMinPulseWidth(PULSE_WIDTH);
  axis6.setMinPulseWidth(PULSE_WIDTH);

  axis1.disableOutputs();
  axis2.disableOutputs();
  axis3.disableOutputs();
  axis4.disableOutputs();
  axis5.disableOutputs();
  axis6.disableOutputs();

  ctrl_loop_timer.begin(update, 1000000/FRQ);

}

void loop() {
  
  if(Serial.available() > 24 && serialFlag) {
    serialFlag = false;
    serial_interrupt();
  }

  if(controlFlag) {
    axis1.run();
    axis2.run();
    axis3.run();
    axis4.run();
    axis5.run();
    axis6.run();
  }

  if(!Serial && controlFlag) {
    axis1.disableOutputs();
    axis2.disableOutputs();
    axis3.disableOutputs();
    axis4.disableOutputs();
    axis5.disableOutputs();
    axis6.disableOutputs();

    controlFlag = false;
    digitalWrite(LED_BUILTIN, LOW);
  }
  
}