
//Describes logging levels.
//FATAL: An unrecoverable error state. Program will halt.
//ERROR: A potentially recoverable error.
//WARN: Not an error, but has the potential to cause problems
//INFO: Significant events that may give insight into the programs current state.
//DEBUG: All available information. Used for debugging.
typedef enum {FATAL = 0, ERROR = 1, WARN = 2, INFO = 3, DEBUG = 4} loglevel;

//Initializes logging at the specified loglevel.
void initialize_logging(loglevel level);

//Logs the string with the specified length at the specified loglevel.
void FSAE_log(loglevel level, const char* str);

