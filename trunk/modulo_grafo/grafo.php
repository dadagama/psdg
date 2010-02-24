<?php
/*
 This file is part of PSDG.

    PSDG is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    PSDG is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
    along with PSDG.  If not, see <http://www.gnu.org/licenses/>.

*/


session_start();

require_once("../modulo_grafo/Grafo.inc");
$objetoGrafo = new Grafo($_SESSION['conexionBDI'],$_SESSION['usu_login']);

switch($_REQUEST['funcion'])
{
	case "obtenerEstructuraTablas":
		/*
		 * estructura json de las tablas		
		[
			{
				"nombre_tabla":"medico",
				"campos_tabla":	[
									["id","PRI"],
									["nombre",""],
									["apellido",""],
									["especialidad",""]
								]
			},
			{	"nombre_tabla"...}
		]
		*/
		echo json_encode($objetoGrafo->obtenerEstructuraTablas());
		break;

	case "obtenerRelaciones":
		echo json_encode($objetoGrafo->obtenerRelaciones());
		break;
}
?>
