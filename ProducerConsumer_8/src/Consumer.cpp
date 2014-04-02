/*
 * Consumer.cpp
 *
 *  Created on: Apr 1, 2014
 *      Author: Stefan Haunsberger
 */

#include "Consumer.h"
#include <string>
#include <stdio.h>			// printf

using namespace std;

Consumer::Consumer(Pool<pair<string*, int> > & queue, const int thread_id, Mutex & mutex) :
	m_shared_queue(queue),
	m_thread_id(thread_id),
	m_printout_mutex(mutex) {
	// TODO Auto-generated constructor stub

}

Consumer::~Consumer() {
	// TODO Auto-generated destructor stub
}

void * Consumer::run() {

	m_printout_mutex.lock();
	printf("Consumer thread: %i; [longID: %lu] -> started ...\n", m_thread_id, (long unsigned int)self());
	m_printout_mutex.unlock();

//	while (true) {
	for (int i = 0;; i++) {
		m_printout_mutex.lock();
		printf("Consumer thread: %i, loop %i ...\n", m_thread_id, i);
		printf("\t waiting for item...\n");
		m_printout_mutex.unlock();
		pair<string*, int> item = (pair<string*, int> ) m_shared_queue.pop();
		// Make sure that all elements of the queue are processed
		if (m_shared_queue.keepWorking() || item.first) {
			*(item.first) += " AFTER";
			m_printout_mutex.lock();
			printLock1(i, item);
			m_printout_mutex.unlock();
//			sleep(1);
		} else {
			printf("Consumer thread: %i", m_thread_id);
			printf("\t No more items to process --> finish\n");
			break;
		}

	}

	pthread_exit(0);

}

void Consumer::printLock1(int i, pair<string*, int>& item) const {
	printf("Consumer thread: %i, loop %i ...\n", m_thread_id, i);
	printf("\t received item...\n");
	printf("\t item content: [%s ; %i]\n", (*item.first).c_str() , item.second);
}
