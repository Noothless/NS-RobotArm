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
#define SPEED 10000

Threads::Mutex pos_lock;

volatile bool serialFlag = true;

AccelStepper axis1(1, 0, 1);
/*
AccelStepper axis2(1, 2, 3);
AccelStepper axis3(1, 4, 5);
AccelStepper axis4(1, 6, 7);
AccelStepper axis5(1, 8, 9);
AccelStepper axis6(1,10,11);
*/
IntervalTimer ctrl_loop_timer;

int prev_ax = 0;

bool queueFlag = false;

struct pos {
    volatile int16_t axis1;
    volatile int16_t axis2;
    volatile int16_t axis3;
    volatile int16_t axis4;
    volatile int16_t axis5;
    volatile int16_t axis6;

    volatile int16_t vel1;
    volatile int16_t vel2;
    volatile int16_t vel3;
    volatile int16_t vel4;
    volatile int16_t vel5;
    volatile int16_t vel6;
};
ArduinoQueue<pos> queue(50);

void update() {
  if(queueFlag)
  {
    
    pos_lock.lock(1);
    pos n = queue.dequeue();
    //pos n = queue.getHead();
    pos_lock.unlock();
    
    /*
    Wire.beginTransmission(8);
    Wire.write(((int16_t)(n.axis1) >> 0) & 0xFF);
    Wire.write(((int16_t)(n.axis1) >> 8) & 0xFF);
    Wire.endTransmission();
    */
    axis1.setMaxSpeed((int)n.vel1);
    /*
    axis2.setMaxSpeed(n.vel2);
    axis3.setMaxSpeed(n.vel3);
    axis4.setMaxSpeed(n.vel4);
    axis5.setMaxSpeed(n.vel5);
    axis6.setMaxSpeed(n.vel6);
    */
    //prev_ax += 50;
    axis1.moveTo((int)n.axis1);
    /*
    axis2.moveTo(n.axis2);
    axis3.moveTo(n.axis3);
    axis4.moveTo(n.axis4);
    axis5.moveTo(n.axis5);
    axis6.moveTo(n.axis6);
    */
  } else if(queue.itemCount() >= QUEUE_SIZE && !queueFlag){
    queueFlag = true;
  }
  
  if(queue.itemCount() == 0){
    queueFlag = false;
  }
  
}

void serial_interrupt_thread() {
  //unsigned int starttime;
  //starttime = millis();
  byte in_bytes[24];
  //while ( (Serial.available() < 25) && ((millis() - starttime) < MAX_SERIAL_WAIT) ) { delay(1); }
  
  while (Serial.available())
  {
    in_bytes[0] = Serial.read();
    if (in_bytes[0] == 10) { break; }
  }
  
  for (int n = 0; n < 24; n++)
  {
    in_bytes[n] = Serial.read();
  }

  pos n;
  
  n.axis1 = (int16_t)((in_bytes[0] << 8) | in_bytes[1]);
  n.vel1 = (int16_t)((in_bytes[2] << 8) | in_bytes[3]);
  /*
  n.axis2 = (int16_t)((in_bytes[4] << 8) | in_bytes[5]);
  n.vel2 = (int16_t)((in_bytes[6] << 8) | in_bytes[7]);
  n.axis3 = (int16_t)((in_bytes[8] << 8) | in_bytes[9]);
  n.vel3 = (int16_t)((in_bytes[10] << 8) | in_bytes[11]);
  n.axis4 = (int16_t)((in_bytes[12] << 8) | in_bytes[13]);
  n.vel4 = (int16_t)((in_bytes[14] << 8) | in_bytes[15]);
  n.axis5 = (int16_t)((in_bytes[16] << 8) | in_bytes[17]);
  n.vel5 = (int16_t)((in_bytes[18] << 8) | in_bytes[19]);
  n.axis6 = (int16_t)((in_bytes[20] << 8) | in_bytes[21]);
  n.vel6 = (int16_t)((in_bytes[22] << 8) | in_bytes[23]);    
  */
  pos_lock.lock(1);
  queue.enqueue(n); //TODO: MUTEX?
  pos_lock.unlock();

  serialFlag = true;
}

void setup() {
  Serial.begin(115200);
  //Wire.begin();
  //pinMode(12, OUTPUT);
  //digitalWrite(12, LOW);
  axis1.setAcceleration(ACCELERATION);
  /*
  axis2.setAcceleration(ACCELERATION);
  axis3.setAcceleration(ACCELERATION);
  axis4.setAcceleration(ACCELERATION);
  axis5.setAcceleration(ACCELERATION);
  axis6.setAcceleration(ACCELERATION);
  */
  axis1.setMinPulseWidth(PULSE_WIDTH);
  axis1.setMaxSpeed(500);
  /*
  axis2.setMinPulseWidth(PULSE_WIDTH);
  axis3.setMinPulseWidth(PULSE_WIDTH);
  axis4.setMinPulseWidth(PULSE_WIDTH);
  axis5.setMinPulseWidth(PULSE_WIDTH);
  axis6.setMinPulseWidth(PULSE_WIDTH);
  */
  ctrl_loop_timer.begin(update, 1000000/FRQ);

}

void loop() {
  
  if(Serial.available() > 24 && serialFlag) {
    serialFlag = false;
    //threads.addThread(serial_interrupt_thread);
    serial_interrupt_thread();
  }

  axis1.run();
  /*
  axis2.run();
  axis3.run();
  axis4.run();
  axis5.run();
  axis6.run();
  */
}