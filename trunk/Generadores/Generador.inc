<?php
/**
 * Interfaz para estandarizar los generadores de datos sintéticos.
 * @author	dadagama
 * @since	22-11-2009
 * @version	1.0
 */
abstract class Generador
{
  /**
   * Arreglo asociativo que almacena las restricciones necesarias para generar
   * los datos sintéticos. estas son las posibles restricciones y valores:<br/>
   * ['tipoOrigen']				=>	string ['lista','tabla','archivo',
   * 										'tablaCondicional','rango'(sólo 
   * 										generador numérico)]
   * ['caracterDelimitador']	=>	char<br/>
   * <b>--- Para conexion a fuente externa ---</b><br/>
   * ['rutaArchivo']	=> string<br/>
   * ['modo']			=> string<br/>
   * ['nombreServidor']	=> string<br/>
   * ['nombreUsuario']	=> string<br/>
   * ['clave'] 			=> string<br/>
   * ['nombreBD']		=> string<br/>
   * 
   * <b>--- Para valores nulos ---</b><br/>
   * ['probabilidadValorNulo']	=> double [0.0 - 100.0]<br/>
   * 
   * <b>--- Para Lista de valores ---</b><br/>
   * ['esSecuencial']	=> boolean<br/>
   * 
   * <b>--- Para Rango de valores (Solo generador numérico) ---</b><br/>
   * ['minimoValor']	=> double<br/>
   * ['maximoValor']	=> double<br/>
   * ['esEntero']		=> boolean<br/>
   * ['esSecuencial']	=> boolean<br/>
   * 
   * <b>--- Para Tabla de valores ---</b><br/>
   * ['esSecuencial']	=> boolean<br/>
   * 
   * <b>--- Para Archivo de valores ---</b><br/>
   * ['esSecuencial']	=> boolean<br/>
   * 
   * <b>--- Para Tabla de valores condicionales ---</b><br/>
   * ['arregloNombresTablasCondicionales']	=> array<br/>
   * ['arregloNombresCamposCondicionales']	=> array<br/>
   * ['arregloCondiciones']					=> array<br/>
   * ['arregloValoresCondicionales']		=> array
   * @var	array
   */
  var $_arregloParametros;
  
  /**
   * Objeto de la clase Conexion para establecer comunicación con alguna fuente
   * externa de valores si el generador lo requiere. Se inicializa con los 
   * valores establecidos en $_arregloParametros['nombreBD']
   * @var	Conexion
   */
  var $_conexionFuenteExterna;

  /**
   * Decide si este generador debe retornar un valor nulo como dato sintético. 
   * La probabilidad de que se pueda generar este valor esta condicionada por el 
   * valor de la variable de clase $_arregloParametros['probabilidadValorNulo']. 
   * La función generar() hace uso de este método.
   * @see		generar()
   * @return	boolean	Verdadero si se debe generar un valor nulo como dato
   * 					sintético. Falso en caso contrario.
   */
  function _generarValorNulo()
  {
    $this->_arregloParametros['probabilidadValorNulo'];
  }
  
  /**
   * Se encarga de inicializar la variable $_arregloParametros de la clase que
   * almacena las restricciones del generador e inicializa la conexión con 
   * alguna fuente externa si lo requiere.
   * @param	$arregloParametros
   */
  function inicializar($arregloParametros);
  
  /**
   * Genera un dato sintético representado en forma de cadena cumpliendo las 
   * restricciones impuestas en la inicializacion.
   * @see		inicializar($arregloParametros)
   * @return	string	Dato sintético generado.
   */
  function generar();
  
  
  /**
   * Se encarga de generar un dato sintético apartir de las restricciones 
   * establecidas en la variable de la clase 
   * $_arregloParametros['esSecuencial'] para determinar si se debe acceder de 
   * manera secuencial ó aleatoria a los valores de la lista. La función 
   * generar() hace uso de este método.
   * @see		generar()
   * @return	string	Dato sintético generado.
   */
  function _generarDesdeLista();
  
  /**
   * Se encarga de generar un dato sintético apartir de las restricciones 
   * establecidas en la variable de la clase $_arregloParametros['minimoValor'] 
   * y $_arregloParametros['maximoValor'] para un rango de valores, 
   * $_arregloParametros['esSecuencial'] para determinar si se debe retornar de 
   * manera secuencial ó aleatoria los valores, 
   * $_arregloParametros['esEntero'] para determinar si se debe retornar un 
   * número entero ó de doble precisión. La función generar() hace uso de este 
   * método.
   * @see		generar()
   * @return string	Dato sintético generado. Su valor es uno de los números 
   * 				contenidos en el rango establecido.
   */
  //function _generarDesdeRango(); ==> para generador numerico nomas
  
  /**
   * Se encarga de generar un dato sintético utilizando el objeto de la clase 
   * $_conexionFuenteExterna para valores provenientes de una tabla y apartir 
   * de las restricciones establecidas en la variable de la clase
   * $_arregloParametros['esSecuencial'] para determinar si se debe acceder de 
   * manera secuencial ó aleatoria a los valores de la tabla. Si es secuencial
   * se generarán empezando desde el primer registro de la tabla. Si se llega al
   * último registro y se necesitan generar más valores, se siguen generando 
   * partiendo nuevamente desde el primer registro del a tabla. La función 
   * generar() hace uso de este método.
   * @see		generar()
   * @return	string	Dato sintético generado. Su valor es uno de los 
   * 					registros contenidos en la tabla. 
   */
  function _generarDesdeTabla();
  
  /**
   * Se encarga de generar un dato sintético utilizando el objeto de la clase 
   * $_conexionFuenteExterna para valores provenientes de un archivo y apartir 
   * de las restricciones establecidas en la variable de la clase
   * $_arregloParametros['esSecuencial'] para determinar si se debe acceder de 
   * manera secuencial ó aleatoria a los valores del archivo. Si es secuencial
   * se generarán empezando desde la primera palabra del archivo. Si se llega a
   * la última palabra y se necesitan generar más valores, se siguen generando 
   * partiendo nuevamente desde la primera palabra del archivo. La función 
   * generar() hace uso de este método.
   * @see		generar()
   * @return	string	Dato sintético generado. Su valor es una palabra 
   * 					contenida en el archivo.
   */
  function _generarDesdeArchivo();
  
  /**
   * Se encarga de generar un dato sintético utilizando el objeto de la clase 
   * $_conexionFuenteExterna para establecer las conexión con la tabla que 
   * contiene los valores para las restricciones condicionales.
   * $_arregloParametros['arregloNombresTablasCondicionales'],
   * $_arregloParametros['arregloNombresCamposCondicionales'],
   * $_arregloParametros['arregloCondiciones'] y
   * $_arregloParametros['arregloValoresCondicionales'] definen el conjunto de 
   * condiciones que se deberán evaluar y lo que debe retornar cada una. La 
   * función generar() hace uso de este método.
   * @see		generar()
   * @return	string	Dato sintético generado. Su valor es el primero de la 
   * 					lista de valores que satisface la condición establecida.
   */
  function generarCondicionadoDesdeTabla();
}
?>