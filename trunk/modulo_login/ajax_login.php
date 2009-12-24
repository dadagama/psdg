<?php
session_start();

if(isset($_REQUEST['usu_login']) && isset($_REQUEST['usu_password']) && isset($_REQUEST['lang']))
{
	require_once("../conexiones/ConexionBDMySQL.inc");
	
	$parametrosConexion['con_servidor'] = "localhost";
	$parametrosConexion['con_usuario'] = "root";
	$parametrosConexion['con_password'] = "root";
	$parametrosConexion['con_nombre_db'] = "BDI";
	
	$_SESSION['conexionBDI'] = $parametrosConexion;

	$conexionBDI = new ConexionBDMySQL($_SESSION['conexionBDI']);
  	$conexionBDI->conectar();
	$sql = "	SELECT usu_login
				FROM PSDG_usuario
				WHERE usu_login = '".$_REQUEST['usu_login']."'
				AND usu_password = sha1('".$_REQUEST['usu_password']."')
				LIMIT 1";
	$conexionBDI->ejecutarSQL($sql);

	if($conexionBDI->obtenerNumeroFilas() == 1)
	{
		$_SESSION['lang'] = $_REQUEST['lang'];
		$_SESSION["usu_login"] = $_REQUEST['usu_login'];
		
		require_once("../modulo_conexiones/fm_conexiones.php");
	}
	else 
		echo "-1";
		
}
else
	echo "-1";
?>