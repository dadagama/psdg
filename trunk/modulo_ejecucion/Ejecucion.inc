<?php 

require_once("../conexiones/ConexionBDMySQL.inc");
require_once("../herramientas/GeneradorHtml.inc");

class Ejecucion
{
	var $conexionBDI;	
	var $usu_login;
	var $html;
	
	function __construct($parametrosConexion,$login)
	{
		$this->conexionBDI = new ConexionBDMySQL($parametrosConexion);
  		$this->conexionBDI->conectar();
  		$this->usu_login = $login;
  		$this->html = new GeneradorHtml($lang);
	}
	
	function crearArregloTablasOrdenadas()
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
		
		$arreglo_tablas_ordenadas = array();
		
		$sql = "SELECT ret_nombre_tabla 
				FROM PSDG_restricciones_tablas
				WHERE ret_usu_login = '".$this->usu_login."'";
		$this->conexionBDI->ejecutarSQL($sql);
		$info_tablas = $this->conexionBDI->obtenerResultadoComoArreglo();
		$indice = 0;
		echo "<pre> TABLAS ORDENADAS:";
		//print_r($info_tablas);
		foreach($info_tablas AS $posicion => $info_tabla)
		{
			$nombre_tabla = $info_tabla[0];
			//echo "<br/>iteracion: $posicion agregar tabla $nombre_tabla <br/>";
			$this->buscarPosicionTablaEnArreglo($nombre_tabla, $arreglo_tablas_ordenadas, (count($arreglo_tablas_ordenadas)-1));
			$indice = count($arreglo_tablas_ordenadas);
			
			//echo "<br/>elementos despues de insercion:".$indice;
		}
		return $arreglo_tablas_ordenadas;
		print_r($arreglo_tablas_ordenadas);
		echo "</pre>";
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
		//echo "<pre>";
		//print_r($info_campos);
		foreach($info_campos AS $posicion => $info_campo)
		{
			$nombre_campo = $info_campo[0];
			//echo "<br/>iteracion: $posicion agregar campo $nombre_campo <br/>";
			$this->buscarPosicionCampoEnArreglo($nombre_campo, $arreglo_campos_ordenados, (count($arreglo_campos_ordenados)-1));
			$indice = count($arreglo_campos_ordenados);
			
			//echo "<br/>elementos despues de insercion:".$indice;
			print_r($arreglo_campos_ordenados);
		}
		return $arreglo_campos_ordenadas;
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
			//echo "&nbsp;&nbsp;&nbsp; comparar con $tabla_ordenada.<br/>";
			if($this->tablaTieneDependencia($nombre_campo, $campo_ordenado))
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
	
}
?>