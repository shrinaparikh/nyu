## CSCI-UA.60-1 Final Exam 
## By Shrina Parikh

CREATE SCHEMA IF NOT EXISTS `asg5` DEFAULT CHARACTER SET utf8 ;
USE `final` ;

DROP TABLE IF EXISTS `final`.`Audience` ;
CREATE TABLE IF NOT EXISTS `final`.`Audience` (
  `Type` VARCHAR(20) NOT NULL,
  PRIMARY KEY (`Type`));
ENGINE = InnoDB;

DROP TABLE IF EXISTS `final`.`Exhibitions` ;
CREATE TABLE IF NOT EXISTS `final`.`Exhibitions` (
	`ExhibitionID` INT AUTO_INCREMENT NOT NULL,
  `Name` VARCHAR(20) NOT NULL,
  'StartDate' DATE(),
  'EndDate' DATE(),
  'IntendedAudience' VARCHAR(20),
  'Description' VARCHAR(100),
  'Cost' DECIMAL(3,2),
  'IsSpecial' BOOLEAN,
  FOREIGN KEY ('IntendedAudience'),
  PRIMARY KEY (`ExhibitionID`));
ENGINE = InnoDB;

DROP TABLE IF EXISTS `final`.`Programs` ;
CREATE TABLE IF NOT EXISTS `final`.`Programs` (
	`ExhibitionID` INT AUTO_INCREMENT NOT NULL,
  `Name` VARCHAR(20) NOT NULL,
  'StartDate' DATE(),
  'EndDate' DATE(),
  'IntendedAudience' VARCHAR(20),
  'ProgType' VARCHAR(20),
  'Description' VARCHAR(100),
  'Cost' DECIMAL(3,2),
  FOREIGN KEY ('IntendedAudience'),
  FOREIGN KEY ('ProgType'),
  PRIMARY KEY (`ProgramID`));
ENGINE = InnoDB;

DROP TABLE IF EXISTS `final`.`ProgramType` ;
CREATE TABLE IF NOT EXISTS `final`.`ProgramType` (
  `Type` VARCHAR(20) NOT NULL,
  `IsEducational` BOOLEAN,
  PRIMARY KEY (`Type`));
ENGINE = InnoDB;

DROP TABLE IF EXISTS `final`.`Research` ;
CREATE TABLE IF NOT EXISTS `final`.`Research` (
	`projectID` INT AUTO_INCREMENT NOT NULL,
  `projectTitle` VARCHAR(50) NOT NULL,
  'Description' VARCHAR(100),
  PRIMARY KEY (`projectID`));
ENGINE = InnoDB;

DROP TABLE IF EXISTS `final`.`Visits` ;
CREATE TABLE IF NOT EXISTS `final`.`Visits` (
	`activityID` INT AUTO_INCREMENT NOT NULL,
  `activityType` VARCHAR(50),
  'Description' VARCHAR(100),
  'Cost' DECIMAL(3,2),
  'IsScheduled' BOOLEAN,
  'IsGroup' BOOLEAN,
  'IsTour' BOOLEAN,
  PRIMARY KEY (`activityID`));
ENGINE = InnoDB;


DROP TABLE IF EXISTS `final`.`ScheduledEvents` ;
CREATE TABLE IF NOT EXISTS `final`.`ScheduledEvents` (
	`eventID` INT AUTO_INCREMENT NOT NULL,
  `activityType` VARCHAR(50),
  'Description' VARCHAR(100),
  'Date' DATE(),
  'Time' TIME(),
  'Cost' DECIMAL(3,2),
  'IsScheduled' BOOLEAN,
  'IsGroup' BOOLEAN,
  'IsTour' BOOLEAN,
  FOREIGN KEY ('ProgramID'),
  PRIMARY KEY (`eventID`));
ENGINE = InnoDB;

