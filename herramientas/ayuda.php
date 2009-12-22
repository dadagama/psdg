<?php 
	session_start();
	if($_REQUEST['nombreBoton'])
	{
		require_once("../conexiones/ConexionBDMySQL.inc");
				
		$conexionBDI = new ConexionBDMySQL($_SESSION['conexionBDI']);
		$conexionBDI->conectar();
		$sql = "	SELECT ayu_mensaje
					FROM PSDG_mensaje_ayuda
					WHERE ayu_nombre_boton = '".$_REQUEST['nombreBoton']."'
					AND ayu_lenguaje = '".$_SESSION['lang']."'
					LIMIT 1";
		$conexionBDI->ejecutarSQL($sql);
		if($conexionBDI->obtenerNumeroFilas() == 1)
		{
			$mensaje = $conexionBDI->obtenerResultadoComoCadena();
			echo utf8_encode($mensaje);
		}
		else
			echo "No existe ayuda para este módulo :(";
	}
	else
		echo "No llegó el numero de mensaje a mostrar :(";
?>