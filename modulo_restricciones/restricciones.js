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
	habilitarSiguienteEtapa(true);//<=======================  OJO OJO OJO OJO OJO QUITAR
	
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
						"llave" :	{
										// the following three rules basically do the same
										valid_children : "none",
										max_children : 0,
										max_depth :0,
										icon :	{ 
													image : "../imagenes/key.png"
												}
									},
						"ok" :	{
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

function habilitarSiguienteEtapa(habilitar)
{
	if(habilitar)
	{
		$('#res_btn_siguiente').removeAttr("disabled");
		setTimeout('efecto("res_btn_siguiente","hide")',0);
		$('#res_btn_siguiente').attr("src","../imagenes/step_1_ok.png");
		setTimeout('efecto("res_btn_siguiente","fadeIn")',0);
	}
	else
	{
		setTimeout('efecto("res_btn_siguiente","hide")',0);
		$('#res_btn_siguiente').attr("src","../imagenes/step_1_off.png");
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
	$.ajax({
		async:		false,
		type: 		"POST",
		dataType:	"html",
		contentType:"application/x-www-form-urlencoded",
		url:		"../modulo_restricciones/restricciones.php",
		data:		"funcion=establecerRestriccionTabla&numero_tuplas="+$('#rec_txt_numero_tuplas').val()+"&nombre_tabla="+nombre_tabla,
		beforeSend:	ajaxSend,
		success:	ajaxSuccess,
		timeout:	10000,
		error:		ajaxError(12)
	}); 
	return false;
}

function mostrarDetalleCampo(nombre_tabla, nombre_campo, tipo_dato)
{
	$.ajax({
		async:		false,
		type: 		"POST",
		dataType:	"html",
		contentType:"application/x-www-form-urlencoded",
		url:		"../modulo_restricciones/restricciones.php",
		data:		"funcion=mostrarDetalleCampo&nombre_campo="+nombre_campo+"&nombre_tabla="+nombre_tabla+"&tipo_dato="+tipo_dato,
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
}