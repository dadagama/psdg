<?php 
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