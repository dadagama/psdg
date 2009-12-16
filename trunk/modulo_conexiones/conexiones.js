function adicionarConexion(no_es_BDO)
{
	var lbl_con_tipo = $("#lbl_con_tipo").html();
	var lbl_con_nombre = $("#lbl_con_nombre").html();
	var lbl_con_nombre_db = $("#lbl_con_nombre_db").html();
	var lbl_con_usuario = $("#lbl_con_usuario").html();
	var lbl_con_password = $("#lbl_con_password").html();
	var lbl_con_nombre_archivo = $("#lbl_con_nombre_archivo").html();
	var lbl_con_nombre_biblioteca = $("#lbl_con_nombre_biblioteca").html();
	
	var con_tipo = $("#con_tipo");
	var con_nombre = $("#con_nombre");
	
	var con_nombre_db = $("#con_nombre_db");
	
	var datos_conexion = $("#fm_datos_conexion").serialize();
	
	if(no_es_BDO)
		validarCampoNoVacio(con_nombre_db, lbl_con_nombre_db, true);
	else
		validarCampoNoVacio(con_nombre_db, lbl_con_nombre_db, true);
		
//	if (validarCampoNoVacio(usu_login, login, true) && validarCampoNoVacio(usu_password, pass, true))
//	{
		/*$.ajax({
					async:		true,
					type: 		"POST",
					dataType:	"html",
					contentType:"application/x-www-form-urlencoded",
					url:		"../modulo_conexiones/ajax_conexiones.php",
					data:		"con_nombre="+con_nombre+"&con_tipo="+con_tipo+"&datos_conexion="+datos_conexion,
					beforeSend:	ajaxSend,
					success:	iniciarSesion,
					timeout:	10000,
					error:		ajaxError(12)
				}); 
//	}
	return false;*/
}