var doc;
var lang = "en";
var lang_js = lang_en;
doc=$(document);
doc.ready(inicializarEventos);

function inicializarEventos()
{
  var btn_login = $("#btn_login");
  btn_login.click(verificar_datos_sesion);
  var chk_lang = $("input[name='chk_lang']");
  chk_lang.click(cambiar_lenguaje);
}

function cambiar_lenguaje()
{
	var chk_lang = $(this);
	lang = chk_lang.val();
	switch(lang)
	{
		case "es":
			lang_js = lang_es;
			break;
		default:
			lang_js = lang_en;
			break;
	}
	$("#lbl_login").html(lang_js[0]);
	$("#lbl_usu_login").html(lang_js[1]);
	$("#lbl_usu_password").html(lang_js[2]);
	$("#btn_login").val(lang_js[3]);
}

function verificar_datos_sesion()
{
	var login = $("#lbl_usu_login").html();
	var pass = $("#lbl_usu_password").html();
	var usu_login = $("#inp_usu_login");
	var usu_password = $("#inp_usu_password");
	if (validarCampoNoVacio(usu_login, login, true) && validarCampoNoVacio(usu_password, pass, true))
	{
		$.ajax({
					async:		true,
					type: 		"POST",
					dataType:	"html",
					contentType:"application/x-www-form-urlencoded",
					url:		"../servidor/servidor.php",
					data:		"usu_login="+usu_login.val()+"&usu_password="+usu_password.val()+"&lang="+lang,
					beforeSend:	ajax_send,
					success:	iniciar_sesion,
					timeout:	4000,
					error:		ajax_error("Connection timeout error.")
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
		ajax_error(lang_js[5]);
}

function ocultar(elemento)
{
	$("#"+elemento).fadeOut("slow");
}

function mostrar(elemento)
{
	$("#"+elemento).slideToggle("slow",ajax_success);
}

function ajax_send()
{
	var lbl_status = $("#lbl_status");
	lbl_status.html(lang_js[6]);
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
