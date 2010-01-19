-- MySQL dump 10.13  Distrib 5.1.41, for redhat-linux-gnu (i386)
--
-- Host: localhost    Database: soj
-- ------------------------------------------------------
-- Server version	5.1.41

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `problem`
--

DROP TABLE IF EXISTS `problem`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `problem` (
  `pid` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `problemName` varchar(50) NOT NULL,
  `accepted` int(10) unsigned DEFAULT '0',
  `submitted` int(10) unsigned DEFAULT '0',
  `discription` blob,
  `input` blob,
  `output` blob,
  `inputCase` blob,
  `outputCase` blob,
  `timeLimit` int(10) unsigned NOT NULL DEFAULT '1000',
  `memoryLimit` int(10) unsigned NOT NULL DEFAULT '64000',
  PRIMARY KEY (`pid`)
) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `problem`
--

LOCK TABLES `problem` WRITE;
/*!40000 ALTER TABLE `problem` DISABLE KEYS */;
INSERT INTO `problem` VALUES (1,'A+B Problem',61,153,'There are pairs of integers. Ouput the sum of each pair of integers.','Pairs of integers.','The sum of each pair of integers line by line.','1 2\n89323 1\n','3\n89324\n',1000,64000);
/*!40000 ALTER TABLE `problem` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `status`
--

DROP TABLE IF EXISTS `status`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `status` (
  `rid` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `pid` int(10) unsigned NOT NULL,
  `uid` int(10) unsigned NOT NULL,
  `judgeStatus` tinyint(3) unsigned NOT NULL DEFAULT '1',
  `language` tinyint(3) unsigned NOT NULL,
  `rtime` int(10) unsigned DEFAULT NULL,
  `rmemory` int(10) unsigned DEFAULT NULL,
  `submitTime` datetime NOT NULL,
  `sourceCode` blob,
  PRIMARY KEY (`rid`)
) ENGINE=MyISAM AUTO_INCREMENT=154 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `status`
--

LOCK TABLES `status` WRITE;
/*!40000 ALTER TABLE `status` DISABLE KEYS */;
INSERT INTO `status` VALUES (16,1,13,4,1,1,608,'2010-01-13 18:24:51','#include <iostream>  \r\nusing namespace std; \r\nint main()  \r\n{  \r\n   int a=1, b=3;  \r\n   cout<<a+b;  \r\n}   \r\n'),(15,1,13,7,1,NULL,NULL,'2010-01-13 18:23:49','#include <iostream.h> \r\nint main() \r\n{ \r\n   int a=1, b=3; \r\n   cout<<a+b; \r\n} \r\n'),(13,1,12,7,1,NULL,NULL,'2010-01-13 17:56:03','#include <iostream>\r\n\r\nvoid main()\r\n{\r\n int a,b;\r\ncin>>a>>b;\r\ncout<<a+b;\r\n}'),(14,1,13,7,1,NULL,NULL,'2010-01-13 18:17:37','include <iostream.h>\r\nint main()\r\n{\r\n   int a=1, b=3;\r\n   cout<<a+b;\r\n}'),(12,1,3,3,1,4,620,'2010-01-13 16:31:53','#include <iostream>\r\nusing namespace std;\r\nint main(){\r\nint a,b;\r\nwhile(cin>>a>>b)cout<<a+b<<endl;\r\nreturn 0;\r\n}'),(11,1,3,7,1,NULL,NULL,'2010-01-13 16:30:10','＃include <iostream>\r\nusing namespace std;\r\nint main(){\r\nint a,b;\r\nwhile(cin>>a>>b)cout<<a+b<<endl;\r\nreturn 0;\r\n}'),(10,1,3,3,2,1,460,'2010-01-13 16:04:57','#include <stdio.h>\r\nint main(){\r\nint a,b;\r\nwhile(scanf(\"%d%d\",&a,&b)!=EOF){\r\nprintf(\"%d\\n\",a+b);\r\n}\r\nreturn 0;\r\n}'),(9,1,3,3,1,1,624,'2010-01-12 20:33:09','#include <iostream>\r\nusing namespace std;\r\nint main(){\r\nint a,b;\r\nwhile(cin>>a>>b){\r\n cout<<a+b<<endl;\r\n}\r\nreturn 0;\r\n}'),(17,1,13,3,1,2,620,'2010-01-13 18:29:15','#include <iostream>   \r\nusing namespace std;  \r\nint main()   \r\n{   \r\n   int a,b;\r\n \r\n   while(cin>>a>>b)  \r\n\r\n   cout<<a+b<<endl; \r\n   return 0;  \r\n}     \r\n'),(18,1,13,7,1,NULL,NULL,'2010-01-13 18:29:51','#include <iostream>    \r\n\r\nint main()    \r\n{    \r\n   int a,b; \r\n  \r\n   while(cin>>a>>b)   \r\n\r\n   cout<<a+b<<endl;  \r\n   return 0;   \r\n}      \r\n \r\n\r\n'),(19,1,13,7,1,NULL,NULL,'2010-01-13 18:30:04','#include <iostream.h>    \r\nusing namespace std;   \r\nint main()    \r\n{    \r\n   int a,b; \r\n  \r\n   while(cin>>a>>b)   \r\n\r\n   cout<<a+b<<endl;  \r\n   return 0;   \r\n}      \r\n \r\n\r\n'),(20,1,16,7,1,NULL,NULL,'2010-01-15 13:11:37','#include <iostream>\r\nusing namespace std;\r\nint main(){\r\nprintf(\"HelloWorld\");\r\nreturn 0;\r\n}   '),(21,1,3,7,2,NULL,NULL,'2010-01-15 13:43:05','#inlcude <stdio.h>\r\nint main(){\r\nint a,b;\r\nwhile(scanf(\"%d%d\",&a,&b)!=EOF){printf(\"%d\\n\",a+b);}\r\nreturn 0;\r\n}'),(22,1,3,3,2,1,464,'2010-01-15 13:43:41','#include <stdio.h>\r\nint main(){\r\nint a,b;\r\nwhile(scanf(\"%d%d\",&a,&b)!=EOF){printf(\"%d\\n\",a+b);}\r\nreturn 0;\r\n}'),(23,1,8,4,1,2,624,'2010-01-15 14:05:21','#include<iostream>\r\nusing namespace std;\r\n\r\nint main()\r\n{\r\nint a,b;\r\n\r\ncin>>a>>b;\r\ncout<<a+b<<endl;\r\n\r\nreturn 0;\r\n\r\n}\r\n'),(24,1,8,3,1,1,620,'2010-01-15 14:06:09','#include<iostream> \r\nusing namespace std; \r\n\r\nint main() \r\n{ \r\nint a,b; \r\n\r\nwhile(cin>>a>>b) \r\ncout<<a+b<<endl; \r\n\r\nreturn 0; \r\n\r\n} \r\n'),(25,1,3,3,2,1,460,'2010-01-15 16:46:55','#include <stdio.h>\r\nint main(){\r\nint a,b;\r\nwhile(scanf(\"%d%d\",&a,&b)!=EOF){printf(\"%d\\n\",a+b);}\r\nreturn 0;\r\n}'),(26,1,3,3,2,1,464,'2010-01-15 16:53:44','#include <stdio.h>\r\nint main(){\r\nint a,b;\r\nwhile(scanf(\"%d%d\",&a,&b)!=EOF){printf(\"%d\\n\",a+b);}\r\nreturn 0;\r\n}'),(27,1,3,3,2,0,464,'2010-01-15 16:57:22','#include <stdio.h>\r\nint main(){\r\nint a,b;\r\nwhile(scanf(\"%d%d\",&a,&b)!=EOF){printf(\"%d\\n\",a+b);}\r\nreturn 0;\r\n}'),(28,1,3,4,1,1,572,'2010-01-15 17:11:40','#include <iostream>\r\nint main(){return 0;}'),(29,1,3,7,2,NULL,NULL,'2010-01-15 17:12:08','#include <cstdio.h>\r\nint main(){return 0;}'),(30,1,3,4,2,0,384,'2010-01-15 17:12:37','#include <stdio.h>\r\nint main(){return 0;}'),(31,1,3,4,2,1,384,'2010-01-15 17:13:00','#include <stdio.h>\r\nint main(){return 0;}'),(32,1,3,3,1,1,620,'2010-01-15 17:53:28','#include <iostream>\r\nusing namespace std;\r\nint main(){\r\nint a,b;\r\nwhile(cin>>a>>b)cout<<a+b<<endl;\r\nreturn 0;\r\n}'),(33,1,3,5,1,NULL,NULL,'2010-01-15 17:54:13','#include <iostream>\r\nusing namespace std;\r\nint main(){\r\nwhile(1);\r\nreturn 0;\r\n}'),(34,1,3,3,1,2,656,'2010-01-15 22:09:36','#include <iostream>\r\n#include <cstdio>\r\nint main(){\r\nint a,b;\r\nwhile(scanf(\"%d%d\",&a,&b)!=EOF){\r\nprintf(\"%d\\n\",a+b);\r\n}\r\n}'),(35,1,3,3,1,2,656,'2010-01-15 22:10:05','#include <iostream>\r\n#include <cstdio>\r\nusing namespace std;\r\nint main(){\r\nint a,b;\r\nwhile(scanf(\"%d%d\",&a,&b)!=EOF){\r\nprintf(\"%d\\n\",a+b);\r\n}\r\n}'),(36,1,3,3,1,0,660,'2010-01-15 22:10:46','#include <iostream>\r\n#include <cstdio>\r\nusing namespace std;\r\nint main(){\r\nint a,b;\r\nwhile(scanf(\"%d%d\",&a,&b)!=EOF){\r\nprintf(\"%d\\n\",a+b);\r\n}\r\nreturn 0;\r\n}'),(37,1,3,3,1,2,624,'2010-01-15 22:11:31','#include <iostream>\r\nusing namespace std;\r\nint main(){\r\nint a,b;\r\nwhile(cin>>a>>b)cout<<a+b<<endl;\r\nreturn 0;\r\n}'),(38,1,3,3,1,1,624,'2010-01-15 22:12:34','#include <iostream>\r\nusing namespace std;\r\nint main(){\r\nint a,b;\r\nwhile(cin>>a>>b)cout<<a+b<<endl;\r\nreturn 0;\r\n}'),(39,1,3,3,1,0,620,'2010-01-15 23:10:34','#include <iostream>\r\nusing namespace std;\r\nint main(){\r\nint a,b;\r\nwhile(cin>>a>>b)cout<<a+b<<endl;\r\nreturn 0;\r\n}'),(40,1,3,3,1,2,620,'2010-01-15 23:30:51','#include <iostream>\r\nusing namespace std;\r\nint main(){\r\nint a,b;\r\nwhile(cin>>a>>b)cout<<a+b<<endl;\r\nreturn 0;\r\n}'),(41,1,3,3,1,1,624,'2010-01-15 23:34:35','#include <iostream>\r\nusing namespace std;\r\nint main(){\r\nint a,b;\r\nwhile(cin>>a>>b)cout<<a+b<<endl;\r\nreturn 0;\r\n}'),(42,1,3,3,2,0,460,'2010-01-15 23:35:24','#include <stdio.h>\r\nint main(){\r\nint a,b;\r\nwhile(scanf(\"%d%d\",&a,&b)!=EOF){printf(\"%d\\n\",a+b);}\r\nreturn 0;\r\n}'),(43,1,3,7,2,NULL,NULL,'2010-01-15 23:53:12','#include <iostream>\r\nusing namespace std;\r\nint main(){\r\nint a,b;\r\nwhile(cin>>a>>b)cout<<a+b<<endl;\r\nreturn 0;\r\n}'),(44,1,3,3,1,0,620,'2010-01-15 23:53:33','#include <iostream>\r\nusing namespace std;\r\nint main(){\r\nint a,b;\r\nwhile(cin>>a>>b)cout<<a+b<<endl;\r\nreturn 0;\r\n}'),(45,1,3,4,1,1,408,'2010-01-15 23:54:27','#include <stdio.h>\r\nint main(){return 0;}'),(46,1,3,4,1,2,404,'2010-01-16 00:00:30','#include <stdio.h>\r\nint main(){return 0;}'),(47,1,3,4,2,0,384,'2010-01-16 00:00:55','#include <stdio.h>\r\nint main(){return 0;}'),(48,1,3,3,1,2,620,'2010-01-16 00:01:24','#include <iostream>\r\nusing namespace std;\r\nint main(){\r\nint a,b;\r\nwhile(cin>>a>>b)cout<<a+b<<endl;\r\nreturn 0;\r\n}'),(49,1,3,3,1,2,620,'2010-01-16 00:02:22','#include <iostream>\r\nusing namespace std;\r\nint main(){\r\nint a,b;\r\nint i,j;\r\nfor(i=0;i<10000;i++){\r\nfor(j=0;j<10000;j++){\r\na+=b;\r\n}\r\n}\r\nwhile(cin>>a>>b)cout<<a+b<<endl;\r\nreturn 0;\r\n}'),(50,1,3,3,1,0,620,'2010-01-16 00:08:19','#include <iostream>\r\nusing namespace std;\r\nint main(){\r\nint a,b;\r\nint i,j;\r\nfor(i=0;i<40000;i++){\r\nfor(j=0;j<10000;j++){\r\na+=b;\r\n}\r\n}\r\nwhile(cin>>a>>b)cout<<a+b<<endl;\r\nreturn 0;\r\n}'),(51,1,3,3,1,1,620,'2010-01-16 00:25:02','#include <iostream>\r\nusing namespace std;\r\nint main(){\r\nint a,b;\r\nint i,j;\r\nfor(i=0;i<20000;i++){\r\nfor(j=0;j<10000;j++){\r\na+=b;\r\n}\r\n}\r\nwhile(cin>>a>>b)cout<<a+b<<endl;\r\nreturn 0;\r\n}'),(52,1,3,3,1,1,620,'2010-01-16 00:25:37','#include <iostream>\r\nusing namespace std;\r\nint main(){\r\nint a,b;\r\nint i,j;\r\nfor(i=0;i<50000;i++){\r\nfor(j=0;j<10000;j++){\r\na+=b;\r\n}\r\n}\r\nwhile(cin>>a>>b)cout<<a+b<<endl;\r\nreturn 0;\r\n}'),(53,1,3,3,1,2,620,'2010-01-16 00:25:52','#include <iostream>\r\nusing namespace std;\r\nint main(){\r\nint a,b;\r\nint i,j;\r\nfor(i=0;i<47000;i++){\r\nfor(j=0;j<10000;j++){\r\na+=b;\r\n}\r\n}\r\nwhile(cin>>a>>b)cout<<a+b<<endl;\r\nreturn 0;\r\n}'),(54,1,3,3,1,2,620,'2010-01-16 00:26:08','#include <iostream>\r\nusing namespace std;\r\nint main(){\r\nint a,b;\r\nint i,j;\r\nfor(i=0;i<44000;i++){\r\nfor(j=0;j<10000;j++){\r\na+=b;\r\n}\r\n}\r\nwhile(cin>>a>>b)cout<<a+b<<endl;\r\nreturn 0;\r\n}'),(55,1,3,3,1,2,620,'2010-01-16 00:26:21','#include <iostream>\r\nusing namespace std;\r\nint main(){\r\nint a,b;\r\nint i,j;\r\nfor(i=0;i<40000;i++){\r\nfor(j=0;j<10000;j++){\r\na+=b;\r\n}\r\n}\r\nwhile(cin>>a>>b)cout<<a+b<<endl;\r\nreturn 0;\r\n}'),(56,1,3,3,1,2,620,'2010-01-16 00:26:42','#include <iostream>\r\nusing namespace std;\r\nint main(){\r\nint a,b;\r\nint i,j;\r\n\r\nwhile(cin>>a>>b)cout<<a+b<<endl;\r\nreturn 0;\r\n}'),(57,1,3,3,1,1,620,'2010-01-16 00:27:06','#include <iostream>\r\nusing namespace std;\r\nint main(){\r\nint a,b;\r\nint i,j;\r\nfor(i=0;i<30000;i++){\r\nfor(j=0;j<10000;j++){\r\na+=b;\r\n}\r\n}\r\nwhile(cin>>a>>b)cout<<a+b<<endl;\r\nreturn 0;\r\n}'),(58,1,3,3,1,1,616,'2010-01-16 00:27:26','#include <iostream>\r\nusing namespace std;\r\nint main(){\r\nint a,b;\r\nint i,j;\r\nfor(i=0;i<20000;i++){\r\nfor(j=0;j<10000;j++){\r\na+=b;\r\n}\r\n}\r\nwhile(cin>>a>>b)cout<<a+b<<endl;\r\nreturn 0;\r\n}'),(59,1,3,3,1,1,624,'2010-01-16 11:37:38','#include <iostream>\r\nusing namespace std;\r\nint c[1000][1000];\r\nint main(){\r\nint a,b;\r\nint i,j;\r\nfor(i=0;i<20000;i++){\r\nfor(j=0;j<10000;j++){\r\na+=b;\r\n}\r\n}\r\nwhile(cin>>a>>b)cout<<a+b<<endl;\r\nreturn 0;\r\n}'),(60,1,3,3,1,1,620,'2010-01-16 11:38:31','#include <iostream>\r\nusing namespace std;\r\nint main(){\r\nint a,b;\r\nint i,j;\r\nint c[1000][1000];\r\nfor(i=0;i<20000;i++){\r\nfor(j=0;j<10000;j++){\r\na+=b;\r\nc[i%1000][j%1000]=a+b;\r\n}\r\n}\r\nwhile(cin>>a>>b)cout<<a+b<<endl;\r\nreturn 0;\r\n}'),(61,1,3,3,1,2,620,'2010-01-16 11:39:06','#include <iostream>\r\nusing namespace std;\r\nint main(){\r\nint a,b;\r\nint i,j;\r\nint c[1000][1000];\r\nfor(i=0;i<10000;i++){\r\nfor(j=0;j<8000;j++){\r\na+=b;\r\nc[i%1000][j%1000]=a+b;\r\n}\r\n}\r\nwhile(cin>>a>>b)cout<<a+b<<endl;\r\nreturn 0;\r\n}'),(62,1,3,3,1,1,624,'2010-01-16 11:39:39','#include <iostream>\r\nusing namespace std;\r\nint main(){\r\nint a,b;\r\nint i,j;\r\nint c[1000][1000];\r\nfor(i=0;i<3000;i++){\r\nfor(j=0;j<8000;j++){\r\na+=b;\r\nc[i%1000][j%1000]=a+b;\r\n}\r\n}\r\nwhile(cin>>a>>b)cout<<a+b<<endl;\r\nreturn 0;\r\n}'),(63,1,3,3,1,2,620,'2010-01-16 11:56:21','#include <iostream>\r\nusing namespace std;\r\nint main(){\r\nint a,b;\r\nint i,j;\r\nint c[2000][2000];\r\nfor(i=0;i<3000;i++){\r\nfor(j=0;j<8000;j++){\r\na+=b;\r\nc[i%2000][j%2000]=a+b;\r\n}\r\n}\r\nwhile(cin>>a>>b)cout<<a+b<<endl;\r\nreturn 0;\r\n}'),(64,1,3,3,1,0,620,'2010-01-16 11:58:04','#include <iostream>\r\nusing namespace std;\r\nint main(){\r\nint a,b;\r\nint i,j;\r\nint c[2000][1000];\r\nfor(i=0;i<3000;i++){\r\nfor(j=0;j<8000;j++){\r\na+=b;\r\nc[i%2000][j%1000]=a+b;\r\n}\r\n}\r\nwhile(cin>>a>>b)cout<<a+b<<endl;\r\nreturn 0;\r\n}'),(65,1,3,5,1,NULL,NULL,'2010-01-16 12:09:33','#include <iostream>\r\nusing namespace std;\r\nint main(){\r\nint * a;\r\nwhile(1)a=new int(10);\r\nreturn 0;\r\n}'),(66,1,3,5,1,NULL,NULL,'2010-01-16 12:10:21','#include <iostream>\r\nusing namespace std;\r\nint main(){\r\nint * a;\r\nwhile(1)a=new int(1000);\r\nreturn 0;\r\n}'),(67,1,3,5,1,NULL,NULL,'2010-01-16 12:11:08','#include <iostream>\r\nusing namespace std;\r\nint main(){\r\nint * a;\r\nwhile(1)a=new int(1000000);\r\nreturn 0;\r\n}'),(68,1,3,4,1,2,576,'2010-01-16 12:11:51','#include <iostream>\r\nint a[10000][300];\r\nint main(){\r\nreturn 0;\r\n}'),(69,1,3,9,1,NULL,NULL,'2010-01-16 12:34:12','#include <iostream>\r\n#include <cstdio>\r\nusing namespace std;\r\nint main(){\r\n	freopen(\"../sout/1\",\"r\",stdin);\r\n	//FILE *f1=fopen(\"../sout/1\",\"r\",stdin);\r\n	char c;\r\n	while(cin>>c){\r\n		cout<<c;\r\n	}\r\n	return 0;\r\n}'),(70,1,3,9,1,NULL,NULL,'2010-01-16 12:36:34','#include <iostream>\r\n#include <cstdio>\r\nusing namespace std;\r\nint main(){\r\n	//freopen(\"../sout/1\",\"r\",stdin);\r\n	FILE *f1=fopen(\"../sout/1\",\"r\");\r\n	char c;\r\n	\r\n	while(fscanf(f1,\"%c\",&c)!=EOF){\r\n		cout<<c;\r\n	}\r\n	fclose(f1);\r\n	return 0;\r\n}'),(71,1,3,9,1,NULL,NULL,'2010-01-16 12:39:04','#include <iostream>\r\n#include <cstdio>\r\nusing namespace std;\r\nint main(){\r\n    //freopen(\"../sout/1\",\"r\",stdin);\r\n    FILE *f1=fopen(\"../sout/1\",\"r\");\r\n    char c;\r\n    \r\n    while(fscanf(f1,\"%c\",&c)!=EOF){\r\n        cout<<c;\r\n    }\r\n    fclose(f1);\r\n    return 0;\r\n}'),(72,1,3,9,1,NULL,NULL,'2010-01-16 12:46:32','#include <iostream>\r\n#include <cstdio>\r\nusing namespace std;\r\nint main(){\r\n	//freopen(\"../sout/1\",\"r\",stdin);\r\n	FILE *f1=fopen(\"1\",\"r\");\r\n	char c;\r\n	\r\n	while(fscanf(f1,\"%c\",&c)!=EOF){\r\n		cout<<c;\r\n	}\r\n	fclose(f1);\r\n	return 0;\r\n}'),(73,1,3,9,1,NULL,NULL,'2010-01-16 12:47:34','#include <iostream>\r\n#include <cstdio>\r\nusing namespace std;\r\nint main(){\r\n	//freopen(\"9\",\"r\",stdin);\r\n	FILE *f1=fopen(\"9\",\"r\");\r\n	char c;\r\n	\r\n	while(fscanf(f1,\"%c\",&c)!=EOF){\r\n		cout<<c;\r\n	}\r\n	fclose(f1);\r\n	return 0;\r\n}'),(74,1,3,9,1,NULL,NULL,'2010-01-16 12:48:34','#include <iostream>\r\n#include <cstdio>\r\nusing namespace std;\r\nint main(){\r\n    //freopen(\"9\",\"r\",stdin);\r\n    FILE *f1=fopen(\"10\",\"r\");\r\n    char c;\r\n    \r\n    while(fscanf(f1,\"%c\",&c)!=EOF){\r\n        cout<<c;\r\n    }\r\n    fclose(f1);\r\n    return 0;\r\n}'),(75,1,3,9,1,NULL,NULL,'2010-01-16 12:49:24','#include <iostream>\r\n#include <cstdio>\r\nusing namespace std;\r\nint main(){\r\n    FILE *f1=fopen(\"sout/1\",\"r\");\r\n    char c;\r\n    while(fscanf(f1,\"%c\",&c)!=EOF){\r\n        cout<<c;\r\n    }\r\n    fclose(f1);\r\n    return 0;\r\n}'),(76,1,3,7,2,NULL,NULL,'2010-01-16 14:01:29','#include <stdio.h>\r\nint main(){\r\n    char c;\r\n    FILE *f1;\r\nf1=fopen(\"sout/1\",\"r\");\r\n    while(fscanf(f1,\"%c\",&c)!=EOF){\r\n        cout<<c;\r\n    }\r\n    fclose(f1);\r\n    return 0;\r\n}'),(77,1,3,9,2,NULL,NULL,'2010-01-16 14:04:05','#include <stdio.h>\r\nint main(){\r\n    char c;\r\n    FILE *f1;\r\n	f1=fopen(\"sout/1\",\"r\");\r\n    while(fscanf(f1,\"%c\",&c)!=EOF){\r\n        printf(\"%c\",c);\r\n    }\r\n    fclose(f1);\r\n    return 0;\r\n}'),(78,1,3,3,1,1,624,'2010-01-16 14:36:05','#include <iostream>\r\nusing namespace std;\r\nint c[1000][1000];\r\nint main(){\r\nint a,b;\r\nint i,j;\r\nfor(i=0;i<20000;i++){\r\nfor(j=0;j<10000;j++){\r\na+=b;\r\n}\r\n}\r\nwhile(cin>>a>>b)cout<<a+b<<endl;\r\nreturn 0;\r\n}'),(79,1,3,3,2,0,460,'2010-01-16 14:37:13','#include <stdio.h>\r\nint main(){\r\nint a,b;\r\nwhile(scanf(\"%d%d\",&a,&b)!=EOF){printf(\"%d\\n\",a+b);}\r\nreturn 0;\r\n}'),(80,1,3,9,1,NULL,NULL,'2010-01-16 14:37:44','#include <iostream>\r\n#include <cstdio>\r\nusing namespace std;\r\nint main(){\r\n    FILE *f1=fopen(\"sout/1\",\"r\");\r\n    char c;\r\n    while(fscanf(f1,\"%c\",&c)!=EOF){\r\n        cout<<c;\r\n    }\r\n    fclose(f1);\r\n    return 0;\r\n}'),(81,1,3,9,2,NULL,NULL,'2010-01-16 14:38:32','#include <stdio.h>\r\nint main(){\r\n    char c;\r\n    FILE *f1;\r\n    f1=fopen(\"sout/1\",\"r\");\r\n    while(fscanf(f1,\"%c\",&c)!=EOF){\r\n        printf(\"%c\",c);\r\n    }\r\n    fclose(f1);\r\n    return 0;\r\n}'),(82,1,3,9,2,NULL,NULL,'2010-01-16 17:06:49','#include <stdio.h>\r\nint main(){\r\n    char c;\r\n    FILE *f1;\r\n    f1=fopen(\"sout/1\",\"r\");\r\n    while(fscanf(f1,\"%c\",&c)!=EOF){\r\n        printf(\"%c\",c);\r\n    }\r\n    fclose(f1);\r\n    return 0;\r\n}'),(83,1,3,9,2,NULL,NULL,'2010-01-16 17:59:43','#include <stdio.h>\r\nint main(){\r\n    char c;\r\n    FILE *f1;\r\n    f1=fopen(\"sout/1\",\"r\");\r\n    while(fscanf(f1,\"%c\",&c)!=EOF){\r\n        printf(\"%c\",c);\r\n    }\r\n    fclose(f1);\r\n    return 0;\r\n}'),(84,1,18,7,1,NULL,NULL,'2010-01-16 22:32:19','<script>alert(\'aa\');</script>s'),(85,1,3,9,2,NULL,NULL,'2010-01-17 12:10:13','#include <stdio.h>\r\nint main(){\r\n    char c;\r\n    FILE *f1;\r\n    f1=fopen(\"sout/1\",\"r\");\r\n    while(fscanf(f1,\"%c\",&c)!=EOF){\r\n        printf(\"%c\",c);\r\n    }\r\n    fclose(f1);\r\n    return 0;\r\n}'),(86,1,3,9,2,NULL,NULL,'2010-01-17 12:23:19','#include <stdio.h>\r\nint main(){\r\n    char c;\r\n    FILE *f1;\r\n    f1=fopen(\"sout/1\",\"r\");\r\n    while(fscanf(f1,\"%c\",&c)!=EOF){\r\n        printf(\"%c\",c);\r\n    }\r\n    fclose(f1);\r\n    return 0;\r\n}'),(87,1,3,9,2,NULL,NULL,'2010-01-17 12:29:07','#include <stdio.h>\r\nint main(){\r\n    char c;\r\n    FILE *f1;\r\n    f1=fopen(\"sout/1\",\"r\");\r\n    while(fscanf(f1,\"%c\",&c)!=EOF){\r\n        printf(\"%c\",c);\r\n    }\r\n    fclose(f1);\r\n    return 0;\r\n}'),(88,1,3,9,2,NULL,NULL,'2010-01-17 12:29:46','#include <stdio.h>\r\nint main(){\r\n    char c;\r\n    FILE *f1;\r\n    f1=fopen(\"sout/1\",\"r\");\r\n    while(fscanf(f1,\"%c\",&c)!=EOF){\r\n        printf(\"%c\",c);\r\n    }\r\n    fclose(f1);\r\n    return 0;\r\n}'),(89,1,3,9,2,NULL,NULL,'2010-01-17 12:38:48','#include <stdio.h>\r\nint main(){\r\n    char c;\r\n    FILE *f1;\r\n    f1=fopen(\"sout/1\",\"r\");\r\n    while(fscanf(f1,\"%c\",&c)!=EOF){\r\n        printf(\"%c\",c);\r\n    }\r\n    fclose(f1);\r\n    return 0;\r\n}'),(90,1,3,9,2,NULL,NULL,'2010-01-17 12:42:30','#include <stdio.h>\r\nint main(){\r\n    char c;\r\n    FILE *f1;\r\n    f1=fopen(\"sout/1\",\"r\");\r\n    while(fscanf(f1,\"%c\",&c)!=EOF){\r\n        printf(\"%c\",c);\r\n    }\r\n    fclose(f1);\r\n    return 0;\r\n}'),(91,1,3,9,2,NULL,NULL,'2010-01-17 12:42:43','#include <stdio.h>\r\nint main(){\r\n    char c;\r\n    FILE *f1;\r\n    f1=fopen(\"sout/1\",\"r\");\r\n    while(fscanf(f1,\"%c\",&c)!=EOF){\r\n        printf(\"%c\",c);\r\n    }\r\n    fclose(f1);\r\n    return 0;\r\n}'),(92,1,3,9,2,NULL,NULL,'2010-01-17 12:46:43','#include <stdio.h>\r\nint main(){\r\n    char c;\r\n    FILE *f1;\r\n    f1=fopen(\"sout/1\",\"r\");\r\n    while(fscanf(f1,\"%c\",&c)!=EOF){\r\n        printf(\"%c\",c);\r\n    }\r\n    fclose(f1);\r\n    return 0;\r\n}'),(93,1,3,9,2,NULL,NULL,'2010-01-17 12:46:53','#include <stdio.h>\r\nint main(){\r\n    char c;\r\n    FILE *f1;\r\n    f1=fopen(\"sout/1\",\"r\");\r\n    while(fscanf(f1,\"%c\",&c)!=EOF){\r\n        printf(\"%c\",c);\r\n    }\r\n    fclose(f1);\r\n    return 0;\r\n}'),(94,1,3,9,2,NULL,NULL,'2010-01-17 12:47:15','#include <stdio.h>\r\nint main(){\r\n    char c;\r\n    FILE *f1;\r\n    f1=fopen(\"sout/1\",\"r\");\r\n    while(fscanf(f1,\"%c\",&c)!=EOF){\r\n        printf(\"%c\",c);\r\n    }\r\n    fclose(f1);\r\n    return 0;\r\n}'),(95,1,3,3,2,1,460,'2010-01-17 12:49:52','#include <stdio.h>\r\nint main(){\r\nint a,b;\r\nwhile(scanf(\"%d%d\",&a,&b)!=EOF){printf(\"%d\\n\",a+b);}\r\nreturn 0;\r\n}'),(96,1,3,3,2,1,464,'2010-01-17 12:50:01','#include <stdio.h>\r\nint main(){\r\nint a,b;\r\nwhile(scanf(\"%d%d\",&a,&b)!=EOF){printf(\"%d\\n\",a+b);}\r\nreturn 0;\r\n}'),(97,1,3,3,2,1,460,'2010-01-17 12:55:46','#include <stdio.h>\r\nint main(){\r\nint a,b;\r\nwhile(scanf(\"%d%d\",&a,&b)!=EOF){printf(\"%d\\n\",a+b);}\r\nreturn 0;\r\n}'),(98,1,3,3,2,1,464,'2010-01-17 12:55:59','#include <stdio.h>\r\nint main(){\r\nint a,b;\r\nwhile(scanf(\"%d%d\",&a,&b)!=EOF){printf(\"%d\\n\",a+b);}\r\nreturn 0;\r\n}'),(99,1,3,3,2,1,460,'2010-01-17 12:56:09','#include <stdio.h>\r\nint main(){\r\nint a,b;\r\nwhile(scanf(\"%d%d\",&a,&b)!=EOF){printf(\"%d\\n\",a+b);}\r\nreturn 0;\r\n}'),(100,1,3,3,2,2,460,'2010-01-17 12:58:23','#include <stdio.h>\r\nint main(){\r\nint a,b;\r\nwhile(scanf(\"%d%d\",&a,&b)!=EOF){printf(\"%d\\n\",a+b);}\r\nreturn 0;\r\n}'),(101,1,3,3,2,2,460,'2010-01-17 12:58:30','#include <stdio.h>\r\nint main(){\r\nint a,b;\r\nwhile(scanf(\"%d%d\",&a,&b)!=EOF){printf(\"%d\\n\",a+b);}\r\nreturn 0;\r\n}'),(102,1,3,3,2,1,464,'2010-01-17 13:03:50','#include <stdio.h>\r\nint main(){\r\nint a,b;\r\nwhile(scanf(\"%d%d\",&a,&b)!=EOF){printf(\"%d\\n\",a+b);}\r\nreturn 0;\r\n}'),(103,1,3,9,2,NULL,NULL,'2010-01-17 13:04:11','#include <stdio.h>\r\nint main(){\r\n    char c;\r\n    FILE *f1;\r\n    f1=fopen(\"sout/1\",\"r\");\r\n    while(fscanf(f1,\"%c\",&c)!=EOF){\r\n        printf(\"%c\",c);\r\n    }\r\n    fclose(f1);\r\n    return 0;\r\n}'),(104,1,3,3,2,3,460,'2010-01-17 13:14:56','#include <stdio.h>\r\nint main(){\r\nint a,b;\r\nwhile(scanf(\"%d%d\",&a,&b)!=EOF){printf(\"%d\\n\",a+b);}\r\nreturn 0;\r\n}'),(105,1,3,3,2,1,460,'2010-01-17 13:20:33','#include <stdio.h>\r\nint main(){\r\nint a,b;\r\nwhile(scanf(\"%d%d\",&a,&b)!=EOF){printf(\"%d\\n\",a+b);}\r\nreturn 0;\r\n}'),(106,1,3,3,2,0,464,'2010-01-17 13:27:07','#include <stdio.h>\r\nint main(){\r\nint a,b;\r\nwhile(scanf(\"%d%d\",&a,&b)!=EOF){printf(\"%d\\n\",a+b);}\r\nreturn 0;\r\n}'),(107,1,3,3,2,1,464,'2010-01-17 13:42:41','#include <stdio.h>\r\nint main(){\r\nint a,b;\r\nwhile(scanf(\"%d%d\",&a,&b)!=EOF){printf(\"%d\\n\",a+b);}\r\nreturn 0;\r\n}'),(108,1,3,3,2,1,460,'2010-01-17 13:53:50','#include <stdio.h>\r\nint main(){\r\nint a,b;\r\nwhile(scanf(\"%d%d\",&a,&b)!=EOF){printf(\"%d\\n\",a+b);}\r\nreturn 0;\r\n}'),(109,1,3,3,2,1,464,'2010-01-17 13:59:01','#include <stdio.h>\r\nint main(){\r\nint a,b;\r\nwhile(scanf(\"%d%d\",&a,&b)!=EOF){printf(\"%d\\n\",a+b);}\r\nreturn 0;\r\n}'),(110,1,3,3,2,2,464,'2010-01-17 14:05:34','#include <stdio.h>\r\nint main(){\r\nint a,b;\r\nwhile(scanf(\"%d%d\",&a,&b)!=EOF){printf(\"%d\\n\",a+b);}\r\nreturn 0;\r\n}'),(111,1,3,3,2,0,460,'2010-01-17 14:14:51','#include <stdio.h>\r\nint main(){\r\nint a,b;\r\nwhile(scanf(\"%d%d\",&a,&b)!=EOF){printf(\"%d\\n\",a+b);}\r\nreturn 0;\r\n}'),(112,1,3,3,2,0,460,'2010-01-17 14:15:13','#include <stdio.h>\r\nint main(){\r\nint a,b;\r\nwhile(scanf(\"%d%d\",&a,&b)!=EOF){printf(\"%d\\n\",a+b);}\r\nreturn 0;\r\n}'),(113,1,3,3,2,2,464,'2010-01-17 14:19:54','#include <stdio.h>\r\nint main(){\r\nint a,b;\r\nwhile(scanf(\"%d%d\",&a,&b)!=EOF){printf(\"%d\\n\",a+b);}\r\nreturn 0;\r\n}'),(114,1,3,3,2,1,460,'2010-01-17 15:08:01','#include <stdio.h>\r\nint main(){\r\nint a,b;\r\nwhile(scanf(\"%d%d\",&a,&b)!=EOF){printf(\"%d\\n\",a+b);}\r\nreturn 0;\r\n}'),(115,1,3,3,2,2,460,'2010-01-17 15:08:13','#include <stdio.h>\r\nint main(){\r\nint a,b;\r\nwhile(scanf(\"%d%d\",&a,&b)!=EOF){printf(\"%d\\n\",a+b);}\r\nreturn 0;\r\n}'),(116,1,3,3,2,1,464,'2010-01-17 15:08:30','#include <stdio.h>\r\nint main(){\r\nint a,b;\r\nwhile(scanf(\"%d%d\",&a,&b)!=EOF){printf(\"%d\\n\",a+b);}\r\nreturn 0;\r\n}'),(117,1,3,3,2,2,460,'2010-01-17 15:08:40','#include <stdio.h>\r\nint main(){\r\nint a,b;\r\nwhile(scanf(\"%d%d\",&a,&b)!=EOF){printf(\"%d\\n\",a+b);}\r\nreturn 0;\r\n}'),(118,1,3,9,2,NULL,NULL,'2010-01-17 15:36:59','#include <stdio.h>\r\nint main(){\r\n    char c;\r\n    FILE *f1;\r\n    f1=fopen(\"sout/1\",\"r\");\r\n    while(fscanf(f1,\"%c\",&c)!=EOF){\r\n        printf(\"%c\",c);\r\n    }\r\n    fclose(f1);\r\n    return 0;\r\n}'),(119,1,3,9,2,NULL,NULL,'2010-01-17 15:37:50','#include <stdio.h>\r\nint main(){\r\n    char c;\r\n    FILE *f1;\r\n    f1=fopen(\"sout/1\",\"r\");\r\n    while(fscanf(f1,\"%c\",&c)!=EOF){\r\n        printf(\"%c\",c);\r\n    }\r\n    fclose(f1);\r\n    return 0;\r\n}'),(125,1,3,5,2,NULL,NULL,'2010-01-17 22:09:32','#include <stdio.h>\r\nint main(){\r\nwhile(1);\r\nreturn 0;\r\n}'),(120,1,3,7,1,NULL,NULL,'2010-01-17 16:35:01','＃include <iostream>\r\nusing namespace std;\r\nint main(){\r\nint a,b;\r\nwhile(cin>>a>>b)cout<<a+b<<endl;\r\nreturn 0;\r\n}'),(121,1,3,7,1,NULL,NULL,'2010-01-17 16:40:28','#include <iostream>\r\nusing namespace std;\r\nint main(){\r\nint a,b,s,k;\r\nint i,j;\r\nfor(i=0;i<100000;i++){\r\nfor(j=0;j<100000;j++){\r\ns+=i*j;\r\nk-=s;\r\n}\r\ncout<<s;\r\nreturn 0;\r\n}'),(122,1,3,5,1,NULL,NULL,'2010-01-17 16:41:27','#include <iostream>\r\nusing namespace std;\r\nint main(){\r\nint a,b,s,k;\r\nint i,j;\r\nfor(i=0;i<100000;i++){\r\nfor(j=0;j<100000;j++){\r\ns+=i*j;\r\nk-=s;\r\n}\r\n}\r\ncout<<s;\r\nreturn 0;\r\n}'),(123,1,3,5,1,NULL,NULL,'2010-01-17 17:00:52','#include <iostream>\r\nusing namespace std;\r\nint main(){\r\nint a,b,s,k;\r\nint i,j;\r\nb=0;\r\nfor(i=0;i<100000;i++){\r\nfor(j=0;j<100000;j++){\r\ns+=i*j;\r\nk-=s;\r\na=s-b;\r\nk=a+s;\r\nb=a-s;\r\nk=b+a;\r\n}\r\n}\r\ns=a+b;\r\nb=a-s;\r\nk=b-k;\r\ns=a+k;\r\ncout<<s;\r\nreturn 0;\r\n}'),(124,1,3,4,1,896,8408,'2010-01-17 17:03:30','#include <iostream>\r\nusing namespace std;\r\nint a[1000][1000],b[1000][1000];\r\nint main(){\r\nint i,j;\r\nfor(i=0;i<10000;i++){\r\nfor(j=0;j<10000;j++){\r\na[i%1000][j%1000]=i+j;\r\nb[i%1000][j%1000]=i-j;\r\n}\r\n}\r\nint k=0;\r\nfor(i=0;i<1000;i++){\r\nfor(j=0;j<1000;j++){\r\nk=a[i][j]+b[i][j];\r\n}\r\n}\r\ncout<<k<<endl;\r\nreturn 0;\r\n}\r\n'),(126,1,3,7,1,NULL,NULL,'2010-01-18 12:11:30','#include <iostream>\r\nusing namespace std;\r\nint main(){\r\nchar c;\r\nfreopen(\"sout/1\",\"r\",stdin);\r\nwhile(scanf(\"%c\",&c)!=EOF)printf(\"%c\",c);\r\nreturn 0;\r\n}'),(127,1,3,9,1,NULL,NULL,'2010-01-18 12:15:28','#include <iostream>\r\n#include <cstdio>\r\nusing namespace std;\r\nint main(){\r\nchar c;\r\nfreopen(\"sout/1\",\"r\",stdin);\r\nwhile(scanf(\"%c\",&c)!=EOF)printf(\"%c\",c);\r\nreturn 0;\r\n}'),(128,1,4,9,1,NULL,NULL,'2010-01-18 18:11:19','#include <iostream>\r\n#include <stdlib.h>\r\n#include <unistd.h>\r\n\r\nusing namespace std;\r\nint main(int argc, char *argv)\r\n{\r\nfork();\r\n}'),(129,1,3,9,1,NULL,NULL,'2010-01-18 18:11:22','#include <iostream>\r\n#include <cstdlib>\r\n#include <sys/wait.h>\r\nusing namespace std;\r\nint func(){\r\n	int pid=fork();\r\n	if(pid<0){\r\n		return -1;\r\n	}\r\n	if(pid==0){\r\n		cout<<\"This is child\"<<endl;\r\n		return 3;\r\n	}\r\n	else{\r\n		cout<<\"This is parent\"<<endl;\r\n		waitpid(0,0,0);\r\n		exit(0);\r\n	}\r\n}\r\nint main(){\r\n	int x=func();\r\n	cout<<\"x=\"<<x<<endl;\r\n	cout<<\"OK\"<<endl;\r\n	return 0;\r\n}'),(130,1,4,5,1,NULL,NULL,'2010-01-18 18:13:11','#include <iostream> \r\n#include <stdlib.h> \r\n#include <unistd.h> \r\n\r\nusing namespace std; \r\nint main(int argc, char *argv) \r\n{ \r\nwhile(true)\r\n    new int;\r\n}'),(131,1,4,5,1,NULL,NULL,'2010-01-18 18:14:45','#include <iostream> \r\n#include <stdlib.h> \r\n#include <unistd.h> \r\n\r\nusing namespace std; \r\nint main(int argc, char *argv) \r\n{ \r\nfor(int i = 0; i < 1000000; i++)\r\n    malloc(4096);\r\n}'),(132,1,4,4,1,34,4572,'2010-01-18 18:15:34','#include <iostream> \r\n#include <stdlib.h> \r\n#include <unistd.h> \r\n\r\nusing namespace std; \r\nint main(int argc, char *argv) \r\n{ \r\nfor(int i = 0; i < 1000; i++)\r\n    malloc(1000*1000);\r\n}'),(133,1,4,4,1,1,576,'2010-01-18 18:18:08','#include <iostream> \r\n#include <stdlib.h> \r\n#include <unistd.h> \r\n\r\nint a[1000*1000*100];\r\n\r\nusing namespace std; \r\nint main(int argc, char *argv) \r\n{ \r\nreturn 0;\r\n}'),(134,1,4,5,1,NULL,NULL,'2010-01-18 18:20:47','#include <iostream> \r\n#include <stdlib.h> \r\n#include <unistd.h> \r\n\r\nint a[1000*1000*100];\r\n\r\nusing namespace std; \r\nint main(int argc, char *argv) \r\n{ \r\na[0] = a[1] = 1;\r\nfor(int i = 2; i < sizeof(a); i++)\r\n    a[i] = a[i - 1] + a[i - 2];\r\n}'),(135,1,4,5,1,NULL,NULL,'2010-01-18 18:21:53','#include <iostream> \r\n#include <stdlib.h> \r\n#include <unistd.h> \r\n\r\nint a[1000*1000*100];\r\n\r\nusing namespace std; \r\nint main(int argc, char *argv) \r\n{ \r\na[0] = a[1] = 1;\r\nfor(int i = 2; i < sizeof(a) / sizeof(a[0]); i++)\r\n    a[i] = a[i - 1] + a[i - 2];\r\n}'),(136,1,4,4,1,368,98224,'2010-01-18 18:24:14','#include <iostream>  \r\n#include <stdlib.h>  \r\n#include <unistd.h>  \r\n\r\nint a[1000*1000*100]; \r\n\r\nusing namespace std;  \r\nint main(int argc, char *argv)  \r\n{  \r\na[0] = a[1] = 1; \r\nfor(int i = 2; i < sizeof(a) / sizeof(a[0]) / 4; i++) \r\n    a[i] = a[i - 1] + a[i - 2]; \r\n}'),(137,1,4,4,1,373,98224,'2010-01-18 18:27:35','#include <iostream>   \r\n#include <stdlib.h>   \r\n#include <unistd.h>   \r\n\r\nint a[1000*1000*100];  \r\n\r\nusing namespace std;   \r\nint main(int argc, char *argv)   \r\n{   \r\na[0] = a[1] = 1;  \r\nfor(int i = 2; i < sizeof(a) / sizeof(a[0]) / 4; i++)  \r\n    a[i] = a[i - 1] + a[i - 2];  \r\n}'),(138,1,4,7,1,NULL,NULL,'2010-01-18 18:34:44','#include <iostream>   \r\n#include <stdlib.h>   \r\n#include <unistd.h>   \r\nusing namespace std;   \r\n\r\nint main(int argc, char *argv)   \r\n{   \r\nfor(int i = 0; i < 1000 * 1000 * 10)\r\n    cout<<\"SB is s and b\"<<endl;\r\n}'),(139,1,4,5,1,NULL,NULL,'2010-01-18 18:36:58','#include <iostream>    \r\n#include <stdlib.h>    \r\n#include <unistd.h>    \r\nusing namespace std;    \r\n\r\nint main(int argc, char *argv)    \r\n{    \r\nfor(int i = 0; i < 1000 * 1000 * 10; i++) \r\n    cout<<\"SB is s and b\"<<endl; \r\n}'),(140,1,3,5,1,NULL,NULL,'2010-01-18 18:41:30','#include <iostream>\r\nusing namespace std;\r\nint a[1000*1000*100];\r\nint main(){\r\nint i;\r\na[0]=1;\r\nfor(i=1;i<1000*1000*100;i++){\r\na[i]=a[i-1]+1;\r\n}\r\ncout<<a[1000*1000*100-1]<<endl;\r\nreturn 0;\r\n}'),(141,1,4,5,1,NULL,NULL,'2010-01-18 18:42:15','#include <iostream>    \r\n#include <stdlib.h>    \r\n#include <unistd.h>    \r\n#include <string.h>\r\nusing namespace std;    \r\n\r\nchar str[1000];\r\nchar *ss = \"SB is s and b\";\r\n\r\nint main(int argc, char *argv)    \r\n{    \r\nfor(char *p = str; p + strlen(ss) < str + 1000 ; p += strlen(ss))\r\n    strcpy(p, ss);\r\nfor(int i = 0; i < 1000 * 100; i++)\r\n    cout<<str;\r\n}'),(142,1,3,5,1,NULL,NULL,'2010-01-18 18:42:28','#include <iostream>\r\nusing namespace std;\r\nint a[1000*1000*100];\r\nint main(){\r\nint i;\r\na[0]=1;\r\nfor(i=1;i<1000*1000*100;i++){\r\na[i]=a[i-1]+1;\r\n}\r\ncout<<a[1000*1000*100-1]<<endl;\r\nreturn 0;\r\n}'),(143,1,3,4,1,666,196164,'2010-01-18 18:43:21','#include <iostream>\r\nusing namespace std;\r\nint a[500*1000*100];\r\nint main(){\r\nint i;\r\na[0]=1;\r\nfor(i=1;i<500*1000*100;i++){\r\na[i]=a[i-1]+1;\r\n}\r\ncout<<a[500*1000*100-1]<<endl;\r\nreturn 0;\r\n}'),(144,1,4,7,1,NULL,NULL,'2010-01-18 18:54:43','#include <iostream>\r\n#include <stdlib.h>\r\n\r\nchar str[1000 * 1000];\r\n\r\nint main(int argc, char *argv[])\r\n{\r\nfor(int i = 0; i < sizeof(str); i++)\r\n    str[i] = rand() % 10 + \'0\';\r\nstr[sizeof(str) - 1] = 0;\r\nfor(int i = 0; i < 1000; i++)\r\n    cout<<str;\r\n}'),(145,1,4,7,1,NULL,NULL,'2010-01-18 18:55:26','#include <iostream>\r\n#include <stdlib.h>\r\n\r\nchar str[1000 * 1000];\r\n\r\nint main(int argc, char *argv[])\r\n{\r\nint i;\r\nfor(i = 0; i < sizeof(str); i++)\r\n    str[i] = rand() % 10 + \'0\';\r\nstr[sizeof(str) - 1] = 0;\r\nfor(i = 0; i < 1000; i++)\r\n    cout<<str;\r\n}'),(146,1,4,5,1,NULL,NULL,'2010-01-18 18:56:25','#include <iostream>\r\n#include <stdlib.h>\r\nusing namespace std;\r\n\r\nchar str[1000 * 1000];\r\n\r\nint main(int argc, char *argv[])\r\n{\r\nint i;\r\nfor(i = 0; i < sizeof(str); i++)\r\n    str[i] = rand() % 10 + \'0\';\r\nstr[sizeof(str) - 1] = 0;\r\nfor(i = 0; i < 1000; i++)\r\n    cout<<str;\r\n}'),(147,1,4,4,1,784,1828,'2010-01-18 18:57:03','#include <iostream>\r\n#include <stdlib.h>\r\nusing namespace std;\r\n\r\nchar str[1000 * 1000];\r\n\r\nint main(int argc, char *argv[])\r\n{\r\nint i;\r\nfor(i = 0; i < sizeof(str); i++)\r\n    str[i] = rand() % 10 + \'0\';\r\nstr[sizeof(str) - 1] = 0;\r\nfor(i = 0; i < 100; i++)\r\n    cout<<str;\r\n}'),(148,1,3,9,1,NULL,NULL,'2010-01-18 19:09:28','#include <iostream>\r\nusing namespace std;\r\nint a[500*1000*100];\r\nint main(){\r\nint i;\r\na[0]=1;\r\nfor(i=1;i<500*1000*100;i++){\r\na[i]=a[i-1]+1;\r\n}\r\ncout<<a[500*1000*100-1]<<endl;\r\nreturn 0;\r\n}'),(149,1,3,6,1,NULL,NULL,'2010-01-18 19:18:57','#include <iostream>\r\nusing namespace std;\r\nint a[500*1000*100];\r\nint main(){\r\nint i;\r\na[0]=1;\r\nfor(i=1;i<500*1000*100;i++){\r\na[i]=a[i-1]+1;\r\n}\r\ncout<<a[500*1000*100-1]<<endl;\r\nreturn 0;\r\n}'),(150,1,3,5,1,NULL,NULL,'2010-01-18 19:21:29','#include <iostream>\r\n#include <cstdio>\r\nusing namespace std;\r\nint main(){\r\nint i;\r\nfor(i=0;i<100*1000*1000;i++){\r\nprintf(\"a\");\r\n}\r\nreturn 0;\r\n}'),(151,1,3,5,1,NULL,NULL,'2010-01-18 19:22:13','#include <iostream>\r\n#include <cstdio>\r\nusing namespace std;\r\nint main(){\r\nint i;\r\nfor(i=0;i<50*1000*1000;i++){\r\nprintf(\"aa\");\r\n}\r\nreturn 0;\r\n}'),(152,1,3,4,1,274,880,'2010-01-18 19:22:55','#include <iostream>\r\n#include <cstdio>\r\nusing namespace std;\r\nint main(){\r\nint i;\r\nfor(i=0;i<1000*1000;i++){\r\nprintf(\"1234567890\");\r\n}\r\nreturn 0;\r\n}'),(153,1,3,9,1,NULL,NULL,'2010-01-18 19:51:55','#include <iostream>\r\n#include <cstdio>\r\nusing namespace std;\r\nint main(){\r\nint i;\r\nfor(i=0;i<1000*1000;i++){\r\nprintf(\"1234567890\");\r\n}\r\nreturn 0;\r\n}');
/*!40000 ALTER TABLE `status` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user`
--

DROP TABLE IF EXISTS `user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `user` (
  `uid` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(32) NOT NULL,
  `email` varchar(128) DEFAULT NULL,
  `nickname` varchar(64) NOT NULL,
  `password` char(32) NOT NULL,
  `school` varchar(32) DEFAULT NULL,
  `gender` tinyint(1) DEFAULT NULL,
  `accepted` int(10) unsigned DEFAULT '0',
  `submitted` int(10) unsigned DEFAULT '0',
  `registerTime` datetime DEFAULT NULL,
  PRIMARY KEY (`uid`),
  UNIQUE KEY `username` (`username`),
  UNIQUE KEY `nickname` (`nickname`)
) ENGINE=MyISAM AUTO_INCREMENT=19 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user`
--

LOCK TABLES `user` WRITE;
/*!40000 ALTER TABLE `user` DISABLE KEYS */;
INSERT INTO `user` VALUES (3,'alazyrabbit','','alazyrabbit','1fccb567a44880e8665b7cb9d0f97271','',2,59,125,'2009-09-17 18:14:15'),(2,'asdfasdf','','asdfasdf','38d2368bdb355fd0acf7eaa86c520b3f','',2,0,0,'2009-09-17 17:51:30'),(4,'powerx1202','powerx1202@gmail.com','ä¸æ–‡é¹','a220a317d4773cd502ceded7a7448287','å±±ä¸œå¤§å­¦',1,0,16,'2009-09-17 21:42:31'),(5,'test','','test','cc03e747a6afbbcbf8be7668acfebee5','',2,0,0,'2009-09-17 21:45:45'),(6,'godlike','','godlike','4f75d8bc38efe07fd24f303eee69b00b','heaven',2,0,0,'2009-09-17 21:56:05'),(7,'godess','','godess','a973d1c139b6dedecc1c79b30efc064d','',0,0,0,'2009-09-17 21:57:55'),(8,'hixuhuiqing','tsingxu@yahoo.cn','tsing_xu','96e79218965eb72c92a549dd5a330112','SDU',1,1,3,'2009-09-18 09:33:23'),(9,'mabaochang','314134278@qq.com','mabaochang','e10adc3949ba59abbe56e057f20f883e','JLU&&SDU',1,0,0,'2009-09-24 19:40:52'),(10,'123abc','zouyun250@126.com','123abc','e10adc3949ba59abbe56e057f20f883e','JLU&&SDU',1,0,0,'2009-09-24 19:42:06'),(11,'yabinxu','','tick','e10adc3949ba59abbe56e057f20f883e','',1,0,0,'2009-11-10 17:22:49'),(12,'a','','a','5d793fc5b00a2348c3fb9ab59e5ca98a','',1,0,1,'2010-01-13 17:54:31'),(13,'yanghdx','','123456','e10adc3949ba59abbe56e057f20f883e','',1,1,6,'2010-01-13 18:03:19'),(14,'JK_L','liujiankun625@yahoo.com.cn','åˆ˜å»ºå¤','25ef754a752450c761f053e4b16bd542','sdu',1,0,0,'2010-01-15 12:44:50'),(15,'eee4','','qq','083696f0769e1f30002ba8084727b1f3','',1,0,0,'2010-01-15 12:45:49'),(16,'shixiao','','shixiao','2c04f98759d784b2d79bd72e8df2457c','',2,0,1,'2010-01-15 12:52:13'),(17,'xunlei','','qq2','083696f0769e1f30002ba8084727b1f3','',1,0,0,'2010-01-15 12:57:38'),(18,'tester','123@123.123','tester','4297f44b13955235245b2497399d7a93','<script>alert(\'aa\');</script>',1,0,1,'2010-01-16 22:31:02');
/*!40000 ALTER TABLE `user` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2010-01-19 10:45:30