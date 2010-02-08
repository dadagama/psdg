<?php 
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
    along with PSDG.  If not, see <http://www.gnu.org/licenses/>.

*/

	session_start();
	
	require_once("../conexiones/ConexionBDMySQL.inc");
	$conexionBDI = new ConexionBDMySQL($_SESSION['conexionBDI']);
	$conexionBDI->conectar();

	$sql = "	SELECT pop_mensaje
				FROM PSDG_mensaje_popup
				WHERE pop_accion = '".$_REQUEST['accion']."'
				AND pop_lenguaje = '".$_SESSION['lang']."'
				LIMIT 1";
	$conexionBDI->ejecutarSQL($sql);
	if($conexionBDI->obtenerNumeroFilas() == 1)
	{
		$mensaje = $conexionBDI->obtenerResultadoComoCadena();
		echo utf8_encode($mensaje);
	}
	else
		echo "No existe ayuda para este módulo :(";
?>
