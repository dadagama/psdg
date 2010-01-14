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
	verificarRestriccionTablaEstablecida("ok");
	habilitarSiguienteEtapa(true);//<=======================  OJO OJO OJO OJO OJO QUITAR
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
		$('#res_btn_siguiente').attr("src","../imagenes/btn_next_1.png");
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
		success:	actualizarDivDetalle,
		timeout:	10000,
		error:		ajaxError(12)
	}); 
	return false;
}

function establecerRestriccionTabla()
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
			success:	verificarRestriccionTablaEstablecida,
			timeout:	10000,
			error:		ajaxError(12)
		});
	}
	else
	{
		ajaxSuccess();
		return false;
	}
}

function verificarRestriccionTablaEstablecida(establecida)
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
													image : "../imagenes/error.png"
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
	/*nombre_tabla = $('#lbl_nombre_tabla').html();
	$.ajax({
		async:		false,
		type: 		"POST",
		dataType:	"html",
		contentType:"application/x-www-form-urlencoded",
		url:		"../modulo_restricciones/restricciones.php",
		data:		"funcion=establecerRestriccionTabla&numero_tuplas="+$('#txt_numero_tuplas').val()+"&nombre_tabla="+nombre_tabla,
		beforeSend:	ajaxSend,
		success:	ajaxSuccess,
		timeout:	10000,
		error:		ajaxError(12)
	}); 
	return false;*/
}

function actualizarFormularioFuenteDeDatos()
{
	hacerVisibleCamposFormularioFuenteDeDatos($("#rec_fuente_datos").val());
}

function hacerVisibleCamposFormularioFuenteDeDatos(tipo_conexion)
{
	$("#rec_tabla_restricciones").children().hide();
	switch(tipo_conexion)
	{
		case '1': 
			break;
		case '2':
			$("#rec_tabla_bd").show();
			break;
		case '3':
			$("#rec_tabla_biblioteca").show();
			break;
		case '4':
			$("#rec_tabla_lista").show();
			break;
		case '5':
			$("#rec_tabla_constante").show();
			break;
		case '6':
			$("#rec_tabla_intervalo").show();
			break;
		case '7':
			$("#rec_tabla_archivo").show();
			break;
	}
}

function actualizarDivDetalle(formulario)
{
	setTimeout('efecto("res_div_detalle","slideToggle")',0);
	setTimeout('mostrarFormularioDetalle(\''+formulario+'\')',500);
}

function mostrarFormularioDetalle(formulario)
{
	$('#res_div_detalle').addClass("oculto");
	$('#res_div_detalle').html(formulario);
	$('#res_div_detalle').removeClass("oculto");
	setTimeout('efecto("res_div_detalle","slideDown")',0);
	actualizarFormularioFuenteDeDatos();
}