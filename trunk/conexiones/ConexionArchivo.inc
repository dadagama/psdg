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
