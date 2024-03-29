/*
 This file is part of PSDG.

    PSDG is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
    along with PSDG.  If not, see <http://www.gnu.org/licenses/>.

*/

DROP TABLE IF EXISTS `PSDG_idioma`;
DROP TABLE IF EXISTS `PSDG_mensaje_popup`;
DROP TABLE IF EXISTS `PSDG_restricciones_campos`;
DROP TABLE IF EXISTS `PSDG_restricciones_tablas`;
DROP TABLE IF EXISTS `PSDG_fuentes_de_tipos`;
DROP TABLE IF EXISTS `PSDG_conexion`;
DROP TABLE IF EXISTS `PSDG_fuentes`;
DROP TABLE IF EXISTS `PSDG_tipo_acceso`;
DROP TABLE IF EXISTS `PSDG_funcion_probabilidad`;
DROP TABLE IF EXISTS `PSDG_tipo_campo_biblioteca`;
DROP TABLE IF EXISTS `PSDG_dependencias_de_tablas`;
DROP TABLE IF EXISTS `PSDG_dependencias_de_campos`;
DROP TABLE IF EXISTS `PSDG_usuario`;
DROP TABLE IF EXISTS `PSDG_tipo_salida_escogida`;
DROP TABLE IF EXISTS `PSDG_funcion`;
DROP TABLE IF EXISTS `PSDG_fuente_markov`;


CREATE TABLE `BDI`.`PSDG_fuente_markov` (
	`fum_codigo` varchar( 50 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'codigo del tipo de fuente markov para gibberish',
	`fum_nombre` VARCHAR( 100 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'nombre de la fuente para el select',
	PRIMARY KEY ( `fum_codigo`)
) ENGINE = InnoDB COMMENT = 'Almacena las distintas fuentes de markov que puede utilizar el usuario para generar datos utilizando tecnica gibberish';

INSERT INTO PSDG_fuente_markov VALUES('alice','Alices Adventures in Wonderland, by Lewis Carroll');
INSERT INTO PSDG_fuente_markov VALUES('calvin','The Wikipedia article on Calvin and Hobbes');
INSERT INTO PSDG_fuente_markov VALUES('kant','The Critique of Pure Reason by Immanuel Kant');


CREATE TABLE `BDI`.`PSDG_funcion` (
	`fun_codigo` INTEGER COLLATE utf8_unicode_ci NOT NULL COMMENT 'codigo del tipo de funcion',
	`fun_nombre` VARCHAR( 100 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'nombre de la funcion',
	`fun_tipo_dato` VARCHAR( 100 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'tipo de dato que soporta el uso de esta funcion',
	PRIMARY KEY ( `fun_nombre`, `fun_tipo_dato`)
) ENGINE = InnoDB COMMENT = 'Almacena las distintas funciones que puede utilizar el usuario para generar datos deacuerdo al tipo de dato del campo';

INSERT INTO PSDG_funcion VALUES(1,'Luhn','bigint');
INSERT INTO PSDG_funcion VALUES(2,'Luhn','varchar');
INSERT INTO PSDG_funcion VALUES(3,'Gibberish-Markov','text');
INSERT INTO PSDG_funcion VALUES(4,'Gibberish-Markov','varchar');


CREATE TABLE `BDI`.`PSDG_tipo_salida_escogida` (
	`tis_usu_login` VARCHAR( 50 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'login del usuario',
	`tis_codigo` VARCHAR( 40 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'codigo del tipo de salida a utilizar',
	PRIMARY KEY ( `tis_usu_login`, `tis_codigo` )
) ENGINE = InnoDB COMMENT = 'Almacena los tipos de salidas escogidas por los usuarios';




CREATE TABLE `BDI`.`PSDG_usuario` (
	`usu_login` VARCHAR( 50 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'login del usuario',
	`usu_password` VARCHAR( 40 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'contraseña del usuario',
	PRIMARY KEY ( `usu_login` )
) ENGINE = InnoDB COMMENT = 'Almacena los usuarios que tienen acceso a la aplicación';

INSERT INTO PSDG_usuario(usu_login, usu_password) VALUES('demo','89e495e7941cf9e40e6980d14a16bf023ccd4c91');

CREATE TABLE `BDI`.`PSDG_dependencias_de_tablas` (
	`det_usu_login` VARCHAR( 50 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'login del usuario',
	`det_nombre_tabla_dependiente` VARCHAR( 100 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'nombre de la tabla dependiente',
	`det_depende_de` VARCHAR( 100 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'nombre de la tabla de la cual depende para sus valores',
	PRIMARY KEY ( `det_nombre_tabla_dependiente`, `det_depende_de`),
	FOREIGN KEY (`det_usu_login`) REFERENCES `PSDG_usuario` (`usu_login`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB COMMENT = 'Almacena las dependencias entre tablas que se crean por las restricciones o llaves';

CREATE TABLE `BDI`.`PSDG_dependencias_de_campos` (
	`dec_usu_login` VARCHAR( 50 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'login del usuario',
	`dec_nombre_tabla` VARCHAR( 100 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'nombre de la tabla a la que pertenece la dependencia',
	`dec_nombre_campo_dependiente` VARCHAR( 100 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'nombre del campo dependiente',
	`dec_depende_de` VARCHAR( 100 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'nombre del campo del cual depende para sus valores',
	PRIMARY KEY ( `dec_nombre_tabla`, `dec_nombre_campo_dependiente`, `dec_depende_de`),
	FOREIGN KEY (`dec_usu_login`) REFERENCES `PSDG_usuario` (`usu_login`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB COMMENT = 'Almacena las dependencias entre campos que se crean por las restricciones';


CREATE TABLE `BDI`.`PSDG_tipo_acceso` (
	`tia_codigo` INTEGER COLLATE utf8_unicode_ci NOT NULL COMMENT 'codigo de identificacion para el tipo de acceso',
	`tia_nombre` VARCHAR( 40 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'nombre del tipo de acceso',
	PRIMARY KEY ( `tia_codigo` )
) ENGINE = InnoDB COMMENT = 'Almacena los tipos de acceso a fuentes de datos en la aplicación';

INSERT INTO PSDG_tipo_acceso VALUES(1,'Secuencial');
INSERT INTO PSDG_tipo_acceso VALUES(2,'Aleatorio');
INSERT INTO PSDG_tipo_acceso VALUES(3,'Probabilistico');

CREATE TABLE `BDI`.`PSDG_tipo_campo_biblioteca` (
	`tcb_codigo` INTEGER COLLATE utf8_unicode_ci NOT NULL COMMENT 'codigo de identificacion para el tipo de campo',
	`tcb_nombre` VARCHAR( 40 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'nombre del tipo de campo',
	PRIMARY KEY ( `tcb_codigo` )
) ENGINE = InnoDB COMMENT = 'Almacena los tipos de campo que componen una biblioteca';

INSERT INTO PSDG_tipo_campo_biblioteca VALUES(1,'Independiente');
INSERT INTO PSDG_tipo_campo_biblioteca VALUES(2,'Dependiente');


CREATE TABLE `BDI`.`PSDG_funcion_probabilidad` (
	`fup_codigo` INTEGER COLLATE utf8_unicode_ci NOT NULL COMMENT 'codigo de identificacion para la funcion de probabilidad',
	`fup_nombre` VARCHAR( 40 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'nombre de la funcion de probabilidad',
	PRIMARY KEY ( `fup_codigo` )
) ENGINE = InnoDB COMMENT = 'Almacena las funciones de probabilidad que se pueden aplicar a los datos';

INSERT INTO PSDG_funcion_probabilidad VALUES(1,'Uniforme');
INSERT INTO PSDG_funcion_probabilidad VALUES(2,'Normal estandar');
INSERT INTO PSDG_funcion_probabilidad VALUES(3,'Exponencial');


CREATE TABLE `BDI`.`PSDG_fuentes` (
	`fue_codigo` INTEGER COLLATE utf8_unicode_ci NOT NULL COMMENT 'codigo del tipo de fuente',
	`fue_nombre` VARCHAR( 100 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'nombre de la fuente de datos',
	`fue_es_externa` CHAR( 1 ) COLLATE utf8_unicode_ci NOT NULL DEFAULT 'f' COMMENT 'bandera que determina si es una fuente externa de datos',
	PRIMARY KEY ( `fue_codigo` )
) ENGINE = InnoDB COMMENT = 'Almacena los distintos fuentes de datos que puede utilizar el usuario para generar datos deacuerdo al SMBD de la BDO';

INSERT INTO PSDG_fuentes VALUES(1,'Ninguna','f');
INSERT INTO PSDG_fuentes VALUES(2,'Base de datos','t');
INSERT INTO PSDG_fuentes VALUES(3,'Biblioteca','t');
INSERT INTO PSDG_fuentes VALUES(4,'Lista de valores','f');
INSERT INTO PSDG_fuentes VALUES(5,'Constante','f');
INSERT INTO PSDG_fuentes VALUES(6,'Intervalo','f');
INSERT INTO PSDG_fuentes VALUES(7,'Archivo','t');
INSERT INTO PSDG_fuentes VALUES(8,'Secuencia','f');
INSERT INTO PSDG_fuentes VALUES(9,'Funcion','f');

CREATE TABLE `BDI`.`PSDG_fuentes_de_tipos` (
	`fdt_motor` VARCHAR( 50 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'nombre del SMBD al que pertenece el tipo de dato',
	`fdt_tipo_de_dato` VARCHAR( 50 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'nombre del tipo de dato que permite el SMBD',
	`fdt_fue_codigo` INTEGER COLLATE utf8_unicode_ci NOT NULL COMMENT 'nombre de la fuente asociada a este tipo de dato',
	FOREIGN KEY (`fdt_fue_codigo`) REFERENCES `PSDG_fuentes` (`fue_codigo`)
) ENGINE = InnoDB COMMENT = 'Almacena los distintos fuentes de datos que puede utilizar el usuario para generar datos deacuerdo al SMBD de la BDO';

INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','char',1);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','char',2);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','char',3);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','char',4);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','char',5);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','char',7);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','char',8);

INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','varchar',1);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','varchar',2);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','varchar',3);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','varchar',4);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','varchar',5);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','varchar',7);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','varchar',8);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','varchar',9);

INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','tinyint',1);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','tinyint',2);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','tinyint',3);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','tinyint',4);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','tinyint',5);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','tinyint',6);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','tinyint',7);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','tinyint',8);

INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','text',1);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','text',2);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','text',3);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','text',4);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','text',5);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','text',7);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','text',8);

INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','int',1);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','int',2);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','int',3);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','int',4);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','int',5);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','int',6);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','int',7);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','int',8);

INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','bigint',1);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','bigint',2);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','bigint',3);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','bigint',4);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','bigint',5);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','bigint',6);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','bigint',7);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','bigint',8);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','bigint',9);

INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','date',1);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','date',2);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','date',3);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','date',4);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','date',5);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','date',6);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','date',7);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','date',8);

INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','timestamp',1);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','timestamp',2);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','timestamp',3);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','timestamp',4);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','timestamp',5);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','timestamp',6);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','timestamp',7);
INSERT INTO PSDG_fuentes_de_tipos VALUES('mysql','timestamp',8);


CREATE TABLE IF NOT EXISTS `PSDG_conexion` (
	`con_nombre` varchar(50) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Nombre asignado a la conexión',
	`con_usu_login` varchar(50) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Nombre asignado a la conexión',
	`con_fue_codigo` INTEGER COLLATE utf8_unicode_ci NOT NULL COMMENT 'nombre de la fuente asociada a esta conexion',
	`con_parametros` varchar(800) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Parametros para realizar la conexión, con el formato p1:v1,p2:v2, ... ,pn:vn',
	PRIMARY KEY ( `con_nombre`, `con_usu_login`, `con_fue_codigo`),
	FOREIGN KEY (`con_usu_login`) REFERENCES `PSDG_usuario` (`usu_login`) ON DELETE CASCADE ON UPDATE CASCADE,
	FOREIGN KEY (`con_fue_codigo`) REFERENCES `PSDG_fuentes` (`fue_codigo`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE= InnoDB COMMENT = 'Almacena las conexiones a fuentes de datos externas a la aplicacion';


CREATE TABLE `BDI`.`PSDG_restricciones_tablas` (
	`ret_usu_login` varchar(50) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Nombre del usuario que establecio la restriccion',
	`ret_nombre_tabla` VARCHAR( 50 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'nombre del SMBD al que pertenece el tipo de dato',
	`ret_numero_tuplas_a_generar` INTEGER COLLATE utf8_unicode_ci NOT NULL COMMENT 'cantidad de tuplas que se generaran para llenar esta tabla',
	FOREIGN KEY (`ret_usu_login`) REFERENCES `PSDG_conexion` (`con_usu_login`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB COMMENT = 'Almacena las restricciones a nivel de tablas para la BDO';

CREATE TABLE `BDI`.`PSDG_restricciones_campos` (
	`rec_usu_login` varchar(50) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Nombre del usuario que establecio la restriccion',
	`rec_nombre_tabla` VARCHAR( 100 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'nombre de la tabla a la que pertenece el campo',
	`rec_nombre_campo` VARCHAR( 100 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'nombre del campo al que pertenece esta restriccion',
	`rec_fue_codigo` INTEGER COLLATE utf8_unicode_ci NOT NULL COMMENT 'nombre del tipo de fuente de donde se obtendran los valores',
	`rec_parametros_tipo_fuente` VARCHAR( 500 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'parametros que utiliza el tipo de fuente para retornar los valores',
/*	`rec_acceso_aleatorio` TINYINT(1) COLLATE utf8_unicode_ci NOT NULL COMMENT 'bandera que indica si los datos se retornan de manera secuencial (0) o aleatoria (1)',*/
	`rec_porcentaje_nulos` INTEGER COLLATE utf8_unicode_ci NOT NULL COMMENT 'Porcentaje que indica la cantidad de nulos que se deben generar para este campo',
	`rec_es_foranea` TINYINT(1) COLLATE utf8_unicode_ci NOT NULL COMMENT 'bandera que indica si el campo es llave foranea (1) o no (0)',
	FOREIGN KEY (`rec_fue_codigo`) REFERENCES `PSDG_fuentes` (`fue_codigo`) ON DELETE CASCADE ON UPDATE CASCADE,
	FOREIGN KEY (`rec_usu_login`) REFERENCES `PSDG_conexion` (`con_usu_login`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB COMMENT = 'Almacena las restricciones a nivel de campos de las tablas para la BDO';


CREATE TABLE IF NOT EXISTS `PSDG_idioma` (
	`idi_texto` varchar(100) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Etiqueta a traducir',
	`idi_lenguaje` char(2) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Abreviatura del lenguaje en el que se encuentra la traducción',
	`idi_traduccion` varchar(500) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Traducción del mensaje',
	PRIMARY KEY ( `idi_texto`,`idi_lenguaje` )
) ENGINE= InnoDB COMMENT = 'Almacena las traducciones de las etiquetas';

/*ESPAÑOL*/
/*general*/
INSERT INTO PSDG_idioma VALUES('ttp_help','es','Haga clic para obtener ayuda sobre esta sección.');
INSERT INTO PSDG_idioma VALUES('select_seleccione','es','Elija una');
/*login*/
INSERT INTO PSDG_idioma VALUES('lbl_login','es','Iniciar Sesión');
INSERT INTO PSDG_idioma VALUES('lbl_usu_login','es','Sesión');
INSERT INTO PSDG_idioma VALUES('lbl_usu_password','es','Contraseña');
INSERT INTO PSDG_idioma VALUES('ttp_usu_login','es','Digite el nombre de su sesión de trabajo');
INSERT INTO PSDG_idioma VALUES('ttp_usu_password','es','Digite su contraseña');
INSERT INTO PSDG_idioma VALUES('ttp_chk_lang_en','es','Inglés');
INSERT INTO PSDG_idioma VALUES('ttp_chk_lang_es','es','Español');
INSERT INTO PSDG_idioma VALUES('btn_login','es','Iniciar Sesión');
/*conexiones*/
INSERT INTO PSDG_idioma VALUES('con_lgn_configurar_conexion','es','Configurar conexión');
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
INSERT INTO PSDG_idioma VALUES('con_lgn_conexiones_bdo_establecida','es','Conexión Establecida a BDO');
INSERT INTO PSDG_idioma VALUES('con_lgn_conexiones_establecidas','es','Conexiones establecidas');
INSERT INTO PSDG_idioma VALUES('con_ttp_siguiente','es','Establecer restricciones');
/*restricciones*/
INSERT INTO PSDG_idioma VALUES('res_lgn_estructura_bd','es','Estructura de la BDO');
INSERT INTO PSDG_idioma VALUES('res_lgn_detalle','es','Detalle');
INSERT INTO PSDG_idioma VALUES('res_ttp_anterior','es','Configurar conexiones');
INSERT INTO PSDG_idioma VALUES('res_ttp_siguiente','es','Establecer formato de salida');

INSERT INTO PSDG_idioma VALUES('ret_lbl_nombre_tabla','es','Nombre de tabla');
INSERT INTO PSDG_idioma VALUES('ret_lbl_cantidad_tuplas','es','Numero de registros');

INSERT INTO PSDG_idioma VALUES('res_lgn_titulo_restricciones','es','Establecer restricciones');
INSERT INTO PSDG_idioma VALUES('res_lgn_info_detalle','es','Información del campo');
INSERT INTO PSDG_idioma VALUES('res_lgn_titulo_setup_fuente','es','Configuración de fuente de datos');
INSERT INTO PSDG_idioma VALUES('rec_lbl_nombre_tabla_info','es','Nombre de la tabla');
INSERT INTO PSDG_idioma VALUES('rec_lbl_nombre_campo','es','Nombre del campo');
INSERT INTO PSDG_idioma VALUES('rec_lbl_tipo_dato','es','Tipo de dato');
INSERT INTO PSDG_idioma VALUES('rec_lbl_permite_nulos','es','Permite valores nulos');
INSERT INTO PSDG_idioma VALUES('rec_lbl_tipo_llave','es','Tipo de llave');
INSERT INTO PSDG_idioma VALUES('rec_lbl_PRIMARY KEY','es','Primaria');
INSERT INTO PSDG_idioma VALUES('rec_lbl_FOREIGN KEY','es','Foranea');
INSERT INTO PSDG_idioma VALUES('rec_lbl_UNIQUE','es','Única');
INSERT INTO PSDG_idioma VALUES('rec_lbl_valor_default','es','Valor por defecto');
INSERT INTO PSDG_idioma VALUES('rec_lbl_extras','es','Extra');
INSERT INTO PSDG_idioma VALUES('rec_lbl_porcentaje_nulos','es','Porcentaje valores nulos');
INSERT INTO PSDG_idioma VALUES('rec_lbl_fuente_datos','es','Fuente de datos');
INSERT INTO PSDG_idioma VALUES('rec_lbl_conexion_archivo','es','Conexión archivo');
INSERT INTO PSDG_idioma VALUES('rec_lbl_conexion_biblioteca','es','Conexión biblioteca');
INSERT INTO PSDG_idioma VALUES('rec_lbl_tipo_campo_biblioteca','es','Tipo de campo orígen');
INSERT INTO PSDG_idioma VALUES('rec_lbl_nombre_campo_biblioteca','es','Nombre del campo orígen');
INSERT INTO PSDG_idioma VALUES('rec_lbl_nombre_campo_independiente','es','Campo independiente');
INSERT INTO PSDG_idioma VALUES('rec_lbl_conexion_bd','es','Conexión base de datos');
INSERT INTO PSDG_idioma VALUES('rec_lbl_nombre_tabla','es','Nombre de la tabla');
INSERT INTO PSDG_idioma VALUES('rec_lbl_tia_codigo','es','Tipo de acceso');
INSERT INTO PSDG_idioma VALUES('rec_lbl_fup_codigo','es','Función de probabilidad');
INSERT INTO PSDG_idioma VALUES('rec_lbl_lista_valores','es','Valores');
INSERT INTO PSDG_idioma VALUES('rec_lbl_desde','es','Desde');
INSERT INTO PSDG_idioma VALUES('rec_lbl_hasta','es','Hasta');
INSERT INTO PSDG_idioma VALUES('rec_lbl_valor_constante','es','Valor');
INSERT INTO PSDG_idioma VALUES('rec_lbl_valor_secuencial','es','Valor inicial');
INSERT INTO PSDG_idioma VALUES('rec_lbl_delta_secuencial','es','Delta');
INSERT INTO PSDG_idioma VALUES('rec_lbl_funcion','es','Nombre de la función');
INSERT INTO PSDG_idioma VALUES('rec_lbl_markov_order','es','Orden');
INSERT INTO PSDG_idioma VALUES('rec_lbl_markov_length','es','Logitud');
INSERT INTO PSDG_idioma VALUES('rec_lbl_markov_input','es','Texto de entrada');

INSERT INTO PSDG_idioma VALUES('rec_ttp_numero_tuplas','es','Número de registros a generar');
INSERT INTO PSDG_idioma VALUES('rec_ttp_fue_codigo','es','Seleccione de donde se obtendrán los posibles valores');
INSERT INTO PSDG_idioma VALUES('rec_ttp_nombre_conexion','es','Seleccione la conexión a la base de datos donde se encuentran los valores');
INSERT INTO PSDG_idioma VALUES('rec_ttp_nombre_tabla','es','Seleccione la tabla de la base de datos donde se encuentran los valores');
INSERT INTO PSDG_idioma VALUES('rec_ttp_nombre_campo','es','Seleccione el campo de la tabla donde se encuentran los valores');
INSERT INTO PSDG_idioma VALUES('rec_ttp_conexion_biblioteca','es','Seleccione la conexión a la biblioteca donde se encuentran los valores');
INSERT INTO PSDG_idioma VALUES('rec_ttp_tipo_campo_biblioteca','es','Seleccione el tipo de campo de la biblioteca');
INSERT INTO PSDG_idioma VALUES('rec_ttp_nombre_campo_independiente','es','Seleccione el campo del que dependerá los valores de este campo');
INSERT INTO PSDG_idioma VALUES('rec_ttp_nombre_campo_biblioteca','es','Seleccione el campo independiente de la biblioteca donde se encuentran los valores');
INSERT INTO PSDG_idioma VALUES('rec_en_dias','es','en días');
INSERT INTO PSDG_idioma VALUES('rec_posicion','es','posición');
INSERT INTO PSDG_idioma VALUES('rec_fecha','es','fecha');
INSERT INTO PSDG_idioma VALUES('rec_ttp_conexion_archivo','es','Seleccione la conexión al archivo donde se encuentran los valores');
INSERT INTO PSDG_idioma VALUES('rec_ttp_fun_codigo','es','Seleccione la función a utilizar que se encargará de crear los valores');
INSERT INTO PSDG_idioma VALUES('rec_ttp_markov_input','es','Seleccione el texto que se utilizará como base para generar las cadenas de Markov');
INSERT INTO PSDG_idioma VALUES('rec_ttp_tia_codigo','es','Seleccione la forma en que serán tomados los valores de la fuente de datos');
INSERT INTO PSDG_idioma VALUES('rec_ttp_fup_codigo','es','Seleccione la función de probabilidad a la que se adaptarán los datos');
INSERT INTO PSDG_idioma VALUES('rec_ttp_btn_establecer','es','Guardar la configuración de este campo');

INSERT INTO PSDG_idioma VALUES('select_Archivo','es','Archivo');
INSERT INTO PSDG_idioma VALUES('select_Base de datos','es','Base de datos');
INSERT INTO PSDG_idioma VALUES('select_Biblioteca','es','Biblioteca');
INSERT INTO PSDG_idioma VALUES('select_Lista de valores','es','Lista de valores');
INSERT INTO PSDG_idioma VALUES('select_Constante','es','Constante');
INSERT INTO PSDG_idioma VALUES('select_Intervalo','es','Intérvalo');
INSERT INTO PSDG_idioma VALUES('select_Ninguna','es','Ninguna');
INSERT INTO PSDG_idioma VALUES('select_Secuencia','es','Secuencia');
INSERT INTO PSDG_idioma VALUES('select_Funcion','es','Función');

INSERT INTO PSDG_idioma VALUES('select_Secuencial','es','Secuencial');
INSERT INTO PSDG_idioma VALUES('select_Aleatorio','es','Aleatorio');
INSERT INTO PSDG_idioma VALUES('select_Probabilistico','es','Probabílistico');

INSERT INTO PSDG_idioma VALUES('select_Uniforme','es','Distribución Uniforme');
INSERT INTO PSDG_idioma VALUES('select_Normal estandar','es','Distribución Normal');
INSERT INTO PSDG_idioma VALUES('select_Exponencial','es','Distribución Exponencial');

INSERT INTO PSDG_idioma VALUES('select_Dependiente','es','Dependiente');
INSERT INTO PSDG_idioma VALUES('select_Independiente','es','Independiente');

INSERT INTO PSDG_idioma VALUES('res_nulo_YES','es','Si');
INSERT INTO PSDG_idioma VALUES('res_nulo_NO','es','No');

INSERT INTO PSDG_idioma VALUES('rec_lbl_media','es','Media');
INSERT INTO PSDG_idioma VALUES('rec_lbl_desviacion_estandar','es','Desviación Estandar');
INSERT INTO PSDG_idioma VALUES('rec_lbl_lambda','es','Lambda');

/*salida*/
INSERT INTO PSDG_idioma VALUES('sal_lgn_tipo_salida','es','Establecer formato de salida');
INSERT INTO PSDG_idioma VALUES('sal_ttp_bd','es','Exportar datos a la BDO');
INSERT INTO PSDG_idioma VALUES('sal_ttp_text','es','Exportar datos a un archivo');

INSERT INTO PSDG_idioma VALUES('sal_lbl_bd','es','Migrar los datos sintéticos a la base de datos objetivo.');
INSERT INTO PSDG_idioma VALUES('sal_lbl_text','es','Migrar los datos sintéticos a un script Sql.');


INSERT INTO PSDG_idioma VALUES('sal_ttp_anterior','es','Configurar restricciones');
INSERT INTO PSDG_idioma VALUES('sal_ttp_siguiente','es','Ejecutar');

/*ejecucion*/
INSERT INTO PSDG_idioma VALUES('eje_lgn_consola','es','Ejecutar');
INSERT INTO PSDG_idioma VALUES('eje_btn_iniciar','es','Iniciar');
INSERT INTO PSDG_idioma VALUES('eje_btn_grafo','es','Ver grafo');

INSERT INTO PSDG_idioma VALUES('eje_ttp_anterior','es','Configurar formato de salida');

INSERT INTO PSDG_idioma VALUES('eje_lbl_inicializando','es','Etapa de inicialización');
INSERT INTO PSDG_idioma VALUES('eje_lbl_ordenando_tablas','es','Priorizando tablas');
INSERT INTO PSDG_idioma VALUES('eje_lbl_generar_datos','es','Etapa de generación de datos');
INSERT INTO PSDG_idioma VALUES('eje_lbl_generando_tabla','es','Generando datos sintéticos para la tabla');

INSERT INTO PSDG_idioma VALUES('eje_lbl_resumen','es','Resúmen de toda la configuración');
INSERT INTO PSDG_idioma VALUES('eje_lbl_conexiones','es','Conexiones establecidas');
INSERT INTO PSDG_idioma VALUES('eje_lbl_num_tuplas','es','Cantidad de registros a generar por tabla');
INSERT INTO PSDG_idioma VALUES('eje_lbl_tipo_salida','es','Tipos de salida seleccionados');
/**************************************************************************************************************/
/*INGLES*/
/*general*/
INSERT INTO PSDG_idioma VALUES('ttp_help','en','Click for help on this section.');
INSERT INTO PSDG_idioma VALUES('select_seleccione','en','Choose one');
/*login*/
INSERT INTO PSDG_idioma VALUES('lbl_login','en','Log in');
INSERT INTO PSDG_idioma VALUES('lbl_usu_login','en','Workspace');
INSERT INTO PSDG_idioma VALUES('lbl_usu_password','en','Password');
INSERT INTO PSDG_idioma VALUES('ttp_usu_login','en','Type your workspace name');
INSERT INTO PSDG_idioma VALUES('ttp_usu_password','en','Type your password');
INSERT INTO PSDG_idioma VALUES('ttp_chk_lang_en','en','English');
INSERT INTO PSDG_idioma VALUES('ttp_chk_lang_es','en','Spanish');
INSERT INTO PSDG_idioma VALUES('btn_login','en','Sign in');
/*conexiones*/
INSERT INTO PSDG_idioma VALUES('con_lgn_configurar_conexion','en','Set connection');
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
INSERT INTO PSDG_idioma VALUES('con_lgn_conexiones_bdo_establecida','en','BDO Connection established');
INSERT INTO PSDG_idioma VALUES('con_lgn_conexiones_establecidas','en','Established connections');
INSERT INTO PSDG_idioma VALUES('con_ttp_siguiente','en','Set restrictions');
/*restricciones*/
INSERT INTO PSDG_idioma VALUES('res_lgn_estructura_bd','en','BDO structure');
INSERT INTO PSDG_idioma VALUES('res_lgn_detalle','en','Detail');
INSERT INTO PSDG_idioma VALUES('res_ttp_anterior','en','Set connections');
INSERT INTO PSDG_idioma VALUES('res_ttp_siguiente','en','Set output type');

INSERT INTO PSDG_idioma VALUES('ret_lbl_nombre_tabla','en','Table name');
INSERT INTO PSDG_idioma VALUES('ret_lbl_cantidad_tuplas','en','Number of records');

INSERT INTO PSDG_idioma VALUES('res_lgn_info_detalle','en','Field information');
INSERT INTO PSDG_idioma VALUES('res_lgn_titulo_restricciones','en','Set restrictions');
INSERT INTO PSDG_idioma VALUES('res_lgn_titulo_setup_fuente','en','Setup data source');
INSERT INTO PSDG_idioma VALUES('rec_lbl_nombre_tabla_info','en','Table name');
INSERT INTO PSDG_idioma VALUES('rec_lbl_nombre_campo','en','Field name');
INSERT INTO PSDG_idioma VALUES('rec_lbl_tipo_dato','en','Data type');
INSERT INTO PSDG_idioma VALUES('rec_lbl_permite_nulos','en','Allow null value');
INSERT INTO PSDG_idioma VALUES('rec_lbl_tipo_llave','en','Key type');
INSERT INTO PSDG_idioma VALUES('rec_lbl_PRIMARY KEY','en','Primary');
INSERT INTO PSDG_idioma VALUES('rec_lbl_FOREIGN KEY','en','Foreign');
INSERT INTO PSDG_idioma VALUES('rec_lbl_UNIQUE','en','Unique');
INSERT INTO PSDG_idioma VALUES('rec_lbl_valor_default','en','Default value');
INSERT INTO PSDG_idioma VALUES('rec_lbl_extras','en','Extra');
INSERT INTO PSDG_idioma VALUES('rec_lbl_porcentaje_nulos','en','Percentage Nulls');
INSERT INTO PSDG_idioma VALUES('rec_lbl_fuente_datos','en','Data source');
INSERT INTO PSDG_idioma VALUES('rec_lbl_conexion_archivo','en','Link file');
INSERT INTO PSDG_idioma VALUES('rec_lbl_conexion_biblioteca','en','Link library');
INSERT INTO PSDG_idioma VALUES('rec_lbl_tipo_campo_biblioteca','en','Source field type');
INSERT INTO PSDG_idioma VALUES('rec_lbl_nombre_campo_biblioteca','en','Source field name');
INSERT INTO PSDG_idioma VALUES('rec_lbl_nombre_campo_independiente','en','Independent field');
INSERT INTO PSDG_idioma VALUES('rec_lbl_conexion_bd','en','Link database');
INSERT INTO PSDG_idioma VALUES('rec_lbl_nombre_tabla','en','Table name');
INSERT INTO PSDG_idioma VALUES('rec_lbl_tia_codigo','en','Access type');
INSERT INTO PSDG_idioma VALUES('rec_lbl_fup_codigo','en','Probability function');
INSERT INTO PSDG_idioma VALUES('rec_lbl_lista_valores','en','Values');
INSERT INTO PSDG_idioma VALUES('rec_lbl_desde','en','From');
INSERT INTO PSDG_idioma VALUES('rec_lbl_hasta','en','to');
INSERT INTO PSDG_idioma VALUES('rec_lbl_valor_constante','en','Value');
INSERT INTO PSDG_idioma VALUES('rec_lbl_valor_secuencial','en','Initial value');
INSERT INTO PSDG_idioma VALUES('rec_lbl_delta_secuencial','en','Delta');
INSERT INTO PSDG_idioma VALUES('rec_lbl_funcion','en','Function name');
INSERT INTO PSDG_idioma VALUES('rec_lbl_markov_order','en','Order');
INSERT INTO PSDG_idioma VALUES('rec_lbl_markov_length','en','Length');
INSERT INTO PSDG_idioma VALUES('rec_lbl_markov_input','en','Input text');

INSERT INTO PSDG_idioma VALUES('rec_ttp_numero_tuplas','en','Number of records to generate');
INSERT INTO PSDG_idioma VALUES('rec_ttp_fue_codigo','en','Select where will obtain the possible values');
INSERT INTO PSDG_idioma VALUES('rec_ttp_nombre_conexion','en','Select connection to the database where the values are obtained');
INSERT INTO PSDG_idioma VALUES('rec_ttp_nombre_tabla','en','Select the database table where the values are obtained');
INSERT INTO PSDG_idioma VALUES('rec_ttp_nombre_campo','en','Select field of table where the values are obtained');
INSERT INTO PSDG_idioma VALUES('rec_ttp_conexion_biblioteca','en','Select connection to the library where the values are obtained');
INSERT INTO PSDG_idioma VALUES('rec_ttp_tipo_campo_biblioteca','en','Select field type of library');
INSERT INTO PSDG_idioma VALUES('rec_ttp_nombre_campo_independiente','en','Select the field that depends on the values of this field');
INSERT INTO PSDG_idioma VALUES('rec_ttp_nombre_campo_biblioteca','en','Select the independent field of the library where the values are obtained');
INSERT INTO PSDG_idioma VALUES('rec_en_dias','en','in days');
INSERT INTO PSDG_idioma VALUES('rec_posicion','en','position');
INSERT INTO PSDG_idioma VALUES('rec_fecha','en','date');
INSERT INTO PSDG_idioma VALUES('rec_ttp_conexion_archivo','en','Select connection to the file where the values are obtained');
INSERT INTO PSDG_idioma VALUES('rec_ttp_fun_codigo','en','Select the function used to be in charge of setting the values');
INSERT INTO PSDG_idioma VALUES('rec_ttp_markov_input','en','Select the text to be used as a basis for generating Markov chain');
INSERT INTO PSDG_idioma VALUES('rec_ttp_tia_codigo','en','Choose how you will be taken the values of the data source');
INSERT INTO PSDG_idioma VALUES('rec_ttp_fup_codigo','en','Select the probability function for adjusting the data');
INSERT INTO PSDG_idioma VALUES('rec_ttp_btn_establecer','en','Save settings for this field');


INSERT INTO PSDG_idioma VALUES('select_Archivo','en','File');
INSERT INTO PSDG_idioma VALUES('select_Base de datos','en','Database');
INSERT INTO PSDG_idioma VALUES('select_Biblioteca','en','Library');
INSERT INTO PSDG_idioma VALUES('select_Lista de valores','en','Value list');
INSERT INTO PSDG_idioma VALUES('select_Constante','en','Constant');
INSERT INTO PSDG_idioma VALUES('select_Intervalo','en','Interval');
INSERT INTO PSDG_idioma VALUES('select_Ninguna','en','None');
INSERT INTO PSDG_idioma VALUES('select_Secuencia','en','Sequence');
INSERT INTO PSDG_idioma VALUES('select_Funcion','en','Function');


INSERT INTO PSDG_idioma VALUES('select_Secuencial','en','Sequential');
INSERT INTO PSDG_idioma VALUES('select_Aleatorio','en','Random');
INSERT INTO PSDG_idioma VALUES('select_Probabilistico','en','Probabilistic');

INSERT INTO PSDG_idioma VALUES('select_Uniforme','en','Uniform distribution');
INSERT INTO PSDG_idioma VALUES('select_Normal estandar','en','Normal distribution');
INSERT INTO PSDG_idioma VALUES('select_Exponencial','en','Exponential distribution');

INSERT INTO PSDG_idioma VALUES('select_Dependiente','en','Dependent');
INSERT INTO PSDG_idioma VALUES('select_Independiente','en','Independent');

INSERT INTO PSDG_idioma VALUES('res_nulo_YES','en','Yes');
INSERT INTO PSDG_idioma VALUES('res_nulo_NO','en','No');

INSERT INTO PSDG_idioma VALUES('rec_lbl_media','en','Mean');
INSERT INTO PSDG_idioma VALUES('rec_lbl_desviacion_estandar','en','Standard deviation');
INSERT INTO PSDG_idioma VALUES('rec_lbl_lambda','en','Lambda');

/*salida*/
INSERT INTO PSDG_idioma VALUES('sal_lgn_tipo_salida','en','Output type');
INSERT INTO PSDG_idioma VALUES('sal_ttp_bd','en','Export data to BDO');
INSERT INTO PSDG_idioma VALUES('sal_ttp_text','en','Export data to file');

INSERT INTO PSDG_idioma VALUES('sal_lbl_bd','en','Migrate synthetic data to target database.');
INSERT INTO PSDG_idioma VALUES('sal_lbl_text','en','Migrate synthetic data to Sql script.');

INSERT INTO PSDG_idioma VALUES('sal_ttp_anterior','en','Set restrictions');
INSERT INTO PSDG_idioma VALUES('sal_ttp_siguiente','en','Run');

/*ejecucion*/
INSERT INTO PSDG_idioma VALUES('eje_lgn_consola','en','Run');
INSERT INTO PSDG_idioma VALUES('eje_btn_iniciar','en','Start');
INSERT INTO PSDG_idioma VALUES('eje_btn_grafo','en','View graph');

INSERT INTO PSDG_idioma VALUES('eje_ttp_anterior','en','Set output type');

INSERT INTO PSDG_idioma VALUES('eje_lbl_inicializando','en','Initialization stage');
INSERT INTO PSDG_idioma VALUES('eje_lbl_ordenando_tablas','en','Prioritizing tables');
INSERT INTO PSDG_idioma VALUES('eje_lbl_generar_datos','en','Data generation stage');
INSERT INTO PSDG_idioma VALUES('eje_lbl_generando_tabla','en','Generating synthetic data for table');

INSERT INTO PSDG_idioma VALUES('eje_lbl_resumen','en','Summary of all configuration');
INSERT INTO PSDG_idioma VALUES('eje_lbl_conexiones','en','Connections established');
INSERT INTO PSDG_idioma VALUES('eje_lbl_num_tuplas','en','Number of records to generate per table');
INSERT INTO PSDG_idioma VALUES('eje_lbl_tipo_salida','en','Selected Output Types');



CREATE TABLE IF NOT EXISTS `PSDG_mensaje_popup` (
	`pop_accion` varchar(50) NOT NULL COMMENT 'Nombre de la accion asociada al mensaje',
	`pop_lenguaje` char(2) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Abreviatura del lenguaje en el que se encuentra el mensaje',
	`pop_mensaje` varchar(800) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Texto del mensaje del popup',
	PRIMARY KEY ( `pop_accion`,`pop_lenguaje` )
) ENGINE= InnoDB COMMENT = 'Almacena los mensajes de ayuda y error en todos los idiomas para los popups';

/*ESPAÑOL*/
/*conexiones*/
INSERT INTO PSDG_mensaje_popup VALUES('con_btn_help_1','es','Debe definir <b>almenos</b> la conexion a la Base de datos objetivo (<b>BDO</b>) que será poblada.<br/><br/>Aquí tambien se definen los parámetros para conectar con fuentes externas que proporcionen tipos de datos adicionales (bases de datos, archivos de texto plano ó bibliotecas).');
INSERT INTO PSDG_mensaje_popup VALUES('con_btn_help_2','es','Aquí se muestran todas las conexiones que se establecieron satisfactoriamente.<br/><br/>Puede eliminar una conexión a una determinada fuente haciendo clic en su respectivo botón <b>Eliminar</b>.');
INSERT INTO PSDG_mensaje_popup VALUES('con_btn_help_3','es','Aquí se muestran la conexión establecida a la Base de Datos Objetivo (BDO).<br/><br/>Puede eliminar la conexión a base de datos haciendo clic en su respectivo botón <b>Eliminar</b>.');
/*RESTRICCIONES*/
INSERT INTO PSDG_mensaje_popup VALUES('res_btn_help_1','es','Esta es la estructura de la base de datos objetivo que será poblada (<b>BDO</b>).<br/><br/>Seleccione las tablas y campos de la BDO que desee poblar para establecer sus parámetros en la ventana <b>Detalle</b>.');
INSERT INTO PSDG_mensaje_popup VALUES('res_btn_help_2','es','Aquí se establecen los parámetros para poblar cada una de las tablas y campos.<br/><br/>Si no desea poblar una determinada tabla de la BDO, establezca a <b>cero (0)</b> el campo <b>Cantidad de tuplas</b>.<br/><br/>Si no desea poblar un determinado campo de una tabla, establezca el valor <b>Ninguna</b> en el campo <b>Fuente de datos</b>.');
INSERT INTO PSDG_mensaje_popup VALUES('res_error_1','es','La operación no se pudo completar. Se necesita establecer primero las condiciones de las siguientes tablas para cumplir las restricciones de llaves foráneas:<br/><b>%v</b>.');

INSERT INTO PSDG_mensaje_popup VALUES('rec_pop_lista_valores','es','Ingrese los posibles valores a generar separados por un salto de linea.<br/><br/><b>Advertencia:</b> los valores deben cumplir con el formato del tipo de dato, si es <b><i>numérico</i></b> deben ser <b><i>sólo números</i></b>, si es <b><i>fecha</i></b> deben tener el formato ISO-8601: <b><i>AAAA-MM-DD</i></b>.');
INSERT INTO PSDG_mensaje_popup VALUES('rec_pop_valor_constante','es','Ingrese el único valor a generar en todos los registros.<br/><br/><b>Advertencia:</b> El valor debe cumplir con el formato del tipo de dato, si es <b><i>numérico</i></b> deben ser un <b><i>número</i></b>, si es <b><i>fecha</i></b> debe tener el formato ISO-8601: <b><i>AAAA-MM-DD</i></b>.');
INSERT INTO PSDG_mensaje_popup VALUES('rec_pop_valor_desde','es','Ingrese el mínimo valor que se puede generar.<br/><br/><b>Advertencia:</b> El valor debe cumplir con el formato del tipo de dato, si es <b><i>numérico</i></b> deben ser un <b><i>número</i></b>, si es <b><i>fecha</i></b> debe tener el formato ISO-8601: <b><i>AAAA-MM-DD</i></b>.');
INSERT INTO PSDG_mensaje_popup VALUES('rec_pop_valor_hasta','es','Ingrese el máximo valor que se puede generar.<br/><br/><b>Advertencia:</b> El valor debe cumplir con el formato del tipo de dato, si es <b><i>numérico</i></b> deben ser un <b><i>número</i></b>, si es <b><i>fecha</i></b> debe tener el formato ISO-8601: <b><i>AAAA-MM-DD</i></b>.');
INSERT INTO PSDG_mensaje_popup VALUES('rec_pop_valor_secuencial','es','Ingrese el valor inicial de la secuencia a generar.<br/><br/><b>Advertencia:</b> El valor debe cumplir con el formato del tipo de dato, si es <b><i>numérico</i></b> deben ser un <b><i>número</i></b>, si es <b><i>fecha</i></b> debe tener el formato ISO-8601: <b><i>AAAA-MM-DD</i></b>.');
INSERT INTO PSDG_mensaje_popup VALUES('rec_pop_delta_secuencial','es','Ingrese el valor a incrementar/decrementar en la secuencia.<br/><br/><b>Advertencia:</b> El valor debe ser un <b><i>numéro</i></b>, si el tipo de dato es <b><i>fecha</i></b> se toma como <b><i>Número de días</i></b>.');
INSERT INTO PSDG_mensaje_popup VALUES('rec_pop_markov_order','es','Este valor establece la longitud esperada de las palabras del texto para inicializar la tabla de markov.<br/><br/>El valor debe ser un <b><i>numéro</i></b>.');
INSERT INTO PSDG_mensaje_popup VALUES('rec_pop_markov_length','es','Ingrese la longitud que tendrá la cadena de markov.<br/><br/>El valor debe ser un <b><i>numéro</i></b>. Tenga cuidado en no sobrepasar la longitud máxima que acepta el campo en la base de datos.');
INSERT INTO PSDG_mensaje_popup VALUES('rec_pop_lambda','es','Ingrese el parámetro <b><i>lambda</b></i> para la distribución exponencial.<br/><br/>El valor debe ser un <b><i>numéro</i></b>.');
INSERT INTO PSDG_mensaje_popup VALUES('rec_pop_media','es','Ingrese el parámetro <b><i>media</b></i> para la distribución normal.<br/><br/>Si el tipo de fuente es <b>[<i>Base de datos, Biblioteca, Lista de valores ó Archivo</i>]</b> el valor simboliza la <b><i>posición</i></b> que será tomada como <b><i>media</i></b>. Si el tipo de fuente es <b>[<i>Intérvalo</i>]</b> será tomado como un valor y debe cumplir con el formato del tipo de dato, si es <b><i>numérico</i></b> debe ser un <b><i>número</i></b>, si es <b><i>fecha</i></b> debe tener el formato ISO-8601: <b><i>AAAA-MM-DD</i></b>.');
INSERT INTO PSDG_mensaje_popup VALUES('rec_pop_desviacion_estandar','es','Ingrese el parámetro <b><i>desviación estandar</b></i> que tendrá la distribución normal.<br/>Si el tipo de fuente es <b>[<i>Base de datos, Biblioteca, Lista de valores ó Archivo</i></b>] simbolizará el <b><i>delta de posición </b></i>que será tomado como <b><i>desviación</b></i>. Si el tipo de fuente es <b>[<i>Intérvalo</i>]</b> debe cumplir con el formato del tipo de dato: si es <b><i>numérico</i></b> indica el <b><i>delta de valor</b></i> que será tomado como <b><i>desviación</b></i>, si es <b><i>fecha</i></b> indica el <b><i>delta en días</b></i> que tomará como desviación.');
INSERT INTO PSDG_mensaje_popup VALUES('rec_pop_porcentaje_nulos','es','Ingrese la probabilidad de que el valor generado sea un valor nulo. Valores entre [0-100].');

/*salida*/
INSERT INTO PSDG_mensaje_popup VALUES('sal_btn_help_1','es','Seleccione una de las opciones del panel para migrar los datos sintéticos generados hacia ese destino.');
/*Ejecución*/
INSERT INTO PSDG_mensaje_popup VALUES('eje_btn_help_1','es','Haga clic en el boton <b>Iniciar</b> para comenzar con el proceso de generar los datos sintéticos.');
/**************************************************************************************************************/
/*INGLES*/
/*conexiones*/
INSERT INTO PSDG_mensaje_popup VALUES('con_btn_help_1','en','You must define at least the connection to the target database (<b>BDO</b>) to be populated.<br/><br/>This also defines the parameters to connect to external sources to provide additional data types (databases, plain text files or libraries).');
INSERT INTO PSDG_mensaje_popup VALUES('con_btn_help_2','en','Here are all the connections that were established successfully. You can delete a connection to a particular source by clicking on its respective <b>Remove</b> button.');
INSERT INTO PSDG_mensaje_popup VALUES('con_btn_help_3','en','Here are the established connection to the target database (BDO).<br/><br/>You can remove the database connection by clicking its respective <b>Delete</b> button.');
/*RESTRICCIONES*/
INSERT INTO PSDG_mensaje_popup VALUES('res_btn_help_1','en','This is the structure of the database to be populated (<b>BDO</b>). Select the tables and fields you want to populate the BDO to set its parameters in the <b>Detail</b> window.');
INSERT INTO PSDG_mensaje_popup VALUES('res_btn_help_2','en','Here you set the parameters to populate each of the tables and fields.<br/><br/>If you do not want to populate a table in the BDO, Set  <b>zero (0)</b> in the field <b>Number of records</b>.<br/><br/>If you do not want to populate a table field, Set  <b>None</b> in the field <b>Data source</b>.');
INSERT INTO PSDG_mensaje_popup VALUES('res_error_1','en','Operation could not be completed. You need first establish conditions on the following tables to meet the foreign key constraints:<br/><b>%v</b>.');


INSERT INTO PSDG_mensaje_popup VALUES('rec_pop_lista_valores','en','Enter possible values that can be generated separated by a newline.<br/><br/><b>Note:</b> Values must comply with the format of data type, if <b><i>numeric</i></b> must be <b><i>only numbers</i></b>, if <b><i>date</i></b> should be ISO-8601 format: <b><i>YYYY-MM-DD</i></b>.');
INSERT INTO PSDG_mensaje_popup VALUES('rec_pop_valor_constante','en','Enter the unique value that can be generated in all records.<br/><br/><b>Note:</b> Value must comply with the format of data type, if <b><i>numeric</i></b> must be <b><i>only numbers</i></b>, if <b><i>date</i></b> should be ISO-8601 format: <b><i>YYYY-MM-DD</i></b>.');
INSERT INTO PSDG_mensaje_popup VALUES('rec_pop_valor_desde','en','Enter the minimum value that can be generated.<br/><br/><b>Note:</b> Value must comply with the format of data type, if <b><i>numeric</i></b> must be <b><i>only numbers</i></b>, if <b><i>date</i></b> should be ISO-8601 format: <b><i>YYYY-MM-DD</i></b>.');
INSERT INTO PSDG_mensaje_popup VALUES('rec_pop_valor_hasta','en','Enter the maximum value that can be generated.<br/><br/><b>Note:</b> Value must comply with the format of data type, if <b><i>numeric</i></b> must be <b><i>only numbers</i></b>, if <b><i>date</i></b> should be ISO-8601 format: <b><i>YYYY-MM-DD</i></b>.');
INSERT INTO PSDG_mensaje_popup VALUES('rec_pop_valor_secuencial','en','Enter the initial value that can be generated by sequence.<br/><br/><b>Note:</b> Value must comply with the format of data type, if <b><i>numeric</i></b> must be <b><i>only numbers</i></b>, if <b><i>date</i></b> should be ISO-8601 format: <b><i>YYYY-MM-DD</i></b>.');
INSERT INTO PSDG_mensaje_popup VALUES('rec_pop_delta_secuencial','en','Enter the value to increase/decrease in the sequence.<br/><br/><b>Note:</b> The value must be a <b><i>number</i></b>, if the data type is <b><i>date</i></b> is taken as <b><i>number of days</i></b>.');
INSERT INTO PSDG_mensaje_popup VALUES('rec_pop_markov_order','en','This sets the expected length of words in the text to initialize the Markov table.<br/><br/>Value must be a <b><i>number</i></b>.');
INSERT INTO PSDG_mensaje_popup VALUES('rec_pop_markov_length','en','Enter length that will the Markov chan.<br/><br/>Value must be a <b><i>number</i></b>. Be careful not to exceed the maximum length accepted the field in the database.');
INSERT INTO PSDG_mensaje_popup VALUES('rec_pop_lambda','en','Enter the <b><i>lambda</b></i> parameter for the exponential distribution.<br/><br/>Value must be a <b><i>number</i></b>.');
INSERT INTO PSDG_mensaje_popup VALUES('rec_pop_media','en',' Enter the <b><i>mean</b></i> parameter for normal distribution.<br/><br/>If source is <b>[<i>Database, Library, Archive or List values</i>]</b> the value represents the position to be taken as <b><i>mean</i></b>. If source is <b>[<i>Interval</i>]</b> is taken as a value and must comply with the format of data type, if <b><i>numeric</i></b> must be <b><i>only numbers</i></b>, if <b><i>date</i></b> should be ISO-8601 format: <b><i>YYYY-MM-DD</i></b>.');
INSERT INTO PSDG_mensaje_popup VALUES('rec_pop_desviacion_estandar','en','Enter the <b><i>standar deviation</b></i> parameter for the exponential distribution.<br/>If source is <b>[<i>Database, Library, Archive or List values</i>]</b> the value represents the <b><i>delta position</b></i> to be taken as <b><i>deviation</i></b>. If source is <b>[<i>Interval</i>]</b> is taken as a value and must comply with the format of data type, if <b><i>numeric</i></b> represents the <b><i>delta value</b></i> is taken as a <b><i>deviation</b></i>, if <b><i>date</i></b> indicates the <b><i>delta in days</b></i> taken as a <b><i>deviation</b></i>.');
INSERT INTO PSDG_mensaje_popup VALUES('rec_pop_porcentaje_nulos','en','Enter the probability that the generated value is null. Values between [0-100].');

/*salida*/
INSERT INTO PSDG_mensaje_popup VALUES('sal_btn_help_1','en','Select a option from panel to migrate generated synthetic data to that destination.');
/*Ejecución*/
INSERT INTO PSDG_mensaje_popup VALUES('eje_btn_help_1','en','Click the <b>Start</b> button to begin the process of generating synthetic data');
