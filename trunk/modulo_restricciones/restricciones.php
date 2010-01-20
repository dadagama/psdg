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
		
	case "establecerRestriccionesForaneas":
		$objetoRestricciones->establecerRestriccionesForaneas();
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
	
	case "actualizarCampoTablasBD":
		$objetoRestricciones->actualizarCampoTablasBD($_REQUEST['nombre_conexion']);
		break;
		
	case "actualizarCampoCamposBD":
		$objetoRestricciones->actualizarCampoCamposBD($_REQUEST['nombre_conexion'], $_REQUEST['nombre_tabla'],$_REQUEST['nombre_campo_actual']);
		break;
		
	case "establecerRestriccionCampo":
		switch($_REQUEST['rec_fue_codigo'])
		{
			case "1"://Ninguna
				break;
				
			case "2"://Base de datos
				$rec_parametros_tipo_fuente = '{"var":"'.$_REQUEST[''].'","var":"'.$_REQUEST[''].'","var":"'.$_REQUEST[''].'"}';
				break;
				
			case "3"://Biblioteca
				$rec_parametros_tipo_fuente = "..";
				break;
				
			case "4"://Lista de valores
				$rec_parametros_tipo_fuente = "..";
				break;
				
			case "5"://Constante
				$rec_parametros_tipo_fuente = "..";
				break;
				
			case "6"://Intervalo
				$rec_parametros_tipo_fuente = "..";
				break;
				
			case "7"://Archivo
				$rec_parametros_tipo_fuente = "..";
				break;
		}
		$objetoRestricciones->actualizarRestriccionCampo(	$_REQUEST['rec_nombre_tabla'],
															$_REQUEST['rec_nombre_campo'],
															$_REQUEST['rec_fue_codigo'],
															$rec_parametros_tipo_fuente,
															$_REQUEST['rec_porcentaje_nulos']);
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