<?php
/*
 This file is part of PSDG.

    PSDG is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    PSDG is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
    along with PSDG.  If not, see <http://www.gnu.org/licenses/>.

*/


require_once("../conexiones/ConexionBDMySQL.inc");

class Grafo
{
	var $conexionBDI;	
	var $conexionBDO;	
	var $conexion_de_prueba;
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
					WHERE con_fue_codigo = '2'
					AND con_usu_login = '".$this->usu_login."'
					AND con_nombre = 'BDO'
					LIMIT 1";

		$this->conexionBDI->ejecutarSQL($sql);
		$con_parametros = $this->conexionBDI->obtenerResultadoComoCadena();
		$arreglo_parametros = json_decode($con_parametros, true);
		$this->conexionBDO = new ConexionBDMySQL($arreglo_parametros);
		$this->conexionBDO->conectar();
	}
	
	function obtenerEstructuraTablas()
	{
		$arregloEstructuraTablas = array();
		
		////////////////////////////////////////////////////////////////////////
		///////////////   OBTENER INFO TABLAS DE LA BDO    /////////////////////
		////////////////////////////////////////////////////////////////////////
		$sql = "SELECT ret_nombre_tabla
				FROM PSDG_restricciones_tablas
				WHERE ret_usu_login = '$this->usu_login'";
		$this->conexionBDI->ejecutarSQL($sql);
		$arreglo_nombres_tablas = $this->conexionBDI->obtenerResultadoComoArreglo();
				
		foreach($arreglo_nombres_tablas AS $pos => $arreglo_nombre_tabla)
		{
			$sql = "SELECT con_parametros
					FROM PSDG_conexion
					WHERE con_usu_login = '$this->usu_login'
					AND con_nombre = 'BDO'";
			$this->conexionBDI->ejecutarSQL($sql);
			$con_parametros = $this->conexionBDI->obtenerResultadoComoCadena();
			$arreglo_parametros = json_decode($con_parametros, true);
			//{"con_servidor":"186.80.78.233","con_nombre_bd":"bd_eps_real","con_usuario":"user","con_password":"user"}			
			
			$estructuraTabla['pertenece_a_bdo'] = true;
			$estructuraTabla['nombre_bd'] = $arreglo_parametros['con_nombre_bd'];
			$estructuraTabla['nombre_tabla'] = $arreglo_nombre_tabla[0];
			$arreglo_info_campos_tabla = $this->conexionBDO->obtenerArregloInfoCamposDeTabla($estructuraTabla['nombre_tabla']);
			
			$arreglo_campos_tabla = array();
			foreach($arreglo_info_campos_tabla AS $pos => $info_campo_tabla)
			{
				$nombre_campo = $info_campo_tabla[0];//field
				$tipo_llave = $info_campo_tabla[3];//key
				$arreglo_campos_tabla[] = array($nombre_campo, $tipo_llave);
			}
			$estructuraTabla['campos_tabla'] = $arreglo_campos_tabla;
			$arregloEstructuraTablas[] = $estructuraTabla;
		}
		
		////////////////////////////////////////////////////////////////////////
		///////////////   OBTENER INFO TABLAS DE LAS BDE    ////////////////////
		////////////////////////////////////////////////////////////////////////
		
		//obtener la info de las tablas de las BDE asociadas
		$sql = "SELECT rec_parametros_tipo_fuente
				FROM PSDG_restricciones_campos
				WHERE rec_usu_login = '$this->usu_login'
				AND rec_fue_codigo = 2
				AND rec_parametros_tipo_fuente NOT LIKE '%\"rec_nombre_conexion\":\"BDO\"%'";
		//echo $sql;
		$this->conexionBDI->ejecutarSQL($sql);
		$arreglo_parametros_conexiones = $this->conexionBDI->obtenerResultadoComoArreglo();
		
		foreach($arreglo_parametros_conexiones AS $pos => $arreglo_parametros_conexion)
		{
			//averiguo los datos para conectarme a la BDE
			$parametros_conexion = json_decode($arreglo_parametros_conexion[0], true);
			//{"rec_nombre_conexion":"BD_real","rec_nombre_tabla":"medico","rec_nombre_campo":"id","rec_tia_codigo":"2"}
			$nombre_conexion = $parametros_conexion['rec_nombre_conexion'];
			$sql = "	SELECT con_parametros
						FROM PSDG_conexion
						WHERE con_fue_codigo = '2'
						AND con_usu_login = '".$this->usu_login."'
						AND con_nombre = '$nombre_conexion'
						LIMIT 1";
			$this->conexionBDI->ejecutarSQL($sql);
			$con_parametros = $this->conexionBDI->obtenerResultadoComoCadena();
			$arreglo_parametros = json_decode($con_parametros, true);
			//{"con_servidor":"186.80.78.233","con_nombre_bd":"bd_eps_real","con_usuario":"user","con_password":"user"}
			//hago conexion con la BDE para obtener la info de sus tablas
			$conexionBDE = new ConexionBDMySQL($arreglo_parametros);
			$conexionBDE->conectar();
			//obtengo info de la tabla asociada
			$estructuraTabla = array();
			$estructuraTabla['pertenece_a_bdo'] = false;
			$estructuraTabla['nombre_bd'] = $arreglo_parametros['con_nombre_bd'];
			$estructuraTabla['nombre_tabla'] = $parametros_conexion['rec_nombre_tabla'];
			//se coloca este condicional para que solo exista una ocurrencia de cada tabla
			//y no se repita la tabla por cada relacion que exista hacia ella
			if(!$this->existeEnArregloEstructuraTablas($estructuraTabla, $arregloEstructuraTablas))
			{
				$arreglo_info_campos_tabla =  $conexionBDE->obtenerArregloInfoCamposDeTabla($parametros_conexion['rec_nombre_tabla']);
				$arreglo_campos_tabla = array();
				foreach($arreglo_info_campos_tabla AS $pos => $info_campo_tabla)
				{
					$nombre_campo = $info_campo_tabla[0];//field
					$tipo_llave = $info_campo_tabla[3];//key
					$arreglo_campos_tabla[] = array($nombre_campo, $tipo_llave);
				}
				$estructuraTabla['campos_tabla'] = $arreglo_campos_tabla;
				$arregloEstructuraTablas[] = $estructuraTabla;
			}
		}
		
		return $arregloEstructuraTablas;
	}
	
	function existeEnArregloEstructuraTablas($estructuraTabla, $arregloEstructuraTablas)
	{
		foreach($arregloEstructuraTablas AS $pos => $arregloEstructuraTabla)
		{
			if($estructuraTabla['nombre_bd'] == $arregloEstructuraTabla['nombre_bd']
			&& $estructuraTabla['nombre_tabla'] == $arregloEstructuraTabla['nombre_tabla'])
				return true;
		}
		return false;
	}
	
	function obtenerRelaciones()
	{
		$arregloRelaciones = array();
		
		$sql = "SELECT rec_nombre_tabla, rec_nombre_campo, rec_fue_codigo, rec_parametros_tipo_fuente
				FROM PSDG_restricciones_campos
				WHERE rec_usu_login = '$this->usu_login'
				AND rec_fue_codigo IN (2,3)";
		$this->conexionBDI->ejecutarSQL($sql);
		$arreglo_info_campos = $this->conexionBDI->obtenerResultadoComoArreglo();
		
		//consulto los parametros de la BDO para obtener el nombre de la BD
		$sql = "SELECT con_parametros
					FROM PSDG_conexion
					WHERE con_usu_login = '$this->usu_login'
					AND con_nombre = 'BDO'";
		$this->conexionBDI->ejecutarSQL($sql);
		$con_parametros = $this->conexionBDI->obtenerResultadoComoCadena();
		$arreglo_parametros_bdo = json_decode($con_parametros, true);
		//{"con_servidor":"localhost","con_nombre_bd":"bd_eps_sintetica","con_usuario":"root","con_password":"root"}			
		
		foreach($arreglo_info_campos AS $pos => $arreglo_info_campo)
		{
			$debe_guardar = false;
			$arreglo_campos_tabla = array();
			$arreglo_campos_tabla['fue_codigo'] = $arreglo_info_campo[2];//rec_fue_codigo
			$arreglo_campos_tabla['bd_origen'] = $arreglo_parametros_bdo['con_nombre_bd']; // nombre de la BDO
			$arreglo_campos_tabla['tabla_origen'] = $arreglo_info_campo[0];//rec_nombre_tabla
			$arreglo_campos_tabla['campo_origen'] = $arreglo_info_campo[1];//rec_nombre_campo
			
			$arreglo_parametros_destino = json_decode($arreglo_info_campo[3], true);//rec_parametros_tipo_fuente


			switch($arreglo_info_campo[2])//rec_fue_codigo
			{
				case "2"://bd
					//$arreglo_parametros => {"con_servidor":"186.80.78.233","con_nombre_bd":"bd_eps_real","con_usuario":"user","con_password":"user"}
					//$arreglo_parametros_destino => {"rec_nombre_conexion":"BDO","rec_nombre_tabla":"afiliado","rec_nombre_campo":"id","rec_tia_codigo":"2"}
					$sql = "SELECT con_parametros
							FROM PSDG_conexion
							WHERE con_usu_login = '$this->usu_login'
							AND con_nombre = '".$arreglo_parametros_destino['rec_nombre_conexion']."'";
					$this->conexionBDI->ejecutarSQL($sql);
					$con_parametros = $this->conexionBDI->obtenerResultadoComoCadena();
					$arreglo_parametros = json_decode($con_parametros, true);	
				
					$arreglo_campos_tabla['bd_destino'] = $arreglo_parametros['con_nombre_bd'];
					$arreglo_campos_tabla['tabla_destino'] = $arreglo_parametros_destino['rec_nombre_tabla'];//rec_nombre_tabla
					$arreglo_campos_tabla['campo_destino'] = $arreglo_parametros_destino['rec_nombre_campo'];//rec_nombre_campo
					$debe_guardar = true;
					break; 
					
				case "3"://biblioteca
					//$arreglo_parametros_destino => {"rec_conexion_biblioteca":"nombres_sexo","rec_tipo_campo_biblioteca":"2","rec_nombre_campo_independiente":"nombre","rec_nombre_campo_biblioteca":"Genero","rec_tia_codigo":"1"}
					if($arreglo_parametros_destino['rec_tipo_campo_biblioteca'] == 2)//si es campo dependiente
					{
						$arreglo_campos_tabla['bd_destino'] = $arreglo_parametros_bdo['con_nombre_bd']; // nombre de la BDO
						$arreglo_campos_tabla['tabla_destino'] = $arreglo_campos_tabla['tabla_origen'];//rec_nombre_tabla (LA MISMA TABLA DE ORIGEN)
						$arreglo_campos_tabla['campo_destino'] = $arreglo_parametros_destino['rec_nombre_campo_independiente'];//rec_nombre_campo
						$debe_guardar = true;
					}
					break; 
			}
			if($debe_guardar)
				$arregloRelaciones[] = $arreglo_campos_tabla;
		}
		return $arregloRelaciones;
	}
}
?>