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
	$("#"+nombreElemento).slideToggle("slow",ajax_success(lang_js[7]));
}

function ajax_send(mensaje)
{
	var lbl_status = $("#lbl_status");
	lbl_status.html(mensaje);
	lbl_status.removeClass("error");
	var lbl_loading = $("#lbl_loading");
	lbl_loading.html('<img src="../imagenes/loading_bar.gif"/>');
}

function ajax_success(mensaje)
{
	var lbl_status = $("#lbl_status");
	lbl_status.html(mensaje);
	lbl_status.removeClass("error");
	var lbl_loading = $("#lbl_loading");
	lbl_loading.html("");
}

function ajax_error(mensaje)
{
	var lbl_status = $("#lbl_status");
	lbl_status.html(mensaje);
	lbl_status.addClass("error");
	var lbl_loading = $("#lbl_loading");
	lbl_loading.html("");
}
