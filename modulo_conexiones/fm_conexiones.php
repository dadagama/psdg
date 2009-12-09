<?php
	session_start();
	$_SESSION['modulo'] = "conexiones";

	require_once("../herramientas/GeneradorHtml.inc");
	$html = new GeneradorHtml($_SESSION['lang']);
	
	$html->cargarJsDeModulo($_SESSION['modulo']);
	
	//DIV CONEXION
	$html->tag("div", array("id"=>"div_conexion"));
		$html->tag("fieldset");
		
			//TITULO DIV
			$html->tag("legend");
				$html->tag("label");
					$html->printText("lbl_conexion");
				$html->end("label");
			$html->end("legend");
			
			//TABLA FORMULARIO
			$html->tag("div", array("class"=>"tabla"));
			
				//FORMULARIO
				$html->tag("div", array("class"=>"fila"));
					$html->tag("div", array("class"=>"tabla_centrada tabla_bloque alto_120"));
					
						//CAMPO TIPO CONEXION
						$html->tag("div", array("class"=>"fila"));
							$html->tag("div", array("class"=>"celda alto_30"));
								$html->tag("label", array("class"=>"etiqueta"));
									$html->printText("lbl_con_tipo");
								$html->end("label");
							$html->end("div");
							$html->tag("div", array("class"=>"celda alto_30"));
								$html->tag("select", array("class"=>"ancho_120", "id"=>"con_tipo", "title"=>$html->getText('ttp_con_tipo')));
									$html->tag("option", array("value"=>"bd"));
										$html->printText("opt_con_tipo_bd");
									$html->end("option");
									$html->tag("option", array("value"=>"archivo"));
										$html->printText("opt_con_tipo_archivo");
									$html->end("option");
								$html->end("select");
							$html->end("div");
						$html->end("div");
					
						//CAMPO NOMBRE CONEXION
						$html->tag("div", array("class"=>"fila"));
							$html->tag("div", array("class"=>"celda alto_30"));
								$html->tag("label", array("class"=>"etiqueta"));
									$html->printText("lbl_con_nombre");
								$html->end("label");
							$html->end("div");
							$html->tag("div", array("class"=>"celda alto_30"));
								$html->tag("input", array("class"=>"ancho_120", "id"=>"con_nombre", "type"=>"text", "maxlength"=>"20", "title"=>$html->getText('ttp_con_nombre')));
							$html->end("div");
						$html->end("div");
						
						//CAMPO USUARIO CONEXION
						$html->tag("div", array("class"=>"fila"));
							$html->tag("div", array("class"=>"celda alto_30"));
								$html->tag("label", array("class"=>"etiqueta"));
									$html->printText("lbl_con_usuario");
								$html->end("label");
							$html->end("div");
							$html->tag("div", array("class"=>"celda alto_30"));
								$html->tag("input", array("class"=>"ancho_120", "id"=>"con_usuario", "type"=>"text", "maxlength"=>"30", "title"=>$html->getText("ttp_con_usuario")));
							$html->end("div");
						$html->end("div");
						
						//CAMPO CONTRASEÑA CONEXION
						$html->tag("div", array("class"=>"fila"));
							$html->tag("div", array("class"=>"celda alto_30"));
								$html->tag("label", array("class"=>"etiqueta"));
									$html->printText("lbl_con_password");
								$html->end("label");
							$html->end("div");
							$html->tag("div", array("class"=>"celda alto_30"));
								$html->tag("input", array("class"=>"ancho_120", "id"=>"con_password", "type"=>"password", "maxlength"=>"30", "title"=>$html->getText('ttp_con_password')));
							$html->end("div");
						$html->end("div");
					$html->end("div");
				$html->end("div");
				
				//BOTON FORMULARIO
				$html->tag("div", array("class"=>"fila"));
					$html->tag("div", array("class"=>"tabla_centrada"));
						$html->tag("div", array("class"=>"fila"));
							$html->tag("div", array("class"=>"celda alto_30"));
								$html->tag("input", array("id"=>"btn_establecer", "type"=>"button", "value"=>$html->getText("btn_establecer")));
							$html->end("div");
						$html->end("div");
					$html->end("div");
				$html->end("div");
				//FIN BOTON FORMULARIO
				
			$html->end("div");
			//FIN TABLA FORMULARIO
			
		$html->end("fieldset"); 
	$html->end("div");
	//FIN DIV CONEXION
	
	
	//DIV DE CONEXIONES
	$html->tag("div", array("id"=>"div_conexiones"));
		$html->tag("fieldset");
		
			$html->tag("legend");
				$html->tag("label");
					$html->printText("lbl_conexiones_establecidas");
				$html->end("label");
			$html->end("legend");
			//TABLA
			/*$html->tag("div", array("class"=>"tabla"));
				$html->tag("div", array("class"=>"fila"));
						$html->tag("div", array("class"=>"tabla_centrada"));
							$html->tag("div", array("class"=>"fila"));
								$html->tag("div", array("class"=>"celda alto_30"));
									$html->tag("label", array("class"=>"etiqueta"));
										$html->printText("lbl_con_nombre");*/
										
		$html->end("fieldset");
	$html->end("div");
	//FIN DIV DE CONEXIONES
?>