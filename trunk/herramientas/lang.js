var lang_en = new Array(
		"Log in",//0
		"User:",//1
		"Type your user name",//2
		"Password:",//3
		"Type your password",//4
		"English",//5
		"Spanish",//6
		"Sign in",//7
		"[%v] field must not be empty.",//8
		"Incorrect user or password.",//9
		"Sending data...",//10
		"OK",//11
		"Error: Connection timeout.",//12
		"Help"//13
	);

var lang_es = new Array(
		"Iniciar sesión",//0
		"Usuario:",//1
		"Digite su nombre de usuario",//2
		"Contraseña:",//3
		"Digite su contraseña",//4
		"Inglés",//5
		"Español",//6
		"Iniciar sesión",//7
		"El campo [%v] no puede estar vacío.",//8
		"Nombre de usuario ó contraseña incorrecta.",//9
		"Enviando información...",//10
		"OK",//11
		"Error: Tiempo de conexión agotado.",//12
		"Ayuda"//13
	);

var lang = "en";
var lang_js = lang_en;
var idiomas_cargados = new Array("en");

function cambiarLenguaje()
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
	$("#usu_login").attr("title",lang_js[2]);
	$("#lbl_usu_password").html(lang_js[3]);
	$("#usu_password").attr("title",lang_js[4]);
	$("#chk_lang_en").attr("title",lang_js[5]);
	$("#chk_lang_es").attr("title",lang_js[6]);
	$("#img_lang_en").attr("title",lang_js[5]);
	$("#img_lang_es").attr("title",lang_js[6]);
	$("#btn_login").val(lang_js[7]);
	$("#btn_login").attr("title",lang_js[7]);
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