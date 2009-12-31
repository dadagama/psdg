<?php

require_once("ConexionBD.inc");
class ConexionBDMySQL extends ConexionBD
{
  function __construct($arregloParametros)
  {
	 $this->_parametrosConexion = $arregloParametros;
  }
  
  function conectar()
  {
	$servidor = $this->_parametrosConexion['con_servidor'];
	$usuario  = $this->_parametrosConexion['con_usuario'];
	$clave    = $this->_parametrosConexion['con_password'];
	$bd       = $this->_parametrosConexion['con_nombre_bd'];

	if($this->_conexion = mysql_connect($servidor, $usuario, $clave, true))
	  return $this->establecer_bd($bd);
	else
	  return false;
  }
  
  function desconectar()
  {
		return mysql_close($this->_conexion);
  }
  
	function establecer_bd($bd)
	{
		return mysql_select_db($bd, $this->_conexion);
	}
	
	function restablecer_bd_original()
	{
		return mysql_select_db($this->_parametrosConexion['con_nombre_bd'], $this->_conexion);
	}
  
	function obtener_error()
	{
		return mysql_error($this->_conexion);
	}
  
  /*function inicializarSQL()
  {
	$this->_sql = $instruccionSQL;
  }*/
  
  function ejecutarSQL($instruccionSQL)
  {
		$this->_resultSet = mysql_query(/*$this->_sql*/$instruccionSQL, $this->_conexion);
  } 
  
	function obtenerResultset()
	{
		return $this->_resultSet;
	}
  
  function obtenerResultadoComoArreglo()
  {
		$arreglo = array();
		while ($row = mysql_fetch_row($this->_resultSet)) 
		{
			$arreglo[] = $row;
		}
		return $arreglo;
  }
  
	function obtenerFilaComoArregloAsociativo()
	{
		if($fila = mysql_fetch_assoc($this->_resultSet))
			return $fila;
		else 
			return false;
	}
	
	function obtenerFilaComoArreglo()
	{
		if($fila = mysql_fetch_array($this->_resultSet))
			return $fila;
		else 
			return false;
	}
  
	/*DEPRECATED, USAR obtenerFilaComoCadena() EN SU LUGAR*/
	function obtenerResultadoComoCadena()
  {
		$row = mysql_fetch_array($this->_resultSet);
		return $row[0];
  }
  
	function obtenerFilaComoCadena()
	{
		$row = mysql_fetch_row($this->_resultSet);
		return implode(",", $row);
	}
	
	function obtenerArregloMetaDatosColumnas()
	{
		$i = 0;
		$arregloMeta = array();
		$numero_campos = mysql_num_fields($this->_resultSet);
		while ($i < $numero_campos) 
		{
			$metaRow = mysql_fetch_field($this->_resultSet, $i);
			$arregloMeta[] = $metaRow;
			$i++;
		}
		return $arregloMeta;
	}
  
  function obtenerParametrosConexion()
  {
	return $this->_parametrosConexion;
  }
  
	function obtenerNumeroFilas()
	{
		return mysql_num_rows($this->_resultSet);
	}
	
	function existeRegistro($campos, $tablas, $condiciones)
	{
		$sql = "SELECT $campos FROM $tablas WHERE $condiciones";
		$this->ejecutarSQL($sql);
		return $this->obtenerNumeroFilas();
	}
}
?>
