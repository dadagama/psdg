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
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

*/

$(document).ready(inicializar);

function inicializar()
{
	$('#eje_div_general').hide();
	$('#eje_div_general').removeClass("oculto");
	setTimeout('efecto("eje_div_general","slideToggle")',1000);
	
	$('#eje_div_botones_secuencia').hide();
	$('#eje_div_botones_secuencia').removeClass("oculto");
	setTimeout('efecto("eje_div_botones_secuencia","fadeIn")',2000);
	
	mostrarResumen();
	
	establecerPosicionSecuencia(4);
}

function habilitarSiguienteEtapa(habilitar)
{
	if(true)//<=======================  OJO OJO OJO OJO OJO CAMBIAR
	{
		$('#sal_btn_siguiente').removeAttr("disabled");
		setTimeout('efecto("sal_btn_siguiente","hide")',0);
		$('#sal_btn_siguiente').attr("src","../imagenes/btn_next_1.png");
		setTimeout('efecto("sal_btn_siguiente","fadeIn")',0);
	}
	else
	{
		setTimeout('efecto("sal_btn_siguiente","hide")',0);
		$('#sal_btn_siguiente').attr("src","../imagenes/btn_next_3.png");
		setTimeout('efecto("sal_btn_siguiente","fadeIn")',0);
		$('#sal_btn_siguiente').attr("disabled","disabled");
	}
}

function mostrarEtapa(ubicacion_etapa)
{
	$.ajax({
				async:		false,
				type: 		"POST",
				dataType:	"html",
				contentType:"application/x-www-form-urlencoded",
				url:		"../modulo_ejecucion/ejecucion.php",
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
	setTimeout('efecto("eje_div_general","fadeOut")',0);
	setTimeout('eliminar("eje_div_general")',2000);
	
	setTimeout('efecto("eje_div_botones_secuencia","fadeOut")',0);
	setTimeout('eliminar("eje_div_botones_secuencia")',2000);
	
	$("#div_cuerpo").append(modulo);
}

function mostrarResumen()
{
	$.ajax({
		async:		false,
		type: 		"POST",
		dataType:	"html",
		contentType:"application/x-www-form-urlencoded",
		url:		"../modulo_ejecucion/ejecucion.php",
		data:		"funcion=mostrarResumen",
		beforeSend:	ajaxSend,
		success:	recibirResumen,
		timeout:	10000,
		error:		ajaxError(12)
	}); 
	return false;
}

function iniciar()
{
	
	$.ajax({
		async:		false,
		type: 		"POST",
		dataType:	"html",
		contentType:"application/x-www-form-urlencoded",
		url:		"../modulo_ejecucion/ejecucion.php",
		data:		"funcion=iniciar",
		beforeSend:	ajaxSend,
		success:	recibirLog,
		timeout:	10000,
		error:		ajaxError(12)
	}); 
	return false;
}

function ejecutar()
{
	
	$.ajax({
		async:		false,
		type: 		"POST",
		dataType:	"html",
		contentType:"application/x-www-form-urlencoded",
		url:		"../modulo_ejecucion/ejecucion.php",
		data:		"funcion=ejecutar",
		beforeSend:	ajaxSend,
		success:	recibirLog,
		timeout:	10000,
		error:		ajaxError(12)
	}); 
	return false;
}

function recibirResumen(log)
{
	var elm = document.getElementById('div_log');
	$('#div_log').append(log);
	elm.scrollTop = elm.scrollHeight;
}


function recibirLog(log)
{
	var log_nuevo = "";
	var elm = document.getElementById('div_log');
	//alert(log);
	if(log == "PSDG_EOF")
	{
		log_nuevo = lang_js[29];
		$('#div_log').append(log_nuevo);		
		elm.scrollTop = elm.scrollHeight;
		ajaxSuccess();
	}
	else if(log == "PSDG_OK")
	{
		log_nuevo = '<img src="../imagenes/ok.png"/><br/>';
		//log_nuevo = log_nuevo.replace(/@br2n/g,"\n");
		$('#div_log').append(log_nuevo);
		elm.scrollTop = elm.scrollHeight;
		ejecutar();
	}
	else if(log == "PSDG_WARNING")
	{
		log_nuevo = '<img src="../imagenes/warning.gif"/><br/>';
		//log_nuevo = log_nuevo.replace(/@br2n/g,"\n");
		$('#div_log').append(log_nuevo);
		elm.scrollTop = elm.scrollHeight;
		ejecutar();
	}	
	else
	{
		log_nuevo = log;
		//log_nuevo = log_nuevo.replace(/@br2n/g,"\n");
		$('#div_log').append(log_nuevo);
		elm.scrollTop = elm.scrollHeight;
		ejecutar();
	}
	//alert('finish!');
}
