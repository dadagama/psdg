/*
 This file is part of PSDG.

    PSDG is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    PSDG is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

*/

$(document).ready(inicializar);

function inicializar()
{
	$('#con_div_general').hide();
	$('#con_div_general').removeClass("oculto");
	setTimeout('efecto("con_div_general","slideToggle")',1000);
	
	$('#con_div_botones_secuencia').hide();
	$('#con_div_botones_secuencia').removeClass("oculto");
	setTimeout('efecto("con_div_botones_secuencia","fadeIn")',2000);
	
	establecerPosicionSecuencia(1);
	
	verificarSiExisteConexionBDO();
	actualizarListadoConexiones();
	//para el upload de archivos con ajax
	new AjaxUpload(	'#con_nombre_archivo',
		{
			action: '../modulo_conexiones/conexiones.php',
			name: 'con_archivo',
			onSubmit : confirmarArchivo,
			onComplete: archivoEnviado
		});
	//para el upload de bibliotecas con ajax
	new AjaxUpload(	'#con_nombre_biblioteca',
		{
			action: '../modulo_conexiones/conexiones.php',
			name: 'con_biblioteca',
			onSubmit : confirmarBiblioteca,
			onComplete: archivoEnviado
		});
}

function habilitarSiguienteEtapa(habilitar)
{
	if(habilitar)
	{
		$('#con_btn_siguiente').removeAttr("disabled");
		setTimeout('efecto("con_btn_siguiente","hide")',0);
		$('#con_btn_siguiente').attr("src","../imagenes/next.png");
		setTimeout('efecto("con_btn_siguiente","fadeIn")',0);
	}
	else
	{
		setTimeout('efecto("con_btn_siguiente","hide")',0);
		$('#con_btn_siguiente').attr("src","../imagenes/next_off.png");
		setTimeout('efecto("con_btn_siguiente","fadeIn")',0);
		$('#con_btn_siguiente').attr("disabled","disabled");
	}
}

function verificarSiExisteConexionBDO()
{
	$.ajax({
		async:		true,
		type: 		"POST",
		dataType:	"html",
		contentType:"application/x-www-form-urlencoded",
		url:		"../modulo_conexiones/conexiones.php",
		data:		"funcion=existeRegistroBDO",
		beforeSend:	ajaxSend,
		success:	existeBDO,
		timeout:	10000,
		error:		ajaxError(12)
	}); 
	return false;
}

function adicionarConexion()
{
	var con_tipo = $("#con_fue_codigo").val();
	if(pasaValidacionCampos(con_tipo))
	{
		var datos_conexion = $("#fm_datos_conexion").serialize();
		$.ajax({
			async:		true,
			type: 		"POST",
			dataType:	"html",
			contentType:"application/x-www-form-urlencoded",
			url:		"../modulo_conexiones/conexiones.php",
			data:		"funcion=insertarConexion&con_nombre="+$("#con_nombre").val()+"&con_tipo="+con_tipo+"&"+datos_conexion,
			beforeSend:	ajaxSend,
			success:	insertoConexion,
			timeout:	10000,
			error:		ajaxError(12)
		}); 
		return false;
	}
}

function confirmarArchivo(file, ext)
{
	ajaxSend();
	if(ext == 'txt')
	{
		if(	confirm("se utilizará el archivo ["+file+"] como fuente de valores ¿Esta seguro?") &&
			pasaValidacionCampos('7'))
		{
			this.setData({
				'funcion': "insertarConexion",
				'con_nombre': $("#con_nombre").val(),
				'con_tipo': $("#con_fue_codigo").val(),
				'con_separador': $("#con_separador").val()
			});
		}
		else
		{
			ajaxSuccess();
			return false;
		}
	}
	else
	{
		ajaxError(19);
		return false;
	}
}

