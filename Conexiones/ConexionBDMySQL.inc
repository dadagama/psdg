<?php
class ConexionBDMySQL extends ConexionBD
{
  function inicializarParametrosDeConexion($arregloParametros)
  {
     $this->_parametrosConexion = $arregloParametros;
  }
  
  function conectar($arregloParametros)
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
  
  function inicializarSQL($instruccionSQL)
  {
    $this->_sql = $instruccionSQL;
  }
  
  function ejecutarSQL($arregloParametros = "")
  {
    $this->_resultSet = mysql_query($this->_sql, $this->_conexion);
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