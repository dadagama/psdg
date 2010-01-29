<?php 
session_start();

require_once("../modulo_ejecucion/Ejecucion.inc");
$objetoEjecucion = new Ejecucion($_SESSION['conexionBDI'],$_SESSION['usu_login']);

switch($_REQUEST['funcion'])
{		
	case "anterior":
		require_once("../modulo_salida/fm_salida.php");
		break;
	
	case "iniciar":
			$_SESSION['nombres_tablas_ordenadas'] = $objetoEjecucion->crearArregloTablasOrdenadas();
			$_SESSION['estado'] = "run";
		break;
		
	case "ejecutar":
//		if($_SESSION['estado'] == "run")
//		{
//			$_SESSION['estado'] = "start";
//		}
//		else if($_SESSION['estado'] == "start")
//		{
//			$_SESSION['estado'] = "work";
////			echo "&nbsp;&nbsp;&nbsp;&nbsp;Tabla: ".$nombre_tabla." [".$num_tuplas."]";
//		}
//		else if($_SESSION['estado'] == "work")
//		{
//			$_SESSION['estado'] = "stop";
//			echo "PSDG_OK";
//		}
//		else// estado = finish
			echo "PSDG_EOF";
//		break;
		
	default:
		exit;
		break;
}
?>