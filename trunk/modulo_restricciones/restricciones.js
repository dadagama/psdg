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
    along with PSDG.  If not, see <http://www.gnu.org/licenses/>.

*/

$(document).ready(inicializar);

function inicializar()
{
	$('#res_div_general').hide();
	$('#res_div_general').removeClass("oculto");
	setTimeout('efecto("res_div_general","slideToggle")',1000);
	
	$('#res_div_botones_secuencia').hide();
	$('#res_div_botones_secuencia').removeClass("oculto");
	setTimeout('efecto("res_div_botones_secuencia","fadeIn")',2000);
	
	establecerPosicionSecuencia(2);
	construirArbolBDO("ok");
   verificarStep();

}

function verificarStep()
{
   $.ajax({
            async:      false,
            type:       "POST",
            dataType:   "html",
            contentType:"application/x-www-form-urlencoded",
            url:     "../modulo_restricciones/restricciones.php",
            data:    "funcion=verificarStepCompleto",
            beforeSend: ajaxSend,
            success: verificarStepCompleto,
            timeout: 10000,
            error:      ajaxError(12)
         }); 
}

function habilitarSiguienteEtapa(habilitar)
{ 
	if(habilitar)
	{
		$('#res_btn_siguiente').removeAttr("disabled");
		setTimeout('efecto("res_btn_siguiente","hide")',0);
		$('#res_btn_siguiente').attr("src","../imagenes/btn_next_1.png");
		setTimeout('efecto("res_btn_siguiente","fadeIn")',0);
	}
	else
	{
		setTimeout('efecto("res_btn_siguiente","hide")',0);
		$('#res_btn_siguiente').attr("src","../imagenes/btn_next_3.png");
		setTimeout('efecto("res_btn_siguiente","fadeIn")',0);
		$('#res_btn_siguiente').attr("disabled","disabled");
	}
}

function mostrarEtapa(ubicacion_etapa)
{
	$.ajax({
				async:		false,
				type: 		"POST",
				dataType:	"html",
				contentType:"application/x-www-form-urlencoded",
				url:		"../modulo_restricciones/restricciones.php",
				data:		"funcion="+ubicacion_etapa,
				beforeSend:	ajaxSend,
				success:	desplegarModulo,
				timeout:	10000,
				error:		ajaxError(12)
			}); 
	return false;
}

function desplegarModulo(modulo)
{
	setTimeout('efecto("res_div_general","fadeOut")',0);
	setTimeout('eliminar("res_div_general")',2000);
	
	setTimeout('efecto("res_div_botones_secuencia","fadeOut")',0);
	setTimeout('eliminar("res_div_botones_secuencia")',2000);
	$("#div_cuerpo").append(modulo);
}

function mostrarDetalleTabla(nombre_tabla)
{
	$.ajax({
		async:		false,
		type: 		"POST",
		dataType:	"html",
		contentType:"application/x-www-form-urlencoded",
		url:		"../modulo_restricciones/restricciones.php",
		data:		"funcion=mostrarDetalleTabla&nombre_tabla="+nombre_tabla,
		beforeSend:	ajaxSend,
		success:	actualizarDivDetalleTabla,
		timeout:	10000,
		error:		ajaxError(12)
	}); 
	return false;
}

function establecerRestriccionTabla()
{
	if(validarInput($('#rec_txt_numero_tuplas'), $('#ret_lbl_cantidad_tuplas').html(), 'numero', true))
	{
		nombre_tabla = $('#rec_lbl_nombre_tabla').html();
		numero_tuplas = $('#rec_txt_numero_tuplas').val();
		var acepta_eliminacion = true;
		if(numero_tuplas == 0)
			acepta_eliminacion = mensajeConfirmacion(27);
		
		if(acepta_eliminacion)
		{
			$.ajax({
				async:		false,
				type: 		"POST",
				dataType:	"html",
				contentType:"application/x-www-form-urlencoded",
				url:		"../modulo_restricciones/restricciones.php",
				data:		"funcion=establecerRestriccionTabla&numero_tuplas="+numero_tuplas+"&nombre_tabla="+nombre_tabla,
				beforeSend:	ajaxSend,
				success:	construirArbolBDO,
				timeout:	10000,
				error:		ajaxError(12)
			});
		}
		else
		{
			ajaxSuccess();
			return false;
		}
	
	  verificarStep();
	}
}

