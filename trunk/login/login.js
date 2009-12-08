var doc;
var lang = "en";
var idiomas_cargados = new Array("en");
var lang_js = lang_en;
doc=$(document);
doc.ready(inicializarEventos);

function inicializarEventos()
{
  var btn_login = $("#btn_login");
  btn_login.click(verificarDatosSesion);
  var chk_lang = $("input[name='chk_lang']");
  chk_lang.click(cambiarLenguaje);
}

function cambiarLenguaje()
{
	var chk_lang = $(this);
	lang = chk_lang.val();
	if(!idiomaEstaCargado(lang))
	{
		agregarIdioma(lang);
		$("body").append("<script type='text/javascript' src='../idiomas/"+lang+".js'></script>");
		
	}
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

function agregarIdioma(idioma)
{
	for ( var x = 0; x < idiomas_cargados.length; x++) 
	{
		if(idiomas_cargados[x] == idioma)
			return;
	}
	idiomas_cargados.push(idioma);
}

function idiomaEstaCargado(idioma)
{
	for ( var x = 0; x < idiomas_cargados.length; x++) 
	{
		if(idiomas_cargados[x] == idioma)
			return true;
	}
}

function verificarDatosSesion()
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
					url:		"login.php",
					data:		"usu_login="+usu_login.val()+"&usu_password="+usu_password.val()+"&lang="+lang,
					beforeSend:	ajaxSend(lang_js[6]),
					success:	iniciarSesion,
					timeout:	5000,
					error:		ajaxError(lang_js[8])
				}); 
	}
	return false;
}

function iniciarSesion(div_conexiones)
{
	if(div_conexiones != '-1')
	{
		setTimeout('ocultar("div_sesion")',0);
		$("#div_cuerpo").append(div_conexiones);
		$('#div_conexiones').hide();
		setTimeout('mostrar("div_conexion")',1000);
	}
	else
		ajax_error(lang_js[5]);
}