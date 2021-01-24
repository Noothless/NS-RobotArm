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

//rosrun rosserial_python serial_node.py /dev/ttyUSB0

#include <Arduino.h>
#include <AccelStepper.h>
#include <ArduinoQueue.h>
#include <ros.h>
#include <nsra_odrive_interface/nsra_control_step.h>

#define frq 1

ros::NodeHandle nh;

AccelStepper axis1(2, 0, 1);
AccelStepper axis2(2, 2, 3); 
AccelStepper axis3(2, 4, 5); 
AccelStepper axis4(2, 6, 7);
AccelStepper axis5(2, 8, 9); 
AccelStepper axis6(2,10,11);

IntervalTimer ctrl_loop_timer;

bool queueFlag = false;

struct pos {
    volatile long axis1;
    volatile long axis2;
    volatile long axis3;
    volatile long axis4;
    volatile long axis5;
    volatile long axis6;
};
ArduinoQueue<pos> queue(50);

void update() {
  if(queueFlag)
  {
    pos o = queue.dequeue();
    pos n = queue.getHead();

    axis1.setMaxSpeed(abs(n.axis1 - o.axis1) * frq);
    axis2.setMaxSpeed(abs(n.axis2 - o.axis2) * frq);
    axis3.setMaxSpeed(abs(n.axis3 - o.axis3) * frq);
    axis4.setMaxSpeed(abs(n.axis4 - o.axis4) * frq);
    axis5.setMaxSpeed(abs(n.axis5 - o.axis5) * frq);
    axis6.setMaxSpeed(abs(n.axis6 - o.axis6) * frq);

    axis1.moveTo(n.axis1);
    axis2.moveTo(n.axis2);
    axis3.moveTo(n.axis3);
    axis4.moveTo(n.axis4);
    axis5.moveTo(n.axis5);
    axis6.moveTo(n.axis6);
  } else if(queue.itemCount() >= 10 && !queueFlag){
    queueFlag = true;
  }
}

void change_pos(const nsra_odrive_interface::nsra_control_step& msg) {
  pos n;
  n.axis1 = msg.axis1*4;
  n.axis2 = msg.axis2*4;
  n.axis3 = msg.axis3*4;
  n.axis4 = msg.axis4*4;
  n.axis5 = msg.axis5*4;
  n.axis6 = msg.axis6*4;
  //axis6.moveTo(n.axis6);
  queue.enqueue(n);
}

ros::Subscriber<nsra_odrive_interface::nsra_control_step> gc("/nsra/axis_step", &change_pos);

void setup() {
  Serial.begin(115200);
  nh.initNode();
  nh.subscribe(gc);
  ctrl_loop_timer.begin(update, 1000000);

  axis1.setAcceleration(5000);
  axis2.setAcceleration(5000);
  axis3.setAcceleration(5000);
  axis4.setAcceleration(5000);
  axis5.setAcceleration(5000);
  axis6.setAcceleration(5000);

  //axis6.setMaxSpeed(50);
}

void loop() {

  nh.spinOnce();
  axis1.run();
  axis2.run();
  axis3.run();
  axis4.run();
  axis5.run();
  axis6.run();

}  