function construirArbolBDO(establecida)
{
	if(establecida == "ok")
	{
		$.ajax({
			async:		false,
			type: 		"POST",
			dataType:	"html",
			contentType:"application/x-www-form-urlencoded",
			url:		"../modulo_restricciones/restricciones.php",
			data:		"funcion=construirArbolBDO",
			beforeSend:	ajaxSend,
			success:	actualizarArbolBDO,
			timeout:	10000,
			error:		ajaxError(12)
		});
		mensaje_barra_estado(26);
	}
	else
		mostrarPopupError("res_error_1", establecida);
}

function actualizarArbolBDO(arbolBDO)
{
	$('#estructura').html("");
	$('#estructura').html(arbolBDO);
	$("#estructura").tree(
		{
			rules :	{
						// only nodes of type root can be top level nodes
						valid_children : [ "tabla" ]
					},
			types :	{
						// all node types inherit the "default" node type
						"default" :	{
										deletable : false,
										draggable : false,
										renameable : false									
									},
						"tabla" :	{
										valid_children : [ "campo","llave","ok" ],
										icon :	{ 
													image : "../imagenes/table.png"
												}
									},
						"campo" :	{
										// the following three rules basically do the same
										valid_children : "none",
										max_children : 0,
										max_depth :0,
										icon :	{ 
													image : "../imagenes/field.png"
												}
									},
						"llave_primaria" :	{
										// the following three rules basically do the same
										valid_children : "none",
										max_children : 0,
										max_depth :0,
										icon :	{ 
													image : "../imagenes/key.png"
												}
									},
						"llave_foranea" :	{
										// the following three rules basically do the same
										valid_children : "none",
										max_children : 0,
										max_depth :0,
										icon :	{ 
													image : "../imagenes/fkey.png"
												}
									},
						"unico" :	{
										// the following three rules basically do the same
										valid_children : "none",
										max_children : 0,
										max_depth :0,
										icon :	{ 
													image : "../imagenes/ok.png"
												}
									}
					},
			ui :	{
						theme_path : "../estilos/themes/apple/style.css",
						theme_name : "apple",
						animation : 200
					}
		}
	);
}

function mostrarDetalleCampo(nombre_tabla, nombre_campo, tipo_dato, permite_nulos, tipo_llave, valor_default, extra)
{
	$.ajax({
		async:		false,
		type: 		"POST",
		dataType:	"html",
		contentType:"application/x-www-form-urlencoded",
		url:		"../modulo_restricciones/restricciones.php",
		data:		"funcion=mostrarDetalleCampo" +
					"&nombre_tabla=" + nombre_tabla +
					"&nombre_campo=" + nombre_campo +
					"&tipo_dato=" + tipo_dato +
					"&permite_nulos=" + permite_nulos +
					"&tipo_llave=" + tipo_llave +
					"&valor_default=" + valor_default +
					"&extra=" + extra,
		beforeSend:	ajaxSend,
		success:	actualizarDivDetalle,
		timeout:	10000,
		error:		ajaxError(12)
	}); 
	return false;
}

function establecerRestriccionCampo()
{
	if(validarCamposFormulario())
	{
		var rec_fue_codigo = $('#rec_fue_codigo').val();
		var rec_nombre_conexion = $('#rec_nombre_conexion').val();
		var rec_nombre_tabla_origen = $('#rec_lbl_nombre_tabla_info').html();
		var rec_nombre_campo_origen = $('#rec_lbl_nombre_campo_info').html();
		var rec_parametros_tipo_fuente = $("#fm_parametros_tipo_fuente").serialize();
		var rec_porcentaje_nulos = $('#rec_porcentaje_nulos').val();
	//alert(rec_parametros_tipo_fuente);
		$.ajax({
			async:		false,
			type: 		"POST",
			dataType:	"html",
			contentType:"application/x-www-form-urlencoded",
			url:		"../modulo_restricciones/restricciones.php",
			data:		"funcion=establecerRestriccionCampo&rec_nombre_tabla_origen="+rec_nombre_tabla_origen+"&rec_nombre_campo_origen="+rec_nombre_campo_origen+"&rec_fue_codigo="+rec_fue_codigo+"&rec_nombre_conexion="+rec_nombre_conexion+"&rec_porcentaje_nulos="+rec_porcentaje_nulos+"&"+rec_parametros_tipo_fuente,
			beforeSend:	ajaxSend,
			success:	restriccionEstablecidaCorrecta,
			timeout:	10000,
			error:		ajaxError(12)
		}); 
		return false;
	}
}

