/*
 This file is part of PSDG.

    PSDG is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

*/

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
			$objetoRestricciones->establecerRestriccionesForaneas($nombre_tabla, $numero_tuplas);
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
		$objetoRestricciones->actualizarCampoTablasBD($_REQUEST['nombre_conexion'],"",$_REQUEST['nombre_tabla_actual']);
		break;
		
	case "actualizarCampoCamposBD":
		$objetoRestricciones->actualizarCampoCamposBD($_REQUEST['nombre_conexion'], $_REQUEST['nombre_tabla'],$_REQUEST['nombre_campo_actual'],"",$_REQUEST['tipo_campo_actual']);
		break;

	case "actualizarCampoCamposBiblioteca":
		$objetoRestricciones->actualizarCampoCamposBiblioteca($_REQUEST['nombre_conexion'], $_REQUEST['tipo_campo']);
		break;
		
	case "actualizarCampoIndependienteBiblioteca":
		$objetoRestricciones->actualizarCampoIndependienteBiblioteca($_REQUEST['nombre_tabla']);
		break;
		
	case "establecerRestriccionCampo":
		if($_REQUEST['rec_tia_codigo'] == 3)//si el acceso es a traves de funcion de probabilidad
		{
			$rec_fup_codigo = ',"rec_fup_codigo":"'.$_REQUEST['rec_fup_codigo'].'"';
			
			if(isset($_REQUEST['rec_lambda']))
				$rec_fup_codigo .= ',"rec_lambda":"'.$_REQUEST['rec_lambda'].'"';
			if(isset($_REQUEST['rec_media']))
				$rec_fup_codigo .= ',"rec_media":"'.$_REQUEST['rec_media'].'"';
			if(isset($_REQUEST['rec_desviacion_estandar']))
				$rec_fup_codigo .= ',"rec_desviacion_estandar":"'.$_REQUEST['rec_desviacion_estandar'].'"';
		}
		$objetoRestricciones->eliminarTablaListaDeValores($_REQUEST['rec_nombre_tabla_origen'], $_REQUEST['rec_nombre_campo_origen']);//si existe
		switch($_REQUEST['rec_fue_codigo'])
		{
			case "1"://Ninguna
				break;
				
			case "2"://Base de datos
				$rec_parametros_tipo_fuente = '{"rec_nombre_conexion":"'.$_REQUEST['rec_nombre_conexion'].'","rec_nombre_tabla":"'.$_REQUEST['rec_nombre_tabla'].'","rec_nombre_campo":"'.$_REQUEST['rec_nombre_campo'].'","rec_tia_codigo":"'.$_REQUEST['rec_tia_codigo'].'"'.$rec_fup_codigo.'}';
				if($_REQUEST['rec_nombre_conexion'] == "BDO")//si depende de una tabla de la BDO
					if($_REQUEST['rec_nombre_tabla_origen'] != $_REQUEST['rec_nombre_tabla'])//si no es de ella misma, es dependencia a nivel de tabla
						$objetoRestricciones->crearDependenciaDeTabla($_REQUEST['rec_nombre_tabla_origen'], $_REQUEST['rec_nombre_tabla']);//crear la dependendia para las prioridades.
					else//si depende de ella misma es una dependencia a nivel de campo
						$objetoRestricciones->crearDependenciaDeCampo($_REQUEST['rec_nombre_tabla'], $_REQUEST['rec_nombre_campo_origen'], $_REQUEST['rec_nombre_campo']);//crear la dependendia para las prioridades.
				break;
				
			case "3"://Biblioteca
				if($_REQUEST['rec_tipo_campo_biblioteca'] == 2)//dependiente
				{
					$rec_nombre_campo_independiente = '"rec_nombre_campo_independiente":"'.$_REQUEST['rec_nombre_campo_independiente'].'",';
					$objetoRestricciones->crearDependenciaDeCampo($_REQUEST['rec_nombre_tabla_origen'], $_REQUEST['rec_nombre_campo_origen'], $_REQUEST['rec_nombre_campo_independiente']);//crear la dependendia para las prioridades.
				}
				$rec_parametros_tipo_fuente = '{"rec_conexion_biblioteca":"'.$_REQUEST['rec_conexion_biblioteca'].'","rec_tipo_campo_biblioteca":"'.$_REQUEST['rec_tipo_campo_biblioteca'].'",'.$rec_nombre_campo_independiente.'"rec_nombre_campo_biblioteca":"'.$_REQUEST['rec_nombre_campo_biblioteca'].'","rec_tia_codigo":"'.$_REQUEST['rec_tia_codigo'].'"'.$rec_fup_codigo.'}';
				break;
				
			case "4"://Lista de valores
				$rec_nombre_tabla_lista_valores = $objetoRestricciones->crearTablaListaDeValores($_REQUEST['rec_lista_valores'], $_REQUEST['rec_nombre_tabla_origen'], $_REQUEST['rec_nombre_campo_origen']);
				$rec_parametros_tipo_fuente = '{"rec_nombre_tabla_lista_valores":"'.$rec_nombre_tabla_lista_valores.'","rec_tia_codigo":"'.$_REQUEST['rec_tia_codigo'].'"'.$rec_fup_codigo.'}';
				break;
				
			case "5"://Constante
				$rec_parametros_tipo_fuente = '{"rec_valor_constante":"'.$_REQUEST['rec_valor_constante'].'"}';
				break;
				
			case "6"://Intervalo
				$rec_parametros_tipo_fuente = '{"rec_valor_desde":"'.$_REQUEST['rec_valor_desde'].'","rec_valor_hasta":"'.$_REQUEST['rec_valor_hasta'].'","rec_tia_codigo":"'.$_REQUEST['rec_tia_codigo'].'"'.$rec_fup_codigo.'}';
				break;
				
			case "7"://Archivo
				$rec_parametros_tipo_fuente = '{"rec_conexion_archivo":"'.$_REQUEST['rec_conexion_archivo'].'","rec_tia_codigo":"'.$_REQUEST['rec_tia_codigo'].'"'.$rec_fup_codigo.'}';
				break;

			case "8"://Secuencial
				$rec_parametros_tipo_fuente = '{"rec_valor_secuencial":"'.$_REQUEST['rec_valor_secuencial'].'","rec_delta_secuencial":"'.$_REQUEST['rec_delta_secuencial'].'"}';
				break;
			
			case "9"://Funcion
				switch($_REQUEST['rec_fun_codigo'])
				{
					case 3://gibberish text
					case 4://gibberish varchar
						$rec_parametros_funcion = ',"rec_markov_order":"'.$_REQUEST['rec_markov_order'].'","rec_markov_length":"'.$_REQUEST['rec_markov_length'].'","rec_markov_input":"'.$_REQUEST['rec_markov_input'].'"';
						break;
				}
				$rec_parametros_tipo_fuente = '{"rec_fun_codigo":"'.$_REQUEST['rec_fun_codigo'].'"'.$rec_parametros_funcion.'}';
				break;
		}
		$objetoRestricciones->actualizarRestriccionCampo(	$_REQUEST['rec_nombre_tabla_origen'],
															$_REQUEST['rec_nombre_campo_origen'],
															$_REQUEST['rec_fue_codigo'],
															$rec_parametros_tipo_fuente,
															$_REQUEST['rec_porcentaje_nulos']);


      /// Verificar si se puede seguir al step 2          
          echo json_encode($objetoRestricciones->verificarStepCompleto());

      /// Fin verificador
		break;
		

   case "verificarStepCompleto":
      echo json_encode($objetoRestricciones->verificarStepCompleto());
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
