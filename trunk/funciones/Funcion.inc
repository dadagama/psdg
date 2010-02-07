<?php
abstract class Funcion
{
	var $_arreglo_parametros;
	function inicializarParametros($parametros)
	{
		$this->_arreglo_parametros = $parametros;
	}
	
	abstract function generar();	
}
?>