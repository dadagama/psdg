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
/*login*/
INSERT INTO PSDG_idioma VALUES('lbl_login','es','Iniciar Sesión');
INSERT INTO PSDG_idioma VALUES('lbl_usu_login','es','Usuario:');
INSERT INTO PSDG_idioma VALUES('lbl_usu_password','es','Contraseña:');
INSERT INTO PSDG_idioma VALUES('ttp_usu_login','es','Digite su nombre de usuario');
INSERT INTO PSDG_idioma VALUES('ttp_usu_password','es','Digite su contraseña');
INSERT INTO PSDG_idioma VALUES('ttp_chk_lang_en','es','Inglés');
INSERT INTO PSDG_idioma VALUES('ttp_chk_lang_es','es','Español');
INSERT INTO PSDG_idioma VALUES('btn_login','es','Iniciar Sesión');
/*conexion*/
INSERT INTO PSDG_idioma VALUES('lbl_conexion','es','Configuración de conexiones');
INSERT INTO PSDG_idioma VALUES('lbl_con_tipo','es','Conectar con:');
INSERT INTO PSDG_idioma VALUES('ttp_con_tipo','es','Tipo de conexión');
INSERT INTO PSDG_idioma VALUES('opt_con_tipo_archivo','es','Archivo');
INSERT INTO PSDG_idioma VALUES('opt_con_tipo_bd','es','Base de datos');
INSERT INTO PSDG_idioma VALUES('lbl_con_nombre','es','Nombre conexión:');
INSERT INTO PSDG_idioma VALUES('ttp_con_nombre','es','Nombre que se utilizará para identificar la conexión');
INSERT INTO PSDG_idioma VALUES('lbl_con_usuario','es','Usuario:');
INSERT INTO PSDG_idioma VALUES('ttp_con_usuario','es','Usuario con el que se conecta a la Base de datos');
INSERT INTO PSDG_idioma VALUES('lbl_con_password','es','Contraseña:');
INSERT INTO PSDG_idioma VALUES('ttp_con_password','es','Contraseña del usuario para la Base de datos');
INSERT INTO PSDG_idioma VALUES('btn_establecer','es','Añadir');
INSERT INTO PSDG_idioma VALUES('lbl_conexiones_establecidas','es','Conexiones establecidas');
/**************************************************************************************************************/
/*INGLES*/
/*login*/
INSERT INTO PSDG_idioma VALUES('lbl_login','en','Log in');
INSERT INTO PSDG_idioma VALUES('lbl_usu_login','en','User:');
INSERT INTO PSDG_idioma VALUES('lbl_usu_password','en','Password:');
INSERT INTO PSDG_idioma VALUES('ttp_usu_login','en','Type your user name');
INSERT INTO PSDG_idioma VALUES('ttp_usu_password','en','Type your password');
INSERT INTO PSDG_idioma VALUES('ttp_chk_lang_en','en','English');
INSERT INTO PSDG_idioma VALUES('ttp_chk_lang_es','en','Spanish');
INSERT INTO PSDG_idioma VALUES('btn_login','en','Sign in');
/*conexion*/
INSERT INTO PSDG_idioma VALUES('lbl_conexion','en','Connection setup');
INSERT INTO PSDG_idioma VALUES('lbl_con_tipo','en','Link to:');
INSERT INTO PSDG_idioma VALUES('ttp_con_tipo','en','Connection type');
INSERT INTO PSDG_idioma VALUES('opt_con_tipo_archivo','en','File');
INSERT INTO PSDG_idioma VALUES('opt_con_tipo_bd','en','Database');
INSERT INTO PSDG_idioma VALUES('lbl_con_nombre','en','Connection name:');
INSERT INTO PSDG_idioma VALUES('ttp_con_nombre','en','Name that identifies the connection in the application');
INSERT INTO PSDG_idioma VALUES('lbl_con_usuario','en','User:');
INSERT INTO PSDG_idioma VALUES('ttp_con_usuario','en','User that connects to the database');
INSERT INTO PSDG_idioma VALUES('lbl_con_password','en','Password:');
INSERT INTO PSDG_idioma VALUES('ttp_con_password','en','User\'s password in the database');
INSERT INTO PSDG_idioma VALUES('btn_establecer','en','Add');
INSERT INTO PSDG_idioma VALUES('lbl_conexiones_establecidas','en','Established connections');

