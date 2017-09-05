#include "logger.h"
#include "WProgram.h"
#include <TimeLib.h>

static loglevel set_level;

void initialize_logging(loglevel level)
{
  set_level = level;
  //Set up the USB serial link.
  Serial.begin(9600);
  //Zero the clock.
  setTime(0);
}

//Private helper function. Prints the timestamp for the log message.
void print_timestamp()
{
  //Print timestamp
  Serial.print("[");
  Serial.print(hour());
  Serial.print("h ");
  Serial.print(minute());
  Serial.print("m ");
  Serial.print(second());
  Serial.print("s] ");
}

void FSAE_log(loglevel level, const char* str)
{
  //Only log if our loglevel is set high enough.
  if (level <= set_level)
    {
      print_timestamp();
      //Print message.
      Serial.println(str);
    }
}

void FSAE_log_hex(loglevel level, const uint64_t hex)
{
  //Only log if our loglevel is set high enough.
  if (level <= set_level)
    {
      print_timestamp();
      //Print our hex.
      Serial.print("0x");
      //Arduino's println doesn't natively support 64 bit print values.
      uint32_t hex_upper = static_cast<uint32_t>(hex >> 32);
      uint32_t hex_lower = static_cast<uint32_t>(hex);
      //WARNING: may thrash endian-ness. Check later.
      Serial.print(hex_upper, HEX);
      Serial.println(hex_lower, HEX);
    }
}
