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
												"type"=>"image", "src"=>"../imagenes/help.png", 
												"alt"=>"Ayuda", 
												"title"=>$this->getText("ttp_help")));
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
	
	function printSelect(&$conexion, $codigo, $valor, $nombre_tabla, $condiciones = "", $codigo_seleccionado = "", $arreglo_atributos_asociativos = "", $arreglo_atributos = "")
	{
		$sql = "SELECT $codigo, $valor
					FROM $nombre_tabla";
		if($condiciones)
			$sql .= "WHERE $condiciones";
		$conexion->ejecutarSQL($sql);
		//echo $sql;
		$this->tag("select", $arreglo_atributos_asociativos, $arreglo_atributos);
		while($datos_opcion = $conexion->obtenerFilaComoArregloAsociativo())
		{
			
			if($datos_opcion[$codigo] == $codigo_seleccionado)
				$seleccionado = "selected";
				
			$this->tag("option", array("value"=>$datos_opcion[$codigo], $seleccionado=>$seleccionado));
				$this->printText("select_".$datos_opcion[$valor]);
			$this->end("option");
		}
		$this->end("select");
	}
}
?>