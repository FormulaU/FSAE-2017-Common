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

void FSAE_log(loglevel level, const char* str)
{
  //Only log if our loglevel is set high enough.
  if (level <= set_level)
    {
      //Print timestamp
      Serial.print("[");
      Serial.print(hour());
      Serial.print("h ");
      Serial.print(minute());
      Serial.print("m ");
      Serial.print(second());
      Serial.print("s] ");
      //Print message.
      Serial.println(str);
    }
}
