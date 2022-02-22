-- MySQL dump 10.13  Distrib 8.0.13, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: istio
-- ------------------------------------------------------
-- Server version	8.0.13

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
 SET NAMES utf8 ;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `hostvips`
--

DROP TABLE IF EXISTS `hostvips`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
 SET character_set_client = utf8mb4 ;
CREATE TABLE `hostvips` (
  `HostVIPs` int(11) NOT NULL,
  `Hostname` varchar(45) NOT NULL,
  `ClusterVIPsID` int(11) NOT NULL,
  `ClusterVIPsAdress` varchar(45) NOT NULL,
  PRIMARY KEY (`Hostname`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `hostvips`
--

LOCK TABLES `hostvips` WRITE;
/*!40000 ALTER TABLE `hostvips` DISABLE KEYS */;
/*!40000 ALTER TABLE `hostvips` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `istio_model`
--

DROP TABLE IF EXISTS `istio_model`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
 SET character_set_client = utf8mb4 ;
CREATE TABLE `istio_model` (
  `id` char(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `istio_model`
--

LOCK TABLES `istio_model` WRITE;
/*!40000 ALTER TABLE `istio_model` DISABLE KEYS */;
INSERT INTO `istio_model` VALUES ('1'),('2');
/*!40000 ALTER TABLE `istio_model` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `istioendpoint`
--

DROP TABLE IF EXISTS `istioendpoint`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
 SET character_set_client = utf8mb4 ;
CREATE TABLE `istioendpoint` (
  `Endpoint` int(11) NOT NULL,
  `Labels` varchar(45) NOT NULL,
  `Address` varchar(45) NOT NULL,
  `ServicePortName` varchar(45) DEFAULT NULL,
  `ServiceAccount` varchar(45) DEFAULT NULL,
  `Network` varchar(45) DEFAULT NULL,
  `LabelLocality` varchar(45) DEFAULT NULL,
  `ClusterID` varchar(45) DEFAULT NULL,
  `EndpointPort` int(11) DEFAULT NULL,
  `LbWeight` int(11) DEFAULT NULL,
  `TLSMode` varchar(45) DEFAULT NULL,
  `Namespace` varchar(45) DEFAULT NULL,
  `WorkloadName` varchar(45) DEFAULT NULL,
  `HostName` varchar(45) DEFAULT NULL,
  `SubDomain` varchar(45) DEFAULT NULL,
  `TunnelAbility` int(11) DEFAULT NULL,
  PRIMARY KEY (`Endpoint`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `istioendpoint`
--

LOCK TABLES `istioendpoint` WRITE;
/*!40000 ALTER TABLE `istioendpoint` DISABLE KEYS */;
INSERT INTO `istioendpoint` VALUES (1,'1','127.0.0.1','test','jyx',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),(2,'2','127.0.0.1','test','jyx',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
/*!40000 ALTER TABLE `istioendpoint` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `portlists`
--

DROP TABLE IF EXISTS `portlists`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
 SET character_set_client = utf8mb4 ;
CREATE TABLE `portlists` (
  `PortLists` int(11) NOT NULL,
  `Name` varchar(45) NOT NULL,
  `Port` int(11) NOT NULL,
  `Protocol` varchar(45) NOT NULL,
  PRIMARY KEY (`Name`,`Port`,`Protocol`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `portlists`
--

LOCK TABLES `portlists` WRITE;
/*!40000 ALTER TABLE `portlists` DISABLE KEYS */;
INSERT INTO `portlists` VALUES (1,'test',8888,'http');
/*!40000 ALTER TABLE `portlists` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `service`
--

DROP TABLE IF EXISTS `service`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
 SET character_set_client = utf8mb4 ;
CREATE TABLE `service` (
  `ServiceAttributes` int(11) NOT NULL,
  `PortList` int(11) NOT NULL,
  `ServiceAccounts` varchar(45) NOT NULL,
  `HostVIPs` int(11) NOT NULL,
  `Address` varchar(45) NOT NULL,
  `Resolution` int(11) NOT NULL,
  `MeshExternal` tinyint(4) DEFAULT NULL,
  `ResourceVersion` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`ServiceAttributes`,`ServiceAccounts`,`PortList`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `service`
--

LOCK TABLES `service` WRITE;
/*!40000 ALTER TABLE `service` DISABLE KEYS */;
INSERT INTO `service` VALUES (1,1,'jyx',127,'127.0.0.1',2,1,'1.0.0'),(1,1,'wz',127,'127.0.0.1',2,1,'1.0.1'),(2,1,'jyx',127,'127.0.0.1',2,1,'1.0.0'),(2,1,'wz',127,'127.0.0.1',2,1,'1.0.1');
/*!40000 ALTER TABLE `service` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `service_labels`
--

DROP TABLE IF EXISTS `service_labels`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
 SET character_set_client = utf8mb4 ;
CREATE TABLE `service_labels` (
  `Labels` int(11) NOT NULL,
  `keyName` varchar(45) NOT NULL,
  `valueName` varchar(45) NOT NULL,
  PRIMARY KEY (`Labels`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `service_labels`
--

LOCK TABLES `service_labels` WRITE;
/*!40000 ALTER TABLE `service_labels` DISABLE KEYS */;
INSERT INTO `service_labels` VALUES (1,'foo','bar'),(2,'kitty','cat');
/*!40000 ALTER TABLE `service_labels` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `serviceattributes`
--

DROP TABLE IF EXISTS `serviceattributes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
 SET character_set_client = utf8mb4 ;
CREATE TABLE `serviceattributes` (
  `ServiceAttributes` int(11) NOT NULL,
  `ServiceAttributescol` varchar(45) NOT NULL,
  `Name` varchar(45) NOT NULL,
  `Namespace` varchar(45) NOT NULL,
  `Labels` varchar(45) DEFAULT NULL,
  `ExportTo` varchar(45) DEFAULT NULL,
  `LabelSelectors` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`ServiceAttributes`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `serviceattributes`
--

LOCK TABLES `serviceattributes` WRITE;
/*!40000 ALTER TABLE `serviceattributes` DISABLE KEYS */;
INSERT INTO `serviceattributes` VALUES (1,'1','excemple','127.0.0.1','1','hqe','1'),(2,'2','test','127.0.0.1','2','wz','2');
/*!40000 ALTER TABLE `serviceattributes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `serviceinstance`
--

DROP TABLE IF EXISTS `serviceinstance`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
 SET character_set_client = utf8mb4 ;
CREATE TABLE `serviceinstance` (
  `ServiceAttributes` int(11) NOT NULL,
  `Port` int(11) NOT NULL,
  `Endpoint` int(11) NOT NULL,
  PRIMARY KEY (`ServiceAttributes`,`Port`,`Endpoint`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `serviceinstance`
--

LOCK TABLES `serviceinstance` WRITE;
/*!40000 ALTER TABLE `serviceinstance` DISABLE KEYS */;
INSERT INTO `serviceinstance` VALUES (1,8888,1),(2,8888,2);
/*!40000 ALTER TABLE `serviceinstance` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping events for database 'istio'
--

--
-- Dumping routines for database 'istio'
--
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-01-11 21:31:16
