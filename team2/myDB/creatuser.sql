CREATE DATABASE `mytest` CHARACTER SET 'utf8';

CREATE TABLE `mytest`.`user`  (
  `id` int(4) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '玩家id',
  `name` varchar(255) NOT NULL DEFAULT '' COMMENT '用户名',
  `pass` varchar(255) NOT NULL DEFAULT '' COMMENT '用户密码',
  `reg_time` varchar(255) NOT NULL DEFAULT '' COMMENT '注册时间',
  `last_login_time` varchar(255) NOT NULL DEFAULT '' COMMENT '上次登陆时间',
  `money` int(4) NOT NULL DEFAULT 100 COMMENT '金币',
  `groupid` int(1) UNSIGNED NOT NULL COMMENT '身份标识 1:玩家 2:管理员',
  PRIMARY KEY (`id`)
) ENGINE = InnoDB CHARACTER SET = utf8;

INSERT INTO `mytest`.`user` (`id`, `name`, `pass`, `reg_time`, `groupid`,`last_login_time`) VALUES (1, 'kxz', '123456', '2021-11-12 00:00:01', 2, '2021-11-12 00:00:02');

INSERT INTO `mytest`.`user` (`id`, `name`, `pass`, `reg_time`, `last_login_time`, `groupid`) VALUES (2, 'zzz', '123456', '2021-11-12 19:46:02', '2021-11-12 19:46:04', 1);


/ https://cloud.tencent.com/developer/article/1745084