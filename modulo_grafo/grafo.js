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

function inicializar()
{
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
	var div_tabla = "<div class='tabla' id='"+nombre_bd+"_"+nombre_tabla+"'>"+
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
						"<th class='nombre_campo campo_tabla alineacion_izquierda'>"+imagen_tipo_llave+
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
	$("#"+nombre_bd+"_"+nombre_tabla).css("left",(indice_tabla * 50)+"px");
	//se le añade movilidad
	$("#"+nombre_bd+"_"+nombre_tabla).draggable({	containment: '#div_grafo',
											//scroll:true,
											scrollSensitivity: 1,
											grid: [10,10],
											opacity: 0.7,
											stack: {group: '#div_grafo div',min: 1} });
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
	alert(info_relaciones);
}

function repaint()
{
	var drawingCanvas = document.getElementById('area_dibujo');
	if(drawingCanvas.getContext) 
	{
		var context = drawingCanvas.getContext('2d');
		drawingCanvas.width = drawingCanvas.width;//reinicio el canvas
		//context.lineWidth = grosor_linea;

		
		//var top_absoluto =  $('#c1').offset().top;
		//var left_absoluto =  $('#c1').offset().left;
		
		//var x0 = left_absoluto;
		//var y0 = top_absoluto + delta_campo;
		//var x1 = left_absoluto - longitud_guion;
		//var y1 = top_absoluto + delta_campo;
		
		//alert("move ("+x0+","+y0+") - ("+x1+","+y1+")");
		context.beginPath();
		//de donde sale
		//context.moveTo(x0, y0);
		//context.lineTo(x1, y1);
		//context.lineTo(0, 0);

		//context.moveTo(x0, y0 + 2 * delta_campo);
		//context.lineTo(x1, y0 + 2 * delta_campo);
		//context.lineTo(0, 300);
		//context.strokeStyle = "#00f";
		//context.stroke();
		context.moveTo(10, 10);
		context.lineTo(50,50);
		context.strokeStyle = "#f00";
		context.stroke();
	}
}