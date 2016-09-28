#ifndef _DEBUGNEW_H_
#define _DEBUGNEW_H_

#include"Tracer.h"
#define new new(__FILE__,__LINE__)

#endif //_DEBUGNEW_H_