function validarCamposFormulario()
{
	var validacion = false;
	var rec_fue_codigo = $('#rec_fue_codigo').val();
	if(validarInputRangoPermitido($('#rec_porcentaje_nulos'), $('#rec_lbl_porcentaje_nulos').html(), 0, 100, false))
	{
		switch(rec_fue_codigo)
		{
			case '1': //ninguna
				validacion = true;
				break;
			case '2'://bd
				if(validarSeleccionComboBox($('#rec_nombre_conexion'), $('#rec_lbl_conexion_bd').html(), false)
				&& validarSeleccionComboBox($('#rec_nombre_tabla'), $('#rec_lbl_nombre_tabla').html(), false)
				&& validarSeleccionComboBox($('#rec_nombre_campo'), $('#rec_lbl_nombre_campo').html(), false))
					validacion = true;
				break;
			case '3'://bilbioteca
				if(validarSeleccionComboBox($('#rec_conexion_biblioteca'), $('#rec_lbl_conexion_biblioteca').html(), false)
				&& validarSeleccionComboBox($('#rec_tipo_campo_biblioteca'), $('#rec_lbl_tipo_campo_biblioteca').html(), false))
					if(($('#rec_tipo_campo_biblioteca').val() == 1 //independiente
					&& validarSeleccionComboBox($('#rec_nombre_campo_biblioteca'), $('#rec_lbl_nombre_campo_biblioteca').html(), false))
					||
					($('#rec_tipo_campo_biblioteca').val() == 2 //dependiente
					&& validarSeleccionComboBox($('#rec_nombre_campo_independiente'), $('#rec_lbl_nombre_campo_independiente').html(), false)
					&& validarSeleccionComboBox($('#rec_nombre_campo_biblioteca'), $('#rec_lbl_nombre_campo_biblioteca').html(), false)))
					validacion = true;
				break;
			case '4'://lista de valores
				if(validarCampoNoVacio($('#rec_lista_valores'), $('#rec_lbl_lista_valores').html(), true))
					validacion = true;
				break;
			case '5'://constante
				if(validarCampoNoVacio($('#rec_valor_constante'), $('#rec_lbl_valor_constante').html(), true))
					validacion = true;
				break;
			case '6'://intervalo
				var tipo_dato = obtenerTipoDeDato();
				if(tipo_dato == "date" || tipo_dato == "timestamp")
				{
					if(validarInput($('#rec_valor_desde'), $('#rec_lbl_desde').html(), "fecha", false)
					&& validarInput($('#rec_valor_hasta'), $('#rec_lbl_hasta').html(), "fecha", false))
					{
						if(validarRangoFechas($('#rec_valor_desde'), $('#rec_valor_hasta'), $('#rec_lbl_desde').html(), $('#rec_lbl_hasta').html()))
							validacion = true;
					}
				}
				else if(validarInput($('#rec_valor_desde'), $('#rec_lbl_desde').html(), "numero", false)
				&& validarInput($('#rec_valor_hasta'), $('#rec_lbl_hasta').html(), "numero", false))
				{
					if(validarRango($('#rec_valor_desde'), $('#rec_valor_hasta'), $('#rec_lbl_desde').html(), $('#rec_lbl_hasta').html()))
						validacion = true;
				}
				break;
			case '7'://archivo
				if(validarSeleccionComboBox($('#rec_conexion_archivo'), $('#rec_lbl_conexion_archivo').html(), false))
					validacion = true;
				break;
			case '8'://secuencial
				var tipo_dato = obtenerTipoDeDato();
				if(tipo_dato == "date" || tipo_dato == "timestamp")
				{
					if(validarInput($('#rec_valor_secuencial'), $('#rec_lbl_valor_secuencial').html(), "fecha", false)
					&& validarInput($('#rec_delta_secuencial'), $('#rec_lbl_delta_secuencial').html(), "numero", false))
						validacion = true;
				}
				else if(validarInput($('#rec_valor_secuencial'), $('#rec_lbl_valor_secuencial').html(), "numero", false)
				&& validarInput($('#rec_delta_secuencial'), $('#rec_lbl_delta_secuencial').html(), "numero", false))
				{
					validacion = true;
				}
				break;
			case '9'://funcion
				if(validarSeleccionComboBox($('#rec_fun_codigo'), $('#rec_lbl_funcion').html(), false))
					validacion = true;
				break;
		}
	}
		//alert(validacion);
		return validacion;
}

