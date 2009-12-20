<?php 

require_once("../conexiones/ConexionBDMySQL.inc");

class Conexiones
{
	var $conexionBDI;	
	var $usu_login;
	
	function __construct($parametrosConexion,$login)
	{
		$this->conexionBDI = new ConexionBDMySQL($parametrosConexion);
  		$this->conexionBDI->conectar();
  		$this->usu_login = $login;
	}

	function existeRegistroBDO()
	{
		$sql = "	SELECT con_tipo
					FROM PSDG_conexion
					WHERE con_tipo = 'bd'
					AND con_usu_login = '".$this->usu_login."'
					AND con_nombre = 'BDO'
					LIMIT 1";

		$this->conexionBDI->ejecutarSQL($sql);
		if($this->conexionBDI->obtenerNumeroFilas() == 1)
			return true;
		else
			return false;
	}
	
	function insertarConexion($con_nombre, $usu_login, $con_tipo, $parametros_conexion)
	{
		$sql = "	INSERT INTO PSDG_conexion
			VALUES (	'".$con_nombre."',
						'".$usu_login."',
						'".$con_tipo."',
						'$parametros_conexion'
			)";
		$this->conexionBDI->ejecutarSQL($sql);
		return $this->conexionBDI->obtenerResultset();
	}
}
?>