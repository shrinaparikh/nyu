-- MySQL Script generated by MySQL Workbench
-- Tue Mar 24 15:54:38 2020
-- Model: New Model    Version: 1.0
-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema asg5
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema asg5
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `asg5` DEFAULT CHARACTER SET utf8 ;
USE `asg5` ;

-- -----------------------------------------------------
-- Table `asg5`.`Instructors`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `asg5`.`Instructors` ;

CREATE TABLE IF NOT EXISTS `asg5`.`Instructors` (
  `N Number` VARCHAR(10) NOT NULL,
  `email` VARCHAR(20) NULL,
  `name` TEXT(20) NULL,
  PRIMARY KEY (`N Number`));


-- -----------------------------------------------------
-- Table `asg5`.`Languages`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `asg5`.`Languages` ;

CREATE TABLE IF NOT EXISTS `asg5`.`Languages` (
  `language` TEXT(20) NOT NULL,
  PRIMARY KEY (`language`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `asg5`.`Divisions`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `asg5`.`Divisions` ;

CREATE TABLE IF NOT EXISTS `asg5`.`Divisions` (
  `Division` TEXT(20) NOT NULL,
  PRIMARY KEY (`Division`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `asg5`.`Departments`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `asg5`.`Departments` ;

CREATE TABLE IF NOT EXISTS `asg5`.`Departments` (
  `Department Name` TEXT(20) NOT NULL,
  `Division` TEXT(20) NULL,
  PRIMARY KEY (`Department Name`),
  INDEX `Division_idx` (`Division` ASC) VISIBLE,
  CONSTRAINT `Division`
    FOREIGN KEY (`Division`)
    REFERENCES `asg5`.`Divisions` (`Division`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `asg5`.`courses`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `asg5`.`courses` ;

CREATE TABLE IF NOT EXISTS `asg5`.`courses` (
  `Course number` VARCHAR(20) NOT NULL,
  `department` TEXT(20) NULL,
  `course title` TEXT(20) NULL,
  `instructor` VARCHAR(10) NULL,
  `credit hours` INT NULL,
  PRIMARY KEY (`Course number`),
  INDEX `department_idx` (`department` ASC) VISIBLE,
  INDEX `instructor_idx` (`instructor` ASC) VISIBLE,
  CONSTRAINT `department`
    FOREIGN KEY (`department`)
    REFERENCES `asg5`.`Departments` (`Department Name`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `instructor`
    FOREIGN KEY (`instructor`)
    REFERENCES `asg5`.`Instructors` (`N Number`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `asg5`.`formats`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `asg5`.`formats` ;

CREATE TABLE IF NOT EXISTS `asg5`.`formats` (
  `format` TEXT(20) NOT NULL,
  PRIMARY KEY (`format`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `asg5`.`books`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `asg5`.`books` ;

CREATE TABLE IF NOT EXISTS `asg5`.`books` (
  `title` TEXT(20) NULL,
  `author` VARCHAR(20) NULL,
  `publisher` TEXT(20) NULL,
  `format` TEXT(20) NULL,
  `hard copy` TINYINT NULL,
  `year` INT NULL,
  `pages` INT NULL,
  `ISBN` VARCHAR(20) NOT NULL,
  `language` TEXT(20) NULL,
  INDEX `format_idx` (`format` ASC) VISIBLE,
  PRIMARY KEY (`ISBN`),
  INDEX `language_idx` (`language` ASC) VISIBLE,
  CONSTRAINT `format`
    FOREIGN KEY (`format`)
    REFERENCES `asg5`.`formats` (`format`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `language`
    FOREIGN KEY (`language`)
    REFERENCES `asg5`.`Languages` (`language`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `asg5`.`RequiredBooks`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `asg5`.`RequiredBooks` ;

CREATE TABLE IF NOT EXISTS `asg5`.`RequiredBooks` (
  `Entry Number` INT NOT NULL AUTO_INCREMENT,
  `ISBN` VARCHAR(20) NULL,
  `course` VARCHAR(20) NULL,
  `required` TINYINT NULL,
  `copies requested` INT NULL,
  PRIMARY KEY (`Entry Number`),
  INDEX `ISBN_idx` (`ISBN` ASC) VISIBLE,
  INDEX `course_idx` (`course` ASC) VISIBLE,
  CONSTRAINT `ISBN`
    FOREIGN KEY (`ISBN`)
    REFERENCES `asg5`.`books` (`ISBN`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `course`
    FOREIGN KEY (`course`)
    REFERENCES `asg5`.`courses` (`Course number`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
