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
		if($this->_debeGenerarValorNulo())
			return "@null";
			
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
