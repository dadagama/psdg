<?php 

require_once("../conexiones/ConexionBDMySQL.inc");

class Traductor
{
	var $lang;
	var $conexionBDI;
	
	function __construct($lang)
	{
		$this->lang = $lang;
		$parametrosConexion['nombreServidor'] = "localhost";
		$parametrosConexion['nombreUsuario'] = "root";
		$parametrosConexion['clave'] = "root";
		$parametrosConexion['nombreBD'] = "BDI";
		
		$this->conexionBDI = new ConexionBDMySQL($parametrosConexion);
  		$this->conexionBDI->conectar();
	}
	
	function traducir($texto)
	{
		$resultado = $texto;
		$sql = "	SELECT idi_traduccion
					FROM PSDG_idioma 
					WHERE idi_texto = '$texto'
					AND idi_lenguaje = '".$this->lang."'
					LIMIT 1";
		$this->conexionBDI->ejecutarSQL($sql);
		if($this->conexionBDI->obtenerNumeroFilas() > 0)
		{
			$resultado = $this->conexionBDI->obtenerResultadoComoCadena();
		}
		return utf8_encode($resultado);
	}
}
?>