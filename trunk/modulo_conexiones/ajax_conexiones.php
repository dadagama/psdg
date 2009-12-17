<?php 
session_start();

require_once("../conexiones/ConexionBDMySQL.inc");
$conexionBDI = new ConexionBDMySQL($_SESSION['conexionBDI']);
$conexionBDI->conectar();

switch($_REQUEST['con_tipo'])
{
	case "bd":
		$parametros_conexion = '"con_nombre_db"=>"'.$_REQUEST['con_nombre_db'].'","con_usuario"=>"'.$_REQUEST['con_usuario'].'","con_password"=>"'.$_REQUEST['con_password'].'"';
		break;
	case "archivo":
		break;
	case "biblioteca":
		break;
}

$sql = "	INSERT INTO PSDG_conexion
			VALUES (	'".$_REQUEST['con_nombre']."',
						'".$_SESSION['usu_login']."',
						'".$_REQUEST['con_tipo']."',
						'$parametros_conexion'
			)";
$conexionBDI->ejecutarSQL($sql);

echo $conexionBDI->obtenerResultset();
?>
