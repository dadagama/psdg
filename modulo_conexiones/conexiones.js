$(document).ready(inicializar);

function inicializar()
{
	verificarSiExisteConexionBDO();
	actualizarListadoConexiones();
	//para el upload de archivos con ajax
	new AjaxUpload(	'#con_nombre_archivo',
		{
			action: '../modulo_conexiones/conexiones.php',
			name: 'con_archivo',
			onSubmit : confirmarArchivo,
			onComplete: archivoEnviado
		});
	//para el upload de bibliotecas con ajax
	new AjaxUpload(	'#con_nombre_biblioteca',
		{
			action: '../modulo_conexiones/conexiones.php',
			name: 'con_biblioteca',
			onSubmit : confirmarBiblioteca,
			onComplete: archivoEnviado
		});
}

function verificarSiExisteConexionBDO()
{
	$.ajax({
		async:		true,
		type: 		"POST",
		dataType:	"html",
		contentType:"application/x-www-form-urlencoded",
		url:		"../modulo_conexiones/conexiones.php",
		data:		"funcion=existeRegistroBDO",
		beforeSend:	ajaxSend,
		success:	existeBDO,
		timeout:	10000,
		error:		ajaxError(12)
	}); 
	return false;
}

function adicionarConexion()
{
	var con_tipo = $("#con_tipo").val();
	if(pasaValidacionCampos(con_tipo))
	{
		var datos_conexion = $("#fm_datos_conexion").serialize();
		$.ajax({
			async:		true,
			type: 		"POST",
			dataType:	"html",
			contentType:"application/x-www-form-urlencoded",
			url:		"../modulo_conexiones/conexiones.php",
			data:		"funcion=insertarConexion&con_nombre="+$("#con_nombre").val()+"&con_tipo="+$("#con_tipo").val()+"&"+datos_conexion,
			beforeSend:	ajaxSend,
			success:	insertoConexion,
			timeout:	10000,
			error:		ajaxError(12)
		}); 
		return false;
	}
}

function confirmarArchivo(file, ext)
{
	ajaxSend();
	if(ext == 'txt')
	{
		if(	confirm("se utilizará el archivo ["+file+"] como fuente de valores ¿Esta seguro?") &&
			pasaValidacionCampos('archivo'))
		{
			this.setData({
				'funcion': "insertarConexion",
				'con_nombre': $("#con_nombre").val(),
				'con_tipo': $("#con_tipo").val()
			});
		}
		else
		{
			ajaxSuccess();
			return false;
		}
	}
	else
	{
		ajaxError(19);
		return false;
	}
}

function confirmarBiblioteca(file, ext)
{
	ajaxSend();
	if(ext == 'lib')
	{
		if(	confirm("se utilizará el archivo ["+file+"] como biblioteca de valores ¿Esta seguro?") &&
			pasaValidacionCampos('archivo'))
		{
			this.setData({
				'funcion': "insertarConexion",
				'con_nombre': $("#con_nombre").val(),
				'con_tipo': $("#con_tipo").val()
			});
		}
		else
		{
			ajaxSuccess();
			return false;
		}
	}
	else
	{
		ajaxError(20);
		return false;
	}
}

function archivoEnviado(file, response)
{
	if(response != false)
	{
		limpiarFormulario();
		actualizarListadoConexiones();
		ajaxSuccess();
	}
	else
		ajaxError(18);
}

function pasaValidacionCampos(con_tipo)
{
	var validacion_abajo = false;
	var validacion_arriba = false;
	
	validacion_arriba = validarCampoNoVacio($("#con_nombre"), $("#lbl_con_nombre").html(), true);
	
	if(validacion_arriba)
	{
		switch(con_tipo)
		{
			case "bd":
				if(validarCampoNoVacio($("#con_nombre_db"), $("#lbl_con_nombre_db").html(), true)
					&& validarCampoNoVacio($("#con_usuario"), $("#lbl_con_usuario").html(), true)
					&& validarCampoNoVacio($("#con_password"), $("#lbl_con_password").html(), true))
					validacion_abajo = true;
				break;
			case "archivo":
				validacion_abajo = true;
				break;
			case "biblioteca":
				validacion_abajo = true;
				break;
		}
	}
	return validacion_abajo;
}

