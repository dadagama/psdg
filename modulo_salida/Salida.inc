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

class Salida
{
	var $conexionBDI;	
	var $usu_login;
	
	function __construct($parametrosConexion,$login)
	{
		$this->conexionBDI = new ConexionBDMySQL($parametrosConexion);
  		$this->conexionBDI->conectar();
  		$this->usu_login = $login;
	}
	
	function seleccionarSalida($tis_codigo)
	{
		if($this->verificarOpcionEscogida())
			$sql = "UPDATE set tis_codigo = '".$tis_codigo."' WHERE tis_usu_login = '".$this->usu_login."'";
		else
			$sql = "INSERT INTO PSDG_tipo_salida_escogida(tis_codigo, tis_usu_login) VALUES('".$tis_codigo."','".$this->usu_login."')";
		$this->conexionBDI->ejecutarSQL($sql);
	}
	
	function verificarOpcionEscogida()
	{
		$sql = "SELECT tis_codigo FROM PSDG_tipo_salida_escogida WHERE tis_usu_login = '".$this->usu_login."'";
		$this->conexionBDI->ejecutarSQL($sql);
		$tis_codigo = "";
		if($this->conexionBDI->obtenerNumeroFilas())
			$tis_codigo = $this->conexionBDI->obtenerFilaComoCadena();
		return $tis_codigo;
	}
}
?>
