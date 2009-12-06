<?php
/**
 * Permite establecer conexión con un archivo de texto plano.
 * @author	dadagama
 * @since	21-11-2009
 * @version	1.0
 */
class ConexionArchivoPlano extends ConexionArchivo
{
  /**
   * Puntero al archivo.
   * @var	resource
   */
  var $_idArchivo;
  
  function inicializarParametrosDeConexion($arregloParametros)
  {
    $this->_parametrosConexion = $arregloParametros;
  }
  
  function conectar()
  {
    $rutaArchivo  = $this->_parametrosConexion['rutaArchivo'];
    $modo         = $this->_parametrosConexion['modo'];
    if(file_exists($rutaArchivo) && ($this->_idArchivo = fopen($rutaArchivo, $modo)))
      return true;
    else
      return false;
  }

  function desconectar()
  {
    if(fclose($this->_idArchivo))
      return true;
    else
      return false;
  }
  
  function leerLinea()
  {
    if(!feof($this->_idArchivo) && is_readable($rutaArchivo))
      return fgets($this->_idArchivo);
    else
      return false;
  }
  
  function escribirLinea($linea)
  {
    if(is_writable($rutaArchivo))
      return fwrite($this->_idArchivo, $linea);
  }
  
  function obtenerParametrosConexion()
  {
    return $this->_parametrosConexion;
  }
}
?>