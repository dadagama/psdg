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

require_once("../modulo_conexiones/Conexiones.inc");
$objetoConexiones = new Conexiones($_SESSION['conexionBDI'],$_SESSION['usu_login']);

switch($_REQUEST['funcion'])
{
	case "existeRegistroBDO":
		echo $objetoConexiones->existeRegistroBDO();
		break;

	case "insertarConexion":
		$con_nombre = $_REQUEST['con_nombre'];
		$usu_login = $_SESSION['usu_login'];
		$con_tipo = $_REQUEST['con_tipo'];
		$error = false;
		
		switch($con_tipo)
		{
			case "2":
				$con_servidor = $_REQUEST['con_servidor'];
				$con_nombre_bd = $_REQUEST['con_nombre_bd'];
				$con_usuario_bd = $_REQUEST['con_usuario'];
				$con_password_bd = $_REQUEST['con_password'];
				$valida = $objetoConexiones->conexionValida($con_servidor,$con_usuario_bd,$con_password_bd,$con_nombre_bd);
				if($valida)
					$parametros_conexion = '{"con_servidor":"'.$con_servidor.'","con_nombre_bd":"'.$con_nombre_bd.'","con_usuario":"'.$con_usuario_bd.'","con_password":"'.$con_password_bd.'"}';
				else
					$error = "bd";
				break;
				
			case "7":
				$nombre_archivo = $_FILES['con_archivo']['name'];
				$separador = $_REQUEST['con_separador'];
				
				if($objetoConexiones->crearTablaConexionExterna($con_nombre, $con_tipo, $nombre_archivo))
				{
					$lines = file($_FILES['con_archivo']['tmp_name']);
					foreach ($lines as $line_num => $line) 
					{
						if($separador)
							$datos = explode($separador, $line);
						else
							$datos = array($line);
						foreach ($datos as $indice => $valor)
						{
							$val[0] = $valor;//toca porque la funcion recibe un arreglo de valores
							$objetoConexiones->insertarValoresEnTabla($con_nombre, $con_tipo, $val);
						}
					}
					$parametros_conexion = '{"con_nombre_archivo_tabla":"'.$usu_login.'_'.$con_tipo.'_'.$con_nombre.'"}';
				}
				else
					$error = "archivo";
				break;
				
			case "3":
				$nombre_archivo = $_FILES['con_biblioteca']['name'];
				$archivo = file($_FILES['con_biblioteca']['tmp_name']);

				if($objetoConexiones->crearTablaConexionExterna($con_nombre, $con_tipo, $nombre_archivo, $archivo[0]))
				{
					foreach ($archivo as $line_num => $line) 
					{
						if($line_num != 0)//no cuento los nombres de los campos
						{
							//echo "\n  ".$line;
							$valores = explode(",", $line);
							//foreach ($datos as $indice => $valor)
							$objetoConexiones->insertarValoresEnTabla($con_nombre, $con_tipo, $valores);
						}
					}
					$parametros_conexion = '{"con_nombre_biblioteca_tabla":"'.$usu_login.'_'.$con_tipo.'_'.$con_nombre.'"}';
				}
				else
					$error = "biblioteca";
				break;
		}
		if(!$error)
		{
			if($objetoConexiones->insertarConexion($con_nombre, $con_tipo, $parametros_conexion))
				echo true;
			else
				echo "conexion";
		}
		else
			echo $error;
		break;
		
	case "obtenerConexiones":
		$arregloConexiones = $objetoConexiones->obtenerArregloInfoConexiones();
		echo json_encode($arregloConexiones);
		break;
	
	case "eliminarConexion":
		$con_nombre = $_REQUEST['con_nombre'];
		$con_tipo = $_REQUEST['con_tipo'];
		echo $objetoConexiones->eliminarConexion($con_nombre, $con_tipo);
		break;
		
	case "siguiente":
		require_once("../modulo_restricciones/fm_restricciones.php");
		break;

	default:
		exit;
		break;
}
?>
