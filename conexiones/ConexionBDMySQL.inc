<?php
/*
 This file is part of PSDG.

    PSDG is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
    along with PSDG.  If not, see <http://www.gnu.org/licenses/>.

*/


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
	
	function obtenerNombresTablasBD($nombre_tabla_actual)
	{
		$arreglo_tablas = array();
		$this->consultarDependenciasForaneas($nombre_tabla_actual, $arreglo_tablas);
		return $arreglo_tablas;
	}
	
	function consultarDependenciasForaneas($nombre_tabla_actual, &$arreglo_tablas)
	{
		//print_r($arreglo_tablas);
		$nombre_bd = $this->_parametrosConexion['con_nombre_bd'];
		$sql = "(SELECT KEY_COLUMN_USAGE.REFERENCED_TABLE_NAME
				FROM KEY_COLUMN_USAGE
				WHERE KEY_COLUMN_USAGE.TABLE_SCHEMA = '$nombre_bd'
				AND KEY_COLUMN_USAGE.TABLE_NAME = '$nombre_tabla_actual'
				AND KEY_COLUMN_USAGE.REFERENCED_TABLE_NAME IS NOT NULL
				AND KEY_COLUMN_USAGE.REFERENCED_COLUMN_NAME IS NOT NULL)";
		$this->establecer_bd("information_schema");
		$this->ejecutarSQL($sql);
		$arreglo_nombres_tablas = $this->obtenerResultadoComoArreglo();
		if($arreglo_nombres_tablas)
		{
			//echo "TIENE dependencias.. meto $nombre_tabla_actual y busco<br>";
			$arreglo_tablas[] = array($nombre_tabla_actual);
			foreach($arreglo_nombres_tablas AS $posicion => $nombre)
			{
				//echo "buscar recursiva de..$nombre[0]<br>";
				$this->consultarDependenciasForaneas($nombre[0], $arreglo_tablas);
			}
		}
		else
		{
			//echo "NO TIENE dependencias..meto $nombre_tabla_actual<br>";
			$arreglo_tablas[] = array($nombre_tabla_actual);
		}
		$this->restablecer_bd_original();
		//print_r($arreglo_tablas);
		//return $arreglo_tablas;
	}
	
	function obtenerNombresCamposTablaBD($nombre_tabla, $tipo_campo_actual="")
	{
		$nombre_bd = $this->_parametrosConexion['con_nombre_bd'];
		if($tipo_campo_actual)
		{
			$tipo_dato = substr($tipo_campo_actual,0,strpos($tipo_campo_actual, "("));
			$sql_tipo = "AND DATA_TYPE = '$tipo_dato'";
		}
		$sql = "SELECT COLUMN_NAME 
				FROM COLUMNS 
				WHERE TABLE_NAME = '$nombre_tabla' 
				AND TABLE_SCHEMA = '$nombre_bd'
				$sql_tipo";
		$this->establecer_bd("information_schema");
		$this->ejecutarSQL($sql);
		$arreglo_nombres_campos = $this->obtenerResultadoComoArreglo();
		$this->restablecer_bd_original();
		return $arreglo_nombres_campos;
	}
}
?>
