$(document).ready(inicializar);

function inicializar()
{
	$('#eje_div_general').hide();
	$('#eje_div_general').removeClass("oculto");
	setTimeout('efecto("eje_div_general","slideToggle")',1000);
	
	$('#eje_div_botones_secuencia').hide();
	$('#eje_div_botones_secuencia').removeClass("oculto");
	setTimeout('efecto("eje_div_botones_secuencia","fadeIn")',2000);
	
	establecerPosicionSecuencia(4);
}

function habilitarSiguienteEtapa(habilitar)
{
	if(true)//<=======================  OJO OJO OJO OJO OJO CAMBIAR
	{
		$('#eje_btn_siguiente').removeAttr("disabled");
		setTimeout('efecto("eje_btn_siguiente","hide")',0);
		$('#eje_btn_siguiente').attr("src","../imagenes/step_1_ok.png");
		setTimeout('efecto("eje_btn_siguiente","fadeIn")',0);
	}
	else
	{
		setTimeout('efecto("eje_btn_siguiente","hide")',0);
		$('#eje_btn_siguiente').attr("src","../imagenes/step_1_off.png");
		setTimeout('efecto("eje_btn_siguiente","fadeIn")',0);
		$('#eje_btn_siguiente').attr("disabled","disabled");
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