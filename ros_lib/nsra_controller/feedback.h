#ifndef _ROS_SERVICE_feedback_h
#define _ROS_SERVICE_feedback_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace nsra_controller
{

static const char FEEDBACK[] = "nsra_controller/feedback";

  class feedbackRequest : public ros::Msg
  {
    public:
      typedef int16_t _axis_type;
      _axis_type axis;

    feedbackRequest():
      axis(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_axis;
      u_axis.real = this->axis;
      *(outbuffer + offset + 0) = (u_axis.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_axis.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->axis);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_axis;
      u_axis.base = 0;
      u_axis.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_axis.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->axis = u_axis.real;
      offset += sizeof(this->axis);
     return offset;
    }

    virtual const char * getType() override { return FEEDBACK; };
    virtual const char * getMD5() override { return "1cf916eb1dedd54ae49bec64eb2326a5"; };

  };

  class feedbackResponse : public ros::Msg
  {
    public:
      typedef int32_t _position_type;
      _position_type position;

    feedbackResponse():
      position(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_position;
      u_position.real = this->position;
      *(outbuffer + offset + 0) = (u_position.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_position.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_position.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_position.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->position);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_position;
      u_position.base = 0;
      u_position.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_position.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_position.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_position.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->position = u_position.real;
      offset += sizeof(this->position);
     return offset;
    }

    virtual const char * getType() override { return FEEDBACK; };
    virtual const char * getMD5() override { return "ada70156e12e6e31948c64c60d8bb212"; };

  };

  class feedback {
    public:
    typedef feedbackRequest Request;
    typedef feedbackResponse Response;
  };

}
#endif
