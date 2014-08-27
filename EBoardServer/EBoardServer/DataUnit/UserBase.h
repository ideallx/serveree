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

class UserBase {
public:
	TS_UINT64 _uid;
	TS_UINT64 _reserved;
	string _username;
	string _password;
	TS_UINT64 _classid;
	unsigned char _role;

public:
	UserBase(TS_UINT64 uid, TS_UINT64 reserved, 
		string username, string password, 
		TS_UINT64 classid, enum RoleOfClass role) :
		_uid(uid),
		_reserved(reserved),
		_username(username),
		_password(password),
		_classid(classid),
		_role(role) {
	}
	UserBase() {};
	virtual ~UserBase() {};
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
