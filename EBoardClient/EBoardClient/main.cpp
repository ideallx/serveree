#include <iostream>
#include <iop_util.h>
#include "Server\DWSClient.h"
#include "DataUnit\UserBase.h"

using namespace std;


int main(int argc, char* argv[]) {
	SOCK_STARTUP();
	
	DWSClient* s1 = new DWSClient();
	unsigned char name[20] = "abcdefg";
	unsigned char pswd[20] = "hijklmn";
	UserBase* user = new UserBase();
	user->_classid = 10000;
	user->_reserved = 1;
	user->_role = RoleTeacher;
	user->_uid = 100;
	
	memcpy(user->_password, pswd, 20);
	memcpy(user->_username, name, 20);

	s1->setUser(*user);
	s1->Start(2222);
	
	DWSClient* s2 = new DWSClient();
	user->_uid = 101;
	s2->setUser(*user);
	s2->Start(2222);

	DWSClient* s3 = new DWSClient();
	user->_uid = 102;
	s3->setUser(*user);
	s3->Start(2222);

	DWSClient* s4 = new DWSClient();
	user->_uid = 103;
	s4->setUser(*user);
	s4->Start(2222);

	DWSClient* s5 = new DWSClient();
	user->_uid = 104;
	s5->setUser(*user);
	s5->Start(2222);

	DWSClient* s6 = new DWSClient();
	user->_uid = 105;
	s6->setUser(*user);
	s6->Start(2222);

	DWSClient* s7 = new DWSClient();
	user->_uid = 106;
	s7->setUser(*user);
	s7->Start(2222);

	while (true) {};

	SOCK_CLEANUP();
	return 0;

}