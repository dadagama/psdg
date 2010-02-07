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
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

*/

<?php
require_once('../generadores/Generador.inc');
class GeneradorFecha extends Generador
{
	//var $_timestamp_minimo;
	//var $_timestamp_maximo;
	
	/**
	 * Se encarga de inicializar las variables de la clase
	 */
	function _inicializarVariables($arreglo_parametros, &$conexion_BDI)
	{
		parent::_inicializarVariables($arreglo_parametros, $conexion_BDI);

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
					contador => timestamp(rec_valor_desde)
				*/
				$arreglo_partes_fecha_actual = explode("-", $this->_arreglo_parametros['contador']);
				$anno = $arreglo_partes_fecha_actual[0];
				$mes = $arreglo_partes_fecha_actual[1];
				$dia = $arreglo_partes_fecha_actual[2];
				$timestamp_fecha_actual = mktime(0,0,0,$mes,$dia,$anno);
				
				$arreglo_partes_fecha_desde = explode("-", $this->_arreglo_parametros['rec_valor_desde']);
				$anno = $arreglo_partes_fecha_desde[0];
				$mes = $arreglo_partes_fecha_desde[1];
				$dia = $arreglo_partes_fecha_desde[2];
				$timestamp_fecha_desde = mktime(0,0,0,$mes,$dia,$anno);
				
				$arreglo_partes_fecha_hasta = explode("-", $this->_arreglo_parametros['rec_valor_hasta']);
				$anno = $arreglo_partes_fecha_hasta[0];
				$mes = $arreglo_partes_fecha_hasta[1];
				$dia = $arreglo_partes_fecha_hasta[2];
				$timestamp_fecha_hasta = mktime(0,0,0,$mes,$dia,$anno);
			
				$this->_arreglo_parametros['contador'] = $timestamp_fecha_actual;
				$this->_arreglo_parametros['timestamp_minimo'] = $timestamp_fecha_desde;
				$this->_arreglo_parametros['timestamp_maximo'] = $timestamp_fecha_hasta;
				
				//Para este caso especial, los parametros de las distribuciones se interpretan como
				//timestamp ó #dias segun sea el caso, y no como posiciones o numeros 
				if($this->_arreglo_parametros['rec_fup_codigo'] == 2)//Normal estandar
				{
					require_once ("../distribuciones/DistribucionNormalEstandar.inc");
					
					$arreglo_partes_fecha_media = explode("-", $this->_arreglo_parametros['rec_media']);
					$anno = $arreglo_partes_fecha_media[0];
					$mes = $arreglo_partes_fecha_media[1];
					$dia = $arreglo_partes_fecha_media[2];
					$timestamp_media = mktime(0,0,0,$mes,$dia,$anno);
					
					$desviacion_en_dias = $this->_arreglo_parametros['rec_desviacion_estandar'];
					$timestamp_desviacion = $desviacion_en_dias * 86400;
		
					$this->_generador_numero_aleatorio = new DistribucionNormalEstandar($timestamp_media, $timestamp_desviacion);
				}
				else if($this->_arreglo_parametros['rec_fup_codigo'] == 3)//Exponencial
				{
					require_once ("../distribuciones/DistribucionExponencial.inc");
					$lambda = $this->_arreglo_parametros['rec_lambda'];
					$this->_generador_numero_aleatorio = new DistribucionExponencial($lambda);
				}
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
				
				if($this->_arreglo_parametros['contador'] < $this->_arreglo_parametros['timestamp_maximo'])
				{
					$timestamp_nueva_fecha = $this->_arreglo_parametros['contador'] + 86400;//se suma un dia en segundos
					$this->_arreglo_parametros['contador'] = date("Y-m-d",$timestamp_nueva_fecha);
				}
				else
					$this->_arreglo_parametros['contador'] = $this->_arreglo_parametros['timestamp_minimo'];
				return date("Y-m-d",$valorrec_valor_hasta);
				break;
						
			case "2"://Aleatorio
				$timestamp_nueva_fecha = mt_rand($this->_arreglo_parametros['timestamp_minimo'], $this->_arreglo_parametros['timestamp_maximo']);
				return date("Y-m-d",$timestamp_nueva_fecha);
				break;
			
			case "3"://Probabilistico
				if($this->_arreglo_parametros['rec_fup_codigo'] == 1)//Uniforme
				{
					$cantidad_valores_posibles =  $this->_arreglo_parametros['timestamp_maximo'] - $this->_arreglo_parametros['timestamp_minimo'] + 1;
					return date("Y-m-d",(floor($this->_generador_numero_aleatorio->generar() * $cantidad_valores_posibles) + $this->_arreglo_parametros['timestamp_minimo']));
				}
				else if($this->_arreglo_parametros['rec_fup_codigo'] == 2)//Normal estandar
				{
					do
						$valor = $this->_generador_numero_aleatorio->generar();
					while($valor < $this->_arreglo_parametros['timestamp_minimo'] || $valor > $this->_arreglo_parametros['timestamp_maximo']);
					return date("Y-m-d",$valor);
				}
				else if($this->_arreglo_parametros['rec_fup_codigo'] == 3)//Exponencial
				{
					do
						$valor = $this->_generador_numero_aleatorio->generar();
					while($valor < $this->_arreglo_parametros['timestamp_minimo'] || $valor > $this->_arreglo_parametros['timestamp_maximo']);
					return date("Y-m-d",$valor);
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
		
		$arreglo_partes_fecha_actual = explode("-", $this->_arreglo_parametros['contador']);
		$anno = $arreglo_partes_fecha_actual[0];
		$mes = $arreglo_partes_fecha_actual[1];
		$dia = $arreglo_partes_fecha_actual[2];
		$timestamp_fecha_actual = mktime(0,0,0,$mes,$dia,$anno);
		
		$delta_dias = $this->_arreglo_parametros['rec_delta_secuencial'];
				
		$timestamp_nueva_fecha = $timestamp_fecha_actual + ($delta_dias * 86400);//multiplica por segundos;
		$this->_arreglo_parametros['contador'] = date("Y-m-d",$timestamp_nueva_fecha);
		//2009-01-15 <== formato estandar
		//$MiTimesTamp = mktime(hora,minuto,segundo,mes,dia,anno);// vuelca 1104534000 
		//date("Y-m-d",$MiTimeStamp);		
		return $dato;
	}
}
?>
