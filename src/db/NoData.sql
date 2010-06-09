-- MySQL dump 10.11
--
-- Host: localhost    Database: soj
-- ------------------------------------------------------
-- Server version	5.0.75-0ubuntu10.3

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
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `problem` (
  `pid` int(10) unsigned NOT NULL auto_increment,
  `problemName` varchar(50) NOT NULL,
  `accepted` int(10) unsigned NOT NULL default '0',
  `submitted` int(10) unsigned NOT NULL default '0',
  `discription` blob,
  `input` blob,
  `output` blob,
  `inputCase` blob,
  `outputCase` blob,
  `timeLimit` int(10) unsigned NOT NULL default '1000',
  `memoryLimit` int(10) unsigned NOT NULL default '64000',
  `did` int(10) unsigned NOT NULL default '1',
  PRIMARY KEY  (`pid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `status`
--

DROP TABLE IF EXISTS `status`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `status` (
  `rid` int(10) unsigned NOT NULL auto_increment,
  `pid` int(10) unsigned NOT NULL,
  `uid` int(10) unsigned NOT NULL,
  `judgeStatus` tinyint(3) unsigned NOT NULL default '1',
  `language` tinyint(3) unsigned NOT NULL,
  `rtime` int(10) unsigned default NULL,
  `rmemory` int(10) unsigned default NULL,
  `submitTime` datetime NOT NULL,
  `sourceCode` blob,
  PRIMARY KEY  (`rid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `testdata`
--

DROP TABLE IF EXISTS `testdata`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `testdata` (
  `did` int(10) unsigned NOT NULL auto_increment,
  `input` blob,
  `output` blob,
  `version` int(10) unsigned NOT NULL default '1',
  PRIMARY KEY  (`did`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `user`
--

DROP TABLE IF EXISTS `user`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `user` (
  `uid` int(10) unsigned NOT NULL auto_increment,
  `username` varchar(32) NOT NULL,
  `email` varchar(128) default NULL,
  `nickname` varchar(64) NOT NULL,
  `password` char(32) NOT NULL,
  `school` varchar(32) default NULL,
  `gender` tinyint(1) default NULL,
  `accepted` int(10) unsigned NOT NULL default '0',
  `submitted` int(10) unsigned NOT NULL default '0',
  `registerTime` datetime default NULL,
  `lastlogintime` datetime default NULL,
  `lastloginip` char(32) default NULL,
  `lastlanguage` char(10) default NULL,
  PRIMARY KEY  (`uid`),
  UNIQUE KEY `username` (`username`),
  UNIQUE KEY `nickname` (`nickname`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2010-06-09 12:20:26
