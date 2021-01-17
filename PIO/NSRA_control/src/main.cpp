#include <Arduino.h>
#include <AccelStepper.h>
#include <ArduinoQueue.h>

#define frq 20

long dummy_pos = 50;
IntervalTimer dummy_timer;
bool dummy_flag = true;

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

void change_pos() {
  if(dummy_pos > 6000)
  {
    dummy_flag = false;
  } else if(dummy_pos < 100)
  {
    dummy_flag = true;
  }

  if(dummy_flag)
  {
    dummy_pos = round(dummy_pos*1.02);      
  }
  else {
    dummy_pos = round(dummy_pos*0.98);
  }
  
  pos n;
  n.axis1 = dummy_pos;
  queue.enqueue(n);
}

void setup() {
  myTimer.begin(update, 50000);
  dummy_timer.begin(change_pos, 50000);
  axis1.setAcceleration(5000);
}

void loop() {

  axis1.run();

}  