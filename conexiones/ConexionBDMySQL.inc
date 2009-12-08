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
    $servidor = $this->_parametrosConexion['nombreServidor'];
    $usuario  = $this->_parametrosConexion['nombreUsuario'];
    $clave    = $this->_parametrosConexion['clave'];
    $bd       = $this->_parametrosConexion['nombreBD'];
    
	if($this->_conexion = mysql_connect($servidor, $usuario, $clave))
	  return mysql_select_db($bd, $this->_conexion);
	else
	  return false;
  }
  
  function desconectar()
  {
    return mysql_close($this->_conexion);
  }
  
  /*function inicializarSQL()
  {
    $this->_sql = $instruccionSQL;
  }*/
  
  function ejecutarSQL($instruccionSQL)
  {
    $this->_resultSet = mysql_query(/*$this->_sql*/$instruccionSQL, $this->_conexion);
  }
  
  function obtenerResultadoComoArreglo()
  {
    return mysql_fetch_assoc($this->_resultSet);
  }
  
  function obtenerParametrosConexion()
  {
    return $this->_parametrosConexion;
  }
}
?>
