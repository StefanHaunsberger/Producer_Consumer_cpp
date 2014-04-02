/*
 * Consumer.h
 *
 *  Created on: Apr 1, 2014
 *      Author: Stefan Haunsberger
 */

#ifndef CONSUMER_H_
#define CONSUMER_H_
#include <string>
#include <utility>
#include "Pool.h"
#include "Mutex.h"
#include "thread.h"
#include "SharedBoolean.h"

using namespace std;

class Consumer : public Thread {

public:
	Consumer(Pool<pair<string*, int> > & queue, const int thread_id, Mutex & mutex);
	virtual ~Consumer();

protected:
	virtual void* run();

private:
	Pool<pair<string*, int> > & m_shared_queue;
	const int m_thread_id;				// thread id
	Mutex & m_printout_mutex;
	void printLock1(int i, pair<string*, int> & item) const;
};

#endif /* CONSUMER_H_ */
