<?php
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
	require_once("../herramientas/GeneradorHtml.inc");
	$html = new GeneradorHtml($_SESSION['lang']);
?>
<html>
	<head>
		<title>PSDG - Manual de usuario</title>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
		<script type="text/javascript" src="../herramientas/jquery-1.3.2.min.js"></script>
		<script type="text/javascript" src="index.js"></script>
		
		<link rel="stylesheet" type="text/css" href="../estilos/formulario.css"/>
		<link rel="stylesheet" type="text/css" href="../estilos/general.css"/>
		<script languaje="javascript">
			var step_seleccionado = 0;
/*
			function $(id){return document.getElementById(id);}
			window.onload=function(){
				var response='<object classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=7,0,19,0" width="825" height="575"></object>';
				$('div_cuerpo').innerHTML=response;
			}
			*/
		</script>
	</head>
	<body>
		<?php
			//DIV LOGO
			$html->tag("div", array("id"=>"div_logo", "class"=>"alineacion_centrado"));
			$html->end("div");
			//FIN DIV LOGO
			
			//DIV SECUENCIA
			$html->tag("div", array("id"=>"div_secuencia", "class"=>"alineacion_centrado alto_80"));
				$html->tag("label", array("class"=>"etiqueta fuente_18"));
					$titulo = "MANUAL DE USUARIO";
					$html->printStaticText(utf8_decode($titulo));
				$html->end("label");
				$html->br();
				$html->tag("label", array("class"=>"etiqueta"));
					$titulo = "Seleccione el módulo del cual desea obtener ayuda";
					$html->printStaticText(utf8_decode($titulo));
				$html->end("label");
				$html->br();
				$html->tag("input", array("type"=>"image", "id"=>"step_1", "src"=>"../imagenes/step_1_off.png", "onmouseover"=>"onMouseOver(1);", "onmouseout"=>"onMouseOut(1);", "onclick"=>"onMouseClic(1);", "alt"=>"paso 1", "title"=>"Configurar Conexiones"),"",true);
				$html->tag("img", array("src"=>"../imagenes/next.png", "alt"=>"next"),"",true);
				$html->tag("input", array("type"=>"image", "id"=>"step_2", "src"=>"../imagenes/step_2_off.png", "onmouseover"=>"onMouseOver(2);", "onmouseout"=>"onMouseOut(2);", "onclick"=>"onMouseClic(2);",  "alt"=>"paso 2", "title"=>"Establecer Restricciones"),"",true);
				$html->tag("img", array("src"=>"../imagenes/next.png", "alt"=>"next"),"",true);
				$html->tag("input", array("type"=>"image", "id"=>"step_3", "src"=>"../imagenes/step_3_off.png", "onmouseover"=>"onMouseOver(3);", "onmouseout"=>"onMouseOut(3);", "onclick"=>"onMouseClic(3);",  "alt"=>"paso 3", "title"=>"Establecer formato de salida"),"",true);
				$html->tag("img", array("src"=>"../imagenes/next.png", "alt"=>"next"),"",true);
				$html->tag("input", array("type"=>"image", "id"=>"step_4", "src"=>"../imagenes/step_4_off.png", "onmouseover"=>"onMouseOver(4);", "onmouseout"=>"onMouseOut(4);", "onclick"=>"onMouseClic(4);",  "alt"=>"paso 4", "title"=>"Ejecución"),"",true);
			$html->end("div");
			//FIN DIV SECUENCIA
			
			//DIV CUERPO
			$html->tag("div", array("id"=>"div_cuerpo"));
				
			$html->end("div");
			//FIN DIV CUERPO
		?>
	</body>
</html>
