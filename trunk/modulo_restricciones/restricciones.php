<?php 
session_start();

require_once("../modulo_restricciones/Restricciones.inc");
$objetoRestricciones = new Restricciones($_SESSION['conexionBDI'], $_SESSION['usu_login'], $_SESSION['lang']);

switch($_REQUEST['funcion'])
{
	case "mostrarDetalleTabla":
		$objetoRestricciones->cargarRestriccionesTabla($_REQUEST['nombre_tabla']);
		echo $objetoRestricciones->crearFormularioRestriccionesTabla();
		break;
	
	case "construirArbolBDO":
		$objetoRestricciones->construirArbolBDO();
		break;
		
	case "establecerRestriccionTabla":
		$numero_tuplas = $_REQUEST['numero_tuplas'];
		$nombre_tabla = $_REQUEST['nombre_tabla'];
		if($numero_tuplas != 0)
			$cadena_precondiciones_no_establecidas = $objetoRestricciones->precondicionesEstablecidas($nombre_tabla);
		if($cadena_precondiciones_no_establecidas)
			echo $cadena_precondiciones_no_establecidas;
		else
		{
			$objetoRestricciones->actualizarRestriccionTabla($nombre_tabla, $numero_tuplas);
			echo "ok";
		}
		break;
		
	case "mostrarDetalleCampo":
		$objetoRestricciones->cargarRestriccionesCampo(	$_REQUEST['nombre_tabla'], 
																		$_REQUEST['nombre_campo'], 
																		$_REQUEST['tipo_dato'],
																		$_REQUEST['permite_nulos'],
																		$_REQUEST['tipo_llave'],
																		$_REQUEST['valor_default'],
																		$_REQUEST['extra']);
		echo $objetoRestricciones->crearFormularioRestriccionesCampo();
		break;
	
	case "establecerRestriccionCampo":
		//$objetoRestricciones->actualizarRestriccionCampo($nombre_tabla, $numero_tuplas);
		break;
		
		
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