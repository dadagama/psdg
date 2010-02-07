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

require_once("../conexiones/ConexionBDMySQL.inc");

class Traductor
{
	var $lang;
	var $conexionBDI;
	
	function __construct($lang)
	{
		$this->lang = $lang;
		$parametrosConexion['con_servidor'] = "localhost";
		$parametrosConexion['con_usuario'] = "root";
		$parametrosConexion['con_password'] = "root";
		$parametrosConexion['con_nombre_bd'] = "BDI";
		
		$this->conexionBDI = new ConexionBDMySQL($parametrosConexion);
  		$this->conexionBDI->conectar();
	}
	
	function traducir($texto)
	{
		$resultado = $texto;
		$sql = "	SELECT idi_traduccion
					FROM PSDG_idioma 
					WHERE idi_texto = '$texto'
					AND idi_lenguaje = '".$this->lang."'
					LIMIT 1";
		$this->conexionBDI->ejecutarSQL($sql);
		if($this->conexionBDI->obtenerNumeroFilas() > 0)
		{
			$resultado = $this->conexionBDI->obtenerResultadoComoCadena();
		}
		//echo "%%".$resultado;
		return utf8_encode($resultado);
	}
}
?>
