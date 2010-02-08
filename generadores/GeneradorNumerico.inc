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

require_once('../generadores/Generador.inc');
class GeneradorNumerico extends Generador
{
	
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
					
			case "8"://secuencia
				/*	
					------ arreglo_parametros -----
					rec_usu_login
					rec_fue_codigo
					rec_porcentaje_nulos
					rec_valor_secuencial
					rec_delta_secuencial
					---
					contador
				*/
				$this->_arreglo_parametros['contador'] = $this->_arreglo_parametros['rec_valor_secuencial'];
				//no hay conexion externa
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
			case "6"://intervalo
				return $this->_generarDesdeIntervalo();
			break;

			case "8"://secuencia
				return $this->_generarDesdeSecuencia();
			break;
			
			case "9"://funcion
				return $this->_generarDesdeFuncion();
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
		$dato = $this->_arreglo_parametros['contador'];
		$this->_arreglo_parametros['contador'] += $this->_arreglo_parametros['rec_delta_secuencial'];
		return $dato;
	}

}
?>
