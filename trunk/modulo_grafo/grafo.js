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

var mitad_campo = 15;//los div_campo son de 30px de alto
var border_campo = 3;//cada div_campo esta separado por 3px entre ellos
var longitud_guion = 15;//fragmento recto que sale del campo
var grosor_linea = 1;//grueso de las lineas
var arreglo_info_relaciones;//arreglo JSon de las relaciones
var drawingCanvas;
var context;

function repaint()
{
		drawingCanvas.width = drawingCanvas.width;//reinicio el canvas
		
		context.beginPath();
		//[{"fue_codigo":"2","bd_origen":"bd_eps_sintetica","tabla_origen":"medico","campo_origen":"nombre","bd_destino":"bd_eps_real","tabla_destino":"medico","campo_destino":"nombre"}]
		for(var indice = 0; indice < arreglo_info_relaciones.length; indice++)
		{
			dibujarRelacion(arreglo_info_relaciones[indice]);
		}
}

function dibujarRelacion(relacion)
{
	//calculo ubicacion canvas
	var posicion_canvas = $('#'+relacion['bd_origen']+"_"+relacion['tabla_origen']+"_"+relacion['campo_origen']).offset();
	var top_canvas = posicion_canvas.top;
	var left_canvas = posicion_canvas.left;
	
	alert("posicion origen canvas = "+left_canvas+","+top_canvas);
	
	//calculo las posicion campo origen
	var ancho_origen = $('#'+relacion['bd_origen']+"_"+relacion['tabla_origen']+"_"+relacion['campo_origen']).width();//NO PARECE NECESITARSE
	var alto_origen = $('#'+relacion['bd_origen']+"_"+relacion['tabla_origen']+"_"+relacion['campo_origen']).height();
	var posicion_origen = $('#'+relacion['bd_origen']+"_"+relacion['tabla_origen']+"_"+relacion['campo_origen']).offset();
	var top_origen = posicion_origen.top;
	var left_origen = posicion_origen.left;
	
	alert(relacion['bd_origen']+"_"+relacion['tabla_origen']+"_"+relacion['campo_origen']+" = "+ancho_origen+","+alto_origen+"-"+top_origen+","+left_origen);
	//calculo posicion campo destino
	var ancho_destino = $('#'+relacion['bd_destino']+"_"+relacion['tabla_destino']+"_"+relacion['campo_destino']).width();;
	var alto_destino = $('#'+relacion['bd_destino']+"_"+relacion['tabla_destino']+"_"+relacion['campo_destino']).height();
	var posicion_destino = $('#'+relacion['bd_destino']+"_"+relacion['tabla_destino']+"_"+relacion['campo_destino']).position();
	var top_destino = posicion_destino.top;
	var left_destino = posicion_destino.left;
	
	
	
	//asigno color de linea deacuerdo a la fuente
	if(relacion['fue_codigo'] == "3")
		context.strokeStyle = "#00f";
	else //if(relacion['fue_codigo'] == "2")
		context.strokeStyle = "#f00";

	//iniciar fragmento recto desde origen 
	punto_choque_origen = (top_origen + (alto_origen / 2));
	alert(left_origen+"choque="+punto_choque_origen);
	context.moveTo(left_origen,punto_choque_origen);
	context.lineTo((left_origen - longitud_guion), (top_origen + (alto_origen / 2)));
	context.lineTo(0,0);
	context.lineTo(50,50);
	context.stroke();
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
		async:		true,
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
		alert('u');
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
	if(pertenece_a_bdo)
	{
		clase_titulo = "titulo_tabla";
		clase_nombre = "nombre_tabla";
	}
	else
	{
		clase_titulo = "titulo_tabla_bde";
		clase_nombre = "nombre_tabla_bde";
	}
	
	//se crea el div tabla
	var div_tabla = "<div class='div_tabla' id='"+nombre_bd+"_"+nombre_tabla+"'>"+
						"<table class='tabla'>"+
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
	$("#"+nombre_bd+"_"+nombre_tabla).css("left",((indice_tabla + 1) * 250)+"px");
	//se le añade movilidad
	$("#"+nombre_bd+"_"+nombre_tabla).draggable({	containment: '#div_grafo',
													//scroll:true,
													scrollSensitivity: 1,
													grid: [10,10],
													opacity: 0.7,
													stack: {group: '#div_grafo div',min: 1}//,
//													drag: function() 
//													{
//														//alert('x');
//													} 
												});
}

function obtenerRelaciones()
{
	$.ajax({
		async:		true,
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
	//[{"fue_codigo":"3","tabla_origen":"afiliado","campo_origen":"sexo","tabla_destino":"afiliado","campo_destino":"nombre"},
	// {...}]
	//alert(info_relaciones);
	arreglo_info_relaciones = eval("("+info_relaciones+")");
	repaint();
}