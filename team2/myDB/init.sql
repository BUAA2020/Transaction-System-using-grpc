CREATE DATABASE `team2data` CHARACTER SET 'utf8';

-- user表
CREATE TABLE `team2data`.`user`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '玩家id',
  `name` varchar(255) NOT NULL DEFAULT '' COMMENT '用户名',
  `pass` varchar(255) NOT NULL DEFAULT '' COMMENT '用户密码',
  `reg_time` varchar(255) NOT NULL DEFAULT '' COMMENT '注册时间',
  `last_login_time` varchar(255) NOT NULL DEFAULT '' COMMENT '上次登陆时间',
  `money` int(4) NOT NULL DEFAULT 100 COMMENT '金币',
  `groupid` int(1) UNSIGNED NOT NULL COMMENT '身份标识 1:玩家 2:管理员',
  PRIMARY KEY (`id`)
) ENGINE = InnoDB CHARACTER SET = utf8;

-- good表
CREATE TABLE `team2data`.`good`  (
  `道具ID` int(4) UNSIGNED NOT NULL AUTO_INCREMENT,
  `道具名称` varchar(255) CHARACTER SET utf8 NOT NULL DEFAULT '',
  `道具类别` varchar(255) CHARACTER SET utf8 NOT NULL DEFAULT '',
  `最低使用等级` int(3) UNSIGNED NOT NULL DEFAULT 0,
  `适用职业` varchar(255) CHARACTER SET utf8 NOT NULL DEFAULT '',
  `物品档次` int(2) UNSIGNED NOT NULL DEFAULT 0 ,
  `物品颜色` int(1) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`道具ID`)
) ENGINE = InnoDB CHARACTER SET = utf8;

load data LOCAL infile './MINI课题-道具配置表.csv'  into table  `team2data`.`good` fields terminated by ',';

-- bag表
CREATE TABLE `team2data`.`bag`  (
  `道具ID` int(4) UNSIGNED NOT NULL,
  `道具名称` varchar(255) CHARACTER SET utf8 NOT NULL DEFAULT '',
  `所属玩家ID` int(4) UNSIGNED NOT NULL,
  `数量` int(4) UNSIGNED NOT NULL DEFAULT 1,
	CONSTRAINT `道具ID外键` FOREIGN KEY (`道具ID`) REFERENCES `team2data`.`good` (`道具ID`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `玩家ID外键` FOREIGN KEY (`所属玩家ID`) REFERENCES `team2data`.`user` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB CHARACTER SET = utf8;



-- onSaleGood表
CREATE TABLE `team2data`.`onSaleGood`  (
  `商城ID` int UNSIGNED NOT NULL AUTO_INCREMENT,
  `道具ID` int UNSIGNED NOT NULL,
  `道具名称` varchar(255) CHARACTER SET utf8 NOT NULL DEFAULT '',
  `售价` int UNSIGNED NOT NULL DEFAULT 10,
  `所属用户ID` int UNSIGNED NOT NULL,
  `道具属性` int NOT NULL DEFAULT 0 COMMENT '0为普通,1为特殊' ,
  `数量` int NOT NULL ,
  PRIMARY KEY (`商城ID`),
	CONSTRAINT `道具外键` FOREIGN KEY (`道具ID`) REFERENCES `team2data`.`good` (`道具ID`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `所属玩家ID外键` FOREIGN KEY (`所属用户ID`) REFERENCES `team2data`.`user` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB CHARACTER SET = utf8;

-- Trade表
CREATE TABLE `team2data`.`trade`  (
  `订单ID` int UNSIGNED NOT NULL AUTO_INCREMENT,
  `订单时间` varchar(255) NOT NULL DEFAULT '',
  `订单类型` int UNSIGNED NOT NULL COMMENT '1为出售，2为购买',
  `道具ID` int UNSIGNED NOT NULL COMMENT '流转的道具ID',
  `玩家ID` int UNSIGNED NOT NULL,
  `交易金额` int UNSIGNED NOT NULL,
  PRIMARY KEY (`订单ID`),
  CONSTRAINT `道具` FOREIGN KEY (`道具ID`) REFERENCES `team2data`.`good` (`道具ID`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `玩家` FOREIGN KEY (`玩家ID`) REFERENCES `team2data`.`user` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE = InnoDB CHARACTER SET = utf8;