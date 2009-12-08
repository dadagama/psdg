DROP TABLE IF EXISTS `PSDG_usuario`;
CREATE TABLE `BDI`.`PSDG_usuario` (
	`usu_codigo` SERIAL NOT NULL AUTO_INCREMENT COMMENT 'consecutivo',
	`usu_login` VARCHAR( 20 ) NOT NULL COMMENT 'login del usuario',
	`usu_password` VARCHAR( 40 ) NOT NULL COMMENT 'contraseña del usuario',
	PRIMARY KEY ( `usu_login` )
) ENGINE = InnoDB COMMENT = 'Almacena los usuarios que tienen acceso a la aplicación';

INSERT INTO PSDG_usuario(usu_login, usu_password) VALUES('demo','89e495e7941cf9e40e6980d14a16bf023ccd4c91');

DROP TABLE IF EXISTS `PSDG_idioma`;
CREATE TABLE IF NOT EXISTS `PSDG_idioma` (
	`idi_texto` varchar(100) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Etiqueta a traducir',
	`idi_lenguaje` char(2) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Abreviatura del lenguaje en el que se encuentra la traducción',
	`idi_traduccion` varchar(500) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Traducción del mensaje',
	PRIMARY KEY ( `idi_texto`,`idi_lenguaje` )
) ENGINE= InnoDB COMMENT = 'Almacena las traducciones de las etiquetas';

/*ESPAÑOL*/
INSERT INTO PSDG_idioma VALUES('lbl_conexion','es','Conexión');
INSERT INTO PSDG_idioma VALUES('lbl_con_nombre','es','Nombre conexión:');
INSERT INTO PSDG_idioma VALUES('ttp_con_nombre','es','Nombre que identifica la conexión en la aplicación');
INSERT INTO PSDG_idioma VALUES('lbl_con_usuario','es','Usuario:');
INSERT INTO PSDG_idioma VALUES('ttp_con_usuario','es','Usuario con el que se conecta a la Base de datos');
INSERT INTO PSDG_idioma VALUES('lbl_con_password','es','Contraseña:');
INSERT INTO PSDG_idioma VALUES('ttp_con_password','es','Contraseña del usuario en la Base de datos');
INSERT INTO PSDG_idioma VALUES('btn_establecer','es','Establecer');
/*INGLES*/
INSERT INTO PSDG_idioma VALUES('lbl_conexion','en','Connection');
INSERT INTO PSDG_idioma VALUES('lbl_con_nombre','en','Connection name:');
INSERT INTO PSDG_idioma VALUES('ttp_con_nombre','en','Name that identifies the connection in the application');
INSERT INTO PSDG_idioma VALUES('lbl_con_usuario','en','User:');
INSERT INTO PSDG_idioma VALUES('ttp_con_usuario','en','User that connects to the database');
INSERT INTO PSDG_idioma VALUES('lbl_con_password','en','Password:');
INSERT INTO PSDG_idioma VALUES('ttp_con_password','en','User\'s password in the database');
INSERT INTO PSDG_idioma VALUES('btn_establecer','en','Set');

