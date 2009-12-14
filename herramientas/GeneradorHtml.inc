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
	
	function br()
	{
		echo "<br/>";
	}
	
	function end($tipo)
	{
		echo "</$tipo>";
	}
	
	function cargarJsDeModulo($modulo)
	{
		$this->tag("script", array("type"=>"text/javascript", "src"=>"../modulo_$modulo/$modulo.js"));
		$this->end("script");
	}
	
	function cargarHerramientasJS()
	{
		$this->tag("script", array("type"=>"text/javascript", "src"=>"../herramientas/funciones.js"));
		$this->end("script");
		$this->tag("script", array("type"=>"text/javascript", "src"=>"../herramientas/validacion.js"));
		$this->end("script");
		//SE DEBERIA INDEPENDIZAR EL ARRAY DE IDIOMAS PARA NO CARGAR TODO EL JS DE LOGIN
		$this->tag("script", array("type"=>"text/javascript", "src"=>"../modulo_login/login.js"));
		$this->end("script");
	}
	
}
?>