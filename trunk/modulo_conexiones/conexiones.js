$(document).ready(inicializar);

function inicializar()
{
	verificarSiExisteConexionBDO();
	//para el upload de archivos con ajax
	new AjaxUpload(	'#con_nombre_archivo',
		{
			action: '../modulo_conexiones/ajax_conexiones.php',
			name: 'con_archivo',
			onSubmit : confirmarArchivo,
			onComplete: archivoEnviado
		});
	//para el upload de bibliotecas con ajax
	new AjaxUpload(	'#con_nombre_biblioteca',
		{
			action: '../modulo_conexiones/ajax_conexiones.php',
			name: 'con_biblioteca',
			onSubmit : confirmarArchivo,
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
		url:		"../modulo_conexiones/ajax_conexiones.php",
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
			url:		"../modulo_conexiones/ajax_conexiones.php",
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
	if(confirm("se utilizará el archivo ["+file+"] como fuente de valores ¿Esta seguro?") &&
			pasaValidacionCampos('archivo'))
	{
		this.setData({
			'funcion': "insertarConexion",
			'con_nombre': $("#con_nombre").val(),
			'con_tipo': $("#con_tipo").val()
		});
	}
	else
		return false;
}

function archivoEnviado(file, response)
{
	limpiarFormulario();
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
	if(datosConexion != false)
	{
		
		verificarSiExisteConexionBDO();
	}
	else
		ajaxError(18);
}

function existeBDO(existe)
{
	if(!existe)
	{
		limpiarFormulario();
		hacerVisibleCamposFormulario('bd');
		colocarFormularioBDO(true);
		ajaxSuccess();
	}
	else
	{
		limpiarFormulario();
		hacerVisibleCamposFormulario('bd');
		colocarFormularioBDO(false);
		ajaxSuccess();
	}
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