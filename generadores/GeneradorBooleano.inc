<?php
require_once('../generadores/Generador.inc');
class GeneradorBooleano extends Generador
{
	var $_arreglo_caracteres;
	
	/**
	 * Se encarga de inicializar las variables de la clase
	 */
	function _inicializarVariables($arreglo_parametros, &$conexion_BDI)
	{
		parent::_inicializarVariables($arreglo_parametros, $conexion_BDI);
	}

	
	/**
	 * Genera un dato sintético representado en forma de cadena cumple con
	 * las restricciones impuestas en la inicializacion.
	 * @see		inicializarParametros($arregloParametros)
	 * @return	string	Dato sintético generado.
	 */
	function generar(&$arreglo_memoria="")
	{
		
		switch($this->_arreglo_parametros['rec_fue_codigo'])
		{
			default:
				$valor = parent::generar($arreglo_memoria);
			break;
		}
		if(in_array($valor, array('','null','false','0')))
			return '0';
		else
			return '1';
	}
}
?>