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
	int _uid;
	int _reserved;
	string _username;
	string _password;
	int _classid;
	int _role;

public:
	UserBase(int uid, int reserved, 
		string username, string password, 
		int classid, int role) :
		_uid(uid),
		_reserved(reserved),
		_username(username),
		_password(password),
		_classid(classid),
		_role(role) {
	}

	UserBase(){};
	virtual ~UserBase(){};
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
