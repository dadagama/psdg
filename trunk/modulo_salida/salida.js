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

$(document).ready(inicializar);

function inicializar()
{
	$('#sal_div_general').hide();
	$('#sal_div_general').removeClass("oculto");
	setTimeout('efecto("sal_div_general","slideToggle")',1000);
	
	$('#sal_div_botones_secuencia').hide();
	$('#sal_div_botones_secuencia').removeClass("oculto");
	setTimeout('efecto("sal_div_botones_secuencia","fadeIn")',2000);
	
	establecerPosicionSecuencia(3);
	verificarOpcionEscogida();
}

function habilitarSiguienteEtapa(habilitar)
{
	if(habilitar)
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
				url:		"../modulo_salida/salida.php",
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
	setTimeout('efecto("sal_div_general","fadeOut")',0);
	setTimeout('eliminar("sal_div_general")',2000);
	
	setTimeout('efecto("sal_div_botones_secuencia","fadeOut")',0);
	setTimeout('eliminar("sal_div_botones_secuencia")',2000);
	
	$("#div_cuerpo").append(modulo);
}

function seleccionarSalida(tis_codigo)
{
	$.ajax({
		async:		false,
		type: 		"POST",
		dataType:	"html",
		contentType:"application/x-www-form-urlencoded",
		url:		"../modulo_salida/salida.php",
		data:		"funcion=seleccionarSalida&tis_codigo="+tis_codigo,
		beforeSend:	ajaxSend,
		success:	verificarOpcion,
		timeout:	10000,
		error:		ajaxError(12)
	}); 
	return false;
}

function verificarOpcionEscogida()
{
	$.ajax({
		async:		false,
		type: 		"POST",
		dataType:	"html",
		contentType:"application/x-www-form-urlencoded",
		url:		"../modulo_salida/salida.php",
		data:		"funcion=verificarOpcionEscogida",
		beforeSend:	ajaxSend,
		success:	verificarOpcion,
		timeout:	10000,
		error:		ajaxError(12)
	}); 
	return false;
}

function verificarOpcion(estado)
{
	//alert(estado);
	if(estado == "error")
		habilitarSiguienteEtapa(false);
	else if(estado == "ok_nuevo")
	{
		habilitarSiguienteEtapa(true);
		actualizarSeleccion(1);//cambiar
		aviso(28);
	}
	else
	{
		habilitarSiguienteEtapa(true);
		actualizarSeleccion(1);//cambiar
	}
}

function actualizarSeleccion(tis_codigo)
{
	$("#btn_tis_bdo").attr("src","../imagenes/btn_db_1.png");
	$("#btn_tis_sql").attr("src","../imagenes/btn_text_1.png");
	if(tis_codigo == 1)
	{
		$("#btn_tis_bdo").attr("src","../imagenes/btn_db_2.png");
		$("#btn_tis_bdo").attr("onmouseout","../imagenes/btn_db_2.png");
	}
}
