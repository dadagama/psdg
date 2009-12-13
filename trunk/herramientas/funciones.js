function ocultar(nombreElemento)
{
	$("#"+nombreElemento).fadeOut("slow");
	setTimeout('eliminar("'+nombreElemento+'")',2000);
}

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
}

function eliminar(nombreElemento)
{
	$("#"+nombreElemento).remove();
}

function mostrar(nombreElemento)
{
	$("#"+nombreElemento).slideToggle("slow",ajaxSuccess(lang_js[11]));
}

function ajaxSend(mensaje)
{
	var lbl_status = $("#lbl_status");
	lbl_status.html(mensaje);
	lbl_status.removeClass("error");
	var lbl_loading = $("#lbl_loading");
	lbl_loading.html('<img src="imagenes/loading_bar.gif"/>');
}

function ajaxSuccess(mensaje)
{
	var lbl_status = $("#lbl_status");
	lbl_status.html(mensaje);
	lbl_status.removeClass("error");
	var lbl_loading = $("#lbl_loading");
	lbl_loading.html("");
}

function ajaxError(mensaje)
{
	var lbl_status = $("#lbl_status");
	lbl_status.html(mensaje);
	lbl_status.addClass("error");
	var lbl_loading = $("#lbl_loading");
	lbl_loading.html("");
}
