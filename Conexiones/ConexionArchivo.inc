<?php
/**
 * Interfaz para estandarizar las conexiones a archivos.
 * @author	dadagama
 * @since	21-11-2009
 * @version	1.0
 */
abstract class ConexionArchivo extends Conexion
{
  /**
   * Lee una linea del archivo.
   * @return	string|boolean	Una cadena con la linea leída del archivo ó 
   * 							falso si no pudo leer.
   */
  function leerLinea();
  
  /**
   * Escribe una linea en el archivo.
   * @return	int|boolean	El número de bytes escritos ó Falso si no pudo 
   * 					 	escribir.
   */
  function escribirLinea($linea);  
}
?>