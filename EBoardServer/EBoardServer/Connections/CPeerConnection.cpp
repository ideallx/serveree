#include "CPeerConnection.h"

CPeerConnection::CPeerConnection(void) {

}

CPeerConnection::CPeerConnection(CAbsSocket* ps) {
	pSocket->copy(ps);
}

CPeerConnection::~CPeerConnection(void) {

}