<?php 

require_once("../conexiones/ConexionBDMySQL.inc");

class Restricciones
{
	var $conexionBDI;	
	var $usu_login;
	
	function __construct($parametrosConexion,$login)
	{
		$this->conexionBDI = new ConexionBDMySQL($parametrosConexion);
  		$this->conexionBDI->conectar();
  		$this->usu_login = $login;
	}

}
?>