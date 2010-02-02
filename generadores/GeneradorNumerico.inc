<?php
require_once('../generadores/Generador.inc');
class GeneradorNumerico extends Generador
{
	var $_minimo;
	var $_maximo;
	
	/**
	 * Se encarga de inicializar las variables de la clase
	 */
	function _inicializarVariables($arreglo_parametros, &$conexion_BDI)
	{
		parent::_inicializarVariables($arreglo_parametros, $conexion_BDI);
		//echo "<br>_inicializarVariables()";
		//print_r($arreglo_parametros);
		switch($this->_arreglo_parametros['rec_fue_codigo'])
		{
			case "6"://intervalo
				/*
					------ arreglo_parametros -----
					rec_usu_login
					rec_fue_codigo
					rec_porcentaje_nulos
					rec_valor_desde
					rec_valor_hasta
					rec_tia_codigo
					---
					contador => rec_valor_desde
				*/
				$this->_arreglo_parametros['contador'] = $this->_arreglo_parametros['rec_valor_desde'];
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
		if($this->_debeGenerarValorNulo)
			return "null";
		//echo "<br>fuente: ".$this->_arreglo_parametros['rec_fue_codigo'];
		switch($this->_arreglo_parametros['rec_fue_codigo'])
		{
			case "6"://intervalo
				return $this->_generarDesdeIntervalo();
			break;
						
			default:
				return parent::generar($arreglo_memoria);
			break;
		}
	}
	
	/**
	 * Se encarga de generar un dato sintético apartir de un rango de valores.
	 * <br/>
	 * Si es secuencial se generarán empezando desde el primer registro de la 
	 * tabla. Si se llega al último registro y se necesitan generar más valores, 
	 * se siguen generando partiendo nuevamente desde el primer registro de la
	 * tabla. La función generar() hace uso de este método.
	 * @see		generar()
	 * @return string	Dato sintético generado. Su valor es uno de los números 
	 * 					contenidos en el rango establecido.
	 */
	function _generarDesdeIntervalo()
	{
		/*
			------ arreglo_parametros -----
			rec_usu_login
			rec_fue_codigo
			rec_porcentaje_nulos
			rec_valor_desde
			rec_valor_hasta
			rec_tia_codigo
		*/
		switch($this->_arreglo_parametros['rec_tia_codigo'])
		{
			case "1"://Secuencial
				$valor = $this->_arreglo_parametros['contador'];
				if($this->_arreglo_parametros['contador'] < $this->_arreglo_parametros['rec_valor_hasta'])
					$this->_arreglo_parametros['contador']++;
				else
					$this->_arreglo_parametros['contador'] = $this->_arreglo_parametros['rec_valor_desde'];
				return $valor;
				break;
			
			case "2"://Aleatorio
				return rand($this->_arreglo_parametros['rec_valor_desde'],$this->_arreglo_parametros['rec_valor_hasta']);
				break;
			
			case "3"://Probabilistico
				if($this->_arreglo_parametros['rec_fup_codigo'] == 1)//Uniforme
				{
					$cantidad_valores_posibles =  $this->_arreglo_parametros['rec_valor_hasta'] - $this->_arreglo_parametros['rec_valor_desde'] + 1;
					return (floor($this->_generador_numero_aleatorio->generar() * $cantidad_valores_posibles) + $this->_arreglo_parametros['rec_valor_desde']);
				}
				else if($this->_arreglo_parametros['rec_fup_codigo'] == 2)//Normal estandar
				{
					do
						$valor = $this->_generador_numero_aleatorio->generar();
					while($valor < $this->_arreglo_parametros['rec_valor_desde'] || $valor > $this->_arreglo_parametros['rec_valor_hasta']);
					return $valor;
				}
				else if($this->_arreglo_parametros['rec_fup_codigo'] == 3)//Exponencial
				{
					do
						$valor = $this->_generador_numero_aleatorio->generar();
					while($valor < $this->_arreglo_parametros['rec_valor_desde'] || $valor > $this->_arreglo_parametros['rec_valor_hasta']);
					return $valor;
				}
				break;
		}
	}
}
?>