#ifndef CAN_ADAPTER_H
#define CAN_ADAPTER_H

#include <FlexCAN.h>
#include <TeensyThreads.h>

// Baud rate for the CAN adapter.
extern const uint32_t g_CAN_baud;
//The lock we use to access the CAN bus.
extern Threads::Mutex* g_p_CAN_lock;

//The type we use for our CAN message callback.
typedef void (*can_msg_callback) (CAN_message_t);

//Registers a handler to be called to handle CAN messages.
//@param callback The callback to use.
//@param identifier The CAN identifier to use.
void register_callback(can_msg_callback callback, uint16_t identifier);
//Deregisters the callback previously registered, so it doesn't get called when messages are received anymore.
void deregister_callback();
//Blocking call.
//Starts the CAN listener, so that the callback assigned to register_callback is called when we have a CAN message.
void start_listener();

#endif //CAN_ADAPTER_H
