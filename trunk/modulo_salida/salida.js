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
	habilitarSiguienteEtapa(true);//<=======================  OJO OJO OJO OJO OJO QUITAR
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