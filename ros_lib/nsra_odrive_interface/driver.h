#ifndef _ROS_SERVICE_driver_h
#define _ROS_SERVICE_driver_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace nsra_odrive_interface
{

static const char DRIVER[] = "nsra_odrive_interface/driver";

  class driverRequest : public ros::Msg
  {
    public:
      typedef int16_t _req_type;
      _req_type req;

    driverRequest():
      req(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_req;
      u_req.real = this->req;
      *(outbuffer + offset + 0) = (u_req.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_req.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->req);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_req;
      u_req.base = 0;
      u_req.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_req.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->req = u_req.real;
      offset += sizeof(this->req);
     return offset;
    }

    virtual const char * getType() override { return DRIVER; };
    virtual const char * getMD5() override { return "dd25d455863aa5d7629ccfd6222c2b5c"; };

  };

  class driverResponse : public ros::Msg
  {
    public:
      typedef float _x_type;
      _x_type x;
      typedef float _y_type;
      _y_type y;

    driverResponse():
      x(0),
      y(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_x;
      u_x.real = this->x;
      *(outbuffer + offset + 0) = (u_x.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_x.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_x.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_x.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->x);
      union {
        float real;
        uint32_t base;
      } u_y;
      u_y.real = this->y;
      *(outbuffer + offset + 0) = (u_y.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_y.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_y.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_y.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->y);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_x;
      u_x.base = 0;
      u_x.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_x.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_x.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_x.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->x = u_x.real;
      offset += sizeof(this->x);
      union {
        float real;
        uint32_t base;
      } u_y;
      u_y.base = 0;
      u_y.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_y.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_y.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_y.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->y = u_y.real;
      offset += sizeof(this->y);
     return offset;
    }

    virtual const char * getType() override { return DRIVER; };
    virtual const char * getMD5() override { return "ff8d7d66dd3e4b731ef14a45d38888b6"; };

  };

  class driver {
    public:
    typedef driverRequest Request;
    typedef driverResponse Response;
  };

}
#endif
