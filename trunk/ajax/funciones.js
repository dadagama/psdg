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
	if (validarCampoNoVacio($("#usu_login"), "Usuario", true) && validarCampoNoVacio($("#usu_password"), "Contraseña", true))
	{
		var usu_login = $("#usu_login").val();
		var usu_password = $("#usu_password").val();
		$.ajax({
					async:		true,
					type: 		"POST",
					dataType:	"html",
					contentType:"application/x-www-form-urlencoded",
					url:		"../servidor/servidor.php",
					data:		"usu_login="+usu_login+"&usu_password="+usu_password,
					beforeSend:	ajax_send,
					success:	iniciar_sesion,
					timeout:	4000,
					error:		ajax_error("Hubo un error al establecer conexión con el servidor.")
				}); 
	}
	return false;
}

function iniciar_sesion(div_conexiones)
{
	if(div_conexiones != '-1')
	{
		setTimeout('ocultar("div_sesion")',0);
		$("#div_cuerpo").append(div_conexiones);
		$('#div_conexiones').hide();
		setTimeout('mostrar("div_conexiones")',1000);
	}
	else
		ajax_error("El usuario no existe o la contraseña es incorrecta.");
}

function ocultar(elemento)
{
	$("#"+elemento).fadeOut(1000);
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
