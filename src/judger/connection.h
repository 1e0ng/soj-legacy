#ifndef CONNECTION_H
#define CONNECTION_H

#include "cake.h"
#include <mysql.h>
#include <stdlib.h>
#include <stdio.h>

class Connection{
public:
	int fetchCake(Cake& x);
		//return 0 if succeeded,
		//return 1 if query failed,
		//return 2 if no queueing cake,
		//return 3 if problem doesn't exist.
	int updateCake(const Cake &x);
		//return 0 if succeeded
		//return 1 if failed
	int init();
		//return 0 if succeeded,return 1 if failed
	void close();
private:
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	bool initialed;
};
#endif
