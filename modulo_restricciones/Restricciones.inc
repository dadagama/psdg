<?php 

require_once("../conexiones/ConexionBDMySQL.inc");

class Restricciones
{
	var $conexionBDI;
	var $conexionBDO;		
	var $usu_login;
	
	function __construct($parametrosConexion,$login)
	{
		$this->conexionBDI = new ConexionBDMySQL($parametrosConexion);
  		$this->conexionBDI->conectar();
  		$this->usu_login = $login;
  		$this->inicializarConexionBDO();
	}
	
	function inicializarConexionBDO()
	{
		$sql = "	SELECT con_parametros
					FROM PSDG_conexion
					WHERE con_tipo = 'bd'
					AND con_usu_login = '".$this->usu_login."'
					AND con_nombre = 'BDO'
					LIMIT 1";

		$this->conexionBDI->ejecutarSQL($sql);
		$con_parametros = $this->conexionBDI->obtenerResultadoComoCadena();
		$arreglo_parametros = json_decode($con_parametros, true);
		//$this->conexionBDO = new ConexionBDMySQL($arreglo_parametros);
	}
	
	function construirArbolBDO()
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
}
?>
