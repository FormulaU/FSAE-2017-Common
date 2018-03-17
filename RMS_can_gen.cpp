#include <RMS_can_gen.h>

void gen_cmd(CAN_message_t* msg,
	     int16_t torque, int16_t speed,
	     bool direction, bool enable,
	     bool discharge, int16_t torque_limit)
{
  msg->id = RMS_BASE_ID + 0x0C0;
  msg->len = 8;

  //Insert the bottom 8 bits of the torque value into byte 0
  msg->buf[0] = torque;
  //Insert the top 8 bits of the torque value into byte 1
  msg->buf[1] = torque >> 8;

  //Insert the bottom 8 bits of the speed value into byte 0
  msg->buf[2] = speed;
  //Insert the top 8 bits of the speed value into byte 1
  msg->buf[3] = speed >> 8;

  //Set the direction byte
  msg->buf[4] = direction;

  //Set the inverter enable byte
  //(Mask just in case, not sure if bool can be an integer value in c++)
  msg->buf[5] = enable & 0x1;

  //Set the inverter bit
  //(Ditto)
  msg->buf[5] = (static_cast<byte>(discharge) << 1) & 0x1;

   //Insert the bottom 8 bits of the speed value into byte 0
  msg->buf[6] = torque_limit;
  //Insert the top 8 bits of the speed value into byte 1
  msg->buf[7] = torque_limit >> 8;
}
