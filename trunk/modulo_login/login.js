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
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

*/

var doc;
doc=$(document);
doc.ready(inicializarEventos);

function inicializarEventos()
{
  var btn_login = $("#btn_login");
  btn_login.click(verificarDatosSesion);
  var chk_lang = $("input[name='chk_lang']");
  chk_lang.click(cambiarLenguaje);
}

function verificarDatosSesion()
{
	var login = $("#lbl_usu_login").html();
	var pass = $("#lbl_usu_password").html();
	var usu_login = $("#usu_login");
	var usu_password = $("#usu_password");
	if (validarCampoNoVacio(usu_login, login, true) && validarCampoNoVacio(usu_password, pass, true))
	{
		$.ajax({
					async:		false,
					type: 		"POST",
					dataType:	"html",
					contentType:"application/x-www-form-urlencoded",
					url:		"../modulo_login/ajax_login.php",
					data:		"usu_login="+usu_login.val()+"&usu_password="+usu_password.val()+"&lang="+lang,
					beforeSend:	ajaxSend,
					success:	iniciarSesion,
					timeout:	10000,
					error:		ajaxError(12)
				}); 
	}
	return false;
}

function iniciarSesion(modulo_conexiones)
{
	if(modulo_conexiones != '-1')
	{
		setTimeout('efecto("div_sesion","fadeOut")',0);
		setTimeout('eliminar("div_sesion")',2000);
		
		$("#div_cuerpo").append(modulo_conexiones);
	}
	else
		ajaxError(9);
}
