<?php
session_start(); 
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
	<body>
		<div class="div_logo alineacion_centrado"></div>
		<div id="div_cuerpo">
		<?php 
			if(isset($_SESSION['modulo']))
			{
				require_once("../modulo_".$_SESSION['modulo']."/fm_".$_SESSION['modulo'].".php");
			}
			else
				require_once("../modulo_login/fm_login.php");
		?>
		</div>
		<div id="barra_de_estado">
			<label id="lbl_loading"></label><label id="lbl_status">PSDG Version 1.0</label>
		</div>
	</body>
</html>