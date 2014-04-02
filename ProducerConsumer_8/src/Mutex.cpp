/*
   mutex.cpp

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

#include "Mutex.h"

Mutex::Mutex() {
	// TODO Auto-generated constructor stub
	pthread_mutex_init(&m_mutex, NULL);
}

Mutex::~Mutex() {
	// TODO Auto-generated destructor stub
	pthread_mutex_destroy(&m_mutex);
}

// just initialize to defaults
int Mutex::lock() {
	return pthread_mutex_lock(&m_mutex);
}
int Mutex::trylock() {
	return pthread_mutex_lock(&m_mutex);
}
int Mutex::unlock() {
	return pthread_mutex_unlock(&m_mutex);
}

