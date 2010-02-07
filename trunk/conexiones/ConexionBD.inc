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
require_once("Conexion.inc");
/**
 * Interfaz para estandarizar las conexiones a Bases de datos.
 * @author	dadagama
 * @since	21-11-2009
 * @version	1.0
 */
abstract class ConexionBD extends Conexion
{
  /**
   * Almacena el resulset arrojado por una instrucción sql.
   * @var	source
   */
  var $_resultSet;
  
  /**
   * Almacena la instrucción sql en forma de cadena.
   * @var	string
   */
  var $_sql;
  
  /**
   * Almacena un identificador de conexión de MySql. 
   * @var	link
   */
  var $_conexion;
  
  abstract function establecer_bd($bd);
  
  abstract function restablecer_bd_original();
  
  /**
   * Convierte una instrucción sql en la sentencia preparada de la clase.
   * @param	$sentenciaSQL	Una instrucción sql con la sintaxis de una sentencia
   * 						preparada.
   */
  //function prepararSentencia($sentenciaSQL); ==> solo postgres
  
  /**
   * Ejecuta la sentencia preparada de la clase en la base de datos con los 
   * valores pasados como parámetro. Utilizando la función <b>_ejecutarSQL</b>.
   * @param	$arregloParametros	Los valores a sustituir en la sentencia 
   * 							preparada.
   * @see	prepararSentencia($sentenciaSQL)
   * @see	_ejecutarSQL()
   */
  //function ejecutarSentenciaPreparada($arregloParametros); ==> solo postgres
  
  /**
   * Inicializa la variable _sql de la clase con la instrucción sql. 
   * <b>_ejecutarSQL</b>.
   * @param	$instruccionSQL	Instrucción sql a ejecutar.
   * @see	ejecutarSQL()
   */
  /*abstract function inicializarSQL();*/
  
  /**
   * Ejecuta la instrucción sql en la base de datos 
   * y guarda el resultado en la variable _resultSet de la clase.
   * @param		$sql	Instrucción sql a ejecutar.
   * @return	resource|boolean	Para SELECT, SHOW, DESCRIBE y EXPLAIN 
   * 								retorna un resultset que se asigna a la 
   * 								variable _resultSet de la clase ó Falso en 
   * 								caso de error. Para INSERT, UPDATE, DELETE y 
   * 								DROP retorna Verdadero si es satisfactoria ó 
   * 								Falso en caso de error.
   * @see		obtenerResultadoComoArreglo()
   */
  abstract function ejecutarSQL($sql);
  
  /**
   * Transforma el resulset de la clase en un arreglo asociativo y lo retorna.
   * El resulset de la clase se debe encontrar inicializado antes de hacer el 
   * llamado a esta función.
   * @return 	array	Arreglo asociativo que representa un registro de la 
   * 					consulta. [nombreCampo] => [valorCampo].
   */
  abstract function obtenerResultadoComoArreglo();
  
  /**
   * Retorna el numero de filas del resulset devuelto por una sentencia SELECT
   * ó SHOW.
   * @return	int	Numero de filas almacenadas en el resultset.
   */
  abstract function obtenerNumeroFilas();
  
}
?>
