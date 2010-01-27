<?php
class GeneradorNumerico extends Generador
{
	
	function generar()
	{
		$valorGenerado = "999";
		switch($this->_arregloParametros['rec_fue_codigo'])
		{
			case "6"://intervalo
				$valorGenerado = $this->_generarDesdeIntervalo();
			break;
			
			case "8"://secuencia
				$valorGenerado = $this->_generarDesdeSecuencia();
			break;
			
			default:
				$valorGenerado = parent::generar();
			break;
		}
		return $valorGenerado;
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
		
	}
	
	/**
	 * Se encarga de generar un dato sintético apartir de un valor base y 
	 * siguiendo una secuencia. La función generar() hace uso de este método.
	 * @see		generar()
	 * @return string	Dato sintético generado. Su valor es uno de los números 
	 * 					contenidos en el rango establecido.
	 */
	function _generarDesdeSecuencia()
	{
		
	}
}
?>