function insertoConexion(datosConexion)
{
	if(datosConexion != "")
	{
		verificarSiExisteConexionBDO();
		actualizarListadoConexiones();
	}
	else
		ajaxError(18);
}

function existeBDO(existe)
{
	limpiarFormulario();
	hacerVisibleCamposFormulario('bd');
	if(!existe)
	{
		colocarFormularioBDO(true);
	}
	else
	{
		colocarFormularioBDO(false);
	}
	ajaxSuccess();
}

function colocarFormularioBDO(colocar)
{
	if(colocar)
	{
		$("#con_nombre").val("BDO");
		$("#con_nombre").attr("disabled","disabled");
		$("#con_tipo").attr("disabled","disabled");
	}
	else
	{
		$("#con_nombre").removeAttr("disabled");
		$("#con_tipo").removeAttr("disabled");
	}
}

function limpiarFormulario()
{
	$("#con_nombre").val("");
	//$("#con_tipo").val("");
	$("#con_nombre_db").val("");
	$("#con_usuario").val("");
	$("#con_password").val("");
	$("#con_nombre_archivo").val("");
	$("#con_nombre_biblioteca").val("");
}

function actualizarFormulario()
{
	hacerVisibleCamposFormulario($("#con_tipo").val());
}

function hacerVisibleCamposFormulario(tipo_conexion)
{
	$("#div_datos_conexion").children().hide();
	switch(tipo_conexion)
	{
		case "bd":
			$("#div_con_bd").show();
			break;
		case "archivo":
			$("#div_con_archivo").show();
			break;
		case "biblioteca":
			$("#div_con_biblioteca").show();
			break;
	}
}

function actualizarListadoConexiones()
{
	$.ajax({
		async:		true,
		type: 		"POST",
		dataType:	"html",
		contentType:"application/x-www-form-urlencoded",
		url:		"../modulo_conexiones/conexiones.php",
		data:		"funcion=obtenerConexiones",
		beforeSend:	ajaxSend,
		success:	mostrarConexiones,
		timeout:	10000,
		error:		ajaxError(12)
	}); 
	return false;
}

function mostrarConexiones(conexiones)
{
	var json_data_object = eval("(" + conexiones + ")");
	var div_conexiones_establecidas = $('#div_conexiones_establecidas');
	div_conexiones_establecidas.empty();
	for(var x = 0; x < json_data_object.length; x++)
	{
		var con_nombre = json_data_object[x].con_nombre;
		var con_tipo = json_data_object[x].con_tipo;
		var imagen_tipo = "../imagenes/";
		var imagen_eliminar = "../imagenes/delete.png";
		switch(con_tipo)
		{
			case "bd":
				imagen_tipo += "bd.png";
				break;
			case "archivo":
				imagen_tipo += "txt.png";
				break;
			case "biblioteca":
				imagen_tipo += "lib.png";
				break;
		}
		
		var div = 				"<div class='fila'>" +
								"	<div class='celda vertical_centro alto_30 conexion_establecida'>" +
								"		<img src='"+imagen_tipo+"'/>" +
								"	</div>" +
								"	<div class='celda vertical_centro alto_30 conexion_establecida'>" +
								"		<label>"+con_nombre+"</label>" +
								"	</div>" +
								"	<div class='celda vertical_centro alto_30 conexion_establecida'>" +
								"		<input type='image' title='"+lang_js[21]+"' alt='eliminar_conexion' src='"+imagen_eliminar+"' onclick='eliminarConexion();'" +
								"	</div>" +
								"</div>";

		div_conexiones_establecidas.append(div);
	}
}

function eliminarConexion()
{
	alert('a');
}