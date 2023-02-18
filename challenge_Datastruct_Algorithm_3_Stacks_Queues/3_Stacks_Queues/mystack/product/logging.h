#ifndef LOGGING_H
#define LOGGING_H

#include <stdio.h>

/*
 * To enable logging change in the makefile "-DDEBUG=0" to -DDEBUG=1"
 * To disable logging do the reverse
 */


#if DEBUG == 1
  #define DBG_PRINTF(...) fprintf(stdout, __VA_ARGS__)
#else
  #define DBG_PRINTF(...) do {} while(0)
#endif


#endif /* LOGGING_H */