function verificarStepCompleto(dato)
{
   if(dato=='true')
    habilitarSiguienteEtapa(true);
   else
    habilitarSiguienteEtapa(false);
}

function restriccionEstablecidaCorrecta(dato)
{
	ajaxSuccess();
   verificarStepCompleto(dato);
   alert(lang_js[26]); 
}

function actualizarFormularioFuenteDeDatos()
{
	hacerVisibleCamposFormularioFuenteDeDatos($("#rec_fue_codigo").val());
}

function hacerVisibleCamposFormularioFuenteDeDatos(tipo_conexion)
{
	$("#rec_tabla_restricciones").children().hide();
	//alert(1);
	switch(tipo_conexion)
	{
		case '1': //ninguna
			break;
		case '2'://bd
			$("#rec_tabla_bd").show();
			$("#rec_probabilidades").show();
			break;
		case '3'://bilbioteca
			$("#rec_tabla_biblioteca").show();
			$("#rec_probabilidades").show();
			break;
		case '4'://lista de valores
			$("#rec_tabla_lista").show();
			$("#rec_probabilidades").show();
			break;
		case '5'://constante
			$("#rec_tabla_constante").show();
			break;
		case '6'://intervalo
			$("#rec_tabla_intervalo").show();
			$("#rec_probabilidades").show();
			break;
		case '7'://archivo
			$("#rec_tabla_archivo").show();
			$("#rec_probabilidades").show();
			break;
		case '8'://secuencial
			$("#rec_tabla_secuencial").show();
			break;
		case '9'://funcion
			$("#rec_tabla_funcion").show();
			break;
	}
	actualizarVisibilidadCampoFuncionProbabilidad();
	actualizarEtiquetasAuxiliaresMediaYDesviacion();
}

function actualizarVisibilidadParametrosFuncion()
{
	//alert(2);
	$("#rec_tabla_markov").hide();
	var tipo_funcion = $("#rec_fun_codigo").val();
	if(tipo_funcion == 3 || tipo_funcion == 4)//gibberish varchar o text
		$("#rec_tabla_markov").show();
}

function actualizarVisibilidadCampoFuncionProbabilidad()
{
	//alert(3);
	$("#rec_fila_funcion_probabilidad").children().hide();
	var tipo_acceso = $("#rec_tia_codigo").val();
	if(tipo_acceso == 3)//probabilistico
		$("#rec_fila_funcion_probabilidad").children().show();
	actualizarVisibilidadCamposDistribucion();
}

function actualizarVisibilidadCamposDistribucion()
{
	//alert(4);
	$("#rec_fila_lambda").children().hide();
	$("#rec_fila_media").children().hide();
	$("#rec_fila_desviacion_estandar").children().hide();
	var tipo_distribucion = $("#rec_fup_codigo").val();
	var tipo_acceso = $("#rec_tia_codigo").val();
	if(tipo_acceso == 3)//probabilistico
	{
		if(tipo_distribucion == 3)//exponencial
			$("#rec_fila_lambda").children().show();
	
		if(tipo_distribucion == 2)//normal
		{
			$("#rec_fila_media").children().show();//mostrar el campo MEDIA
			$("#rec_fila_desviacion_estandar").children().show();
		}
	}

}

