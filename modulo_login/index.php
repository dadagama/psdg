<?php
session_start();

if(!isset($_SESSION['step']))
	$_SESSION['step'] = 0;
	
require_once("../herramientas/GeneradorHtml.inc");
$html = new GeneradorHtml($_SESSION['lang']);
?>
<html>
	<head>
		<title>PSDG</title>
		<meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/> 
		<script type="text/javascript" src="../herramientas/validacion.js"></script>
		<script type="text/javascript" src="../herramientas/jquery-1.3.2.min.js"></script>
		<script type="text/javascript" src="../herramientas/funciones.js"></script>
		<link rel="stylesheet" type="text/css" href="../estilos/formulario.css">
		<link rel="stylesheet" type="text/css" href="../estilos/general.css">
	</head>
	<body onload="establecerPosicionSecuencia(<?php echo $_SESSION['step']; ?>)">
		<?php
			//DIV LOGO
			$html->tag("div", array("id"=>"div_logo", "class"=>"alineacion_centrado"));
			$html->end("div");
			//FIN DIV LOGO
			
			//DIV SECUENCIA
			$html->tag("div", array("id"=>"div_secuencia", "class"=>"alineacion_centrado"));
				$html->tag("img", array("id"=>"step_1", "src"=>"../imagenes/step_1_off.png", "alt"=>"paso 1", "title"=>"Establecer restricciones"));
				$html->tag("img", array("src"=>"../imagenes/next.png", "alt"=>"next"));
				$html->tag("img", array("id"=>"step_2", "src"=>"../imagenes/step_2_off.png", "alt"=>"2", "title"=>"2"));
				$html->tag("img", array("src"=>"../imagenes/next.png", "alt"=>"next"));
				$html->tag("img", array("id"=>"step_3", "src"=>"../imagenes/step_3_off.png", "alt"=>"3", "title"=>"3"));
				$html->tag("img", array("src"=>"../imagenes/next.png", "alt"=>"next"));
				$html->tag("img", array("id"=>"step_4", "src"=>"../imagenes/step_4_off.png", "alt"=>"4", "title"=>"4"));
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
		?>
	</body>
</html>