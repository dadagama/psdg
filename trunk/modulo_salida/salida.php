<?php 
session_start();

require_once("../modulo_salida/Salida.inc");
$objetoSalida = new Salida($_SESSION['conexionBDI'],$_SESSION['usu_login']);

switch($_REQUEST['funcion'])
{		
	case "anterior":
		require_once("../modulo_restricciones/fm_restricciones.php");
		break;

	case "siguiente":
		require_once("../modulo_ejecucion/fm_ejecucion.php");
		break;
		
	default:
		exit;
		break;
}
?>