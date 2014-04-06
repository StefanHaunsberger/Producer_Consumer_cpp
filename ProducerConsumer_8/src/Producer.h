/*
 * Producer.h
 *
 *  Created on: Apr 1, 2014
 *      Author: Stefan Haunsberger
 */

#ifndef PRODUCER_H_
#define PRODUCER_H_

#include <string>		// string
#include <utility>	// pair
#include <vector>		// vector
#include "Mutex.h"
#include "thread.h"
#include "SharedBoolean.h"
#include "WorkerQueue.h"

using namespace std;

class Producer : public Thread {
public:
	Producer(std::vector<string> & hit_queue, WorkerQueue<pair<string*, int> > & shared_queue, const int thread_id, Mutex & mutex);
	virtual ~Producer();

protected:
	void * run();

private:
	std::vector<string> & m_hit_queue;		// queue with elements to pass on to worker-queue
	WorkerQueue<pair<string*, int> > & m_shared_queue;	// worker queue shared between producer and consumer
	const int m_thread_id;						// thread id
	Mutex & m_mutex;									// mutex for printing
	void printLock1(int i, pair<string*, int> & item) const;

};

#endif /* PRODUCER_H_ */
