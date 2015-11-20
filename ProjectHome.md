## Summary ##
SOJ means Small Online Judge. It's a system to test the correctness of programs.

## Developer ##
SOJ is developed by Wilbur Ding, [Liang Sun](http://liangsun.org) and Hesey Wang.

## Features ##
SOJ compiles, executes, and test submitted code with pre-constructed data.

SOJ system executes submitted code with restrictions, including time limit, memory limit, security restriction and so on. When completed, the system captures the output of user's program and compares it with the standard output. The system tell the user the result by displaying on the web. The system also supports re-judgement upon mistakes happen.

SOJ also has a rank list.

## Framework ##
Currently, SOJ has 4 parts:

1.Web server: You may choose any web server such as nginx or apache as the front end. Currently the back end is written in PHP.

2.Distributor: This role is for retrieving source codes from DB server and distributes them to Judger. It's written in C++, you need to compile on your machine with g++ on a Linux or Unix platform. Both x86 and x86\_64 are supported.

3.Judger: Once it get source code from Distributor, it compile the source code and run it in a sand box. Then it compares the result with the standard output to decide if the source code is qualified. It then return the result to Distributor, who will store the result into DB server. Note there is only one Distributor, while there may be more than one Judger. Judger is also written in C++.

4.DB server: Currently deployed on MySQL, but the DB server is so simple that it should be OK to deploy on other kinds of DB servers, such as Microsoft SQL Server, Oracle 10g, or DB2.


## TO DO ##
1.An administrator web page will be added to support adding, editing and deleting problems.

2.More languages will be supported, like Python.

## Demo ##
SOJ is currently deployed here:[SOJ](http://smalloj.com).