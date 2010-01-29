<?php 

require_once("../conexiones/ConexionBDMySQL.inc");

class Salida
{
	var $conexionBDI;	
	var $usu_login;
	
	function __construct($parametrosConexion,$login)
	{
		$this->conexionBDI = new ConexionBDMySQL($parametrosConexion);
  		$this->conexionBDI->conectar();
  		$this->usu_login = $login;
	}
	
	function seleccionarSalida($tis_codigo)
	{
		if($this->verificarOpcionEscogida())
			$sql = "UPDATE set tis_codigo = '".$tis_codigo."' WHERE tis_usu_login = '".$this->usu_login."'";
		else
			$sql = "INSERT INTO PSDG_tipo_salida_escogida(tis_codigo, tis_usu_login) VALUES('".$tis_codigo."','".$this->usu_login."')";
		$this->conexionBDI->ejecutarSQL($sql);
	}
	
	function verificarOpcionEscogida()
	{
		if($this->conexionBDI->existeRegistro("tis_codigo", "PSDG_tipo_salida_escogida", "tis_usu_login = '".$this->usu_login."'"))
			return true;
		else 
			return false;
	}
}
?>