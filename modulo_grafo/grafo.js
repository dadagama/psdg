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

//var mitad_campo = 15;//los div_campo son de 30px de alto
var padding_campo = 3;//cada div_campo tiene 3px de padding
var longitud_guion = 15;//fragmento recto que sale del campo
var grosor_linea = 1;//grueso de las lineas
var arreglo_info_relaciones;//arreglo JSon de las relaciones
var drawingCanvas;
var context;

function repaint()
{
		drawingCanvas.width = drawingCanvas.width;//reinicio el canvas
		//[{"fue_codigo":"2","bd_origen":"bd_eps_sintetica","tabla_origen":"medico","campo_origen":"nombre","bd_destino":"bd_eps_real","tabla_destino":"medico","campo_destino":"nombre"}]
		for(var indice = 0; indice < arreglo_info_relaciones.length; indice++)
		{
			dibujarRelacion(arreglo_info_relaciones[indice]);
		}
}

function dibujarRelacion(relacion)
{
	//calculo ubicacion canvas
	var posicion_canvas = $('#area_dibujo').offset();
	var top_canvas = posicion_canvas.top;
	var left_canvas = posicion_canvas.left;
	
	//alert("canvas: "+left_canvas+","+top_canvas);
	
	//calculo las posicion campo origen
	var ancho_origen = $('#'+relacion['bd_origen']+"_"+relacion['tabla_origen']+"_"+relacion['campo_origen']).outerWidth();//NO PARECE NECESITARSE
	var alto_origen = $('#'+relacion['bd_origen']+"_"+relacion['tabla_origen']+"_"+relacion['campo_origen']).outerHeight();
	var posicion_origen = $('#'+relacion['bd_origen']+"_"+relacion['tabla_origen']+"_"+relacion['campo_origen']).offset();
	var top_origen = (posicion_origen.top - top_canvas);
	var left_origen = (posicion_origen.left - left_canvas /*- padding_campo*/);
	
	//alert("origen: "+ancho_origen+","+alto_origen+"-"+top_origen+","+left_origen);
	//origen: 177,16-55,253
	//calculo posicion campo destino
	var ancho_destino = $('#'+relacion['bd_destino']+"_"+relacion['tabla_destino']+"_"+relacion['campo_destino']).outerWidth();
	var alto_destino = $('#'+relacion['bd_destino']+"_"+relacion['tabla_destino']+"_"+relacion['campo_destino']).outerHeight();
	var posicion_destino = $('#'+relacion['bd_destino']+"_"+relacion['tabla_destino']+"_"+relacion['campo_destino']).offset();
	var top_destino = (posicion_destino.top - top_canvas);
	var left_destino = (posicion_destino.left - left_canvas);
	
	//alert("destino: "+ancho_destino+","+alto_destino+"-"+top_destino+","+left_destino);
	
	//asigno color de linea deacuerdo a la fuente
	var estilo_stroke = "";
	var punto_choque_horizontal_origen = 0;
	if(relacion['fue_codigo'] == "3")
	{
		estilo_stroke = "#f00";
		punto_choque_horizontal_origen = left_origen + ancho_origen + padding_campo;
		delta_guion = longitud_guion * -1;
	}
	else if(relacion['fue_codigo'] == "2")
	{
		estilo_stroke = "#00f";
		punto_choque_horizontal_origen = left_origen;
		delta_guion = longitud_guion;
	}
		
	context.beginPath();
	context.strokeStyle = estilo_stroke;
	//iniciar fragmento recto del origen 
	punto_choque_vertical_origen = (top_origen + (alto_origen / 2));
	context.moveTo(punto_choque_horizontal_origen, punto_choque_vertical_origen);
	context.lineTo((punto_choque_horizontal_origen - delta_guion), punto_choque_vertical_origen);
	//trazar linea
	punto_choque_destino = (top_destino + (alto_destino / 2));
	context.lineTo((left_destino + ancho_destino + padding_campo + longitud_guion), punto_choque_destino);
	//iniciar fragmento recto del destino
	context.lineTo((left_destino + ancho_destino + padding_campo),punto_choque_destino);
	context.stroke();
	context.closePath();
	
	//crear semicirculo
	context.beginPath();
	context.fillStyle = estilo_stroke;
	context.arc((left_destino + ancho_destino + padding_campo),punto_choque_destino,5,-Math.PI/2,Math.PI/2,false);
	context.fill();
	context.stroke();
	context.closePath();
}

function inicializar()
{
	drawingCanvas = document.getElementById('area_dibujo');
	if(drawingCanvas.getContext) 
	{
		context = drawingCanvas.getContext('2d');
		context.lineWidth = grosor_linea;
	}
	obtenerEstructuraTablas();
	obtenerRelaciones();
}

function obtenerEstructuraTablas()
{
	$.ajax({
		async:		false,
		type: 		"POST",
		dataType:	"html",
		contentType:"application/x-www-form-urlencoded",
		url:		"../modulo_grafo/grafo.php",
		data:		"funcion=obtenerEstructuraTablas",
		success:	recibirJSONTablas,
		timeout:	10000
	}); 
	return false;
}

