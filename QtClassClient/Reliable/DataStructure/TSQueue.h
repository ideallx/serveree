#ifndef _DATASTRUCTURE_TSQUEUE						// for avoiding multiple including
#define _DATASTRUCTURE_TSQUEUE

#ifndef __STDAFX__
#define WIN32_LEAN_AND_MEAN 
#include <iostream>
#include <string.h>
#include <algorithm>
#include <functional>

#include <iop_thread.h>
using namespace std;
#endif //__STDAFX__

template <class ElemType>
class AbsQueue{
public:
    AbsQueue(){}
    virtual ~AbsQueue(){}

	virtual int isEmpty() const					= 0;
	virtual int isFull() const					= 0;

	virtual void makeEmpty()					= 0;
	virtual bool enQueue(const ElemType &x)		= 0;
	virtual bool deQueue(ElemType& x)			= 0;
	virtual bool head(ElemType& x) const		= 0;
	
private:
    AbsQueue(const AbsQueue &) { }
};

//****************************Queue*******************************//
template <class ElemType> class Queue : public AbsQueue<ElemType> {
private:
	int InitQueueSize;
	int front;
	int rear;
	ElemType *elemArray;

	bool doubleSize();
	void increment(int &x);
	
public:
	// TODO for test
	int curSize;
	Queue();
	Queue(unsigned int queueSize);	
	const Queue &operator = (const Queue &R);			
	~Queue() { delete[] elemArray; }

	void makeEmpty() { front = rear = 0; }
	int isEmpty() const { return front == rear; }
	int isFull() const { return ( rear + 1 ) % curSize == front; }
	int size() const { return (rear - front + curSize) % curSize; }

	bool head(ElemType& x) const;
	bool enQueue(const ElemType &x);
	bool deQueue(ElemType& x);
};

template <class ElemType>
Queue<ElemType>::Queue(){
	InitQueueSize = 1024;
	curSize = InitQueueSize;
	front = 0;
	rear = 0;
	elemArray = new ElemType[InitQueueSize];
}

template <class ElemType>
Queue<ElemType>::Queue(unsigned int queueSize) {
	if (queueSize > 0)
		InitQueueSize = queueSize;
	else
		InitQueueSize = 1024;

	curSize = InitQueueSize;
	front = 0;
	rear = 0;
	elemArray = new ElemType[InitQueueSize];
}

template <class ElemType>
bool Queue<ElemType>::head(ElemType& x) const{
	if (isEmpty()) { 
		return false; 
	} else {
		memcpy(&x, &elemArray[front], sizeof(ElemType));
		return true;
	}
}

template <class ElemType>
bool Queue<ElemType>::enQueue ( const ElemType &x ){
	if (isFull()) {
		if (!doubleSize())		// if out of mem, return
			return false;
	}

	memcpy(&elemArray[rear], &x, sizeof(ElemType));		//elemArray[rear] = x;
	increment(rear);

	return true;
}

template <class ElemType>
void Queue<ElemType>::increment(int &x) {
	if (++x == curSize) x = 0;
}

template <class ElemType>
bool Queue<ElemType>::deQueue(ElemType& x) {
	if (isEmpty()) { 
		return false;
	} else {
		memcpy(&x, &elemArray[front], sizeof(ElemType));
		increment(front);
		return true;
	}
}

template <class ElemType>
bool Queue <ElemType>::doubleSize() {
	//int newSize = 2 * curSize;
	//ElemType *newArray = new ElemType[newSize];

	//int j, k;
	//for (j = 0, k = front; k != rear; j++, increment(k)) 
	//	newArray[j] = elemArray[k];

	//front = 0;
	//rear = j;
	//curSize = newSize;

 //   // cout << "double" << endl;

	//delete[] elemArray;
	//elemArray = newArray;
	int NewSize = 2 * curSize;
	ElemType * old = elemArray;
	elemArray = new ElemType[NewSize];
	if (elemArray == NULL)
		return false;

	int j, k;
	for ( j = 0, k = front; k!= rear; j++, increment(k)) elemArray[j] = old[k];
	front = 0;
	rear = j;
	curSize = NewSize;
	delete [] old;
	return true;
}

template< class ElemType>
const Queue<ElemType>& Queue<ElemType>::operator = ( const Queue<ElemType>&R ){
	if (this == &R) 
		return this;

	delete[] elemArray;
	elemArray = new ElemType[R.curSize];
	curSize = R.curSize;
	int j, k;
	for (j = 0, k = R.front; k < R.rear; j++, increment(k)) 
		elemArray[j] = R.elemArray[k];

	front = 0;
	rear = j;
	return *this;
}

//****************************TSQueue*******************************/
template <class T>
// һ��Ҫ�Ŷ����������Ѫ���ܵĽ�ѵ��������������2�������˰�
// ���ḱ������enqueue�����ݡ�ָ��ֻ����4�ֽڡ��������ն���ĳ��������档
class TSQueue{
protected:
    iop_lock_t          mutex_lock;
	Queue<T>*			m_queue;					// the object of queue.

public:
	TSQueue() {
        iop_lock_init(&mutex_lock);
        iop_lock(&mutex_lock);
		m_queue = new Queue<T>;
		if (m_queue)
			m_queue->makeEmpty();					// clear
        iop_unlock(&mutex_lock);
	}

	TSQueue(unsigned int size) {
        iop_lock_init(&mutex_lock);
        iop_lock(&mutex_lock);
		m_queue = new Queue<T>(size);
		if (m_queue)
			m_queue->makeEmpty();					// clear
        iop_unlock(&mutex_lock);
	}

	virtual ~TSQueue() {
        iop_lock(&mutex_lock);
		m_queue->makeEmpty();
		delete m_queue;
        iop_unlock(&mutex_lock);
        iop_lock_destroy(&mutex_lock);
	}

	bool enQueue(const T& t) {
        iop_lock(&mutex_lock);
		bool rc = m_queue->enQueue(t);					// push
        iop_unlock(&mutex_lock);
		return rc;
	}

	bool deQueue(T& t){
        iop_lock(&mutex_lock);
		bool rc = m_queue->deQueue(t);					// cout << "pop" << endl;
        iop_unlock(&mutex_lock);
		return rc;
	}

	bool isEmpty(void){
        iop_lock(&mutex_lock);
		bool rc = m_queue->isEmpty();
        iop_unlock(&mutex_lock);
		return rc;
	}

	void clean(void) {
        iop_lock(&mutex_lock);
		m_queue->makeEmpty();
        iop_unlock(&mutex_lock);
	}


	bool head(T& t){
        iop_lock(&mutex_lock);
		bool rc = m_queue->head(t);
        iop_unlock(&mutex_lock);
		return rc;
	}

	unsigned int size(void){
        iop_lock(&mutex_lock);
		unsigned int rc = m_queue->size();
        iop_unlock(&mutex_lock);
		return rc;
	}
};
#endif //__TSQUEUE
