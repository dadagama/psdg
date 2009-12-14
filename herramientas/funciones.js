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
		$("#div_logout").show();
	else
		$("#div_logout").hide();
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

function ocultar(nombreElemento)
{
	$("#"+nombreElemento).fadeOut("slow");
	setTimeout('eliminar("'+nombreElemento+'")',2000);
}

function eliminar(nombreElemento)
{
	$("#"+nombreElemento).remove();
}

function mostrar(nombreElemento)
{
	$("#"+nombreElemento).slideToggle("slow",ajaxSuccess);
}

function esconder(nombreElemento)
{
	$("#"+nombreElemento).slideToggle("slow",ajaxSuccess);
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

function ajaxError(numero)
{
	var lbl_status = $("#lbl_status");
	lbl_status.html(lang_js[numero]);
	lbl_status.addClass("error");
	var lbl_loading = $("#lbl_loading");
	lbl_loading.html("");
}

function mostrarPopupAyuda(numero)
{
	$.ajax({
		async:		true,
		type: 		"POST",
		dataType:	"html",
		contentType:"application/x-www-form-urlencoded",
		url:		"../herramientas/ayuda.php",
		data:		"numero="+numero,
		success:	mostrarPopup
	});
}

function mostrarPopup(mensaje)
{
	var div_mensaje = $("#div_mensaje");
	var div_ayuda = $("#div_ayuda");
	var lbl_ayuda = $("#lbl_ayuda");
	lbl_ayuda.html("<b>"+lang_js[13]+"</b>");
	div_ayuda.hide();
	div_ayuda.removeClass("oculto");
	div_mensaje.html(mensaje);
	setTimeout('mostrar("div_ayuda")',0);
}
