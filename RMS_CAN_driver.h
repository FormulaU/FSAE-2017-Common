#ifndef RMS_CAN_DRIVER_H
#define RMS_CAN_DRIVER_H

#include <can_adapter.h>

enum message_type {
  temperatures_1 = RMS_CAN_driver::CAN_OFFSET+0x0000,
  temperatures_2 = RMS_CAN_driver::CAN_OFFSET+0x0001,
  temperatures_3 = RMS_CAN_driver::CAN_OFFSET+0x0002,
  analog_in_voltages = RMS_CAN_driver::CAN_OFFSET+0x0003,
  digital_in_stat = RMS_CAN_driver::CAN_OFFSET+0x0004,
  motor_pos_info = RMS_CAN_driver::CAN_OFFSET+0x0005,
  current_info = RMS_CAN_driver::CAN_OFFSET+0x0006,
  voltage_info = RMS_CAN_driver::CAN_OFFSET+0x0007,
  flux_info = RMS_CAN_driver::CAN_OFFSET+0x0008,
  internal_voltages = RMS_CAN_driver::CAN_OFFSET+0x0009,
  internal_states = RMS_CAN_driver::CAN_OFFSET+0x000A,
  fault_codes = RMS_CAN_driver::CAN_OFFSET+0x000B,
  torque_timer_info = RMS_CAN_driver::CAN_OFFSET+0x000C,
  mod_idx_and_flux_weakening = RMS_CAN_driver::CAN_OFFSET+0x000D,
  firmware_info = RMS_CAN_driver::CAN_OFFSET+0x000E,
  diag_data = RMS_CAN_driver::CAN_OFFSET+0x000F
};

class RMS_CAN_driver
{
 public:
  static const uint16_t CAN_OFFSET = 0x00A0;
  //Constructor
  RMS_CAN_driver();

  //CAN callback. Called with a CAN message that was received from the controller
  void handle_msg(const CAN_message_t*); 
 private:
};

#endif //RMS_CAN_DRIVER_H
