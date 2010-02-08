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

require_once("../modulo_ejecucion/Ejecucion.inc");
$objetoEjecucion = new Ejecucion($_SESSION['conexionBDI'],$_SESSION['usu_login'], $_SESSION['lang']);

switch($_REQUEST['funcion'])
{		
	case "anterior":
		require_once("../modulo_salida/fm_salida.php");
		break;
	
	case "iniciar":
			$_SESSION['nombres_tablas_ordenadas'] = $objetoEjecucion->crearArregloTablasOrdenadas();
			$_SESSION['estado'] = "mensaje_tabla";
			$_SESSION['indice_tablas'] = 0;
			$_SESSION['estado'] = "mensaje_tabla";
			$objetoEjecucion->mostrarMensajeOrdenarTablas();
		break;
		
	case "ejecutar":
		if(/*$_SESSION['indice_tablas'] < 2)*/$_SESSION['nombres_tablas_ordenadas'][$_SESSION['indice_tablas']])
		{
			if($_SESSION['estado'] == "mensaje_tabla")
			{
				$nombre_tabla = $_SESSION['nombres_tablas_ordenadas'][$_SESSION['indice_tablas']];
				$_SESSION['num_registros'] = $objetoEjecucion->obtenerNumeroRegistros($nombre_tabla);
				$campos_ordenados = $objetoEjecucion->crearArregloCamposOrdenados($nombre_tabla);
				$_SESSION['nombres_campos_ordenados'] = $campos_ordenados;
				//print_r($campos_ordenados);
				$objetoEjecucion->mostrarMensajeGenerarTabla($nombre_tabla);
				$_SESSION['estado'] = "generar";
			}
			else if($_SESSION['estado'] == "generar")
			{
				$objetoEjecucion->generarDatosTabla($_SESSION['nombres_tablas_ordenadas'][$_SESSION['indice_tablas']], $_SESSION['num_registros'],$_SESSION['nombres_campos_ordenados']);
				$_SESSION['errores'] = $objetoEjecucion->obtenerErrores();
				$_SESSION['estado'] = "fin_generar";
			}
			else if($_SESSION['estado'] == "fin_generar")
			{
				$_SESSION['estado'] = "mostrar_errores";
				if($_SESSION['errores'])
					echo "PSDG_WARNING";
				else
					echo "PSDG_OK";
			}
			else if($_SESSION['estado'] == "mostrar_errores")
			{
				$objetoEjecucion->mostrarErrores($_SESSION['errores']);
				$_SESSION['estado'] = "mensaje_tabla";
				$_SESSION['indice_tablas']++;
			}
		}
		else// estado = finish
			echo "PSDG_EOF";
		break;
		
	default:
		exit;
		break;
}
?>
