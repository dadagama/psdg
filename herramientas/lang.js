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

var lang_en = new Array(
		"Log in",//0
		"Workspace",//1
		"Type your workspace name",//2
		"Password",//3
		"Type your password",//4
		"English",//5
		"Spanish",//6
		"Sign in",//7
		"[%v] field must not be empty.",//8
		"Incorrect user or password.",//9
		"Sending data...",//10
		"OK",//11
		"Error: Connection timeout.",//12
		"Help",//13
		"Set connections",//14
		"Set restrictions",//15
		"Set output type",//16
		"Run",//17
		"Connection name already exists in the BDI",//18
		"Allowed file extension is [.txt]",//19
		"Allowed library extension is[.lib]",//20
		"Remove this connection",//21
		"The connection could not be removed",//22
		"Unable to establish connection with the DB, check the connection parameters.",//23
		"Warning",//24
		"",//25 - para uso de info externa.
		"Constraint set correctly.",//26
		"If this value is set to zero, tables that depend on this will also be excluded. Are you sure?",//27
		"Output type established correctly.",//28
		"Process completed!",//29
		"Not a valid direction.",//30
		"can contain only letters.",//31
		"can contain only numbers.",//32
		"this connection will be remove ¿Are you sure?",//33
		"position",//34
		"delta of position",//35
		"date",//36
		"delta in days",//37
		"value",//38
		"delta value"//39
	);

var lang_es = new Array(
		"Iniciar sesión",//0
		"Sesión",//1
		"Digite el nombre de su sesión de trabajo",//2
		"Contraseña",//3
		"Digite su contraseña",//4
		"Inglés",//5
		"Español",//6
		"Iniciar sesión",//7
		"El campo [%v] no puede estar vacío.",//8
		"Nombre de usuario ó contraseña incorrecta.",//9
		"Enviando información...",//10
		"OK",//11
		"Error: Tiempo de conexión agotado.",//12
		"Ayuda",//13
		"Configurar conexiones",//14
		"Establecer restricciones",//15
		"Establecer tipo de salida",//16
		"Ejecutar",//17
		"La conexión ya existe en la BDI",//18
		"La extensión permitida para archivos es [.txt]",//19
		"La extensión permitida para bibliotecas es [.lib]",//20
		"Eliminar esta conexión",//21
		"La conexión no pudo ser eliminada",//22
		"No se pudo establecer conexión con la BD, revise los parámetros de conexión.",//23
		"Advertencia",//24
		"",//25 - para uso de info externa.
		"Restricción establecida correctamente.",//26
		"Si este valor se establece en cero, las tablas que dependan de esta también serán excluídas. ¿Esta seguro?",//27
		"Formato de salida establecido correctamente.",//28
		"Proceso finalizado",//29
		"no es una dirección válida.",//30
		"[%v] solo puede contener letras.",//31
		"[%v] solo puede contener números.",//32
		"Esta conexión será eliminada ¿Está seguro?",//33
		"posición",//34
		"delta de posición",//35
		"fecha",//36
		"delta en días",//37
		"valor",//38
		"delta de valor"//39
	);

var lang = "en";
var lang_js = lang_en;
var idiomas_cargados = new Array("en");

function cambiarLenguaje()
{
	var chk_lang = $(this);
	lang = chk_lang.val();
	establecerIdioma(lang);
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
	$("#step_1").attr("title",lang_js[14]);
	$("#step_2").attr("title",lang_js[15]);
	$("#step_3").attr("title",lang_js[16]);
	$("#step_4").attr("title",lang_js[17]);
}

function establecerIdioma(lang)
{
	switch(lang)
	{
		case "es":
			lang_js = lang_es;
			break;
		default:
			lang_js = lang_en;
			break;
	}	
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
