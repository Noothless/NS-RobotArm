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

#define MAX_SERIAL_WAIT 35
#define QUEUE_SIZE 10
#define ACCELERATION 5000
#define FRQ 10
#define PULSE_WIDTH 50

Threads::Mutex pos_lock;

volatile bool serialFlag = true;

AccelStepper axis1(1, 0, 1);
AccelStepper axis2(1, 2, 3);
AccelStepper axis3(1, 4, 5);
AccelStepper axis4(1, 6, 7);
AccelStepper axis5(1, 8, 9);
AccelStepper axis6(1,10,11);

IntervalTimer ctrl_loop_timer;

int prev_ax = 0;

bool queueFlag = false;

struct pos {
    volatile int axis1;
    volatile int axis2;
    volatile int axis3;
    volatile int axis4;
    volatile int axis5;
    volatile int axis6;
};
ArduinoQueue<pos> queue(50);

void update() {
  if(queueFlag)
  {
    pos_lock.lock(5);
    pos o = queue.dequeue();
    pos n = queue.getHead();
    pos_lock.unlock();

    axis1.setMaxSpeed(abs(n.axis1 - o.axis1) * FRQ);
    axis2.setMaxSpeed(abs(n.axis2 - o.axis2) * FRQ);
    axis3.setMaxSpeed(abs(n.axis3 - o.axis3) * FRQ);
    axis4.setMaxSpeed(abs(n.axis4 - o.axis4) * FRQ);
    axis5.setMaxSpeed(abs(n.axis5 - o.axis5) * FRQ);
    axis6.setMaxSpeed(abs(n.axis6 - o.axis6) * FRQ);

    
    Wire.beginTransmission(8);
    Wire.write(((uint16_t)(n.axis1 + 32767) >> 0) & 0xFF);
    Wire.write(((uint16_t)(n.axis1 + 32767) >> 8) & 0xFF);
    Wire.endTransmission();
    /*
    Wire.beginTransmission(8);
    Wire.write(((uint16_t)(n.axis1 + 32767) >> 0) & 0xFF);
    Wire.write(((uint16_t)(n.axis1 + 32767) >> 8) & 0xFF);
    Wire.endTransmission();
    */

    axis1.moveTo(n.axis1);
    axis2.moveTo(n.axis2);
    axis3.moveTo(n.axis3);
    axis4.moveTo(n.axis4);
    axis5.moveTo(n.axis5);
    axis6.moveTo(n.axis6);
  } else if(queue.itemCount() >= QUEUE_SIZE && !queueFlag){
    queueFlag = true;
  }
  if(queue.itemCount() == 0){
    queueFlag = false;
  }
  /*
  Wire.beginTransmission(8);
  Wire.write(queue.itemCount());
  Wire.endTransmission();
  */
}

void serial_interrupt_thread() {
  unsigned int starttime;
  starttime = millis();
  byte in_bytes[12];
  while ( (Serial.available() < 13) && ((millis() - starttime) < MAX_SERIAL_WAIT) ) { delay(1); }

  Wire.beginTransmission(8);
  Wire.write(Serial.available());
  Wire.endTransmission();

  
  while (true)
  {
    in_bytes[0] = Serial.read();
    if (in_bytes[0] == '\n')
    {
      Wire.write(in_bytes[0]);
      break;
    }
  }
  //Wire.endTransmission();
  for (int n = 0; n < 12; n++)
  {
    in_bytes[n] = Serial.read();
    Wire.write(in_bytes[n]);
  }
  

  pos n;

  n.axis1 = (((in_bytes[11] << 8) | in_bytes[10]) - 32767);
  n.axis2 = (((in_bytes[9] << 8) | in_bytes[8]) - 32767);
  n.axis3 = (((in_bytes[7] << 8) | in_bytes[6]) - 32767);
  n.axis4 = (((in_bytes[5] << 8) | in_bytes[4]) - 32767);
  n.axis5 = (((in_bytes[3] << 8) | in_bytes[2]) - 32767);
  n.axis6 = (((in_bytes[1] << 8) | in_bytes[0]) - 32767);

  /*
    n.axis1 = (((in_bytes[0] << 8) | in_bytes[1]) - 32767);
    n.axis2 = (((in_bytes[2] << 8) | in_bytes[3]) - 32767);
    n.axis3 = (((in_bytes[4] << 8) | in_bytes[5]) - 32767);
    n.axis4 = (((in_bytes[6] << 8) | in_bytes[7]) - 32767);
    n.axis5 = (((in_bytes[8] << 8) | in_bytes[9]) - 32767);
    n.axis6 = (((in_bytes[10] << 8) | in_bytes[11]) - 32767);
    */
  
  

  pos_lock.lock(5);
  queue.enqueue(n); //TODO: MUTEX?
  pos_lock.unlock();

  

  /*
  n.axis1 = ((in_bytes[0] << 8) | in_bytes[1])*4;
  n.axis2 = ((in_bytes[2] << 8) | in_bytes[3])*4;
  n.axis3 = ((in_bytes[4] << 8) | in_bytes[5])*4;
  n.axis4 = ((in_bytes[6] << 8) | in_bytes[7])*4;
  n.axis5 = ((in_bytes[8] << 8) | in_bytes[9])*4;
  n.axis6 = ((in_bytes[10] << 8) | in_bytes[11])*4;
  */
  serialFlag = true;
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  //pinMode(12, OUTPUT);
  //digitalWrite(12, LOW);
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

  ctrl_loop_timer.begin(update, 1000000/FRQ);

}

void loop() {
  if(Serial.available() > 10 && serialFlag) {
    serialFlag = false;
    //threads.addThread(serial_interrupt_thread);
    serial_interrupt_thread();
  }
  axis1.run();
  axis2.run();
  axis3.run();
  axis4.run();
  axis5.run();
  axis6.run();
}