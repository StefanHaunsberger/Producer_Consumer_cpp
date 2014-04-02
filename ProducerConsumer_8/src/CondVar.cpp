/*
 * CondVar.cpp
 *
 *  Created on: Apr 1, 2014
 *      Author: Stefan Haunsberger
 *
 *
 *   Header for a Pthread condition variable class in C++.
 *
 *   ------------------------------------------
 *
 *  Copyright © 2013 [Vic Hargrave - http://vichargrave.com]
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include "CondVar.h"
#include "Mutex.h"

using namespace std;

CondVar::CondVar(Mutex & mutex) :
		m_mutex(mutex) {
	pthread_cond_init(&m_cond, NULL);
}

CondVar::~CondVar() {
	// TODO Auto-generated destructor stub
}

int CondVar::wait() {
	return  pthread_cond_wait(&m_cond, &(m_mutex.m_mutex));
}

int CondVar::signal() {
	return pthread_cond_signal(&m_cond);
}

int CondVar::broadcast() {
	return pthread_cond_broadcast(&m_cond);
}
