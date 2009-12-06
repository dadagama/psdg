<?php
class GeneradorNumerico extends Generador
{
  function inicializar($arregloParametros)
  {
    $this->_arregloParametros = $arregloParametros;
  }
  
  function generar()
  {
    switch($this->_arregloParametros['tipoOrigen'])
    {
      case "lista":
        $this->_generarDesdeLista();
        break;
        
      case "tabla":
        $this->_generarDesdeTabla();
        break;
        
      case "archivo":
        $this->_generarDesdeArchivo();
        break;
        
      case "tablaCondicional":
        $this->generarCondicionadoDesdeTabla();
        break;
        
      case "rango":
        $this->_generarDesdeRango();
        break;
    }
  }
  
  function _generarDesdeLista()
  {
    
  }
  
  function _generarDesdeTabla()
  {
    
  }
  
  function _generarDesdeArchivo()
  {
    
  }
  
  function generarCondicionadoDesdeTabla()
  {
    
  }
  
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
  function _generarDesdeRango()
  {
    
  }
}
?>