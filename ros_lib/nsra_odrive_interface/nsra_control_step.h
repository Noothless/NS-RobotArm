#ifndef _ROS_nsra_odrive_interface_nsra_control_step_h
#define _ROS_nsra_odrive_interface_nsra_control_step_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace nsra_odrive_interface
{

  class nsra_control_step : public ros::Msg
  {
    public:
      typedef int32_t _axis1_type;
      _axis1_type axis1;
      typedef int32_t _axis2_type;
      _axis2_type axis2;
      typedef int32_t _axis3_type;
      _axis3_type axis3;
      typedef int32_t _axis4_type;
      _axis4_type axis4;
      typedef int32_t _axis5_type;
      _axis5_type axis5;
      typedef int32_t _axis6_type;
      _axis6_type axis6;

    nsra_control_step():
      axis1(0),
      axis2(0),
      axis3(0),
      axis4(0),
      axis5(0),
      axis6(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_axis1;
      u_axis1.real = this->axis1;
      *(outbuffer + offset + 0) = (u_axis1.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_axis1.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_axis1.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_axis1.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->axis1);
      union {
        int32_t real;
        uint32_t base;
      } u_axis2;
      u_axis2.real = this->axis2;
      *(outbuffer + offset + 0) = (u_axis2.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_axis2.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_axis2.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_axis2.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->axis2);
      union {
        int32_t real;
        uint32_t base;
      } u_axis3;
      u_axis3.real = this->axis3;
      *(outbuffer + offset + 0) = (u_axis3.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_axis3.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_axis3.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_axis3.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->axis3);
      union {
        int32_t real;
        uint32_t base;
      } u_axis4;
      u_axis4.real = this->axis4;
      *(outbuffer + offset + 0) = (u_axis4.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_axis4.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_axis4.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_axis4.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->axis4);
      union {
        int32_t real;
        uint32_t base;
      } u_axis5;
      u_axis5.real = this->axis5;
      *(outbuffer + offset + 0) = (u_axis5.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_axis5.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_axis5.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_axis5.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->axis5);
      union {
        int32_t real;
        uint32_t base;
      } u_axis6;
      u_axis6.real = this->axis6;
      *(outbuffer + offset + 0) = (u_axis6.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_axis6.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_axis6.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_axis6.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->axis6);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_axis1;
      u_axis1.base = 0;
      u_axis1.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_axis1.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_axis1.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_axis1.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->axis1 = u_axis1.real;
      offset += sizeof(this->axis1);
      union {
        int32_t real;
        uint32_t base;
      } u_axis2;
      u_axis2.base = 0;
      u_axis2.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_axis2.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_axis2.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_axis2.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->axis2 = u_axis2.real;
      offset += sizeof(this->axis2);
      union {
        int32_t real;
        uint32_t base;
      } u_axis3;
      u_axis3.base = 0;
      u_axis3.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_axis3.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_axis3.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_axis3.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->axis3 = u_axis3.real;
      offset += sizeof(this->axis3);
      union {
        int32_t real;
        uint32_t base;
      } u_axis4;
      u_axis4.base = 0;
      u_axis4.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_axis4.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_axis4.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_axis4.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->axis4 = u_axis4.real;
      offset += sizeof(this->axis4);
      union {
        int32_t real;
        uint32_t base;
      } u_axis5;
      u_axis5.base = 0;
      u_axis5.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_axis5.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_axis5.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_axis5.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->axis5 = u_axis5.real;
      offset += sizeof(this->axis5);
      union {
        int32_t real;
        uint32_t base;
      } u_axis6;
      u_axis6.base = 0;
      u_axis6.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_axis6.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_axis6.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_axis6.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->axis6 = u_axis6.real;
      offset += sizeof(this->axis6);
     return offset;
    }

    virtual const char * getType() override { return "nsra_odrive_interface/nsra_control_step"; };
    virtual const char * getMD5() override { return "8d76cae6683f63e0ae2877b8fbfdf1d6"; };

  };

}
#endif
