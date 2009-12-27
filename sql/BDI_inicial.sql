DROP TABLE IF EXISTS `PSDG_conexion`;
DROP TABLE IF EXISTS `PSDG_usuario`;
DROP TABLE IF EXISTS `PSDG_idioma`;
DROP TABLE IF EXISTS `PSDG_mensaje_ayuda`;


CREATE TABLE `BDI`.`PSDG_usuario` (
	`usu_login` VARCHAR( 20 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'login del usuario',
	`usu_password` VARCHAR( 40 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'contraseña del usuario',
	PRIMARY KEY ( `usu_login` )
) ENGINE = InnoDB COMMENT = 'Almacena los usuarios que tienen acceso a la aplicación';

CREATE TABLE IF NOT EXISTS `PSDG_conexion` (
	`con_nombre` varchar(50) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Nombre asignado a la conexión',
	`con_usu_login` varchar(20) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Nombre asignado a la conexión',
	`con_tipo` varchar(10) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Tipo de fuente al que se conectará',
	`con_parametros` varchar(800) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Parametros para realizar la conexión, con el formato p1:v1,p2:v2, ... ,pn:vn',
	PRIMARY KEY ( `con_nombre`, `con_usu_login`, `con_tipo`),
	FOREIGN KEY (`con_usu_login`) REFERENCES `PSDG_usuario` (`usu_login`)
) ENGINE= InnoDB COMMENT = 'Almacena las conexiones a fuentes de datos externas a la aplicacion';
INSERT INTO PSDG_usuario(usu_login, usu_password) VALUES('demo','89e495e7941cf9e40e6980d14a16bf023ccd4c91');

CREATE TABLE IF NOT EXISTS `PSDG_idioma` (
	`idi_texto` varchar(100) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Etiqueta a traducir',
	`idi_lenguaje` char(2) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Abreviatura del lenguaje en el que se encuentra la traducción',
	`idi_traduccion` varchar(500) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Traducción del mensaje',
	PRIMARY KEY ( `idi_texto`,`idi_lenguaje` )
) ENGINE= InnoDB COMMENT = 'Almacena las traducciones de las etiquetas';

/*ESPAÑOL*/
/*general*/
INSERT INTO PSDG_idioma VALUES('ttp_help','es','Haga clic para obtener ayuda sobre esta sección.');
/*login*/
INSERT INTO PSDG_idioma VALUES('lbl_login','es','Iniciar Sesión');
INSERT INTO PSDG_idioma VALUES('lbl_usu_login','es','Usuario');
INSERT INTO PSDG_idioma VALUES('lbl_usu_password','es','Contraseña');
INSERT INTO PSDG_idioma VALUES('ttp_usu_login','es','Digite su nombre de usuario');
INSERT INTO PSDG_idioma VALUES('ttp_usu_password','es','Digite su contraseña');
INSERT INTO PSDG_idioma VALUES('ttp_chk_lang_en','es','Inglés');
INSERT INTO PSDG_idioma VALUES('ttp_chk_lang_es','es','Español');
INSERT INTO PSDG_idioma VALUES('btn_login','es','Iniciar Sesión');
/*conexiones*/
INSERT INTO PSDG_idioma VALUES('con_lgn_configurar_conexion','es','Configuración de conexiones');
INSERT INTO PSDG_idioma VALUES('con_lbl_tipo','es','Conectar con');
INSERT INTO PSDG_idioma VALUES('con_ttp_tipo','es','Tipo de conexión');
INSERT INTO PSDG_idioma VALUES('con_opt_tipo_archivo','es','Archivo');
INSERT INTO PSDG_idioma VALUES('con_opt_tipo_bd','es','Base de datos');
INSERT INTO PSDG_idioma VALUES('con_opt_tipo_biblioteca','es','Biblioteca');
INSERT INTO PSDG_idioma VALUES('con_lbl_nombre','es','Nombre conexión');
INSERT INTO PSDG_idioma VALUES('con_ttp_nombre','es','Nombre que se utilizará para identificar la conexión');
INSERT INTO PSDG_idioma VALUES('con_lgn_datos_conexion','es','Parámetros de conexión');
INSERT INTO PSDG_idioma VALUES('con_lbl_servidor','es','Servidor');
INSERT INTO PSDG_idioma VALUES('con_ttp_servidor','es','URL del servidor');
INSERT INTO PSDG_idioma VALUES('con_lbl_nombre_bd','es','Nombre BD');
INSERT INTO PSDG_idioma VALUES('con_ttp_nombre_bd','es','Nombre de la Base de datos');
INSERT INTO PSDG_idioma VALUES('con_lbl_usuario','es','Usuario');
INSERT INTO PSDG_idioma VALUES('con_ttp_usuario','es','Usuario con el que se conecta a la Base de datos');
INSERT INTO PSDG_idioma VALUES('con_lbl_password','es','Contraseña');
INSERT INTO PSDG_idioma VALUES('con_ttp_password','es','Contraseña del usuario con el que se conecta la Base de datos');
INSERT INTO PSDG_idioma VALUES('con_lbl_separador','es','Caracter separador');
INSERT INTO PSDG_idioma VALUES('con_ttp_separador','es','Caracter que se utiliza para separar los valores');
INSERT INTO PSDG_idioma VALUES('con_lbl_nombre_archivo','es','Archivo');
INSERT INTO PSDG_idioma VALUES('con_ttp_nombre_archivo','es','Ruta del archivo de texto plano a importar');
INSERT INTO PSDG_idioma VALUES('con_lbl_nombre_biblioteca','es','Biblioteca');
INSERT INTO PSDG_idioma VALUES('con_ttp_nombre_biblioteca','es','Ruta de la biblioteca a importar');
INSERT INTO PSDG_idioma VALUES('con_btn_establecer','es','Añadir');
INSERT INTO PSDG_idioma VALUES('con_lgn_conexiones_establecidas','es','Conexiones establecidas');
INSERT INTO PSDG_idioma VALUES('con_ttp_siguiente','es','Establecer restricciones');
/*restricciones*/
INSERT INTO PSDG_idioma VALUES('res_lgn_estructura_bd','es','Estructura de la BDO');
INSERT INTO PSDG_idioma VALUES('res_lgn_detalle','es','Detalle');
INSERT INTO PSDG_idioma VALUES('res_ttp_anterior','es','Establecer conexiones');
INSERT INTO PSDG_idioma VALUES('res_ttp_siguiente','es','Establecer tipo de salida');
/**************************************************************************************************************/
/*INGLES*/
/*general*/
INSERT INTO PSDG_idioma VALUES('ttp_help','en','Click for help on this section.');
/*login*/
INSERT INTO PSDG_idioma VALUES('lbl_login','en','Log in');
INSERT INTO PSDG_idioma VALUES('lbl_usu_login','en','User');
INSERT INTO PSDG_idioma VALUES('lbl_usu_password','en','Password');
INSERT INTO PSDG_idioma VALUES('ttp_usu_login','en','Type your user name');
INSERT INTO PSDG_idioma VALUES('ttp_usu_password','en','Type your password');
INSERT INTO PSDG_idioma VALUES('ttp_chk_lang_en','en','English');
INSERT INTO PSDG_idioma VALUES('ttp_chk_lang_es','en','Spanish');
INSERT INTO PSDG_idioma VALUES('btn_login','en','Sign in');
/*conexiones*/
INSERT INTO PSDG_idioma VALUES('con_lgn_configurar_conexion','en','Connection setup');
INSERT INTO PSDG_idioma VALUES('con_lbl_tipo','en','Link to');
INSERT INTO PSDG_idioma VALUES('con_ttp_tipo','en','Connection type');
INSERT INTO PSDG_idioma VALUES('con_opt_tipo_archivo','en','File');
INSERT INTO PSDG_idioma VALUES('con_opt_tipo_bd','en','Database');
INSERT INTO PSDG_idioma VALUES('con_opt_tipo_biblioteca','en','Library');
INSERT INTO PSDG_idioma VALUES('con_lbl_nombre','en','Connection name');
INSERT INTO PSDG_idioma VALUES('con_ttp_nombre','en','Name that identifies the connection in the application');
INSERT INTO PSDG_idioma VALUES('con_lgn_datos_conexion','en','Connection parameters');
INSERT INTO PSDG_idioma VALUES('con_lbl_servidor','en','Server');
INSERT INTO PSDG_idioma VALUES('con_ttp_servidor','en','URL Server');
INSERT INTO PSDG_idioma VALUES('con_lbl_nombre_bd','en','DB name');
INSERT INTO PSDG_idioma VALUES('con_ttp_nombre_bd','en','Database name');
INSERT INTO PSDG_idioma VALUES('con_lbl_usuario','en','User');
INSERT INTO PSDG_idioma VALUES('con_ttp_usuario','en','User that connects to the database');
INSERT INTO PSDG_idioma VALUES('con_lbl_password','en','Password');
INSERT INTO PSDG_idioma VALUES('con_ttp_password','en','User\'s password in the database');
INSERT INTO PSDG_idioma VALUES('con_lbl_separador','en','Separator character');
INSERT INTO PSDG_idioma VALUES('con_ttp_separador','en','Character used to separate the values');
INSERT INTO PSDG_idioma VALUES('con_lbl_nombre_archivo','en','File');
INSERT INTO PSDG_idioma VALUES('con_ttp_nombre_archivo','en','URL plain text file to import');
INSERT INTO PSDG_idioma VALUES('con_lbl_nombre_biblioteca','en','Library');
INSERT INTO PSDG_idioma VALUES('con_ttp_nombre_biblioteca','en','URL library to import');
INSERT INTO PSDG_idioma VALUES('con_btn_establecer','en','Add');
INSERT INTO PSDG_idioma VALUES('con_lgn_conexiones_establecidas','en','Established connections');
INSERT INTO PSDG_idioma VALUES('con_ttp_siguiente','en','Set restrictions');
/*restricciones*/
INSERT INTO PSDG_idioma VALUES('res_lgn_estructura_bd','en','BDO structure');
INSERT INTO PSDG_idioma VALUES('res_lgn_detalle','en','Detalle');
INSERT INTO PSDG_idioma VALUES('res_ttp_anterior','en','Set Connections');
INSERT INTO PSDG_idioma VALUES('res_ttp_siguiente','en','Set output type');




CREATE TABLE IF NOT EXISTS `PSDG_mensaje_ayuda` (
	`ayu_nombre_boton` varchar(50) NOT NULL COMMENT 'Nombre del botón al que pertenece el mensaje de ayuda',
	`ayu_lenguaje` char(2) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Abreviatura del lenguaje en el que se encuentra el mensaje',
	`ayu_mensaje` varchar(800) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Texto del mensaje de ayuda',
	PRIMARY KEY ( `ayu_nombre_boton`,`ayu_lenguaje` )
) ENGINE= InnoDB COMMENT = 'Almacena los mensajes de ayuda en todos los idiomas';

/*ESPAÑOL*/
/*conexiones*/
INSERT INTO PSDG_mensaje_ayuda VALUES('con_btn_help_1','es','Aquí se definen los parámetros para conectar con fuentes externas de información que proporcionen tipos de datos adicionales (bases de datos, archivos de texto plano ó bibliotecas).<br/><br/>Tambien se deben definir <b>como mínimo</b> los parámetros de conexion a la Base de datos objetivo (<b>BDO</b>) que será poblada.<br/><br/>Toda la informacion se almacena en la Base de Datos Interna (<b>BDI</b>).');
INSERT INTO PSDG_mensaje_ayuda VALUES('con_btn_help_2','es','Aquí se muestran todas las conexiones que se establecieron satisfactoriamente.<br/><br/>Puede eliminar una conexión a una determinada fuente haciendo clic en su respectivo botón <b>Eliminar</b>.');
/*RESTRICCIONES*/
INSERT INTO PSDG_mensaje_ayuda VALUES('res_btn_help_1','es','Esta es la estructura de la base de datos que será poblada (<b>BDO</b>).<br/><br/>Haz clic en cada una de las tablas y campos de la BDO para configurar sus parámetros en la ventana <b>Detalle</b>.');
INSERT INTO PSDG_mensaje_ayuda VALUES('res_btn_help_2','es','Aquí se establecen los parámetros para poblar cada una de las tablas y campos.<br/><br/>Si no desea poblar un determinado campo ó tabla de la BDO, seleccione el valor <b>No llenar</b>.');
/**************************************************************************************************************/
/*INGLES*/
/*conexiones*/
INSERT INTO PSDG_mensaje_ayuda VALUES('con_btn_help_1','en','Here you define the parameters to connect to external information sources that provide additional data types (databases, plain text files or libraries).<br/><br/>Also you should define <b>at least</b> the parameters of connection to the Target Database (<b>BDO</b>), which will be populated.<br/><br/>All information is stored in the Internal Database (<b>BDI</b>).');
INSERT INTO PSDG_mensaje_ayuda VALUES('con_btn_help_2','en','Here are all the connections that were established successfully. You can delete a connection to a particular source by clicking on its respective <b>Remove</b> button.');
/*RESTRICCIONES*/
INSERT INTO PSDG_mensaje_ayuda VALUES('res_btn_help_1','en','This is the structure of the database to be populated (<b>BDO</b>). Click on each of the tables and fields of the BDO to set its parameters in the <b>Detail</b> window.');
INSERT INTO PSDG_mensaje_ayuda VALUES('res_btn_help_2','en','Here you set the parameters to populate each of the tables and fields. If you do not want to populate a field or table in the BDO, select  <b>No fill</b>.');