function actualizarEtiquetasAuxiliaresMediaYDesviacion()
{
	/* Si el tipo de fuente es [Base de datos, Biblioteca, Lista de 
	 * valores ó Archivo] la media simboliza la POSICION del valor que 
	 * será tomado como media. Si el tipo de fuente es [Intérvalo] será 
	 * tomado como un VALOR y debe cumplir con el formato del tipo de 
	 * dato, si es numérico debe ser un número, si es fecha simboliza una FECHA
	 * y debe tener el formato ISO-8601: AAAA-MM-DD.*/
	var fue_codigo = $("#rec_fue_codigo").val();
	var tipo_dato = obtenerTipoDeDato();
	$('#rec_media').datepicker( 'destroy' );//quitar funcionalidad datepicker
	//alert(fue_codigo+","+tipo_dato);
	switch(fue_codigo)
	{
		case '2'://bd
		case '3'://biblioteca
		case '4'://lista de valores
		case '7'://archivo
			$('#rec_lbl_auxiliar_media').html(lang_js[34]);//actualizo el mensaje auxiliar
			$('#rec_lbl_auxiliar_desviacion').html(lang_js[35]);
			break;
			
		case '6'://intervalo
			if(tipo_dato == "date" || tipo_dato == "timestamp")
			{
				$('#rec_lbl_auxiliar_media').html(lang_js[36]);
				$('#rec_lbl_auxiliar_desviacion').html(lang_js[37]);
				$('#rec_media').datepicker({ dateFormat: 'yy-mm-dd' });
			}
			else
			{
				$('#rec_lbl_auxiliar_media').html(lang_js[38]);
				$('#rec_lbl_auxiliar_desviacion').html(lang_js[39]);
			}
			break;
	}
}

