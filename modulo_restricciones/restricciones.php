<?php 
session_start();

require_once("../modulo_restricciones/Restricciones.inc");
$objetoRestricciones = new Restricciones($_SESSION['conexionBDI'], $_SESSION['usu_login'], $_SESSION['lang']);

switch($_REQUEST['funcion'])
{		
	case "anterior":
		require_once("../modulo_conexiones/fm_conexiones.php");
		break;

	case "siguiente":
		require_once("../modulo_salida/fm_salida.php");
		break;
		
	default:
		exit;
		break;
}
?>