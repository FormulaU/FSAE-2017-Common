#include <can_adapter.h>

//I hate this more than almost anything else in the entire world. 
// Baud rate for the CAN adapter.
const uint32_t g_CAN_baud = 250000;
//The lock we use to access the CAN bus.
Threads::Mutex* g_p_CAN_lock = new Threads::Mutex();

static can_msg_callback handler = NULL;
static uint8_t id;
static CAN_message_t msg;
static FlexCAN* p_can0 = NULL;

//Registers a handler to be called to handle CAN messages.
//@param callback The callback to use.
//@param identifier The CAN identifier to use. 
void register_callback(can_msg_callback callback, uint16_t identifier)
{
  handler = callback;
  id = identifier;
}

//Deregisters the callback previously registered, so it doesn't get called when messages are received anymore.
void deregister_callback()
{
  g_p_CAN_lock->lock();
  handler = NULL;
  g_p_CAN_lock->unlock();
}

//Blocking call. Returns when we're no longer listening for CAN messages.
//Starts the CAN listener, so that the callback assigned to register_callback is called when we have a CAN message.
void start_listener()
{
  //Lock entering the listener. Will unlock when we hit yield.
  g_p_CAN_lock->lock();
  if (p_can0 == NULL)
    {
      //Set up the CAN interface.
      p_can0 = new FlexCAN(g_CAN_baud, id);
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
      g_p_CAN_lock->unlock();
      yield();//yield.
      //lock, to make the handler pointer threadsafe.
      g_p_CAN_lock->lock();
    }
  //Unlock exiting the loop.
  g_p_CAN_lock->unlock();
  p_can0->end();
}