function recibirJSONTablas(info_tablas)
{
	var arreglo_info_tablas = eval("("+info_tablas+")");
	/*[
		{
			"nombre_bd":"bd_real",
			"nombre_tabla":"cita_medica",
			"campos_tabla":	[
								["id_afiliado","MUL"],
								["id_medico","MUL"],
								["fecha",""],
								["motivo",""]
							]
		}
	]*/
	for(var indice = 0; indice < arreglo_info_tablas.length; indice++)
	{
		crearDivTabla(arreglo_info_tablas[indice], indice);
		//alert('u');
	}
	
//	$("#tablita").draggable({	containment: '#cuerpito',
//		drag: function() 
//		{
			//repaint();
//		} 
//	});
}

function crearDivTabla(obj_tabla, indice_tabla)
{
	var pertenece_a_bdo = obj_tabla['pertenece_a_bdo'];
	var nombre_bd = obj_tabla['nombre_bd'];
	var nombre_tabla = obj_tabla['nombre_tabla'];
	var arreglo_campos_tabla = obj_tabla['campos_tabla'];
	var clase_titulo = "";
	var clase_nombre = "";
	var clase_tabla = "";
	if(pertenece_a_bdo)
	{
		clase_titulo = "titulo_tabla";
		clase_nombre = "nombre_tabla";
		clase_tabla = "tabla_bdo";
	}
	else
	{
		clase_titulo = "titulo_tabla_bde";
		clase_nombre = "nombre_tabla_bde";
		clase_tabla = "tabla_bde";
	}
	
	//se crea el div tabla
	var div_tabla = "<div class='div_tabla' id='"+nombre_bd+"_"+nombre_tabla+"'>"+
						"<table class='tabla "+clase_tabla+"'>"+
							"<thead>"+
								"<tr>"+
									"<th class='"+clase_nombre+" "+clase_titulo+"'>"+
									"<label>"+nombre_bd+"."+nombre_tabla+"</label></th>"+
								"</tr>"+
							"</thead>"+						
							"<tbody>";
	
	//agrego los atributos a la tabla
	for(var indice = 0; indice < arreglo_campos_tabla.length; indice++)
	{
		
		if(arreglo_campos_tabla[indice][1] == "PRI")
			tipo_llave = "key";
		else if(arreglo_campos_tabla[indice][1] == "MUL")
			tipo_llave = "fkey";
		else
			tipo_llave = "field";
		var imagen_tipo_llave = "<img src='../imagenes/"+tipo_llave+".png' class='vertical_centro imagen_campo'/>";
		
		div_tabla += "<tr>"+
						"<th id='"+nombre_bd+"_"+nombre_tabla+"_"+arreglo_campos_tabla[indice][0]+"' class='nombre_campo campo_tabla alineacion_izquierda'>"+imagen_tipo_llave+
						"<label>"+arreglo_campos_tabla[indice][0]+"</label></th>"+
					"</tr>";
	}
	//cierro la tabla
	div_tabla +=			"</tbody>"+
						"</table>"+
					"</div>";
	
	//se añade al DOM
	$('#div_grafo').append(div_tabla);
	//alert(indice_tabla+","+nombre_tabla);
	$("#"+nombre_bd+"_"+nombre_tabla).css("left",((indice_tabla) * 50)+"px");
	//se le añade movilidad
	$("#"+nombre_bd+"_"+nombre_tabla).draggable({	containment: '#div_grafo',
													//scroll:true,
													scrollSensitivity: 1,
													grid: [10,10],
													opacity: 0.7,
													stack: {group: '#div_grafo div',min: 1},
													drag: function() 
													{
														repaint();
													} 
												});
}

function obtenerRelaciones()
{
	$.ajax({
		async:		false,
		type: 		"POST",
		dataType:	"html",
		contentType:"application/x-www-form-urlencoded",
		url:		"../modulo_grafo/grafo.php",
		data:		"funcion=obtenerRelaciones",
		success:	recibirJSONRelaciones,
		timeout:	10000
	}); 
	return false;
}

function recibirJSONRelaciones(info_relaciones)
{
	/*
	 [
		 {"fue_codigo":"2","bd_origen":"bd_eps_sintetica","tabla_origen":"medico","campo_origen":"id","bd_destino":"bd_eps_real","tabla_destino":"medico","campo_destino":"id"},
		 {"fue_codigo":"2","bd_origen":"bd_eps_real","tabla_origen":"medico","campo_origen":"nombre","bd_destino":"bd_eps_real","tabla_destino":"medico","campo_destino":"nombre"},
		 {"fue_codigo":"3","bd_origen":"bd_eps_real","tabla_origen":"afiliado","campo_origen":"sexo","tabla_destino":"afiliado","campo_destino":"nombre"}
	 ]
	*/
	//alert(info_relaciones);
	arreglo_info_relaciones = eval("("+info_relaciones+")");
	repaint();
}