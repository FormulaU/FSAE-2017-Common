#include <can_adapter.h>

static can_msg_callback handler = NULL;
static uint8_t id;
static CAN_message_t msg;
static FlexCAN* p_can0 = NULL;
//Registers a handler to be called to handle CAN messages.
//@param callback The callback to use.
//@param identifier The CAN identifier to use.
void register_callback(can_msg_callback callback, uint8_t identifier)
{
  handler = callback;
  id = identifier;
}

//Deregisters the callback previously registered, so it doesn't get called when messages are received anymore.
void deregister_callback()
{
  CAN_lock.lock();
  handler = NULL;
  CAN_lock.unlock();
}

//Blocking call. Returns when we're no longer listening for CAN messages.
//Starts the CAN listener, so that the callback assigned to register_callback is called when we have a CAN message.
void start_listener()
{
  //Lock entering the listener. Will unlock when we hit yield.
  CAN_lock.lock();
  if (p_can0 == NULL)
    {
      //Set up the CAN interface.
      p_can0 = new FlexCAN(CAN_baud, id);
    }
  p_can0->begin();
  while (handler != NULL)
    {
      if (p_can0->available())
	{
	  //Read CAN message and call callback.
	  p_can0->read(msg);
	  handler(msg);
	}
      CAN_lock.unlock();
      yield();//yield.
      //lock, to make the handler pointer threadsafe.
      CAN_lock.lock();
    }
  //Unlock exiting the loop.
  CAN_lock.unlock();
  p_can0->end();
}
