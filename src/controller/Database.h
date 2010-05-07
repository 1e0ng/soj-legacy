/*
 * =====================================================================================
 *
 *       Filename:  Database.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/06/2010 09:52:27 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef DATABASE_H
#define DATABASE_H
#include <mysql.h>
#include <string>

class Database
{
public:
    Database();
    ~Database();

    int Init();
    void Close();
    int Query(const std::string &sql, MYSQL_RES **res);
private:
    MYSQL *conn;
    bool bValid;
};

#endif

