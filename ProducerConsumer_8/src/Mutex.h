/*
   mutex.h

   Header for a Pthread mutex class in C++.

   ------------------------------------------

   Copyright © 2013 [Vic Hargrave - http://vichargrave.com]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef MUTEX_H_
#define MUTEX_H_

#include <pthread.h>

class Mutex {
	friend class CondVar;
	pthread_mutex_t m_mutex;

public:
	Mutex();
	virtual ~Mutex();
	int lock();
	int trylock();
	int unlock();
};

#endif /* MUTEX_H_ */
