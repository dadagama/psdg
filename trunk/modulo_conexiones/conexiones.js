function adicionarConexion()
{
	if(pasaValidacionCampos())
	{
		var datos_conexion = $("#fm_datos_conexion").serialize();
		$.ajax({
			async:		true,
			type: 		"POST",
			dataType:	"html",
			contentType:"application/x-www-form-urlencoded",
			url:		"../modulo_conexiones/ajax_conexiones.php",
			data:		"con_nombre="+$("#con_nombre").val()+"&con_tipo="+$("#con_tipo").val()+"&"+datos_conexion,
			beforeSend:	ajaxSend,
			success:	insertoConexion,
			timeout:	10000,
			error:		ajaxError(12)
		}); 
		return false;
	}
}

function pasaValidacionCampos()
{
	var validacion_abajo = false;
	var validacion_arriba = false;
	var con_tipo = $("#con_tipo").val();
	
	validacion_arriba = validarCampoNoVacio($("#con_tipo"), $("#lbl_con_tipo").html(), true) && validarCampoNoVacio($("#con_nombre"), $("#lbl_con_nombre").html(), true);
	
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
				if(validarCampoNoVacio($("#con_nombre_archivo"), $("#lbl_con_nombre_archivo").html(), true))
					validacion_abajo = true;
				break;
			case "biblioteca":
				if(validarCampoNoVacio($("#con_nombre_biblioteca"), $("#lbl_con_nombre_biblioteca").html(), true))
					validacion_abajo = true;
				break;
		}
	}
	return validacion_abajo;
}

function insertoConexion(inserto)
{
	if(inserto)
	{
		restablecerFormulario();
		ajaxSuccess();
	}
	else
		ajaxError(18);
}

function restablecerFormulario()
{
	$("#con_nombre").val("");
	$("#con_tipo").val("");
	$("#con_nombre_db").val("");
	$("#con_usuario").val("");
	$("#con_password").val("");
	$("#con_nombre_archivo").val("");
	$("#con_nombre_biblioteca").val("");
	hacerVisibleCamposFormulario('bd');
}

function hacerVisibleCamposFormulario(tipo_conexion)
{
	$("#fm_datos_conexion").;
	switch(tipo_conexion)
	{
		case "bd":

			break;
		case "archivo":

			break;
		case "biblioteca":

			break;
	}
}