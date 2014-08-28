/*
 * MsgPool.h
 *
 *  Created on: 2014-6-13
 *      Author: root
 */

#ifndef _DATASTRUCTURE_POOL_H_
#define _DATASTRUCTURE_POOL_H_

#include <semaphore.h>
#include <queue>
#include <iostream>
using namespace std;

template <class ElemType>
class Pool {
protected:
	sem_t sem_pool;
	queue<ElemType>* list_res;

public:
	Pool();
	virtual ~Pool();

	ElemType getRes();
	void releaseRes(ElemType T);
};

template <class ElemType>
Pool<ElemType>::Pool() {
	// TODO Auto-generated constructor stub
	sem_init((sem_t*) &sem_pool, 0, 1);

	sem_wait((sem_t*) &sem_pool);
	list_res = new queue<ElemType>();
	sem_post((sem_t*) &sem_pool);
}

template <class ElemType>
ElemType Pool<ElemType>::getRes() {
	ElemType ret;
	sem_wait((sem_t*) &sem_pool);
	if (list_res->empty()) {
		ret = NULL;
	} else {
		ret = list_res->front();
		list_res->pop();
	}
	sem_post((sem_t*) &sem_pool);
	return ret;
}

template <class ElemType>
void Pool<ElemType>::releaseRes(ElemType T) {
	sem_wait((sem_t*) &sem_pool);
	list_res->push(T);
	sem_post((sem_t*) &sem_pool);
}

template <class ElemType>
Pool<ElemType>::~Pool() {
	sem_wait((sem_t*) &sem_pool);
	cout << "delete pool" << endl;
	cout << list_res->size() << endl;
	if (NULL != list_res) {
		while (!list_res->empty()) {
			ElemType T = list_res->front();
			list_res->pop();
			if (T != NULL) {
				delete T;
				T = NULL;
			}
		}
	}
	delete list_res;
	list_res = NULL;
	sem_post((sem_t*) &sem_pool);
}

#endif /* POOL_H_ */
