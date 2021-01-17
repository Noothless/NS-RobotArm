#ifndef _ROS_SERVICE_bd_coords_h
#define _ROS_SERVICE_bd_coords_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace nsra_odrive_interface
{

static const char BD_COORDS[] = "nsra_odrive_interface/bd_coords";

  class bd_coordsRequest : public ros::Msg
  {
    public:
      typedef int16_t _test_type;
      _test_type test;

    bd_coordsRequest():
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

    virtual const char * getType() override { return BD_COORDS; };
    virtual const char * getMD5() override { return "0d3772b8a5da1299e56c0ae15e8afe56"; };

  };

  class bd_coordsResponse : public ros::Msg
  {
    public:
      uint32_t x_coords_length;
      typedef float _x_coords_type;
      _x_coords_type st_x_coords;
      _x_coords_type * x_coords;
      uint32_t y_coords_length;
      typedef float _y_coords_type;
      _y_coords_type st_y_coords;
      _y_coords_type * y_coords;

    bd_coordsResponse():
      x_coords_length(0), st_x_coords(), x_coords(nullptr),
      y_coords_length(0), st_y_coords(), y_coords(nullptr)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->x_coords_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->x_coords_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->x_coords_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->x_coords_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->x_coords_length);
      for( uint32_t i = 0; i < x_coords_length; i++){
      union {
        float real;
        uint32_t base;
      } u_x_coordsi;
      u_x_coordsi.real = this->x_coords[i];
      *(outbuffer + offset + 0) = (u_x_coordsi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_x_coordsi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_x_coordsi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_x_coordsi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->x_coords[i]);
      }
      *(outbuffer + offset + 0) = (this->y_coords_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->y_coords_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->y_coords_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->y_coords_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->y_coords_length);
      for( uint32_t i = 0; i < y_coords_length; i++){
      union {
        float real;
        uint32_t base;
      } u_y_coordsi;
      u_y_coordsi.real = this->y_coords[i];
      *(outbuffer + offset + 0) = (u_y_coordsi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_y_coordsi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_y_coordsi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_y_coordsi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->y_coords[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      uint32_t x_coords_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      x_coords_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      x_coords_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      x_coords_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->x_coords_length);
      if(x_coords_lengthT > x_coords_length)
        this->x_coords = (float*)realloc(this->x_coords, x_coords_lengthT * sizeof(float));
      x_coords_length = x_coords_lengthT;
      for( uint32_t i = 0; i < x_coords_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_x_coords;
      u_st_x_coords.base = 0;
      u_st_x_coords.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_x_coords.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_x_coords.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_x_coords.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_x_coords = u_st_x_coords.real;
      offset += sizeof(this->st_x_coords);
        memcpy( &(this->x_coords[i]), &(this->st_x_coords), sizeof(float));
      }
      uint32_t y_coords_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      y_coords_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      y_coords_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      y_coords_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->y_coords_length);
      if(y_coords_lengthT > y_coords_length)
        this->y_coords = (float*)realloc(this->y_coords, y_coords_lengthT * sizeof(float));
      y_coords_length = y_coords_lengthT;
      for( uint32_t i = 0; i < y_coords_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_y_coords;
      u_st_y_coords.base = 0;
      u_st_y_coords.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_y_coords.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_y_coords.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_y_coords.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_y_coords = u_st_y_coords.real;
      offset += sizeof(this->st_y_coords);
        memcpy( &(this->y_coords[i]), &(this->st_y_coords), sizeof(float));
      }
     return offset;
    }

    virtual const char * getType() override { return BD_COORDS; };
    virtual const char * getMD5() override { return "3e7b502d2903126e58e1db18212b3d0a"; };

  };

  class bd_coords {
    public:
    typedef bd_coordsRequest Request;
    typedef bd_coordsResponse Response;
  };

}
#endif
