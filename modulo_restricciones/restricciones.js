$(document).ready(inicializar);

function inicializar()
{
	$('#res_div_general').hide();
	$('#res_div_general').removeClass("oculto");
	setTimeout('efecto("res_div_general","slideToggle")',1000);
	
	$('#res_div_botones_secuencia').hide();
	$('#res_div_botones_secuencia').removeClass("oculto");
	setTimeout('efecto("res_div_botones_secuencia","fadeIn")',2000);
	
	establecerPosicionSecuencia(2);
	habilitarSiguienteEtapa(true);//<=======================  OJO OJO OJO OJO OJO QUITAR
}

function habilitarSiguienteEtapa(habilitar)
{
	if(habilitar)
	{
		$('#res_btn_siguiente').removeAttr("disabled");
		setTimeout('efecto("res_btn_siguiente","hide")',0);
		$('#res_btn_siguiente').attr("src","../imagenes/step_1_ok.png");
		setTimeout('efecto("res_btn_siguiente","fadeIn")',0);
	}
	else
	{
		setTimeout('efecto("res_btn_siguiente","hide")',0);
		$('#res_btn_siguiente').attr("src","../imagenes/step_1_off.png");
		setTimeout('efecto("res_btn_siguiente","fadeIn")',0);
		$('#res_btn_siguiente').attr("disabled","disabled");
	}
}

function mostrarEtapa(ubicacion_etapa)
{
	$.ajax({
				async:		false,
				type: 		"POST",
				dataType:	"html",
				contentType:"application/x-www-form-urlencoded",
				url:		"../modulo_restricciones/restricciones.php",
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
	setTimeout('efecto("res_div_general","fadeOut")',0);
	setTimeout('eliminar("res_div_general")',2000);
	
	setTimeout('efecto("res_div_botones_secuencia","fadeOut")',0);
	setTimeout('eliminar("res_div_botones_secuencia")',2000);
	
	$("#div_cuerpo").append(modulo);
}