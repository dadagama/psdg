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
	$("#"+nombreElemento).slideToggle("slow",ajaxSuccess(lang_js[7]));
}

function ajaxSend(mensaje)
{
	var lbl_status = $("#lbl_status");
	lbl_status.html(mensaje);
	lbl_status.removeClass("error");
	var lbl_loading = $("#lbl_loading");
	lbl_loading.html('<img src="../imagenes/loading_bar.gif"/>');
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
