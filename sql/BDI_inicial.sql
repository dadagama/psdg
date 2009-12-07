DROP TABLE IF EXISTS `PSDG_usuario`;
CREATE TABLE `BDI`.`PSDG_usuario` (
	`usu_codigo` SERIAL NOT NULL AUTO_INCREMENT COMMENT 'consecutivo',
	`usu_login` VARCHAR( 20 ) NOT NULL COMMENT 'login del usuario',
	`usu_password` VARCHAR( 40 ) NOT NULL COMMENT 'contraseña del usuario',
	PRIMARY KEY ( `usu_login` )
) ENGINE = InnoDB COMMENT = 'Alamacena los usuarios que tienen acceso a la aplicación';

INSERT INTO PSDG_usuario(usu_login, usu_password) VALUES('demo','89e495e7941cf9e40e6980d14a16bf023ccd4c91');

DROP TABLE IF EXISTS `PSDG_idioma`;
CREATE TABLE IF NOT EXISTS `PSDG_idioma` (
	`idi_codigo` SERIAL NOT NULL AUTO_INCREMENT COMMENT 'consecutivo',
	`idi_texto` varchar(500) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Mensaje en el idioma por defecto (ingles)',
	`idi_lenguaje` char(2) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Abreviatura del lenguaje en el que se encuentra la traducción',
	`idi_traduccion` varchar(500) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Traducción del mensaje',
	KEY `idi_texto` (`idi_texto`(333))
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

INSERT INTO PSDG_idioma VALUES(1,'Connection','es','Conexión');
INSERT INTO PSDG_idioma VALUES(2,'Connection name:','es','Nombre conexión:');
INSERT INTO PSDG_idioma VALUES(3,'Name that identifies the connection in the application','es','Nombre que identifica la conexión en la aplicación');
INSERT INTO PSDG_idioma VALUES(4,'User:','es','Usuario:');
INSERT INTO PSDG_idioma VALUES(5,'User that connects to the database','es','Usuario con el que se conecta a la Base de datos');
INSERT INTO PSDG_idioma VALUES(6,'Password:','es','Contraseña:');
INSERT INTO PSDG_idioma VALUES(7,'User\'s password in the database','es','Contraseña del usuario en la Base de datos');
INSERT INTO PSDG_idioma VALUES(8,'Set','es','Establecer');
/*INSERT INTO PSDG_usuario VALUES(9,'Add this link to the list of connections','es','Agrega esta conexión a la lista de conexiones');
INSERT INTO PSDG_usuario VALUES(10,'','es','');
INSERT INTO PSDG_usuario VALUES(11,'','es','');
INSERT INTO PSDG_usuario VALUES(12,'','es','');
INSERT INTO PSDG_usuario VALUES(13,'','es','');
INSERT INTO PSDG_usuario VALUES(14,'','es','');*/
