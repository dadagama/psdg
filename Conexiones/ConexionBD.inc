<?php
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
  function inicializarSQL($instruccionSQL);
  
  /**
   * Ejecuta la instrucción de la variable _sql de la clase en la base de datos 
   * y guarda el resultado en la variable _resultSet de la clase.
   * @return	resource|boolean	Para SELECT, SHOW, DESCRIBE y EXPLAIN 
   * 								retorna un resultset que se asigna a la 
   * 								variable _resultSet de la clase ó Falso en 
   * 								caso de error. Para INSERT, UPDATE, DELETE y 
   * 								DROP retorna Verdadero si es satisfactoria ó 
   * 								Falso en caso de error.
   * @see		inicializarSQL($instruccionSQL)
   * @see		obtenerResultadoComoArreglo()
   */
  function ejecutarSQL($arregloParametros = "");
  
  /**
   * Transforma el resulset de la clase en un arreglo asociativo y lo retorna.
   * El resulset de la clase se debe encontrar inicializado antes de hacer el 
   * llamado a esta función.
   * @see		inicializarSQL($instruccionSQL)
   * @return 	array	Arreglo asociativo que representa un registro de la 
   * 					consulta. [nombreCampo] => [valorCampo].
   */
  function obtenerResultadoComoArreglo();
  
  
}
?>