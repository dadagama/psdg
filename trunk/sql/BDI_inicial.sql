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
/*conexiones*/
INSERT INTO PSDG_idioma VALUES('lgn_con_configurar_conexion','es','Configuración de conexiones');
INSERT INTO PSDG_idioma VALUES('lbl_con_tipo','es','Conectar con:');
INSERT INTO PSDG_idioma VALUES('ttp_con_tipo','es','Tipo de conexión');
INSERT INTO PSDG_idioma VALUES('opt_con_tipo_archivo','es','Archivo');
INSERT INTO PSDG_idioma VALUES('opt_con_tipo_bd','es','Base de datos');
INSERT INTO PSDG_idioma VALUES('opt_con_tipo_biblioteca','es','Biblioteca');
INSERT INTO PSDG_idioma VALUES('lbl_con_nombre','es','Nombre conexión:');
INSERT INTO PSDG_idioma VALUES('ttp_con_nombre','es','Nombre que se utilizará para identificar la conexión');
INSERT INTO PSDG_idioma VALUES('lgn_con_datos_conexion','es','Datos de conexión');
INSERT INTO PSDG_idioma VALUES('lbl_con_nombre_db','es','Nombre BD:');
INSERT INTO PSDG_idioma VALUES('ttp_con_nombre_db','es','Nombre de la Base de datos');
INSERT INTO PSDG_idioma VALUES('lbl_con_usuario','es','Usuario:');
INSERT INTO PSDG_idioma VALUES('ttp_con_usuario','es','Usuario con el que se conecta a la Base de datos');
INSERT INTO PSDG_idioma VALUES('lbl_con_password','es','Contraseña:');
INSERT INTO PSDG_idioma VALUES('ttp_con_password','es','Contraseña del usuario con el que se conecta la Base de datos');
INSERT INTO PSDG_idioma VALUES('btn_establecer','es','Añadir');
INSERT INTO PSDG_idioma VALUES('lgn_con_conexiones_establecidas','es','Conexiones establecidas');
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
/*conexiones*/
INSERT INTO PSDG_idioma VALUES('lgn_con_configurar_conexion','en','Connection setup');
INSERT INTO PSDG_idioma VALUES('lbl_con_tipo','en','Link to:');
INSERT INTO PSDG_idioma VALUES('ttp_con_tipo','en','Connection type');
INSERT INTO PSDG_idioma VALUES('opt_con_tipo_archivo','en','File');
INSERT INTO PSDG_idioma VALUES('opt_con_tipo_bd','en','Database');
INSERT INTO PSDG_idioma VALUES('opt_con_tipo_biblioteca','en','Library');
INSERT INTO PSDG_idioma VALUES('lbl_con_nombre','en','Connection name:');
INSERT INTO PSDG_idioma VALUES('ttp_con_nombre','en','Name that identifies the connection in the application');
INSERT INTO PSDG_idioma VALUES('lgn_con_datos_conexion','en','Connection data');
INSERT INTO PSDG_idioma VALUES('lbl_con_nombre_db','en','DB name:');
INSERT INTO PSDG_idioma VALUES('ttp_con_nombre_db','en','Database name');
INSERT INTO PSDG_idioma VALUES('lbl_con_usuario','en','User:');
INSERT INTO PSDG_idioma VALUES('ttp_con_usuario','en','User that connects to the database');
INSERT INTO PSDG_idioma VALUES('lbl_con_password','en','Password:');
INSERT INTO PSDG_idioma VALUES('ttp_con_password','en','User\'s password in the database');
INSERT INTO PSDG_idioma VALUES('btn_establecer','en','Add');
INSERT INTO PSDG_idioma VALUES('lgn_con_conexiones_establecidas','en','Established connections');


DROP TABLE IF EXISTS `PSDG_mensaje_ayuda`;
CREATE TABLE IF NOT EXISTS `PSDG_mensaje_ayuda` (
	`ayu_codigo` INTEGER NOT NULL COMMENT 'consecutivo',
	`ayu_lenguaje` char(2) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Abreviatura del lenguaje en el que se encuentra el mensaje',
	`ayu_mensaje` varchar(800) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Texto del mensaje de ayuda',
	PRIMARY KEY ( `ayu_codigo`,`ayu_lenguaje` )
) ENGINE= InnoDB COMMENT = 'Almacena los mensajes de ayuda en todos los idiomas';

/*ESPAÑOL*/
/*conexiones*/
INSERT INTO PSDG_mensaje_ayuda VALUES('1','es','Aquí se definen los parámetros para conectar con fuentes externas de información que proporcionen tipos de datos adicionales (bases de datos, archivos de texto plano ó bibliotecas).<br/>Tambien se deben definir <b>como mínimo</b> los parámetros de conexion a la Base de datos objetivo (BDO) que será poblada.');
/**************************************************************************************************************/
/*INGLES*/
/*conexiones*/
INSERT INTO PSDG_mensaje_ayuda VALUES('1','en','Here you define the parameters to connect to external information sources that provide additional data types (databases, plain text files or libraries).<br/>Also you should define <b>at least</b> the parameters of connection to the Target Database (BDO), which will be populated.');