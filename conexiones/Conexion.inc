<?php
/**
 * Interfaz para estandarizar las conexiones a fuentes externas.
 * @author	dadagama
 * @since	21-11-2009
 * @version	1.0
 */
abstract class Conexion
{
  /**
   * Arreglo asociativo que almacena los datos necesarios para realizar esta 
   * conexión con la fuente externa. estos son las posibles valores:<br/>
   * --- Para conexion con archivo ---<br/>
   * ['rutaArchivo']	=> string<br/>
   * ['modo']			=> string<br/>
   * --- Para conexion con BD ---<br/>
   * ['con_servidor']	=> string<br/>
   * ['con_usuario']	=> string<br/>
   * ['con_password']	=> string<br/>
   * ['con_nombre_bd']	=> string
   * @var	array
   */
  var $_parametrosConexion;
  
  /**
   * Establece los parametros de conexión inicializando la variable
   * $_parametrosConexion de la clase con los parámetros del generador.
   * @param		&$arregloParametros	Puntero al arreglo asociativo con los 
   * 								parametros de conexión.
   */
  //abstract function inicializarParametrosDeConexion($arregloParametros);
  //Los parametros de conexion se inicializaran atraves del constructor de la
  //clase respectiva
  
  /**
   * Efectua esta conexión con la fuente externa.
   * @return	boolean	Verdadero si logra conectar, Falso en caso 
   * 					contrario.
   */
  abstract function conectar();
  
  /**
   * Termina esta conexión con la fuente externa.
   * @return	boolean	Verdadero si logra desconectar, Falso en caso contrario.
   */
  abstract function desconectar();
  
  /**
   * Retorna el arreglo que contiene los datos necesarios para realizar esta
   * conexión con la fuente externa.
   * @return	array
   */
  abstract function obtenerParametrosConexion();
}
?>
