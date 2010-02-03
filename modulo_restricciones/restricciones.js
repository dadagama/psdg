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
	var rec_fue_codigo = $('#rec_fue_codigo').val();
	var rec_nombre_conexion = $('#rec_nombre_conexion').val();
	var rec_nombre_tabla_origen = $('#rec_lbl_nombre_tabla').html();
	var rec_nombre_campo_origen = $('#rec_lbl_nombre_campo').html();
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
         //$("#rec_probabilidades").show();/// hay esto?
         break;
	}
}

function actualizarVisibilidadCampoFuncionProbabilidad()
{
	$("#rec_fila_funcion_probabilidad").children().hide();
	var tipo_acceso = $("#rec_tia_codigo").val();
	if(tipo_acceso == 3)//probabilistico
		$("#rec_fila_funcion_probabilidad").children().show();
}

function actualizarVisibilidadCamposDistribucion()
{
  $("#rec_fila_lambda").children().hide();
  $("#rec_fila_media").children().hide();
  $("#rec_fila_desviacion_estandar").children().hide();
  var tipo_distribucion = $("#rec_fup_codigo").val();
  if(tipo_distribucion == 3)//exponencial
      $("#rec_fila_lambda").children().show();

  if(tipo_distribucion == 2)//normal
  {
      $("#rec_fila_media").children().show();
      $("#rec_fila_desviacion_estandar").children().show();
  }

}

function actualizarVisibilidadCampoIndependiente()
{
	$("#rec_fila_campo_independiente").children().hide();

	var tipo_campo = $('#rec_tipo_campo_biblioteca').val();

	if(tipo_campo == 2)//dependiente
		$("#rec_fila_campo_independiente").children().show();
}

function actualizarOpcionTipoCampo()
{
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
	$("#rec_probabilidades").children().hide();
	var tipo_campo_biblioteca = $("#rec_tipo_campo_biblioteca").val();
	if(tipo_campo_biblioteca != 2)//no sea dependiente
		$("#rec_probabilidades").children().show();
}

function actualizarDivDetalle(formulario)
{
	setTimeout('efecto("res_div_detalle","fadeOut")',0);//slideToggle
	setTimeout('mostrarFormularioDetalle(\''+formulario+'\')',500);
}

function mostrarFormularioDetalle(formulario)
{
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
	var nombre_campo_actual = $('#rec_lbl_nombre_campo').html();
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
	var nombre_tabla = $('#rec_lbl_nombre_tabla').html();
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