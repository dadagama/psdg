/*
 This file is part of PSDG.

    PSDG is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
    along with PSDG.  If not, see <http://www.gnu.org/licenses/>.

*/

function establecerPosicionSecuencia(secuencia_activa)
{
	for ( var ints = 1; ints <= 4; ints++) 
	{
		if(ints < secuencia_activa)
			$("#step_"+ints).attr("src","../imagenes/step_"+ints+"_on.png");
		else if(ints == secuencia_activa)
			$("#step_"+ints).attr("src","../imagenes/step_"+ints+"_on.png");
		else
			$("#step_"+ints).attr("src","../imagenes/step_"+ints+"_off.png");
	}
	mostrarTituloSecuenciaActiva(secuencia_activa);
	mostrarBotonLogout(secuencia_activa);
}

function mostrarTituloSecuenciaActiva(secuencia_activa)
{
	if(secuencia_activa == 0)
		$("#lbl_titulo_step").html(""); 	
	else
	{
		switch(secuencia_activa)
		{
			case 1: $("#lbl_titulo_step").html(lang_js[14]); break;
			case 2: $("#lbl_titulo_step").html(lang_js[15]); break;
			case 3: $("#lbl_titulo_step").html(lang_js[16]); break;
			case 4: $("#lbl_titulo_step").html(lang_js[17]); break;
		}
	}
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
			$("#"+nombreElemento).show("slow",ajaxSuccess);true
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

function aviso(num_mensaje)
{
	alert(lang_js[num_mensaje]);
}
