#include <Arduino.h>
#include <AccelStepper.h>
#include <ArduinoQueue.h>
#include <ros.h>
#include <std_msgs/Int32.h>

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
    axis2.setMaxSpeed(400);
    axis3.setMaxSpeed(400);
    axis4.setMaxSpeed(400);
    axis5.setMaxSpeed(400);
    axis6.setMaxSpeed(400);

    axis1.moveTo(n.axis1);
  }
}

void change_pos(const std_msgs::Int32& msg) {
  pos n;
  n.axis1 = msg.data;
  queue.enqueue(n);
}

ros::Subscriber<std_msgs::Int32> gc("/nsra/axis1_step", &change_pos);

void setup() {
  Serial.begin(115200);
  nh.initNode();
  nh.subscribe(gc);
  myTimer.begin(update, 50000);
  axis1.setAcceleration(5000);
}

void loop() {

  nh.spinOnce();
  axis1.run();

}  