/*
 * SharedBoolean.cpp
 *
 *  Created on: Mar 31, 2014
 *      Author: Stefan Haunsberger
 */

#include "SharedBoolean.h"

SharedBoolean::SharedBoolean() :
	m_keep_working(true) {
	// TODO Auto-generated constructor stub

}

SharedBoolean::~SharedBoolean() {
	// TODO Auto-generated destructor stub
}

bool SharedBoolean::keepWorking() {
	m_mutex.lock();
	bool res = m_keep_working;
	m_mutex.unlock();
	return res;
}

void SharedBoolean::setKeepWorking(bool keep_working) {
	m_mutex.lock();
	m_keep_working = keep_working;
	m_mutex.unlock();
}