function confirmarBiblioteca(file, ext)
{
	ajaxSend();
	if(ext == 'lib')
	{
		if(	confirm("se utilizará el archivo ["+file+"] como biblioteca de valores ¿Esta seguro?") &&
			pasaValidacionCampos('3'))
		{
			this.setData({
				'funcion': "insertarConexion",
				'con_nombre': $("#con_nombre").val(),
				'con_tipo': $("#con_fue_codigo").val()
			});
		}
		else
		{
			ajaxSuccess();
			return false;
		}
	}
	else
	{
		ajaxError(20);
		return false;
	}
}

function archivoEnviado(file, response)
{
	//alert("archivo: "+response);
	switch(response)
	{
		case "archivo":
			ajaxError(18);
			break;
		case "biblioteca":
			ajaxError(18);
			break;
		case "conexion":
			ajaxError(18);
			break;
		default:
			limpiarFormulario();
			hacerVisibleCamposFormulario('2');
			actualizarListadoConexiones();
			ajaxSuccess();
			break;
	}
}

function pasaValidacionCampos(con_tipo)
{
	var validacion_abajo = false;
	var validacion_arriba = false;
	
	validacion_arriba = validarCampoNoVacio($("#con_nombre"), $("#con_lbl_nombre").html(), true);
	
	if(validacion_arriba)
	{
		switch(con_tipo)
		{
			case '2':
				if(validarCampoNoVacio($("#con_servidor"), $("#con_lbl_servidor").html(), true)
					&&validarCampoNoVacio($("#con_nombre_bd"), $("#con_lbl_nombre_bd").html(), true)
					&& validarCampoNoVacio($("#con_usuario"), $("#con_lbl_usuario").html(), true)
					&& validarCampoNoVacio($("#con_password"), $("#con_lbl_password").html(), true))
					validacion_abajo = true;
				break;
			case '7':
				//if(validarCampoNoVacio($("#con_separador"), $("#con_lbl_separador").html(), true))
					validacion_abajo = true;
				break;
			case '3':
				validacion_abajo = true;
				break;
		}
	}
	return validacion_abajo;
}

function insertoConexion(datosConexion)
{
	//alert(datosConexion);
	switch(datosConexion)
	{
		case "bd":
			ajaxError(23);
			break;
		case "conexion":
			ajaxError(18);
			break;
		default:
			verificarSiExisteConexionBDO();
			actualizarListadoConexiones();
			break;
	}
}

function existeBDO(existe)
{
	limpiarFormulario();
	hacerVisibleCamposFormulario('2');
	if(!existe)
	{
		colocarFormularioBDO(true);
		habilitarSiguienteEtapa(false);
	}
	else
	{
		colocarFormularioBDO(false);
		habilitarSiguienteEtapa(true);
	}
	ajaxSuccess();
}


function colocarFormularioBDO(colocar)
{
	if(colocar)
	{
		$("#con_nombre").val("BDO");
		$("#con_nombre").attr("disabled","disabled");
		$("#con_fue_codigo").attr("disabled","disabled");
	}
	else
	{
		$("#con_nombre").removeAttr("disabled");
		$("#con_fue_codigo").removeAttr("disabled");
	}
}

function limpiarFormulario()
{
	$("#con_nombre").val("");
	$("#con_fue_codigo").val("");
	$("#con_servidor").val("");
	$("#con_nombre_bd").val("");
	$("#con_usuario").val("");
	$("#con_password").val("");
	$("#con_nombre_archivo").val("");
	$("#con_separador").val("");
	$("#con_nombre_biblioteca").val("");
}

function actualizarFormulario()
{
	hacerVisibleCamposFormulario($("#con_fue_codigo").val());
}

function hacerVisibleCamposFormulario(tipo_conexion)
{
	$("#con_div_datos_conexion").children().hide();
	switch(tipo_conexion)
	{
		case '2':
			$("#con_div_bd").show();
			break;
		case '7':
			$("#con_div_archivo").show();
			break;
		case '3':
			$("#con_div_biblioteca").show();
			break;
	}
}

