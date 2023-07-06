#ifndef __LOG_H_
#define __LOG_H_

//#define LOG_ENABLE

#ifdef LOG_ENABLE
/* Your implementation of Transmit Function */
#include "stdio.h"       

#define LOG_INFO(...)    		    printf(__VA_ARGS__)
#define LOG(condition,message)   	if (condition) { LOG_INFO("%s", message); } else { LOG_INFO("FAIL: %s", message); }

#else
#define LOG_INFO(...)
#define LOG(...)
#endif
#endif	/* __LOG_H_ */
