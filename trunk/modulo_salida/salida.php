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
session_start();

require_once("../modulo_salida/Salida.inc");
$objetoSalida = new Salida($_SESSION['conexionBDI'],$_SESSION['usu_login']);

switch($_REQUEST['funcion'])
{		
	case "anterior":
		require_once("../modulo_restricciones/fm_restricciones.php");
		break;

	case "siguiente":
		require_once("../modulo_ejecucion/fm_ejecucion.php");
		break;

	case "seleccionarSalida":
		$objetoSalida->seleccionarSalida($_REQUEST['tis_codigo']);
		echo "ok_nuevo";
		break;
		
	case "verificarOpcionEscogida":
		if($tis_codigo = $objetoSalida->verificarOpcionEscogida())
			echo $tis_codigo;
		else
			echo "error";
		break;	
		
	default:
		exit;
		break;
}
?>
