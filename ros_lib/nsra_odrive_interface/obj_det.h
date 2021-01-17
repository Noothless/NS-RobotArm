#ifndef _ROS_nsra_odrive_interface_obj_det_h
#define _ROS_nsra_odrive_interface_obj_det_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace nsra_odrive_interface
{

  class obj_det : public ros::Msg
  {
    public:
      uint32_t Center_x_length;
      typedef float _Center_x_type;
      _Center_x_type st_Center_x;
      _Center_x_type * Center_x;
      uint32_t Center_y_length;
      typedef float _Center_y_type;
      _Center_y_type st_Center_y;
      _Center_y_type * Center_y;
      uint32_t Top_length;
      typedef float _Top_type;
      _Top_type st_Top;
      _Top_type * Top;
      uint32_t Right_length;
      typedef float _Right_type;
      _Right_type st_Right;
      _Right_type * Right;
      uint32_t Left_length;
      typedef float _Left_type;
      _Left_type st_Left;
      _Left_type * Left;
      uint32_t Bottom_length;
      typedef float _Bottom_type;
      _Bottom_type st_Bottom;
      _Bottom_type * Bottom;

    obj_det():
      Center_x_length(0), st_Center_x(), Center_x(nullptr),
      Center_y_length(0), st_Center_y(), Center_y(nullptr),
      Top_length(0), st_Top(), Top(nullptr),
      Right_length(0), st_Right(), Right(nullptr),
      Left_length(0), st_Left(), Left(nullptr),
      Bottom_length(0), st_Bottom(), Bottom(nullptr)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->Center_x_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->Center_x_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->Center_x_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->Center_x_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Center_x_length);
      for( uint32_t i = 0; i < Center_x_length; i++){
      union {
        float real;
        uint32_t base;
      } u_Center_xi;
      u_Center_xi.real = this->Center_x[i];
      *(outbuffer + offset + 0) = (u_Center_xi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Center_xi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Center_xi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Center_xi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Center_x[i]);
      }
      *(outbuffer + offset + 0) = (this->Center_y_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->Center_y_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->Center_y_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->Center_y_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Center_y_length);
      for( uint32_t i = 0; i < Center_y_length; i++){
      union {
        float real;
        uint32_t base;
      } u_Center_yi;
      u_Center_yi.real = this->Center_y[i];
      *(outbuffer + offset + 0) = (u_Center_yi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Center_yi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Center_yi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Center_yi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Center_y[i]);
      }
      *(outbuffer + offset + 0) = (this->Top_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->Top_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->Top_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->Top_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Top_length);
      for( uint32_t i = 0; i < Top_length; i++){
      union {
        float real;
        uint32_t base;
      } u_Topi;
      u_Topi.real = this->Top[i];
      *(outbuffer + offset + 0) = (u_Topi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Topi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Topi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Topi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Top[i]);
      }
      *(outbuffer + offset + 0) = (this->Right_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->Right_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->Right_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->Right_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Right_length);
      for( uint32_t i = 0; i < Right_length; i++){
      union {
        float real;
        uint32_t base;
      } u_Righti;
      u_Righti.real = this->Right[i];
      *(outbuffer + offset + 0) = (u_Righti.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Righti.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Righti.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Righti.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Right[i]);
      }
      *(outbuffer + offset + 0) = (this->Left_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->Left_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->Left_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->Left_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Left_length);
      for( uint32_t i = 0; i < Left_length; i++){
      union {
        float real;
        uint32_t base;
      } u_Lefti;
      u_Lefti.real = this->Left[i];
      *(outbuffer + offset + 0) = (u_Lefti.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Lefti.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Lefti.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Lefti.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Left[i]);
      }
      *(outbuffer + offset + 0) = (this->Bottom_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->Bottom_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->Bottom_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->Bottom_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Bottom_length);
      for( uint32_t i = 0; i < Bottom_length; i++){
      union {
        float real;
        uint32_t base;
      } u_Bottomi;
      u_Bottomi.real = this->Bottom[i];
      *(outbuffer + offset + 0) = (u_Bottomi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Bottomi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Bottomi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Bottomi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Bottom[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      uint32_t Center_x_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      Center_x_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      Center_x_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      Center_x_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->Center_x_length);
      if(Center_x_lengthT > Center_x_length)
        this->Center_x = (float*)realloc(this->Center_x, Center_x_lengthT * sizeof(float));
      Center_x_length = Center_x_lengthT;
      for( uint32_t i = 0; i < Center_x_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_Center_x;
      u_st_Center_x.base = 0;
      u_st_Center_x.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_Center_x.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_Center_x.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_Center_x.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_Center_x = u_st_Center_x.real;
      offset += sizeof(this->st_Center_x);
        memcpy( &(this->Center_x[i]), &(this->st_Center_x), sizeof(float));
      }
      uint32_t Center_y_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      Center_y_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      Center_y_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      Center_y_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->Center_y_length);
      if(Center_y_lengthT > Center_y_length)
        this->Center_y = (float*)realloc(this->Center_y, Center_y_lengthT * sizeof(float));
      Center_y_length = Center_y_lengthT;
      for( uint32_t i = 0; i < Center_y_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_Center_y;
      u_st_Center_y.base = 0;
      u_st_Center_y.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_Center_y.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_Center_y.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_Center_y.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_Center_y = u_st_Center_y.real;
      offset += sizeof(this->st_Center_y);
        memcpy( &(this->Center_y[i]), &(this->st_Center_y), sizeof(float));
      }
      uint32_t Top_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      Top_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      Top_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      Top_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->Top_length);
      if(Top_lengthT > Top_length)
        this->Top = (float*)realloc(this->Top, Top_lengthT * sizeof(float));
      Top_length = Top_lengthT;
      for( uint32_t i = 0; i < Top_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_Top;
      u_st_Top.base = 0;
      u_st_Top.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_Top.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_Top.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_Top.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_Top = u_st_Top.real;
      offset += sizeof(this->st_Top);
        memcpy( &(this->Top[i]), &(this->st_Top), sizeof(float));
      }
      uint32_t Right_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      Right_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      Right_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      Right_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->Right_length);
      if(Right_lengthT > Right_length)
        this->Right = (float*)realloc(this->Right, Right_lengthT * sizeof(float));
      Right_length = Right_lengthT;
      for( uint32_t i = 0; i < Right_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_Right;
      u_st_Right.base = 0;
      u_st_Right.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_Right.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_Right.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_Right.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_Right = u_st_Right.real;
      offset += sizeof(this->st_Right);
        memcpy( &(this->Right[i]), &(this->st_Right), sizeof(float));
      }
      uint32_t Left_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      Left_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      Left_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      Left_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->Left_length);
      if(Left_lengthT > Left_length)
        this->Left = (float*)realloc(this->Left, Left_lengthT * sizeof(float));
      Left_length = Left_lengthT;
      for( uint32_t i = 0; i < Left_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_Left;
      u_st_Left.base = 0;
      u_st_Left.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_Left.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_Left.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_Left.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_Left = u_st_Left.real;
      offset += sizeof(this->st_Left);
        memcpy( &(this->Left[i]), &(this->st_Left), sizeof(float));
      }
      uint32_t Bottom_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      Bottom_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      Bottom_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      Bottom_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->Bottom_length);
      if(Bottom_lengthT > Bottom_length)
        this->Bottom = (float*)realloc(this->Bottom, Bottom_lengthT * sizeof(float));
      Bottom_length = Bottom_lengthT;
      for( uint32_t i = 0; i < Bottom_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_Bottom;
      u_st_Bottom.base = 0;
      u_st_Bottom.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_Bottom.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_Bottom.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_Bottom.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_Bottom = u_st_Bottom.real;
      offset += sizeof(this->st_Bottom);
        memcpy( &(this->Bottom[i]), &(this->st_Bottom), sizeof(float));
      }
     return offset;
    }

    virtual const char * getType() override { return "nsra_odrive_interface/obj_det"; };
    virtual const char * getMD5() override { return "a60b11e6056b636d26413bf317fce5b0"; };

  };

}
#endif
