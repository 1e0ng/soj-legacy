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
    static Database &GetInstance()
    {
        static Database instance;
        return instance;
    }

    int Init(const std::string &host, const std::string &username, const std::string &password, const std::string &schema);
    void Close();
    int Query(const std::string &sql, MYSQL_RES **res);
private:
    Database();
    ~Database();
    Database(const Database &);
    Database &operator=(const Database &);

    MYSQL *conn;
    bool bValid;
};

#endif

