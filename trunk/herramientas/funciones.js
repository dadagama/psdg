function establecerPosicionSecuencia(secuencia_activa)
{
	for ( var int = 1; int <= 4; int++) 
	{
		if(int < secuencia_activa)
			$("#step_"+int).attr("src","../imagenes/step_"+int+"_ok.png");
		else if(int == secuencia_activa)
			$("#step_"+int).attr("src","../imagenes/step_"+int+"_on.png");
		else
			$("#step_"+int).attr("src","../imagenes/step_"+int+"_off.png");
	}
	mostrarBotonLogout(secuencia_activa);
}

function mostrarBotonLogout(secuencia_activa)
{
	if(secuencia_activa != 0)
		setTimeout('efecto("div_logout","fadeIn")',1500);
	else
		setTimeout('efecto("div_logout","hide")',0);
}

function cerrarSesion()
{
	$.ajax({
		async:		false,
		type: 		"POST",
		dataType:	"html",
		contentType:"application/x-www-form-urlencoded",
		url:		"../herramientas/logout.php",
		data:		"logout=true",
		success:	redireccionarIndex
	});
	return false;
}

function redireccionarIndex() 
{
	document.location.href="../modulo_login/index.php";
}

function eliminar(nombreElemento)
{
	$("#"+nombreElemento).remove();
}

function efecto(nombreElemento, nombreEfecto)
{
	switch(nombreEfecto)
	{
		case "slideToggle":
			$("#"+nombreElemento).slideToggle("slow",ajaxSuccess);
			break;
		case "fadeIn":
			$("#"+nombreElemento).fadeIn("slow",ajaxSuccess);
			break;
		case "fadeOut":
			$("#"+nombreElemento).fadeOut("slow",ajaxSuccess);
			break;
		case "hide":
			$("#"+nombreElemento).hide();
			break;	
		default:
			$("#"+nombreElemento).show("slow",ajaxSuccess);
			break;
	}
}

function ajaxSend()
{
	var lbl_status = $("#lbl_status");
	lbl_status.html(lang_js[10]);
	lbl_status.removeClass("error");
	var lbl_loading = $("#lbl_loading");
	lbl_loading.html('<img src="../imagenes/loading_bar.gif"/>');
}

function ajaxSuccess()
{
	var lbl_status = $("#lbl_status");
	lbl_status.html(lang_js[11]);
	lbl_status.removeClass("error");
	var lbl_loading = $("#lbl_loading");
	lbl_loading.html("");
}

function mensaje_barra_estado(numero)
{
	var lbl_status = $("#lbl_status");
	lbl_status.html(lang_js[numero]);
	lbl_status.removeClass("error");
	var lbl_loading = $("#lbl_loading");
	lbl_loading.html("");
}

function mensajeConfirmacion(numero, datos)
{
	var mensaje = lang_js[numero].replace("%v", datos);
	return confirm(mensaje);
}

function ajaxError(numero)
{
	var lbl_status = $("#lbl_status");
	lbl_status.html(lang_js[numero]);
	lbl_status.addClass("error");
	var lbl_loading = $("#lbl_loading");
	lbl_loading.html("");
}

function mostrarPopupAyuda(accion)
{
	$.ajax({
		async:		true,
		type: 		"POST",
		dataType:	"html",
		contentType:"application/x-www-form-urlencoded",
		url:		"../herramientas/popup.php",
		data:		"accion="+accion,
		success:	popupAyuda
	});
}

function mostrarPopupError(accion, mensaje_embebido)
{
	lang_js[25] = mensaje_embebido;
	$.ajax({
		async:		true,
		type: 		"POST",
		dataType:	"html",
		contentType:"application/x-www-form-urlencoded",
		url:		"../herramientas/popup.php",
		data:		"accion="+accion,
		success:	popupError
	});
}

function popupAyuda(mensaje)
{
	var div_mensaje = $("#div_mensaje");
	var div_ayuda = $("#div_ayuda");
	var lbl_ayuda = $("#lbl_ayuda");
	lbl_ayuda.html("<b>"+lang_js[13]+"</b>");
	div_ayuda.hide();
	div_ayuda.removeClass("oculto");
	div_mensaje.html(mensaje);
	setTimeout('efecto("div_ayuda","slideToggle")',0);
}

function popupError(mensaje)
{
	var div_mensaje = $("#div_mensaje");
	var div_ayuda = $("#div_ayuda");
	var lbl_ayuda = $("#lbl_ayuda");
	lbl_ayuda.html("<b>"+lang_js[24]+"</b>");
	div_ayuda.hide();
	div_ayuda.removeClass("oculto");
	mensaje = mensaje.replace("%v", lang_js[25]);
	div_mensaje.html(mensaje);
	setTimeout('efecto("div_ayuda","slideToggle")',0);
}