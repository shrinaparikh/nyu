--
-- Host: warehouse    Database: sp4681_test2
-- ------------------------------------------------------
-- Server version	5.5.64-MariaDB

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
-- Table structure for table `albums`
--

DROP TABLE IF EXISTS `albums`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `albums` (
  `position` int(11) NOT NULL,
  `artist` varchar(45) DEFAULT NULL,
  `name` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`position`),
  KEY `artist_idx` (`artist`),
  CONSTRAINT `artist` FOREIGN KEY (`artist`) REFERENCES `artists` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `albums`
--

LOCK TABLES `albums` WRITE;
/*!40000 ALTER TABLE `albums` DISABLE KEYS */;
INSERT INTO `albums` VALUES (1,'The Strokes','The New Abnormal'),(2,'Dua Lipa','Future Nostalgia'),(3,'Laura Marling','Song For Our Daughte'),(4,'Nightwish','Human II Nature'),(5,'Lewis Capaldi','Divinely Uninspired '),(6,'Joe Satriani','Shapeshifting'),(7,'The Weeknd','After Hours'),(8,'Harry Styles','Fine Line'),(9,'Cadet','The Rated Legend'),(10,'Pearl Jam','Gigaton'),(11,'Billie Eilish','When We All Fall Asl'),(12,'Paul Heaton & Jacqui Abbott','Machester Calling'),(13,'Kidz Bop Kids','Kidz Bop 2020'),(14,'Rod Stewart','You\'re In My Heart'),(15,'Elton John','Diamonds'),(16,'Fleetwood Mac','Rumours'),(17,'Matt Monro','Stranger in Paradise'),(18,'Queen','The Platinum$
/*!40000 ALTER TABLE `albums` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `artists`
--

DROP TABLE IF EXISTS `artists`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `artists` (
  `name` varchar(45) NOT NULL,
  `position` int(11) NOT NULL,
  `weeks` int(11) DEFAULT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `artists`
--

LOCK TABLES `artists` WRITE;
/*!40000 ALTER TABLE `artists` DISABLE KEYS */;
INSERT INTO `artists` VALUES ('Arizona Zervas',0,0),('Billie Eilish',2,86),('blackbear',0,0),('Blake Shelton',0,0),('Bob Marley & The Wailers',0,0),('BTS',10,184),('Cadet',0,0),('Camila Cabello',0,0),('DaBaby',15,63),('Doja Cat',0,0),('Drake',3,303),('Dua Lipa',7,102),('Elton John',0,0),('Fleetwood Mac',0,0),('Future',0,0),('Gabby Barrett',0,0),('Harry Styles',0,0),('Joe Satriani',0,0),('John Pine',9,4),('Justin Bieber',0,0),('Kidz Bop Kids',0,0),('Laura Marling',0,0),('Lewis Capaldi',0,0),('Lil Baby',12,101),('Lil Mosey',0,0),('Lil Uzi Vert',11,130),('Luke Combs',6,164),('Maren Morris',0,0),('Maroon 5',0,0),('Matt Monro',0,0),('Megan Thee Stallion',0,0),('Nightwish',0$
/*!40000 ALTER TABLE `artists` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `songs`
--

DROP TABLE IF EXISTS `songs`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `songs` (
  `position` int(11) NOT NULL,
  `lastWeek` int(11) DEFAULT NULL,
  `peak` int(11) DEFAULT NULL,
  `duration` int(11) DEFAULT NULL,
  `name` varchar(20) DEFAULT NULL,
  `artistName` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`position`),
  KEY `artistName_idx` (`artistName`),
  CONSTRAINT `artistName` FOREIGN KEY (`artistName`) REFERENCES `artists` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `songs`
--

LOCK TABLES `songs` WRITE;
/*!40000 ALTER TABLE `songs` DISABLE KEYS */;
INSERT INTO `songs` VALUES (1,2,1,20,'Blinding Lights','The Weeknd'),(2,1,1,2,'Toosie Slide','Drake'),(3,3,1,19,'The Box','Roddy Ricch'),(4,4,2,24,'Don\'t Start Now','Dua Lipa'),(5,8,5,15,'Say So','Doja Cat'),(6,7,6,19,'Adore You','Harry Styles'),(7,6,1,33,'Circles','Post Malone'),(8,5,2,14,'Life is Good','Future'),(9,9,8,10,'Intentions','Justin Bieber'),(10,10,8,23,'everything i wanted','Billie Eilish'),(11,11,1,49,'Someone You Loved','Lewis Capaldi'),(12,13,12,19,'My Oh My','Camila Cabello'),(13,12,12,30,'The Bones','Maren Morris'),(14,14,14,5,'Savage','Megan Thee Stallion'),(15,15,2,30,'Memories','Maroon 5'),(16,18,16,10,'Blueberry Faygo','Lil Mosey'),(17,20,17,16,'$
/*!40000 ALTER TABLE `songs` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2020-04-24 20:47:19



