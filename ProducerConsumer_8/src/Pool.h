#ifndef __POOL_H__
#define __POOL_H__

#include "Mutex.h"
#include <stdio.h>
#include <queue>
#include <unistd.h>
#include "CondVar.h"
#include "SharedBoolean.h"

template<class T> class Pool {

private:
	std::queue<T> m_data;
	Mutex m_mutex;
	int m_max_size;
	CondVar m_cond_var_not_empty;
	CondVar m_cond_var_not_full;
	SharedBoolean m_keep_working;				// Signals when producer thread has finished

public:

	Pool(const int max_size = 4) :
			m_max_size(max_size),
			m_cond_var_not_empty(m_mutex),
			m_cond_var_not_full(m_mutex) {

	}

	~Pool() {
		m_mutex.lock();
		while (m_data.size())
			m_data.pop();
		m_mutex.unlock();
	}

	int size() {
		m_mutex.lock();
		int result = m_data.size();
		m_mutex.unlock();
		return result;
	}

	void setKeepWorking(bool keep_working) {
		m_keep_working.setKeepWorking(keep_working);
		if (!keep_working) {
			// Send signal so waiting consumer threads terminate
			m_cond_var_not_empty.broadcast();
		}
	}

	bool keepWorking() {
		return m_keep_working.keepWorking();
	}

	void push(T item) {
		m_mutex.lock();
		while (m_data.size() >= m_max_size) {
			printf("-- -- Producer: max size reached [%i]!\n", m_max_size);
			m_cond_var_not_full.wait();
		}
		m_data.push(item);
		m_cond_var_not_empty.signal();
		m_mutex.unlock();
	}

	T pop() {
		m_mutex.lock();
		// Wait as long as there are no items in the queue and the producer
		// thread is online
		while (m_data.size() <= 0 && m_keep_working.keepWorking()) {
			m_cond_var_not_empty.wait();
		}
		T item;
		if (m_data.size() > 0) {
			item = m_data.front();
			m_data.pop();
			m_cond_var_not_full.signal();
			m_mutex.unlock();
			return item;
		} else {
			// Thread received signal for termination
			// (no items in queue and producer thread has finished)
			m_mutex.unlock();
			return item;
		}
	}

};


#endif
