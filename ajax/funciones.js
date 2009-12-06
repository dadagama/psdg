var doc;
doc=$(document);
doc.ready(inicializarEventos);

function inicializarEventos()
{
  var btn_login;
  btn_login = $("#btn_login");
  btn_login.click(verificar_datos_sesion);
}

function verificar_datos_sesion()
{
	var usu_login = $("#usu_login").val();
	var usu_password = $("#usu_password").val();
	$.ajax({
				async:		true,
				type: 		"POST",
				dataType:	"html",
				contentType:"application/x-www-form-urlencoded",
				url:		"index2.php",
				data:		"usu_login="+usu_login+"&usu_password="+usu_password,
				beforeSend:	ajax_send,
				success:	iniciar_sesion,
				timeout:	3000,
				error:		ajax_error
			}); 
	return false;
}

function iniciar_sesion(div_conexiones)
{
	if(div_conexiones != '-1')
	{
		$("#div_cuerpo").append(div_conexiones);
		$('#div_conexiones').hide();
		$("#div_sesion").fadeOut(1000);
		setTimeout('mostrar("div_conexiones")',1000);
	}
	else
		ajax_error("El usuario no existe o la contraseña es incorrecta.");
}

function mostrar(elemento)
{
	$("#"+elemento).fadeIn(1000,ajax_success);
}

function ajax_send()
{
	var lbl_status = $("#lbl_status");
	lbl_status.html('Enviando información...');
	lbl_status.removeClass("error");
	var lbl_loading = $("#lbl_loading");
	lbl_loading.html('<img src="../imagenes/loading_bar.gif"/>');
}

function ajax_success()
{
	var lbl_status = $("#lbl_status");
	lbl_status.html('OK');
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
