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
//$con_servidor = $_REQUEST['con_servidor'];
//$con_nombre_bd = $_REQUEST['con_nombre_db'];
//$con_usuario_bd = $_REQUEST['con_usuario'];
//$con_password_bd = $_REQUEST['con_password'];
//'{"a":1,"b":2,"c":3,"d":4,"e":5}';		
//$servidor = $this->_parametrosConexion['nombreServidor'];
//$usuario  = $this->_parametrosConexion['nombreUsuario'];
//$clave    = $this->_parametrosConexion['clave'];
//$bd       = $this->_parametrosConexion['nombreBD'];
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