CREATE TABLE `user` (
  `uid` int(10) unsigned NOT NULL auto_increment,
  `username` varchar(32) NOT NULL,
  `email` varchar(128) default NULL,
  `nickname` varchar(64) NOT NULL,
  `password` char(32) NOT NULL,
  `school` varchar(32) default NULL,
  `gender` tinyint(1) default NULL,
  `accepted` int(10) unsigned default '0',
  `submitted` int(10) unsigned default '0',
  `registerTime` datetime default NULL,
  PRIMARY KEY  (`uid`),
  UNIQUE KEY `username` (`username`),
  UNIQUE KEY `nickname` (`nickname`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 

CREATE TABLE `problem` (
  `pid` int(10) unsigned NOT NULL auto_increment,
  `problemName` varchar(50) NOT NULL,
  `accepted` int(10) unsigned default '0',
  `submitted` int(10) unsigned default '0',
  `discription` blob,
  `input` blob,
  `output` blob,
  `inputCase` blob,
  `outputCase` blob,
  `timeLimit` int(10) unsigned NOT NULL default '1000',
  `memoryLimit` int(10) unsigned NOT NULL default '64000',
  PRIMARY KEY  (`pid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8

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
) ENGINE=MyISAM  DEFAULT CHARSET=utf8
