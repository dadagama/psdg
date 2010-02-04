<?php
require_once('../generadores/Generador.inc');
class GeneradorCadena extends Generador
{
	var $_arreglo_caracteres;
	
	/**
	 * Se encarga de inicializar las variables de la clase
	 */
	function _inicializarVariables($arreglo_parametros, &$conexion_BDI)
	{
		parent::_inicializarVariables($arreglo_parametros, $conexion_BDI);
		
		//36 caracteres
		$this->arreglo_caracteres = array('a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','1','2','3','4','5','6','7','8','9','0');
		switch($this->_arreglo_parametros['rec_fue_codigo'])
		{
			case "8"://secuencia
				$this->_arreglo_parametros['contador'] = $this->_arreglo_parametros['rec_valor_secuencial'];
				break;
		}
	}

	
	/**
	 * Genera un dato sintético representado en forma de cadena cumple con
	 * las restricciones impuestas en la inicializacion.
	 * @see		inicializarParametros($arregloParametros)
	 * @return	string	Dato sintético generado.
	 */
	function generar(&$arreglo_memoria="")
	{
		//echo "<br>fuente: ".$this->_arreglo_parametros['rec_fue_codigo'];
		switch($this->_arreglo_parametros['rec_fue_codigo'])
		{
			case "8"://secuencia
				return $this->_generarDesdeSecuencia();
			break;
			
			default:
				return parent::generar($arreglo_memoria);
				break;
		}
	}
	
	/**
	 * Se encarga de generar un dato sintético apartir de un valor base y 
	 * siguiendo una secuencia. La función generar() hace uso de este método.
	 * @see		generar()
	 * @return string	Dato sintético generado. Su valor es uno de los valores 
	 * 					contenidos en la secuencia establecida.
	 */
	function _generarDesdeSecuencia()
	{
		/*	
			------ arreglo_parametros -----
			rec_usu_login
			rec_fue_codigo
			rec_porcentaje_nulos
			rec_valor_secuencial
			rec_delta_secuencial
			---
			contador => rec_valor_secuencial
		*/
		$arreglo_binario_invertido = $this->_obtenerContadorEnArregloBinario();
		$dato = "";
		foreach($arreglo_binario_invertido AS $pos => $utilizar)
			if($utilizar)
				$dato .= $this->arreglo_caracteres[$pos];
		$this->_arreglo_parametros['contador'] += $this->_arreglo_parametros['rec_delta_secuencial'];
		//2147483647 => maximo numero entero en php en server 32 bits
		//es decir q el maximo valor de la secuencia es
		//abcdefghijklmnopqrstuvwxyz12345
		if($this->_arreglo_parametros['contador'] >= 2147483647)
			$this->_arreglo_parametros['contador'] = $this->_arreglo_parametros['rec_valor_secuencial'];
		return $dato;
	}
	
	function _obtenerContadorEnArregloBinario()
	{
		$arreglo_binario_invertido = array();
		$dividendo = $this->_arreglo_parametros['contador'];
		$divisor = 2;
		do
		{
			$multiplicador = $dividendo / $divisor;
			$modulo = $dividendo % $divisor;
			$arreglo_binario_invertido[] = $modulo;
			$dividendo = $multiplicador;
		}
		while($multiplicador != 0);
		
		return $arreglo_binario_invertido;
	}
}
?>