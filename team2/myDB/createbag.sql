CREATE TABLE `mytest`.`bag`  (
  `道具ID` int UNSIGNED NOT NULL,
  `道具名称` varchar(255) NOT NULL,
  `所属玩家ID` int UNSIGNED NOT NULL,
  `数量` int UNSIGNED NOT NULL DEFAULT 1,
  CONSTRAINT `道具ID外键` FOREIGN KEY (`道具ID`) REFERENCES `mytest`.`good` (`道具ID`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `玩家ID外键` FOREIGN KEY (`所属玩家ID`) REFERENCES `mytest`.`user` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `道具名称外键` FOREIGN KEY (`道具名称`) REFERENCES `mytest`.`good` (`道具名称`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB CHARACTER SET = utf8