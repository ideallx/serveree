/*
 * MsgPool.h
 *
 *  Created on: 2014-6-13
 *      Author: root
 */

#ifndef _DATASTRUCTURE_POOL_H_
#define _DATASTRUCTURE_POOL_H_

#include <iop_thread.h>
#include <semaphore.h>
#include <queue>
#include <iostream>
using namespace std;

template <class ElemType>
class Pool {
protected:
	iop_lock_t lockPool;
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
	iop_lock_init(&lockPool);

	iop_lock(&lockPool);
	list_res = new queue<ElemType>();
	iop_unlock(&lockPool);
}

template <class ElemType>
ElemType Pool<ElemType>::getRes() {
	ElemType ret;
	iop_lock(&lockPool);
	if (list_res->empty()) {
		ret = NULL;
	} else {
		ret = list_res->front();
		list_res->pop();
	}
	iop_unlock(&lockPool);
	return ret;
}

template <class ElemType>
void Pool<ElemType>::releaseRes(ElemType T) {
	iop_lock(&lockPool);
	list_res->push(T);
	iop_unlock(&lockPool);
}

template <class ElemType>
Pool<ElemType>::~Pool() {
	iop_lock(&lockPool);
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
	iop_unlock(&lockPool);

	
	iop_lock_destroy(&lockPool);
}

#endif /* POOL_H_ */
