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
			$_SESSION['estado'] = "mensaje_tabla";
			$_SESSION['indice_tablas'] = 0;
			$_SESSION['estado'] = "mensaje_tabla";
		break;
		
	case "ejecutar":
		if($_SESSION['nombres_tablas_ordenadas'][$_SESSION['indice_tablas']])
		{
			if($_SESSION['estado'] == "mensaje_tabla")
			{
			echo "entra";
				$nombre_tabla = $_SESSION['nombres_tablas_ordenadas'][$_SESSION['indice_tablas']];
				$nombres_campos = $objetoEjecucion->crearArregloCamposOrdenados($nombre_tabla);
				print_r($nombres_campos);
				//crear mensaje tabla
				$_SESSION['estado'] = "generar";
			}
			else if($_SESSION['estado'] == "generar")
			{
				//echo "<br>camelling...<br>";
				$_SESSION['estado'] = "fin_generar";
			}
			else if($_SESSION['estado'] == "fin_generar")
			{
				$_SESSION['estado'] = "mensaje_tabla";
				$_SESSION['indice_tablas']++;
				echo "PSDG_OK";
			}
		}
		else// estado = finish
			echo "PSDG_EOF";
		break;
		
	default:
		exit;
		break;
}
?>