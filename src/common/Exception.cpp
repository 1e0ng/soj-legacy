/*
 * =====================================================================================
 *
 *       Filename:  Exception.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/16/2010 01:03:19 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wilbur Ding (), powerx1202@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include "Exception.h"

OJException::~OJException()throw()
{

}

const char *OJException::What()const throw()
{
    return "exception";
}
