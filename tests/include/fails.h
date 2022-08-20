#ifndef __FAILS_H__
#define __FAILS_H__

#include "debug.h"

#define F_NOTHROW(type) FAIL() << "Exception \"" << type << "\" was not thrown"
#define F_WRONGTHROW(expected, error) FAIL() << "Expected exception \"" << expected << "\", got \"" << error->what() << "\""
#define F_WRONGEXCEPTION(expected) FAIL() << "Expected exception of type " << expected << ", got wrong type"

#define F_THROW(ex) FAIL() << "Failed with exception: " << ex->what()

#endif
