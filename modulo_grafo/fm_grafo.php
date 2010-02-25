<?php
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
	    along with PSDG.  If not, see <http://www.gnu.org/licenses/>.
	
	*/
	
		session_start();	
		require_once("../herramientas/GeneradorHtml.inc");
		$html = new GeneradorHtml("es");
?>
<html>
	<head>
		<title>PSDG - Grafo de dependencias</title>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
		<script type="text/javascript" src="../herramientas/jquery-1.3.2.min.js"></script>
		<script type="text/javascript" src="../herramientas/jquery-ui-1.7.2.custom.min.js"></script>
		<link rel="stylesheet" type="text/css" href="../estilos/general.css"/>
		<link rel="stylesheet" type="text/css" href="../estilos/grafo.css"/>
	</head>
	<body>
	<?php	
		$html->cargarHerramientaJS("jquery-ui-1.7.2.custom.min");
		$html->cargarModuloJS("grafo");
		
		//DIV LOGO
		$html->tag("div", array("id"=>"div_logo", "class"=>"alineacion_centrado"));
		$html->end("div");
		//FIN DIV LOGO
		
		//DIV cuerpo
		$html->tag("div", array("id"=>"div_cuerpo_grafo"));
		
			//DIV grafo
			$html->tag("div", array("id"=>"div_grafo"));
			//canvas
			$html->tag("canvas" , array("height"=>"580", "width"=>"1024", "id"=>"area_dibujo"));
			$html->end("canvas");
			//fin canvas
			
			
			
			$html->end("div");
			//FIN DIV grafo
			
		$html->end("div");
		//FIN DIV cuerpo
	?>
	</body>
</html>