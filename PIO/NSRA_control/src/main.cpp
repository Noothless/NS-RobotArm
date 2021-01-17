#include <Arduino.h>
#include <AccelStepper.h>
#include <ArduinoQueue.h>
#include <ros.h>
#include <nsra_odrive_interface/nsra_control_step.h>

#define frq 20

ros::NodeHandle nh;

AccelStepper axis1(2, 0, 1);
AccelStepper axis2(2, 2, 3); 
AccelStepper axis3(2, 4, 5); 
AccelStepper axis4(2, 6, 7);
AccelStepper axis5(2, 8, 9); 
AccelStepper axis6(2, 10, 11);

IntervalTimer myTimer;

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
  if(queue.itemCount() >= 3){
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
  }
}

void change_pos(const nsra_odrive_interface::nsra_control_step& msg) {
  pos n;
  n.axis1 = msg.axis1;
  n.axis2 = msg.axis2;
  n.axis3 = msg.axis3;
  n.axis4 = msg.axis4;
  n.axis5 = msg.axis5;
  n.axis6 = msg.axis6;
  queue.enqueue(n);
}

ros::Subscriber<nsra_odrive_interface::nsra_control_step> gc("/nsra/axis_step", &change_pos);

void setup() {
  Serial.begin(115200);
  nh.initNode();
  nh.subscribe(gc);
  myTimer.begin(update, 50000);

  axis1.setAcceleration(5000);
  axis2.setAcceleration(5000);
  axis3.setAcceleration(5000);
  axis4.setAcceleration(5000);
  axis5.setAcceleration(5000);
  axis6.setAcceleration(5000);
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