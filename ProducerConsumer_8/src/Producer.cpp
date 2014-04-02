/*
 * Producer.cpp
 *
 *  Created on: Apr 1, 2014
 *      Author: Stefan Haunsberger
 */

#include "Producer.h"
#include <stdio.h>			// printf

Producer::Producer(std::vector<string>& hit_queue, Pool<pair<string*, int> >& shared_queue, const int thread_id, Mutex& mutex) :
	m_hit_queue(hit_queue),
	m_shared_queue(shared_queue),
	m_thread_id(thread_id),
	m_mutex(mutex) {

}

Producer::~Producer() {
	// TODO Auto-generated destructor stub
}

void * Producer::run() {

	m_mutex.lock();
	printf("Producer thread: %i; [longID: %lu] -> started ...\n", m_thread_id, (long unsigned int)self());
	m_mutex.unlock();

	for (int i = 0; i < m_hit_queue.size(); i++) {
		pair<string*, int> item(&m_hit_queue[i], i);
		m_mutex.lock();
		printLock1(i, item);
		m_mutex.unlock();
		m_shared_queue.push(item);
		m_mutex.lock();
		printf("Producer thread: %i, loop %i ...\n", m_thread_id, i);
		printf("\t produced item...\n");
		m_mutex.unlock();
//		sleep(1);

	}

	// Producer threads finish with production
	m_shared_queue.setKeepWorking(false);

	printf("Producer thread %lu; ThreadID: %i - FINISHED ...\n", (long unsigned int)self(), m_thread_id);

	pthread_exit(0);

}

void Producer::printLock1(int i, pair<string*, int>& item) const {
	printf("Producer thread: %i, loop %i ...\n", m_thread_id, i);
	printf("\t prepare item...\n");
	printf("\t item content: [%s ; %i]\n", (*item.first).c_str(), item.second);
	printf("\t... waiting to produce item...\n");
}
