/*
 * SharedBoolean.h
 *
 *  Created on: Mar 31, 2014
 *      Author: Stefan Haunsberger
 */

#ifndef SHAREDBOOLEAN_H_
#define SHAREDBOOLEAN_H_
#include "Mutex.h"

class SharedBoolean {

private:
	bool m_keep_working;
	Mutex m_mutex;

public:
	SharedBoolean();
	virtual ~SharedBoolean();
	bool keepWorking();
	void setKeepWorking(bool keep_working);
};

#endif /* SHAREDBOOLEAN_H_ */
