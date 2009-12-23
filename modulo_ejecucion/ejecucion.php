<?php 
session_start();

require_once("../modulo_ejecucion/Ejecucion.inc");
$objetoEjecucion = new Ejecucion($_SESSION['conexionBDI'],$_SESSION['usu_login']);

switch($_REQUEST['funcion'])
{		
	case "anterior":
		require_once("../modulo_salida/fm_salida.php");
		break;
		
	default:
		exit;
		break;
}
?>