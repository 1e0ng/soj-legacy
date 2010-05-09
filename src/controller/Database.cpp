/*
 * =====================================================================================
 *
 *       Filename:  Database.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/06/2010 10:01:25 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include "Database.h"
#include "Log.h"
#include <iostream>
#include <assert.h>
using namespace std;

Database::Database()
{
    bValid = false;
    conn = NULL;
}

Database::~Database()
{
    Close();
}

int Database::Init(const string &host, const string &username, const string &password, const string &schema)
{
    if(mysql_library_init(0, 0, 0))
    {
        cerr<<"mysql_library_init() initialization failed!"<<endl;
        return -1;
    }
    if((conn = mysql_init(NULL)) == NULL)
    {
        cerr<<"mysql_init() failed!"<<endl;
        mysql_library_end();
        return -1;
    }
    if(!mysql_real_connect(conn, host.c_str(), username.c_str(), password.c_str(), schema.c_str(), 0, NULL, 0))
    {
        cerr<<mysql_error(conn)<<endl;
        mysql_close(conn);
        mysql_library_end();
        return -1;
    }
    bValid = true;
    return 0;
}

void Database::Close()
{
    if(bValid && conn)
    {
        mysql_close(conn);
        mysql_library_end();
    }
    conn = NULL;
    bValid = false;
}

int Query(const string &sql, MYSQL_RES **res)
{
    assert(bValid);

    if(mysql_query(conn, sql.c_str()))
    {
        Log("%s(Error no:%d)", mysql_error(conn), mysql_errno(conn));
        return -1;
    }
    MYSQL_RES *p = mysql_store_result(conn);
    if(p)//select statement
    {
        if(res)*res = p;
        return mysql_num_fields(p);
    }
    else//nonselect statement
    {
        if(mysql_field_count(conn) == 0)
            return mysql_affected_rows(mysql);
        else
        {
            Log("%s(Error no:%d)", mysql_error(conn), mysql_errno(conn));
            return -1;
        }
    }

    return -1;
}

/*
int main(int argc, char *argv[])
{
    Database db;
    if(db.Init() < 0)
        cerr<<"Init error!"<<endl;
}
*/
