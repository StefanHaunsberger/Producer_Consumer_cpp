//============================================================================
// Name        : ProducerConsumer_5.cpp
// Author      : Stefan Haunsberger
// Version     :
// Copyright   : Your copyright notice
// Description : Producer/Consumer Example in C++
//								Inclusive thread termination
//============================================================================

#include <iostream>		// cout
#include <string>			// string
#include <utility>		// pair
#include <vector>			// vector
#include "Consumer.h"
#include "Mutex.h"
#include "Producer.h"
#include <stdio.h>
#include "WorkerQueue.h"

using namespace std;

int main() {
	cout << "Producer-Consumer" << endl; // prints Producer-Consumer

	int num_items = 10;
	int num_threads = 2;

	vector<string> hit_queue;
	WorkerQueue<pair<string*, int> > shared_queue;
	Mutex mutex;

	// Set value to signal NULL
//	pair<string*, int> null_element(NULL, 0);
	shared_queue.Null(pair<string*, int> (NULL, 999));

	////////////////////////////////////////////////////////////////////////
	// Initialize hit items
	printf("Initialize hit-vector\n");
	for (int i = 0; i < num_items; i++) {
		hit_queue.push_back("Producer item before manipulation");
		printf("\t %i: queue content: %s\n", i, hit_queue[i].c_str());
	}
	hit_queue.push_back("LAST Producer item before manipulation");
	printf("\t %i: queue content: %s\n", (int)(hit_queue.size()-1), hit_queue.at(hit_queue.size()-1).c_str());

	cout << "\n" << endl;

	////////////////////////////////////////////////////////////////////////
	// Initialize consumer threads
	vector<Consumer*> consumer_threads;
	for (int i = 0; i < num_threads; i++) {
		consumer_threads.push_back(new Consumer(shared_queue, i, mutex));
	}
	// Initialize producer thread
	Producer * producer = new Producer(hit_queue, shared_queue, 1, mutex);

	////////////////////////////////////////////////////////////////////////
	// Start threads
	for (int i = 0; i < num_threads; i++) {
		consumer_threads[i]->start();
	}
	producer->start();

	////////////////////////////////////////////////////////////////////////
	// Wait for all threads to be finished
	for (int i = 0; i < num_threads; i++) {
		consumer_threads[i]->join();
	}
	producer->join();

	printf("\n===================================================\n");
	printf("RESULTS:\n-------------\n");
	for (int i = 0; i < (signed int) hit_queue.size(); i++) {
		string item = hit_queue.at(i);
		printf("%i: queue content: [%s]\n", i, item.c_str());
	}

	cout << "ALL threads finished" << endl;

	return 0;
}
