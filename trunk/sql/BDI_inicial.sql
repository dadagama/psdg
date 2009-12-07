CREATE TABLE `BDI`.`PSDG_usuario` (
`usu_codigo` SERIAL NOT NULL AUTO_INCREMENT COMMENT 'consecutivo',
`usu_login` VARCHAR( 20 ) NOT NULL COMMENT 'login del usuario',
`usu_password` VARCHAR( 40 ) NOT NULL COMMENT 'contraseña del usuario',
PRIMARY KEY ( `usu_login` )
) ENGINE = InnoDB COMMENT = 'Alamacena los usuarios que tienen acceso a la aplicación';
