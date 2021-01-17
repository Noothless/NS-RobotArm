#ifndef _ROS_SERVICE_requested_state_h
#define _ROS_SERVICE_requested_state_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace nsra_odrive_interface
{

static const char REQUESTED_STATE[] = "nsra_odrive_interface/requested_state";

  class requested_stateRequest : public ros::Msg
  {
    public:
      typedef int16_t _axis_type;
      _axis_type axis;
      typedef int16_t _requested_state_type;
      _requested_state_type requested_state;

    requested_stateRequest():
      axis(0),
      requested_state(0)
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
      union {
        int16_t real;
        uint16_t base;
      } u_requested_state;
      u_requested_state.real = this->requested_state;
      *(outbuffer + offset + 0) = (u_requested_state.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_requested_state.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->requested_state);
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
      union {
        int16_t real;
        uint16_t base;
      } u_requested_state;
      u_requested_state.base = 0;
      u_requested_state.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_requested_state.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->requested_state = u_requested_state.real;
      offset += sizeof(this->requested_state);
     return offset;
    }

    virtual const char * getType() override { return REQUESTED_STATE; };
    virtual const char * getMD5() override { return "a10318c9ebc765320932e18d76aa3b6f"; };

  };

  class requested_stateResponse : public ros::Msg
  {
    public:
      typedef bool _result_type;
      _result_type result;

    requested_stateResponse():
      result(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_result;
      u_result.real = this->result;
      *(outbuffer + offset + 0) = (u_result.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->result);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_result;
      u_result.base = 0;
      u_result.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->result = u_result.real;
      offset += sizeof(this->result);
     return offset;
    }

    virtual const char * getType() override { return REQUESTED_STATE; };
    virtual const char * getMD5() override { return "eb13ac1f1354ccecb7941ee8fa2192e8"; };

  };

  class requested_state {
    public:
    typedef requested_stateRequest Request;
    typedef requested_stateResponse Response;
  };

}
#endif
