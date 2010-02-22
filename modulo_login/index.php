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

	session_start();
	
	if(!isset($_SESSION['step']))
		$_SESSION['step'] = 0;
		
	require_once("../herramientas/GeneradorHtml.inc");
	$html = new GeneradorHtml($_SESSION['lang']);
	
	if(isset($_SESSION['lang']))
		$idioma = $_SESSION['lang'];
	else
	{
		$idioma = 'en';
		$_SESSION['lang'] = 'en';
	}
?>
<html>
	<head>
		<title>PSDG</title>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
		<script type="text/javascript" src="../herramientas/validacion.js"></script>
		<script type="text/javascript" src="../herramientas/jquery-1.3.2.min.js"></script>
		<script type="text/javascript" src="../herramientas/funciones.js"></script>
		<script type="text/javascript" src="../herramientas/lang.js"></script>
		<script type="text/javascript" src="../herramientas/ui.core.js"></script>
		<script type="text/javascript" src="../herramientas/ui.datepicker.js"></script>
		
		<link rel="stylesheet" type="text/css" href="../estilos/redmond/ui.all.css" />
		<link rel="stylesheet" type="text/css" href="../estilos/redmond/ui.datepicker.css" />
		<link rel="stylesheet" type="text/css" href="../estilos/formulario.css"/>
		<link rel="stylesheet" type="text/css" href="../estilos/general.css"/>
	</head>
	<body onload="establecerPosicionSecuencia(<?php echo $_SESSION['step']; ?>); mostrarBotonLogout(<?php echo $_SESSION['step']; ?>); establecerIdioma('<?php echo $idioma; ?>')">
		<?php
			//DIV LOGO
			$html->tag("div", array("id"=>"div_logo", "class"=>"alineacion_centrado"));
			$html->end("div");
			//FIN DIV LOGO
			
			//DIV SECUENCIA
			$html->tag("div", array("id"=>"div_secuencia", "class"=>"alineacion_centrado alto_70"));
				$html->tag("img", array("id"=>"step_1", "src"=>"../imagenes/step_1_off.png", "alt"=>"paso 1", "title"=>"Set connections"));
				$html->end("img");
				$html->tag("img", array("src"=>"../imagenes/next.png", "alt"=>"next"));
				$html->end("img");
				$html->tag("img", array("id"=>"step_2", "src"=>"../imagenes/step_2_off.png", "alt"=>"paso 2", "title"=>"Set restrictions"));
				$html->end("img");
				$html->tag("img", array("src"=>"../imagenes/next.png", "alt"=>"next"));
				$html->end("img");
				$html->tag("img", array("id"=>"step_3", "src"=>"../imagenes/step_3_off.png", "alt"=>"paso 3", "title"=>"Set output type"));
				$html->end("img");
				$html->tag("img", array("src"=>"../imagenes/next.png", "alt"=>"next"));
				$html->end("img");
				$html->tag("img", array("id"=>"step_4", "src"=>"../imagenes/step_4_off.png", "alt"=>"paso 4", "title"=>"Run"));
				$html->end("img");
				
				$html->br();
				
				$html->tag("div", array("class"=>"tabla"));
					$html->tag("div", array("class"=>"fila"));
						$html->tag("div", array("id"=>"div_titulo_step", "class"=>"celda vertical_centro centrado alto_30"));
								$html->tag("label", array("id"=>"lbl_titulo_step", "class"=>"etiqueta fuente_18"));
								$html->end("label");
						$html->end("div");
					$html->end("div");
				$html->end("div");
				
				$html->tag("div", array("id"=>"div_logout"));
					$html->tag("input", array("id"=>"btn_logout", "type"=>"image", "onclick"=>"cerrarSesion();", "src"=>"../imagenes/btn_logout_1.png", "onmouseover"=>"this.src='../imagenes/btn_logout_2.png'", "onmouseout"=>"this.src='../imagenes/btn_logout_1.png'", "alt"=>"Cerrar sesión/Logout", "title"=>"Cerrar sesión/Logout"));
					$html->end("input");
				$html->end("div");
				
				$html->tag("div", array("id"=>"div_manual"));
					$html->tag("a", array("href"=>"../manual_de_usuario/index.php", "target"=>"_blank"));
						$html->tag("img", array("id"=>"btn_manual", "src"=>"../imagenes/manual.png", "alt"=>"Guía del usuario/User Guide", "title"=>"Guía del usuario/User Guide", "class"=>"sin_borde"), "", true);
					$html->end("a");
				$html->end("div");
					
			$html->end("div");
			//FIN DIV SECUENCIA
			
			//DIV CUERPO
			$html->tag("div", array("id"=>"div_cuerpo"));
				if(isset($_SESSION['modulo']) && $_SESSION['modulo'] != "login")
					require_once("../modulo_".$_SESSION['modulo']."/fm_".$_SESSION['modulo'].".php");
				else
					require_once("../modulo_login/fm_login.php");
			$html->end("div");
			//FIN DIV CUERPO
			
			//DIV BARRA DE ESTADO
			$html->tag("div", array("id"=>"barra_de_estado"));
				$html->tag("label", array("id"=>"lbl_loading"));
				$html->end("label");
				$html->tag("label", array("id"=>"lbl_status"));
					$html->printStaticText("PSDG Version 1.0");
				$html->end("label");
			$html->end("div");
			//FIN DIV BARRA DE ESTADO
			
			//DIV AYUDA
			$html->tag("div", array("id"=>"div_ayuda", "class"=>"oculto"));
			
				$html->tag("label", array("id"=>"lbl_ayuda", "class"=>"titulo"));
				$html->end("label");
				
				$html->tag("button", array("id"=>"boton_cerrar", "onclick"=>"efecto('div_ayuda','slideToggle');"));
						$html->printStaticText("X");
				$html->end("button");
				
				$html->tag("label", array("id"=>"div_mensaje"));
				$html->end("label");
				
			$html->end("div");
			//FIN DIV AYUDA
		?>
	</body>
</html>
