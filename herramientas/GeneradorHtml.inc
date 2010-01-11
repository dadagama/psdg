<?php

require_once ("../herramientas/Traductor.inc");

class GeneradorHtml
{
	var $traductor;
	
	function __construct($lang)
	{
		$this->traductor = new Traductor($lang);
	}

	function printText($texto)
	{
		echo stripslashes($this->traductor->traducir($texto));
	}
	
	function printStaticText($texto)
	{
		echo stripslashes(utf8_encode($texto));
	}
	
	function getText($texto)
	{
		return $this->traductor->traducir($texto);
	}

	function tag($tag, $arrayAtributosAsociativos="", $arrayAtributos="")
	{
		if($arrayAtributosAsociativos)
			foreach($arrayAtributosAsociativos as $tipo => $valor)
				$atributosAsociativos .= " $tipo=\"$valor\"";
		if($arrayAtributos)
			foreach($arrayAtributos as $pos => $valor)
				$atributos .= " $valor";
		echo "<".stripslashes($tag)." ".stripslashes($atributosAsociativos)." ".stripslashes($atributos).">";
	}
	
	function botonAyuda($nombreBoton)
	{
		$this->tag("div", array("class"=>"div_help"));
			$this->tag("input", array(	"onclick"=>"mostrarPopupAyuda('$nombreBoton');", 
												"type"=>"image", 
												"src"=>"../imagenes/btn_help_1.png", 
												"alt"=>"Ayuda", 
												"title"=>$this->getText("ttp_help"),
												"onmouseover"=>"this.src='../imagenes/btn_help_2.png'",
												"onmouseout"=>"this.src='../imagenes/btn_help_1.png'"));
		$this->end("div");
	}
	
	function br()
	{
		echo "<br/>";
	}
	
	function end($tipo)
	{
		echo "</$tipo>";
	}
	
	function cargarModuloJS($modulo)
	{
		$this->tag("script", array("type"=>"text/javascript", "src"=>"../modulo_$modulo/$modulo.js"));
		$this->end("script");
	}
	
	function cargarHerramientaJS($herramienta)
	{
		$this->tag("script", array("type"=>"text/javascript", "src"=>"../herramientas/$herramienta.js"));
		$this->end("script");
	}
	
	function printSelect(&$conexion = "", $codigo, $valor, $nombre_tabla, $condiciones = "", $codigo_seleccionado = "", $arreglo_atributos_asociativos = "", $arreglo_atributos = "", $primeraOpcion = "", $traducir_opciones = true)
	{
		$this->tag("select", $arreglo_atributos_asociativos, $arreglo_atributos);
		
		if($primeraOpcion)
		{
			$this->tag("option", array("value"=>""));
				$this->printText($primeraOpcion);
			$this->end("option");
		}
		
		if($conexion)
		{
			$sql = "SELECT $codigo, $valor
						FROM $nombre_tabla";
			if($condiciones)
				$sql .= " WHERE $condiciones";
			$conexion->ejecutarSQL($sql);
//			echo $sql;
			while($datos_opcion = $conexion->obtenerFilaComoArregloAsociativo())
			{
				if($datos_opcion[$codigo] == $codigo_seleccionado)
					$seleccionado = "selected";
					
				$this->tag("option", array("value"=>$datos_opcion[$codigo], $seleccionado=>$seleccionado));
					if($traducir_opciones)
						$this->printText("select_".$datos_opcion[$valor]);
					else
						$this->printStaticText($datos_opcion[$valor]);
				$this->end("option");
			}
		}
		$this->end("select");
	}
	
//	function printSelectEspecial(&$conexion = "", $sql = "", $opcion_seleccionada = "", $arreglo_atributos_asociativos = "", $arreglo_atributos = "", $primeraOpcion = "", $traducir_opciones = false)
//	{
////		echo $sql;
//		$this->tag("select", $arreglo_atributos_asociativos, $arreglo_atributos);
//		
//		if($primeraOpcion)
//		{
//			$this->tag("option", array("value"=>""));
//				$this->printText($primeraOpcion);
//			$this->end("option");
//		}
//		
//		if($conexion && $sql)
//		{
//			$conexion->ejecutarSQL($sql);
//			while($dato_opcion = $conexion->obtenerFilaComoArreglo())
//			{
//				if($dato_opcion[0] == $opcion_seleccionada)
//					$seleccionado = "selected";
//					
//				$this->tag("option", array("value"=>$dato_opcion[0], $seleccionado=>$seleccionado));
//					if($traducir_opciones)
//						$this->printText("select_".$dato_opcion[0]);
//					else
//						$this->printStaticText($dato_opcion[0]);
//				$this->end("option");
//			}
//		}
//		$this->end("select");
//	}
	
	function traducirArreglo($arreglo)
	{
		$arreglo_traduccion = array();
		foreach($arreglo AS $pos => $texto)
		{
			$arreglo_traduccion[] = $this->getText($texto);
		}
		return $arreglo_traduccion;
	}
}
?>