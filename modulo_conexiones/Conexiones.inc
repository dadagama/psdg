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
	
	function insertarConexion($con_nombre, $con_tipo, $parametros_conexion)
	{
		switch($con_tipo)
		{
			case "bd":
				//nada
				break;
			case "archivo":
				
				break;
			case "biblioteca":
				break;
		}
		$sql = "	INSERT INTO PSDG_conexion
			VALUES (	'".$con_nombre."',
						'".$this->usu_login."',
						'".$con_tipo."',
						'$parametros_conexion'
			)";
		$this->conexionBDI->ejecutarSQL($sql);
		return $this->conexionBDI->obtenerResultset();
	}
	
	function crearTablaConexionExterna($con_nombre, $tipo_conexion, $nombre_archivo)
	{
		$sql = "	CREATE TABLE ".$this->usu_login."_".$tipo_conexion."_".$con_nombre."
			(valor TEXT) ENGINE = InnoDB COMMENT = 'create by $nombre_archivo'";
		$this->conexionBDI->ejecutarSQL($sql);
		return $this->conexionBDI->obtenerResultset();
	}
	
	function insertarValoresEnTabla($con_nombre, $tipo_conexion, $valor)
	{
		$sql = "	INSERT INTO ".$this->usu_login."_".$tipo_conexion."_".$con_nombre."
			VALUES ('$valor')";
		$this->conexionBDI->ejecutarSQL($sql);
		return $this->conexionBDI->obtenerResultset();
	}
	
	function obtenerArregloInfoConexiones()
	{
		$sql = "	SELECT con_nombre, con_tipo
					FROM PSDG_conexion";
		$this->conexionBDI->ejecutarSQL($sql);
		return $this->conexionBDI->obtenerResultadoComoArreglo();
	}
}
?>