function obtenerTipoDeDato()
{
	var tipo_dato_extendido = $("#rec_lbl_tipo_dato").html();
	var posicion_parentesis = tipo_dato_extendido.search(/\(/);
	//alert(posicion_parentesis);
	var tipo = "";
	if(posicion_parentesis != -1)
		tipo = tipo_dato_extendido.substr(0,posicion_parentesis);
	else
		tipo = tipo_dato_extendido;
	//alert(tipo);
	return tipo;
}

function actualizarVisibilidadCampoIndependiente()
{
	//alert(5);
	$("#rec_fila_campo_independiente").children().hide();
	var tipo_campo = $('#rec_tipo_campo_biblioteca').val();
	if(tipo_campo == 2)//dependiente
		$("#rec_fila_campo_independiente").children().show();
}

function actualizarOpcionTipoCampo()
{
	//alert(6);
	if(!$("#rec_conexion_biblioteca").val())
	{
		$("select#rec_tipo_campo_biblioteca option[selected]").removeAttr("selected");
		$("select#rec_tipo_campo_biblioteca option[value='']").attr("selected", "selected");
		//$("#rec_tipo_campo_biblioteca").
		//alert("h");
	}
}

function actualizarVisibilidadTipoAcceso()
{
	//alert(7);
	$("#rec_probabilidades").children().hide();
	var tipo_campo_biblioteca = $("#rec_tipo_campo_biblioteca").val();
	if(tipo_campo_biblioteca != 2)//no sea dependiente
		$("#rec_probabilidades").children().show();
}

function actualizarDivDetalleTabla(formulario)
{
	//alert(8);
	setTimeout('efecto("res_div_detalle","fadeOut")',0);//slideToggle
	setTimeout('mostrarFormularioDetalleTabla(\''+formulario+'\')',500);
}

function mostrarFormularioDetalleTabla(formulario)
{
	//alert(9);
	formulario = formulario.replace(/@br2n/g,"\n");
	$('#res_div_detalle').addClass("oculto");
	$('#res_div_detalle').html(formulario);
	$('#res_div_detalle').removeClass("oculto");
	setTimeout('efecto("res_div_detalle","fadeIn")',0);//slideDown
}

function actualizarDivDetalle(formulario)
{
	//alert(8);
	setTimeout('efecto("res_div_detalle","fadeOut")',0);//slideToggle
	setTimeout('mostrarFormularioDetalle(\''+formulario+'\')',500);
}

function mostrarFormularioDetalle(formulario)
{
	//alert(9);
	formulario = formulario.replace(/@br2n/g,"\n");
	$('#res_div_detalle').addClass("oculto");
	$('#res_div_detalle').html(formulario);
	$('#res_div_detalle').removeClass("oculto");
	setTimeout('efecto("res_div_detalle","fadeIn")',0);//slideDown
	actualizarFormularioFuenteDeDatos();
	actualizarVisibilidadCampoFuncionProbabilidad();
	actualizarVisibilidadCamposDistribucion();
	actualizarVisibilidadCampoIndependiente();
	actualizarVisibilidadTipoAcceso();
	actualizarVisibilidadParametrosFuncion();
}

function actualizarCampoTablasBD()
{
	var nombre_conexion = $('#rec_nombre_conexion').val();
	var nombre_tabla_actual = $('#rec_lbl_nombre_tabla').html();
	//alert(nombre_tabla_actual);
	$('#rec_nombre_tabla').html("");
	$.ajax({
		async:		false,
		type: 		"POST",
		dataType:	"html",
		contentType:"application/x-www-form-urlencoded",
		url:		"../modulo_restricciones/restricciones.php",
		data:		"funcion=actualizarCampoTablasBD&nombre_conexion="+nombre_conexion+"&nombre_tabla_actual="+nombre_tabla_actual,
		beforeSend:	ajaxSend,
		success:	actualizarSelectTablasBD,
		timeout:	10000,
		error:		ajaxError(12)
	});
	actualizarCampoCamposBD();
}

function actualizarSelectTablasBD(opciones)
{
	$('#rec_nombre_tabla').html(opciones);
	ajaxSuccess();
}

function actualizarCampoCamposBD()
{
	var nombre_conexion = $('#rec_nombre_conexion').val();
	var nombre_tabla = $('#rec_nombre_tabla').val();
	var nombre_campo_actual = $('#rec_lbl_nombre_campo_info').html();//se cambio por suposicion, si no funciona hay q confirmar
	var tipo_campo_actual = $('#rec_lbl_tipo_dato').html();
	$('#rec_nombre_campo').html("");
	$.ajax({
		async:		false,
		type: 		"POST",
		dataType:	"html",
		contentType:"application/x-www-form-urlencoded",
		url:		"../modulo_restricciones/restricciones.php",
		data:		"funcion=actualizarCampoCamposBD&nombre_conexion="+nombre_conexion+"&nombre_tabla="+nombre_tabla+"&nombre_campo_actual="+nombre_campo_actual+"&tipo_campo_actual="+tipo_campo_actual,
		beforeSend:	ajaxSend,
		success:	actualizarSelectCampoBD,
		timeout:	10000,
		error:		ajaxError(12)
	});
}

function actualizarSelectCampoBD(opciones)
{
	$('#rec_nombre_campo').html(opciones);
	ajaxSuccess();
}

function actualizarCampoCamposBiblioteca()
{
	var nombre_conexion = $('#rec_conexion_biblioteca').val();
	var tipo_campo = $('#rec_tipo_campo_biblioteca').val();
	actualizarVisibilidadCampoIndependiente();
	
	$('#rec_nombre_campo_biblioteca').html("");
	//alert(nombre_conexion+","+tipo_campo);
	$.ajax({
		async:		false,
		type: 		"POST",
		dataType:	"html",
		contentType:"application/x-www-form-urlencoded",
		url:		"../modulo_restricciones/restricciones.php",
		data:		"funcion=actualizarCampoCamposBiblioteca&nombre_conexion="+nombre_conexion+"&tipo_campo="+tipo_campo,
		beforeSend:	ajaxSend,
		success:	actualizarSelectCampoBiblioteca,
		timeout:	10000,
		error:		ajaxError(12)
	});
}

function actualizarSelectCampoBiblioteca(opciones)
{
	$('#rec_nombre_campo_biblioteca').html(opciones);
	ajaxSuccess();
}

function actualizarCampoIndependienteBiblioteca()
{
	var nombre_tabla = $('#rec_lbl_nombre_tabla_info').html();
	//$this->arreglo_restricciones['rec_nombre_tabla'], $parametros_conexion['rec_nombre_campo_independiente']
	$('#rec_nombre_campo_independiente').html("");
	//alert(nombre_conexion+","+tipo_campo);
	$.ajax({
		async:		false,
		type: 		"POST",
		dataType:	"html",
		contentType:"application/x-www-form-urlencoded",
		url:		"../modulo_restricciones/restricciones.php",
		data:		"funcion=actualizarCampoIndependienteBiblioteca&nombre_tabla="+nombre_tabla,
		beforeSend:	ajaxSend,
		success:	actualizarSelectCampoIndependiente,
		timeout:	10000,
		error:		ajaxError(12)
	});
}

function actualizarSelectCampoIndependiente(opciones)
{
	$('#rec_nombre_campo_independiente').html(opciones);
	ajaxSuccess();
}
