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
		switch($con_tipo)
		{
			case "bd":
				$parametros_conexion = '"con_nombre_db":"'.$con_nombre_bd.'","con_usuario":"'.$con_usuario_bd.'","con_password":"'.$con_password_bd.'"';
				break;
			case "archivo":
				$parametros_conexion = '"con_nombre_archivo_tabla":"FILE_'.$usu_login.'_'.$con_nombre.'"';
				break;
			case "biblioteca":
				$parametros_conexion = '"con_nombre_biblioteca_tabla":"LIB_'.$usu_login.'_'.$con_nombre.'"';
				break;
		}
		echo $objetoConexiones->insertarConexion($con_nombre, $usu_login, $con_tipo, $parametros_conexion);
		break;
		
	default:
		exit;
		break;
}
?>