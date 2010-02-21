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


require_once("../conexiones/ConexionBDMySQL.inc");
require_once("../herramientas/GeneradorHtml.inc");

class Ejecucion
{
	var $conexionBDI;	
	var $conexionBDO;
	var $usu_login;
	var $html;
	var $_arreglo_generadores;
	var $warnings;
	
	function __construct($parametrosConexion, $login, $lang)
	{
		$this->conexionBDI = new ConexionBDMySQL($parametrosConexion);
  		$this->conexionBDI->conectar();
  		$this->usu_login = $login;
  		$this->inicializarConexionBDO();
  		$this->html = new GeneradorHtml($lang);
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
	
	function mostrarResumen()
	{
		$this->html->tag("label", array("class"=>"etiqueta"));
			$this->html->printText("eje_lbl_resumen");
		$this->html->end("label");
		$this->html->br();
		$this->html->espacios(8);
		$this->html->tag("label", array("class"=>"etiqueta"));
			$this->html->printText("eje_lbl_conexiones");
		$this->html->end("label");
		$this->html->br();
		
		$sql = "SELECT con_nombre
				FROM PSDG_conexion
				WHERE con_usu_login = '".$this->usu_login."'";
		$this->conexionBDI->ejecutarSQL($sql);
		$info_conexiones = $this->conexionBDI->obtenerResultadoComoArreglo();
		
		foreach($info_conexiones AS $pos => $info_conexion)
		{
			$this->html->espacios(16);
			$this->html->tag("label", array("class"=>"etiqueta_cursiva"));
				$this->html->tag("img", array("src"=>"../imagenes/ok.png"),"",true);
				$this->html->espacios(2);
				$this->html->printStaticText($info_conexion[0]);
			$this->html->end("label");
			$this->html->br();
		}
		
		$this->html->espacios(8);
		$this->html->tag("label", array("class"=>"etiqueta"));
			$this->html->printText("eje_lbl_num_tuplas");
		$this->html->end("label");
		$this->html->br();
		
		$sql = "SELECT ret_nombre_tabla, ret_numero_tuplas_a_generar
				FROM PSDG_restricciones_tablas
				WHERE ret_usu_login = '".$this->usu_login."'";
		$this->conexionBDI->ejecutarSQL($sql);
		$info_tablas = $this->conexionBDI->obtenerResultadoComoArreglo();
		
		foreach($info_tablas AS $pos => $info_tabla)
		{
			$this->html->espacios(16);
			$this->html->tag("label", array("class"=>"etiqueta_cursiva"));
				$this->html->tag("img", array("src"=>"../imagenes/key.png"),"",true);	
				$this->html->espacios(2);
				$this->html->printStaticText($info_tabla[0].":");
				$this->html->espacios(2);
				$this->html->printStaticText($info_tabla[1]);
			$this->html->end("label");
			$this->html->br();
		}
		
		$this->html->espacios(8);
		$this->html->tag("label", array("class"=>"etiqueta"));
			$this->html->printText("eje_lbl_tipo_salida");
		$this->html->end("label");
		$this->html->br();
		
		$sql = "SELECT tis_codigo
				FROM PSDG_tipo_salida_escogida
				WHERE tis_usu_login = '".$this->usu_login."'";
		$this->conexionBDI->ejecutarSQL($sql);
		$info_salidas = $this->conexionBDI->obtenerResultadoComoArreglo();
		
		foreach($info_salidas AS $pos => $info_salida)
		{
			$this->html->espacios(16);
			$this->html->tag("label", array("class"=>"etiqueta_cursiva"));
				switch($info_salida[0])
				{
					case "1": $salida = $this->html->printText("sal_ttp_bd"); break;
					case "2": $salida = $this->html->printText("sal_ttp_text"); break;
				}
				$this->html->printStaticText($salida);
			$this->html->end("label");
			$this->html->br();
		}
	}
	
	function crearArregloTablasOrdenadas()
	{	
		$arreglo_tablas_ordenadas = array();
		
		$sql = "SELECT ret_nombre_tabla 
				FROM PSDG_restricciones_tablas
				WHERE ret_usu_login = '".$this->usu_login."'";
		$this->conexionBDI->ejecutarSQL($sql);
		$info_tablas = $this->conexionBDI->obtenerResultadoComoArreglo();
		$indice = 0;
		//echo "<pre> TABLAS ORDENADAS:";
		//print_r($info_tablas);
		foreach($info_tablas AS $posicion => $info_tabla)
		{
			$nombre_tabla = $info_tabla[0];
			//echo "<br/>iteracion: $posicion agregar tabla $nombre_tabla <br/>";
			$this->buscarPosicionTablaEnArreglo($nombre_tabla, $arreglo_tablas_ordenadas, (count($arreglo_tablas_ordenadas)-1));
			$indice = count($arreglo_tablas_ordenadas);
			
			//echo "<br/>elementos despues de insercion:".$indice;
		}
		//print_r($arreglo_tablas_ordenadas);
		//echo "</pre>";
		return $arreglo_tablas_ordenadas;
	}

	function buscarPosicionTablaEnArreglo($nombre_tabla, &$arreglo_tablas_ordenadas, $indice)
	{
		//echo "&nbsp;&nbsp;&nbsp; buscarPosicionTablaEnArreglo($nombre_tabla, $arreglo_tablas_ordenadas,$indice)<br/>";
		if(empty($arreglo_tablas_ordenadas))
		{
			$arreglo_tablas_ordenadas[0] = $nombre_tabla;
			//echo "&nbsp;&nbsp;&nbsp; vacio, agrego al comienzo.<br/>";
		}
		else
		{
			$tabla_ordenada = $arreglo_tablas_ordenadas[$indice];
			//echo "&nbsp;&nbsp;&nbsp; comparar con $tabla_ordenada.<br/>";
			if($this->tablaTieneDependencia($nombre_tabla, $tabla_ordenada))
			{
				$this->agregarElementoArregloEnPosicion($nombre_tabla, $arreglo_tablas_ordenadas, $indice+1);
				//echo "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; depende, agrego en posiscion $indice+1.<br/>";
			}
			else
			{
				if($indice == 0)
				{
					//echo "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; no depende, pero no hay mas, agrego en cero.<br/>";
					$this->agregarElementoArregloEnPosicion($nombre_tabla, $arreglo_tablas_ordenadas, 0);
				}
				else
				{
					//echo "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; no depende, pero hay mas, busco con $indice-1.<br/>";
					$this->buscarPosicionTablaEnArreglo($nombre_tabla, $arreglo_tablas_ordenadas, $indice-1);
				}
			}
		}
	}
	
	function tablaTieneDependencia($tabla, $tabla_ordenada)
	{
		$sql = "SELECT det_nombre_tabla_dependiente  
				FROM PSDG_dependencias_de_tablas
				WHERE det_usu_login = '".$this->usu_login."'
				AND det_nombre_tabla_dependiente = '".$tabla."'
				AND det_depende_de = '".$tabla_ordenada."'";
		//echo $sql;
		$this->conexionBDI->ejecutarSQL($sql);
		if($this->conexionBDI->obtenerNumeroFilas())
			return true;
		else
			return false;
	}
	
	
	function crearArregloCamposOrdenados($nombre_tabla)
	{
		$arreglo_campos_ordenados = array();
		
		$sql = "SELECT rec_nombre_campo 
				FROM PSDG_restricciones_campos
				WHERE rec_usu_login = '".$this->usu_login."'
				AND rec_nombre_tabla = '".$nombre_tabla."'";
		//echo $sql;
		$this->conexionBDI->ejecutarSQL($sql);
		$info_campos = $this->conexionBDI->obtenerResultadoComoArreglo();
		$indice = 0;
		//echo "<pre>CAMPOS ORDENADOS TABA $nombre_tabla<br>";
		//print_r($info_campos);
		foreach($info_campos AS $posicion => $info_campo)
		{
			$nombre_campo = $info_campo[0];
			//echo "<br/>iteracion: $posicion agregar campo $nombre_campo <br/>";
			$this->buscarPosicionCampoEnArreglo($nombre_campo, $arreglo_campos_ordenados, (count($arreglo_campos_ordenados)-1));
			$indice = count($arreglo_campos_ordenados);
			
			//echo "<br/>elementos despues de insercion:".$indice;
			//print_r($arreglo_campos_ordenados);
		}
		//print_r($arreglo_campos_ordenados);
		//echo "</pre>";
		return $arreglo_campos_ordenados;
	}
	
	
	function buscarPosicionCampoEnArreglo($nombre_campo, &$arreglo_campos_ordenados, $indice)
	{
		//echo "&nbsp;&nbsp;&nbsp; buscarPosicionTablaEnArreglo($nombre_tabla, $arreglo_tablas_ordenadas,$indice)<br/>";
		if(empty($arreglo_campos_ordenados))
		{
			$arreglo_campos_ordenados[0] = $nombre_campo;
			//echo "&nbsp;&nbsp;&nbsp; vacio, agrego al comienzo.<br/>";
		}
		else
		{
			$campo_ordenado = $arreglo_campos_ordenados[$indice];
			//echo "&nbsp;&nbsp;&nbsp; comparar con $campo_ordenado.<br/>";
			if($this->campoTieneDependencia($nombre_campo, $campo_ordenado))
			{
				$this->agregarElementoArregloEnPosicion($nombre_campo, $arreglo_campos_ordenados, $indice+1);
				//echo "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; depende, agrego en posiscion $indice+1.<br/>";
			}
			else
			{
				if($indice == 0)
				{
					//echo "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; no depende, pero no hay mas, agrego en cero.<br/>";
					$this->agregarElementoArregloEnPosicion($nombre_campo, $arreglo_campos_ordenados, 0);
				}
				else
				{
					//echo "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; no depende, pero hay mas, busco con $indice-1.<br/>";
					$this->buscarPosicionCampoEnArreglo($nombre_campo, $arreglo_campos_ordenados, $indice-1);
				}
			}
		}
	}
	
	function campoTieneDependencia($nombre_campo, $campo_ordenado)
	{
		$sql = "SELECT dec_nombre_campo_dependiente  
				FROM PSDG_dependencias_de_campos
				WHERE dec_usu_login = '".$this->usu_login."'
				AND dec_nombre_campo_dependiente = '".$nombre_campo."'
				AND dec_depende_de = '".$campo_ordenado."'";
		//echo $sql;
		$this->conexionBDI->ejecutarSQL($sql);
		if($this->conexionBDI->obtenerNumeroFilas())
			return true;
		else
			return false;
	}
	
	function agregarElementoArregloEnPosicion($elemento, &$arreglo_elementos, $posicion)
	{
		$nuevo_arreglo = array();
		$x = 0;
		for(; $x < $posicion; $x++)
			$nuevo_arreglo[$x] = $arreglo_elementos[$x];
		$nuevo_arreglo[$x] = $elemento;
		$x++;
		for(; $x <= count($arreglo_elementos); $x++)
			$nuevo_arreglo[$x] = $arreglo_elementos[$x-1];
		$arreglo_elementos = $nuevo_arreglo;
	}
	
	function mostrarMensajeOrdenarTablas()
	{
		$this->html->br();
			$this->html->tag("label", array("class"=>"etiqueta"));
				$this->html->printText("eje_lbl_inicializando");
			$this->html->end("label");
		$this->html->br();
			$this->html->espacios(4);
			$this->html->printText("eje_lbl_ordenando_tablas");
			$this->html->espacios(2);
			$this->html->tag("img", array("src"=>"../imagenes/ok.png"));
		$this->html->br();	
			$this->html->tag("label", array("class"=>"etiqueta"));
				$this->html->printText("eje_lbl_generar_datos");
			$this->html->end("label");
		$this->html->br();
	}
	
	function mostrarMensajeGenerarTabla($nombre_tabla)
	{
		$this->html->tag("label");
			$this->html->espacios(4);
			$this->html->printText("eje_lbl_generando_tabla");
		$this->html->end("label");
		$this->html->espacios(2);
		$this->html->tag("label", array("class"=>"etiqueta_cursiva"));
			$this->html->printStaticText($nombre_tabla);
		$this->html->end("label");
	}
	
	function obtenerNumeroRegistros($nombre_tabla)
	{
		$sql = "SELECT 	ret_numero_tuplas_a_generar  
				FROM PSDG_restricciones_tablas
				WHERE ret_usu_login = '".$this->usu_login."'
				AND ret_nombre_tabla = '".$nombre_tabla."'
				LIMIT 1";
		$this->conexionBDI->ejecutarSQL($sql);
		return $this->conexionBDI->obtenerFilaComoCadena();
	}
	
	function generarDatosTabla($nombre_tabla, $num_registros, $arreglo_campos)
	{
		//echo "<pre>Tabla: $nombre_tabla, num_REG: $num_registros<br>";
		//print_r($arreglo_campos);
		$this->warnings = "";
		$this->inicializarGeneradores($nombre_tabla, $arreglo_campos);
		
		$campos = implode(",", $arreglo_campos);
		//echo "++++";
//		print_r($this->_arreglo_generadores);
		for($x = 0; $x < $num_registros; $x++)
		{
			$valores = array();
			$arreglo_memoria = array(); //$this->crearArregloMemoria($arreglo_campos);
			//print_r($this->_arreglo_generadores);
			foreach($this->_arreglo_generadores AS $pos => $generador)
			{
				$valor = $generador->generar($arreglo_memoria);
				//echo "<br>$valor";
				$arreglo_memoria[$arreglo_campos[$pos]] = $valor;
				if($valor == "@null")
					$valores[] = "null";
				else
					$valores[] = "'".$valor."'";
			}
			//echo "<br>---".$valores[0];
			$valores = implode(",", $valores);
			//echo "***";
			$sql_tupla = "INSERT INTO $nombre_tabla($campos) VALUES ($valores)";
			$this->conexionBDO->ejecutarSQL($sql_tupla);
			//echo "<br>--".$sql_tupla."->".$this->conexionBDO->obtener_error();
			if($error = $this->conexionBDO->obtener_error())
				$this->warnings .= "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;".$sql_tupla." -> ".$error."<br/>";
		}
	}
	
	/*function $this->crearArregloMemoria($arreglo_campos)
	{
		$arreglo_asociativo
		foreach($arreglo_campos AS $pos => $nombre_campo)
			$arreglo_asociativo[$nombre_campo] = "";
		return $arreglo_asociativo;
	}*/
	
	function obtenerErrores()
	{
		return $this->warnings;
	}
	
	function mostrarErrores($errores)
	{
		$this->html->tag("label", array("class"=>"etiqueta_error"));
			$this->html->printStaticText($errores);
		$this->html->end("label");
	}
	
	function inicializarGeneradores($nombre_tabla, $arreglo_campos)
	{
		//	se inicializa el arreglo de generadores
		$this->_arreglo_generadores = array();
		foreach($arreglo_campos AS $pos => $nombre_campo)
		{
			//echo "<br>crearGenerador($nombre_tabla, $nombre_campo);";
			$this->_arreglo_generadores[] = $this->crearGenerador($nombre_tabla, $nombre_campo); 
		}
	}
	
	function crearGenerador($nombre_tabla, $nombre_campo)
	{
		$info_restriciones_campo = $this->obtenerRestriccionesCampo($nombre_tabla, $nombre_campo);
		$restricciones_campo = json_decode($info_restriciones_campo['rec_parametros_tipo_fuente'] , true);
		$restricciones_campo['rec_fue_codigo'] = $info_restriciones_campo['rec_fue_codigo'];
		$restricciones_campo['rec_usu_login'] = $this->usu_login;
		$restricciones_campo['rec_porcentaje_nulos'] = $info_restriciones_campo['rec_porcentaje_nulos'];
		
		$tipo_dato = $this->obtenerTipoDatoCampo($nombre_tabla, $nombre_campo);
		
		//echo "<br>restricciones campo $nombre_tabla --> $nombre_campo [$tipo_dato]:<br>";
		//print_r($restricciones_campo);
				
		$generador = "";
		switch($tipo_dato)
		{
			case "char":
				require_once('../generadores/GeneradorCaracter.inc');
				$generador = new GeneradorCaracter();
				$generador->_inicializarVariables($restricciones_campo, $this->conexionBDI);
				break;
			
			case "varchar":
				require_once('../generadores/GeneradorCadena.inc');
				$generador = new GeneradorCadena();
				$generador->_inicializarVariables($restricciones_campo, $this->conexionBDI);
				break;
			
			case "text":
				$generador = new GeneradorCadena();
				$generador->_inicializarVariables($restricciones_campo, $this->conexionBDI);
				break;
			
			case "int":
				require_once('../generadores/GeneradorNumerico.inc');
				$generador = new GeneradorNumerico();
				$generador->_inicializarVariables($restricciones_campo, $this->conexionBDI);
				break;
			
			case "bigint":
				require_once('../generadores/GeneradorNumerico.inc');
				$generador = new GeneradorNumerico();
				$generador->_inicializarVariables($restricciones_campo, $this->conexionBDI);
				break;
			
			case "tinyint":
				require_once('../generadores/GeneradorBooleano.inc');
				$generador = new GeneradorBooleano();
				$generador->_inicializarVariables($restricciones_campo, $this->conexionBDI);
				break;	
			
			case "date":
				require_once('../generadores/GeneradorFecha.inc');
				$generador = new GeneradorFecha();
				$generador->_inicializarVariables($restricciones_campo, $this->conexionBDI);
				break;
			
			case "timestamp":
				require_once('../generadores/GeneradorFecha.inc');
				$generador = new GeneradorFecha();
				$generador->_inicializarVariables($restricciones_campo, $this->conexionBDI);
				break;

		}
		return $generador;
	}
	
	function obtenerRestriccionesCampo($nombre_tabla, $nombre_campo)
	{
		$sql = "SELECT rec_fue_codigo, rec_parametros_tipo_fuente, rec_porcentaje_nulos
				FROM PSDG_restricciones_campos
				WHERE rec_usu_login = '".$this->usu_login."'
				AND rec_nombre_tabla = '".$nombre_tabla."'
				AND rec_nombre_campo = '".$nombre_campo."'
				LIMIT 1";
		$this->conexionBDI->ejecutarSQL($sql);
		//echo "<br>SQL!!!:$sql";
		return $this->conexionBDI->obtenerFilaComoArregloAsociativo();
	}
	
	function obtenerTipoDatoCampo($nombre_tabla, $nombre_campo)
	{
		$parametros_conexion_BDO = $this->conexionBDO->obtenerParametrosConexion();
		$nombre_BDO = $parametros_conexion_BDO['con_nombre_bd'];
		$sql = "	SELECT DATA_TYPE
					FROM COLUMNS
					WHERE COLUMNS.TABLE_SCHEMA = '".$nombre_BDO."'
					AND TABLE_NAME = '".$nombre_tabla."'
					AND COLUMN_NAME = '".$nombre_campo."'";
		//echo $sql;
		$this->conexionBDO->establecer_bd("information_schema");
		$this->conexionBDO->ejecutarSQL($sql);
		$tipo_dato = $this->conexionBDO->obtenerFilaComoCadena();
		$this->conexionBDO->restablecer_bd_original();
		return $tipo_dato;
	}
}
?>
