/*
 * UserBase.h
 *
 *  Created on: 2014-6-18
 *      Author: root
 */

#ifndef USERBASE_H_
#define USERBASE_H_

#include <string>
#include <iostream>

#include "../Stdafx.h"

using namespace std;

struct UserBase {
	TS_UINT64 _uid;
	TS_UINT64 _reserved;
	TS_UINT64 _classid;
	unsigned char _role;
	unsigned char _username[20];
	unsigned char _password[20];
};


static ostream& operator<< (ostream& out, const UserBase& T) {
	out << T._username << " " 
		<< T._password << " " 
		<< T._uid << " " 
		<< T._classid << " " 
		<< T._role << endl;
	return out;
}

#endif /* USERBASE_H_ */
