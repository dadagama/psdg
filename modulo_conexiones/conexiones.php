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
		$con_nombre_bd = $_REQUEST['con_nombre_db'];
		$con_usuario_bd = $_REQUEST['con_usuario'];
		$con_password_bd = $_REQUEST['con_password'];
		$error = false;
		switch($con_tipo)
		{
			case "bd":
				$parametros_conexion = '"con_nombre_db":"'.$con_nombre_bd.'","con_usuario":"'.$con_usuario_bd.'","con_password":"'.$con_password_bd.'"';
				break;
			case "archivo":
				$nombre_archivo = $_FILES['con_archivo']['name'];			
				if($objetoConexiones->crearTablaConexionExterna($con_nombre, "FILE", $nombre_archivo))
				{
					$lines = file($_FILES['con_archivo']['tmp_name']);
					foreach ($lines as $line_num => $line) 
					{
						$datos = explode(" ", $line);
						foreach ($datos as $indice => $valor)
							$objetoConexiones->insertarValoresEnTabla($con_nombre, "FILE", $valor);
					}
					$parametros_conexion = '"con_nombre_archivo_tabla":"'.$usu_login.'_FILE_'.$con_nombre.'"';
				}
				else
					$error = true;
				break;
			case "biblioteca":
				$parametros_conexion = '"con_nombre_biblioteca_tabla":"'.$usu_login.'_LIB_'.$con_nombre.'"';
				break;
		}
		if(!$error)
			echo $objetoConexiones->insertarConexion($con_nombre, $con_tipo, $parametros_conexion);
		else
			echo false;
		break;
		
	case "obtenerConexiones":
		$arregloConexiones = $objetoConexiones->obtenerArregloInfoConexiones();
		echo json_encode($arregloConexiones);
		break;

	default:
		exit;
		break;
}
?>