function actualizarListadoConexiones()
{
	$.ajax({
		async:		true,
		type: 		"POST",
		dataType:	"html",
		contentType:"application/x-www-form-urlencoded",
		url:		"../modulo_conexiones/conexiones.php",
		data:		"funcion=obtenerConexiones",
		beforeSend:	ajaxSend,
		success:	mostrarConexiones,
		timeout:	10000,
		error:		ajaxError(12)
	}); 
	return false;
}

function mostrarConexiones(conexiones)
{
	var json_data_object = eval("(" + conexiones + ")");
	var div_conexiones_establecidas = $('#con_div_conexiones_establecidas');
	var div_conexion_bdo = $('#con_div_conexion_bdo');
	div_conexiones_establecidas.empty();
	div_conexion_bdo.empty();
	for(var x = 0; x < json_data_object.length; x++)
	{
		var con_nombre = json_data_object[x][0];
		var con_tipo = json_data_object[x][1];
		var imagen_tipo = "../imagenes/";
		var imagen_eliminar = "../imagenes/delete.png";
		
		switch(con_tipo)
		{
			case '2':
				imagen_tipo += "bd.png";
				break;
			case '7':
				imagen_tipo += "txt.png";
				break;
			case '3':
				imagen_tipo += "lib.png";
				break;
		}
		
		var div = 				"<div class='fila'>" +
								"	<div class='ancho_50 celda vertical_centro alto_40 centrado borde_inferior'>" +
								"		<img src='"+imagen_tipo+"'/>" +
								"	</div>" +
								"	<div class='celda vertical_centro alto_40 conexion_establecida borde_inferior'>" +
								"		<label>"+con_nombre+"</label>" +
								"	</div>" +
								"	<div class='ancho_50 celda vertical_centro alto_40 conexion_establecida borde_inferior'>" +
								"		<input type='image' title='"+lang_js[21]+"' class='boton' alt='eliminar_conexion' src='"+imagen_eliminar+"' onmouseout='this.src=\""+imagen_eliminar+"\"' onclick='eliminarConexion(\""+con_nombre+"\",\""+con_tipo+"\");'" +
								"	</div>" +
								"</div>";
		if(con_nombre != "BDO")
			div_conexiones_establecidas.append(div);
		else
			div_conexion_bdo.append(div);
	}
}

function eliminarConexion(con_nombre, con_tipo)
{
	$.ajax({
		async:		true,
		type: 		"POST",
		dataType:	"html",
		contentType:"application/x-www-form-urlencoded",
		url:		"../modulo_conexiones/conexiones.php",
		data:		"funcion=eliminarConexion&con_nombre="+con_nombre+"&con_tipo="+con_tipo,
		beforeSend:	confirmarEliminada,
		success:	conexionEliminada,
		timeout:	10000,
		error:		ajaxError(12)
	}); 
	return false;
}

function confirmarEliminada()
{
	ajaxSend();
	if(!confirm("se eliminará esta la conexion ¿Esta seguro?"))
	{
		ajaxSuccess();
		return false;
	}
	return true;
}

function conexionEliminada(eliminada)
{
	if(eliminada)
	{
		verificarSiExisteConexionBDO();
		actualizarListadoConexiones();
	}
	else
		ajaxError(22);
}

function mostrarEtapa(ubicacion_etapa)
{
	$.ajax({
				async:		false,
				type: 		"POST",
				dataType:	"html",
				contentType:"application/x-www-form-urlencoded",
				url:		"../modulo_conexiones/conexiones.php",
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
	setTimeout('efecto("con_div_general","fadeOut")',0);
	setTimeout('eliminar("con_div_general")',2000);
	
	setTimeout('efecto("con_div_botones_secuencia","fadeOut")',0);
	setTimeout('eliminar("con_div_botones_secuencia")',2000);
	
	$("#div_cuerpo").append(modulo);
}
