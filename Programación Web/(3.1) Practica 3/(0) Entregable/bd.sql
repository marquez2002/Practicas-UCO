-- phpMyAdmin SQL Dump
-- version 2.7.0-pl2
-- http://www.phpmyadmin.net
-- 
-- Servidor: oraclepr.uco.es
-- Tiempo de generación: 29-08-2024 a las 16:35:04
-- Versión del servidor: 5.1.73
-- Versión de PHP: 5.3.3
-- 
-- Base de datos: `i02jijia`
-- 

-- --------------------------------------------------------

-- 
-- Estructura de tabla para la tabla `Activity`
-- 

DROP TABLE IF EXISTS Asistent;
DROP TABLE IF EXISTS Monitor;
DROP TABLE IF EXISTS Activity;
DROP TABLE IF EXISTS Camp;
DROP TABLE IF EXISTS Inscription;
DROP TABLE IF EXISTS Camp_Activity;
DROP TABLE IF EXISTS Camp_Monitor;
DROP TABLE IF EXISTS Monitor_Activity;

CREATE TABLE `Activity` (
  `name` varchar(64) NOT NULL DEFAULT '',
  `levelEducation` varchar(64) NOT NULL DEFAULT '',
  `timetable` varchar(64) DEFAULT NULL,
  `asistents` int(3) NOT NULL,
  `numberMonitor` int(3) NOT NULL,
  PRIMARY KEY (`name`,`levelEducation`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- 
-- Volcar la base de datos para la tabla `Activity`
-- 

INSERT INTO `Activity` VALUES ('Futbol', 'JUVENIL', 'TARDE', 22, 3);
INSERT INTO `Activity` VALUES ('Padel', 'JUVENIL', 'TARDE', 8, 1);

-- --------------------------------------------------------

-- 
-- Estructura de tabla para la tabla `Asistent`
-- 

CREATE TABLE `Asistent` (
  `id` int(3) NOT NULL AUTO_INCREMENT,
  `name` varchar(64) NOT NULL,
  `surname` varchar(64) NOT NULL,
  `email` varchar(64) NOT NULL,
  `password` varchar(64) NOT NULL,
  `role` varchar(64) NOT NULL,
  `date` date NOT NULL,
  `special` tinyint(2) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=12 DEFAULT CHARSET=latin1 AUTO_INCREMENT=12 ;

-- 
-- Volcar la base de datos para la tabla `Asistent`
-- 

INSERT INTO `Asistent` VALUES (1, 'Lucia', 'Berjon', 'lucia@gmail.com', 'password', '1', '2005-01-15', 1);
INSERT INTO `Asistent` VALUES (2, 'Paco', 'Encinas', 'paco@gmail.com', 'paco1234', '0', '2009-05-10', 0);

-- --------------------------------------------------------

-- 
-- Estructura de tabla para la tabla `Camp`
-- 

CREATE TABLE `Camp` (
  `id` int(3) NOT NULL AUTO_INCREMENT,
  `startDate` date NOT NULL,
  `idMonitor` int(3) DEFAULT NULL,
  `levelEducation` varchar(64) NOT NULL,
  `special` int(3) DEFAULT NULL,
  `endDate` date NOT NULL,
  `maximunAsistent` int(3) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `fk_id_monitor` (`idMonitor`),
  KEY `fk_special` (`special`)
) ENGINE=MyISAM AUTO_INCREMENT=9 DEFAULT CHARSET=latin1 AUTO_INCREMENT=9 ;

-- 
-- Volcar la base de datos para la tabla `Camp`
-- 

INSERT INTO `Camp` VALUES (1, '2024-09-10', NULL, 'JUVENIL', NULL, '2024-09-17', 10);
INSERT INTO `Camp` VALUES (2, '2024-12-24', NULL, 'JUVENIL', NULL, '2024-12-31', 25);

-- --------------------------------------------------------

-- 
-- Estructura de tabla para la tabla `Camp_Activity`
-- 

CREATE TABLE `Camp_Activity` (
  `idCamp` int(3) NOT NULL DEFAULT '0',
  `name` varchar(64) NOT NULL DEFAULT '',
  `levelEducation` varchar(64) DEFAULT NULL,
  PRIMARY KEY (`idCamp`,`name`),
  KEY `fk_name` (`name`),
  KEY `fk_level_education` (`levelEducation`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- 
-- Volcar la base de datos para la tabla `Camp_Activity`
-- 


-- --------------------------------------------------------

-- 
-- Estructura de tabla para la tabla `Inscription`
-- 

CREATE TABLE `Inscription` (
  `idAsistent` int(3) NOT NULL DEFAULT '0',
  `idCamp` int(3) NOT NULL DEFAULT '0',
  `inscriptionDate` date NOT NULL,
  `price` float NOT NULL,
  `completada_` tinyint(1) NOT NULL,
  `cancelada_` tinyint(1) NOT NULL,
  PRIMARY KEY (`idAsistent`,`idCamp`),
  KEY `fk_id_camp` (`idCamp`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- 
-- Volcar la base de datos para la tabla `Inscription`
-- 


-- --------------------------------------------------------

-- 
-- Estructura de tabla para la tabla `Monitor`
-- 

CREATE TABLE `Monitor` (
  `id` int(3) NOT NULL AUTO_INCREMENT,
  `name` varchar(64) NOT NULL,
  `surname` varchar(64) NOT NULL,
  `special` tinyint(2) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=24 DEFAULT CHARSET=latin1 AUTO_INCREMENT=24 ;

-- 
-- Volcar la base de datos para la tabla `Monitor`
-- 

INSERT INTO `Monitor` VALUES (1, 'Jesus', 'Gil', 1);
INSERT INTO `Monitor` VALUES (2, 'Antonio', 'Casas', 0);

-- --------------------------------------------------------

-- 
-- Estructura de tabla para la tabla `Monitor_Activity`
-- 

CREATE TABLE `Monitor_Activity` (
  `idMonitor` int(3) NOT NULL DEFAULT '0',
  `name` varchar(64) NOT NULL DEFAULT '',
  `levelEducation` varchar(64) NOT NULL DEFAULT '',
  PRIMARY KEY (`idMonitor`,`name`,`levelEducation`),
  KEY `fk_name` (`name`),
  KEY `fk_level_education` (`levelEducation`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- 
-- Volcar la base de datos para la tabla `Monitor_Activity`
-- 


