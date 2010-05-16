/*
 * =====================================================================================
 *
 *       Filename:  Exception.h
 *
 *    Description:  exception base
 *
 *        Version:  1.0
 *        Created:  05/16/2010 01:01:42 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef EXCEPTION_H
#define EXCEPTION_H

class OJException
{
public:
    OJException()throw(){}
    ~OJException()throw();

    virtual const char *What()const throw();
};

#endif
