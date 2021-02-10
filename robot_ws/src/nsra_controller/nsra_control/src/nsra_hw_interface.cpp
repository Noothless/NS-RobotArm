/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2015, University of Colorado, Boulder
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the Univ of CO, Boulder nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

/* Author: Dave Coleman
   Desc:   Example ros_control hardware interface blank template for the RRBot
           For a more detailed simulation example, see sim_hw_interface.cpp
*/

#include <nsra_control/nsra_hw_interface.h>
#include "std_msgs/Float64.h"
#include "std_msgs/Int32.h"
#include <vector>
#include <nsra_odrive_interface/nsra_control_step.h>

namespace nsra_control
{

NSRAHWInterface::NSRAHWInterface(ros::NodeHandle &nh, urdf::Model *urdf_model)
  : nsra_controller::GenericHWInterface(nh, urdf_model)
{
  ROS_INFO_NAMED("nsra_hardware_interface", "NSRAHWInterface Ready.");

  drive_pub1 = nh_.advertise<std_msgs::Float64>("drive_pub1", 5);
  drive_pub2 = nh_.advertise<std_msgs::Float64>("drive_pub2", 5);
  drive_pub3 = nh_.advertise<std_msgs::Float64>("drive_pub3", 5);
  drive_pub4 = nh_.advertise<std_msgs::Float64>("drive_pub4", 5);
  drive_pub5 = nh_.advertise<std_msgs::Float64>("drive_pub5", 5);
  drive_pub6 = nh_.advertise<std_msgs::Float64>("drive_pub6", 5);

  axis_step = nh_.advertise<nsra_odrive_interface::nsra_control_step>("axis_step", 5);
  
   try
  {
    ser.setPort("/dev/controller");
    ser.setBaudrate(115200);
    serial::Timeout to = serial::Timeout::simpleTimeout(1000);
    ser.setTimeout(to);
    ser.open();
  }
  catch (serial::IOException& e)
  {
    ROS_ERROR_STREAM("Unable to open port ");
  }

  if(ser.isOpen()) {
        ROS_INFO_STREAM("Serial Port initialized");
  }
  else {
        ROS_ERROR_STREAM("Port failed! ");
  }
  
  /*
  try
  {
    serial_stream.Open(SERIAL_PORT);
    ROS_INFO_NAMED("nsra_hardware_interface", "Connected!");
  }
  catch (char *excp)
  {
    ROS_INFO_NAMED("nsra_hardware_interface", "Serial Error!");
  }

  serial_stream.SetBaudRate(LibSerial::SerialStreamBuf::BAUD_9600);
  serial_stream.SetCharSize(LibSerial::SerialStreamBuf::CHAR_SIZE_8);
  serial_stream.SetFlowControl(LibSerial::SerialStreamBuf::FLOW_CONTROL_NONE);
  serial_stream.SetParity(LibSerial::SerialStreamBuf::PARITY_NONE);
  serial_stream.SetNumOfStopBits(1);
  */
  for(int i = 0; i <= 5; i++) {
    saved_pos.push_back(0);
  }
}
/*
NSRAHWInterface::~NSRAHWInterface(){
  serial_stream.Close();
}
*/
void NSRAHWInterface::read(ros::Duration &elapsed_time)
{
  for (size_t i = 0; i < num_joints_; i++) {
    //ROS_INFO("read:1");
    /*
    ODrive_Interface_test::feedback feedback;
    feedback.request.axis = i + 1;
    axis_position.call(feedback);
    double p = feedback.response.position;
    joint_position_[i] = p;
    */
    joint_position_[i] = saved_pos[i];
  }
}

unsigned char NSRAHWInterface::reverse(unsigned char b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}

void NSRAHWInterface::write(ros::Duration &elapsed_time)
{
  /*
  if ( ! serial_stream.good() )
  {
    ROS_INFO_NAMED("nsra_hardware_interface", "Serial Error - test!");
  }
  */
  // Safety
  enforceLimits(elapsed_time);
  nsra_odrive_interface::nsra_control_step msg_step;
  const int BUFFER_SIZE = 13;
  unsigned char data[BUFFER_SIZE];
  data[0] = '\n';
  for (size_t i = 0; i < num_joints_; i++) {
    double pi = 2*acos(0.0);
    std_msgs::Float64 msg;
    int steps;
    int steps_old;
    if(i == 0)
    {
      msg.data = joint_position_command_[i]*1024000/pi/8192;
      drive_pub1.publish(msg);
      steps = round(joint_position_command_[i]*12500/pi);
      steps_old = round(saved_pos[i]*12500/pi);
      msg_step.axis1 = abs(steps_old - steps)*10;
    } else if(i == 1)
    {
      msg.data = joint_position_command_[i]*(1024000*0.885)/pi/8192;
      drive_pub2.publish(msg);
      steps = round(joint_position_command_[i]*12500*0.885/pi);
      steps_old = round(saved_pos[i]*12500*0.885/pi);
      msg_step.axis2 = abs(steps_old - steps)*10;
    } else if(i == 2)
    {
      msg.data = joint_position_command_[i]*(-204800)/pi/8192;
      drive_pub3.publish(msg);
      steps = round(joint_position_command_[i]*(-2500)/pi);
      steps_old = round(saved_pos[i]*(-2500)/pi);
      msg_step.axis3 = abs(steps_old - steps)*10;
    } else if(i == 3)
    {
      msg.data = joint_position_command_[i]*204800/pi/8192;
      drive_pub4.publish(msg);
      steps = round(joint_position_command_[i]*2500/pi);
      steps_old = round(saved_pos[i]*2500/pi);
      msg_step.axis4 = abs(steps_old - steps)*10;
    } else if(i == 4)
    {
      msg.data = joint_position_command_[i]*204800/pi/8192;
      drive_pub5.publish(msg);
      steps = round(joint_position_command_[i]*2500/pi);
      steps_old = round(saved_pos[i]*2500/pi);
      msg_step.axis5 = abs(steps_old - steps)*10;
    } else if(i == 5)
    {
      msg.data = joint_position_command_[i]*327680/pi/8192;
      drive_pub6.publish(msg);
      steps = round(joint_position_command_[i]*4000/pi);
      steps_old = round(saved_pos[i]*4000/pi);
      msg_step.axis6 = abs(steps_old - steps)*10;
    }
    data[i*2+1] = ((uint16_t)(steps + 32000) >> 0) & 0xFF;
    data[i*2+2] = ((uint16_t)(steps + 32000) >> 8) & 0xFF;

    saved_pos[i] = joint_position_command_[i];
  }
  axis_step.publish(msg_step);
  
  //ROS_INFO_NAMED("nsra_hardware_interface", String(((data[0] << 8) | data[1])*4));
  //std::cout << abs((int16_t)((data[4] << 8) | data[3])) << std::endl;
  
  try {
    ser.write(data, BUFFER_SIZE);
  } catch (char *excp)
  {
    ROS_ERROR_STREAM("Error!");
  }
  
  /*
  test_pos -= 100;
  std::cout << test_pos << std::endl;
  unsigned char data_test[3];
  data_test[0] = '\n';
  data_test[1] = ((uint16_t)(test_pos + 32000) >> 0) & 0xFF;
  data_test[2] = ((uint16_t)(test_pos + 32000) >> 8) & 0xFF;
  ser.write(data_test, 3);
  */
  //serial_stream.DrainWriteBuffer();
}

void NSRAHWInterface::enforceLimits(ros::Duration &period)
{
  // ----------------------------------------------------
  // ----------------------------------------------------
  // ----------------------------------------------------
  //
  // CHOOSE THE TYPE OF JOINT LIMITS INTERFACE YOU WANT TO USE
  // YOU SHOULD ONLY NEED TO USE ONE SATURATION INTERFACE,
  // DEPENDING ON YOUR CONTROL METHOD
  //
  // EXAMPLES:
  //
  // Saturation Limits ---------------------------
  //
  // Enforces position and velocity
  //pos_jnt_sat_interface_.enforceLimits(period);
  //
  // Enforces velocity and acceleration limits
  // vel_jnt_sat_interface_.enforceLimits(period);
  //
  // Enforces position, velocity, and effort
  // eff_jnt_sat_interface_.enforceLimits(period);

  // Soft limits ---------------------------------
  //
  // pos_jnt_soft_limits_.enforceLimits(period);
  // vel_jnt_soft_limits_.enforceLimits(period);
  // eff_jnt_soft_limits_.enforceLimits(period);
  //
  // ----------------------------------------------------
  // ----------------------------------------------------
  // ---------------------------------------------------- 
}

}  // namespace
