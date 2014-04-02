/*
 * CondVar.h
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

#ifndef CONDVAR_H_
#define CONDVAR_H_
#include "Mutex.h"
#include "thread.h"

class CondVar {

pthread_cond_t m_cond;
Mutex & m_mutex;

public:
	CondVar(Mutex & mutex);
	virtual ~CondVar();

	int wait();
	int signal();
	int broadcast();

};

#endif /* CONDVAR_H_ */
