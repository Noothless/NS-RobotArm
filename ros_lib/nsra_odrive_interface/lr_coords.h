#ifndef _ROS_SERVICE_lr_coords_h
#define _ROS_SERVICE_lr_coords_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace nsra_odrive_interface
{

static const char LR_COORDS[] = "nsra_odrive_interface/lr_coords";

  class lr_coordsRequest : public ros::Msg
  {
    public:
      typedef int16_t _test_type;
      _test_type test;

    lr_coordsRequest():
      test(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_test;
      u_test.real = this->test;
      *(outbuffer + offset + 0) = (u_test.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_test.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->test);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_test;
      u_test.base = 0;
      u_test.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_test.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->test = u_test.real;
      offset += sizeof(this->test);
     return offset;
    }

    virtual const char * getType() override { return LR_COORDS; };
    virtual const char * getMD5() override { return "0d3772b8a5da1299e56c0ae15e8afe56"; };

  };

  class lr_coordsResponse : public ros::Msg
  {
    public:
      typedef float _x_left_type;
      _x_left_type x_left;
      typedef float _y_left_type;
      _y_left_type y_left;
      typedef float _x_right_type;
      _x_right_type x_right;
      typedef float _y_right_type;
      _y_right_type y_right;
      typedef float _x1_left_type;
      _x1_left_type x1_left;
      typedef float _y1_left_type;
      _y1_left_type y1_left;
      typedef float _x1_right_type;
      _x1_right_type x1_right;
      typedef float _y1_right_type;
      _y1_right_type y1_right;

    lr_coordsResponse():
      x_left(0),
      y_left(0),
      x_right(0),
      y_right(0),
      x1_left(0),
      y1_left(0),
      x1_right(0),
      y1_right(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_x_left;
      u_x_left.real = this->x_left;
      *(outbuffer + offset + 0) = (u_x_left.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_x_left.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_x_left.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_x_left.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->x_left);
      union {
        float real;
        uint32_t base;
      } u_y_left;
      u_y_left.real = this->y_left;
      *(outbuffer + offset + 0) = (u_y_left.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_y_left.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_y_left.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_y_left.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->y_left);
      union {
        float real;
        uint32_t base;
      } u_x_right;
      u_x_right.real = this->x_right;
      *(outbuffer + offset + 0) = (u_x_right.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_x_right.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_x_right.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_x_right.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->x_right);
      union {
        float real;
        uint32_t base;
      } u_y_right;
      u_y_right.real = this->y_right;
      *(outbuffer + offset + 0) = (u_y_right.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_y_right.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_y_right.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_y_right.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->y_right);
      union {
        float real;
        uint32_t base;
      } u_x1_left;
      u_x1_left.real = this->x1_left;
      *(outbuffer + offset + 0) = (u_x1_left.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_x1_left.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_x1_left.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_x1_left.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->x1_left);
      union {
        float real;
        uint32_t base;
      } u_y1_left;
      u_y1_left.real = this->y1_left;
      *(outbuffer + offset + 0) = (u_y1_left.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_y1_left.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_y1_left.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_y1_left.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->y1_left);
      union {
        float real;
        uint32_t base;
      } u_x1_right;
      u_x1_right.real = this->x1_right;
      *(outbuffer + offset + 0) = (u_x1_right.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_x1_right.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_x1_right.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_x1_right.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->x1_right);
      union {
        float real;
        uint32_t base;
      } u_y1_right;
      u_y1_right.real = this->y1_right;
      *(outbuffer + offset + 0) = (u_y1_right.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_y1_right.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_y1_right.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_y1_right.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->y1_right);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_x_left;
      u_x_left.base = 0;
      u_x_left.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_x_left.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_x_left.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_x_left.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->x_left = u_x_left.real;
      offset += sizeof(this->x_left);
      union {
        float real;
        uint32_t base;
      } u_y_left;
      u_y_left.base = 0;
      u_y_left.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_y_left.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_y_left.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_y_left.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->y_left = u_y_left.real;
      offset += sizeof(this->y_left);
      union {
        float real;
        uint32_t base;
      } u_x_right;
      u_x_right.base = 0;
      u_x_right.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_x_right.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_x_right.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_x_right.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->x_right = u_x_right.real;
      offset += sizeof(this->x_right);
      union {
        float real;
        uint32_t base;
      } u_y_right;
      u_y_right.base = 0;
      u_y_right.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_y_right.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_y_right.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_y_right.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->y_right = u_y_right.real;
      offset += sizeof(this->y_right);
      union {
        float real;
        uint32_t base;
      } u_x1_left;
      u_x1_left.base = 0;
      u_x1_left.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_x1_left.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_x1_left.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_x1_left.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->x1_left = u_x1_left.real;
      offset += sizeof(this->x1_left);
      union {
        float real;
        uint32_t base;
      } u_y1_left;
      u_y1_left.base = 0;
      u_y1_left.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_y1_left.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_y1_left.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_y1_left.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->y1_left = u_y1_left.real;
      offset += sizeof(this->y1_left);
      union {
        float real;
        uint32_t base;
      } u_x1_right;
      u_x1_right.base = 0;
      u_x1_right.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_x1_right.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_x1_right.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_x1_right.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->x1_right = u_x1_right.real;
      offset += sizeof(this->x1_right);
      union {
        float real;
        uint32_t base;
      } u_y1_right;
      u_y1_right.base = 0;
      u_y1_right.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_y1_right.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_y1_right.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_y1_right.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->y1_right = u_y1_right.real;
      offset += sizeof(this->y1_right);
     return offset;
    }

    virtual const char * getType() override { return LR_COORDS; };
    virtual const char * getMD5() override { return "b8d0cb1e6077160f43151089095df12e"; };

  };

  class lr_coords {
    public:
    typedef lr_coordsRequest Request;
    typedef lr_coordsResponse Response;
  };

}
#endif
