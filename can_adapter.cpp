#include <can_adapter.h>

//I hate this more than almost anything else in the entire world. 
//The lock we use to access the CAN bus.
Threads::Mutex* g_p_CAN_lock = new Threads::Mutex();

static can_msg_callback handler = NULL;
static void* callback_ctx = NULL;
static CAN_message_t msg;
static FlexCAN* p_can0 = NULL;

//Sets up the CAN bus for use. Should only be called once.
void initialize_can()
{
  p_can0 = new FlexCAN(g_CAN_BAUD);
  p_can0->begin();
}

//Cleans up the CAN bus
void deinitialize_can()
{
  p_can0->end();
  delete p_can0;
  p_can0 = 0;
}
//Registers a handler to be called to handle CAN messages.
//@param callback The callback to use.
//@param identifier The CAN identifier to use. 
void register_callback(const can_msg_callback callback, void* ctx)
{
  callback_ctx = ctx;
  handler = callback;
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
  while (handler != NULL)
    {
      if (p_can0->available())
	{
	  //Read CAN message and call callback.
	  p_can0->read(msg);
	  handler(&msg, callback_ctx);
	}
      g_p_CAN_lock->unlock();
      yield();//yield.
      //lock, to make the handler pointer threadsafe.
      g_p_CAN_lock->lock();
    }
  //Unlock exiting the loop.
  g_p_CAN_lock->unlock();
}

// Writes the specified message to the CAN bus.
//@param The message to write out on the CAN bus.
void can_write(CAN_message_t msg)
{
  g_p_CAN_lock->lock();
  p_can0->write(msg);
  g_p_CAN_lock->unlock();
}
