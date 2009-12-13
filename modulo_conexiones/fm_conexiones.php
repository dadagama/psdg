<?php
	session_start();
	$_SESSION['modulo'] = "conexiones";
	$_SESSION['step'] = 1;

	require_once("../herramientas/GeneradorHtml.inc");
	$html = new GeneradorHtml($_SESSION['lang']);
	
	$html->cargarJsDeModulo($_SESSION['modulo']);
	
	//DIV GENERAL
	$html->tag("div", array("id"=>"div_general_conexiones", "class"=>"tabla"));
		$html->tag("div", array("class"=>"fila"));
			$html->tag("div", array("class"=>"celda vertical_arriba"));
	
				//DIV CONEXION
				$html->tag("div", array("id"=>"div_conexion"));
										
					$html->tag("fieldset");
					
						//BOTON AYUDA
						$html->tag("div", array("class"=>"div_help"));
							$html->tag("img", array("src"=>"../imagenes/help.png", "alt"=>"Ayuda", "title"=>"Haga clic para obtener ayuda sobre este módulo."));
						$html->end("div");
					
						//TITULO DIV
						$html->tag("legend");
							$html->tag("label");
								$html->printText("lgn_con_configurar_conexion");
							$html->end("label");
						$html->end("legend");
						
						//TABLA FORMULARIO PARTE ARRIBA
						$html->tag("div", array("class"=>"tabla"));
						
							//FORMULARIO
							$html->tag("div", array("class"=>"fila"));
								$html->tag("div", array("class"=>"tabla_centrada"));
								
									//CAMPO TIPO CONEXION
									$html->tag("div", array("class"=>"fila"));
										$html->tag("div", array("class"=>"celda vertical_centro alto_30"));
											$html->tag("label", array("class"=>"etiqueta"));
												$html->printText("lbl_con_tipo");
											$html->end("label");
										$html->end("div");
										$html->tag("div", array("class"=>"celda vertical_centro alto_30"));
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
										$html->tag("div", array("class"=>"celda vertical_centro alto_30"));
											$html->tag("label", array("class"=>"etiqueta"));
												$html->printText("lbl_con_nombre");
											$html->end("label");
										$html->end("div");
										$html->tag("div", array("class"=>"celda vertical_centro alto_30"));
											$html->tag("input", array("class"=>"ancho_120", "id"=>"con_nombre", "type"=>"text", "maxlength"=>"20", "title"=>$html->getText('ttp_con_nombre')));
										$html->end("div");
									$html->end("div");
								$html->end("div");
							$html->end("div");
							
							//TABLA FORMULARIO PARTE ABAJO (DATOS CONEXION)
							$html->tag("div", array("class"=>"fila"));
							
							$html->tag("fieldset");
					
								//TITULO DIV
								$html->tag("legend");
									$html->tag("label");
										$html->printText("lgn_con_datos_conexion");
									$html->end("label");
								$html->end("legend");
							
								$html->tag("div", array("class"=>"tabla_centrada"));
									
									//CAMPO DB CONEXION
									$html->tag("div", array("class"=>"fila"));
										$html->tag("div", array("class"=>"celda vertical_centro alto_30"));
											$html->tag("label", array("class"=>"etiqueta"));
												$html->printText("lbl_con_nombre_db");
											$html->end("label");
										$html->end("div");
										$html->tag("div", array("class"=>"celda vertical_centro alto_30"));
											$html->tag("input", array("class"=>"ancho_120", "id"=>"con_nombre_db", "type"=>"text", "maxlength"=>"30", "title"=>$html->getText("ttp_con_nombre_db")));
										$html->end("div");
									$html->end("div");
								
									//CAMPO USUARIO CONEXION
									$html->tag("div", array("class"=>"fila"));
										$html->tag("div", array("class"=>"celda vertical_centro alto_30"));
											$html->tag("label", array("class"=>"etiqueta"));
												$html->printText("lbl_con_usuario");
											$html->end("label");
										$html->end("div");
										$html->tag("div", array("class"=>"celda vertical_centro alto_30"));
											$html->tag("input", array("class"=>"ancho_120", "id"=>"con_usuario", "type"=>"text", "maxlength"=>"30", "title"=>$html->getText("ttp_con_usuario")));
										$html->end("div");
									$html->end("div");
									
									//CAMPO CONTRASEÑA CONEXION
									$html->tag("div", array("class"=>"fila"));
										$html->tag("div", array("class"=>"celda vertical_centro alto_30"));
											$html->tag("label", array("class"=>"etiqueta"));
												$html->printText("lbl_con_password");
											$html->end("label");
										$html->end("div");
										$html->tag("div", array("class"=>"celda vertical_centro alto_30"));
											$html->tag("input", array("class"=>"ancho_120", "id"=>"con_password", "type"=>"password", "maxlength"=>"30", "title"=>$html->getText('ttp_con_password')));
										$html->end("div");
									$html->end("div");
								$html->end("div");
							$html->end("fieldset"); 
							$html->end("div");
							
							//BOTON FORMULARIO
							$html->tag("div", array("class"=>"fila"));
								$html->tag("div", array("class"=>"tabla_centrada"));
									$html->tag("div", array("class"=>"fila"));
										$html->tag("div", array("class"=>"celda vertical_centro alto_30"));
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
				
			$html->end("div");
			$html->tag("div", array("class"=>"celda vertical_arriba"));
			
				//DIV DE CONEXIONES
				$html->tag("div", array("id"=>"div_conexiones"));
					$html->tag("fieldset");
			
						$html->tag("legend");
							$html->tag("label");
								$html->printText("lgn_con_conexiones_establecidas");
							$html->end("label");
						$html->end("legend");
						//TABLA
						/*$html->tag("div", array("class"=>"tabla"));
							$html->tag("div", array("class"=>"fila"));
									$html->tag("div", array("class"=>"tabla_centrada"));
										$html->tag("div", array("class"=>"fila"));
											$html->tag("div", array("class"=>"celda vertical_centro alto_30"));
												$html->tag("label", array("class"=>"etiqueta"));
													$html->printText("lbl_con_nombre");*/
													
					$html->end("fieldset");
				$html->end("div");
				//FIN DIV DE CONEXIONES
				
			$html->end("div");
		$html->end("div");
	$html->end("div");
	//FIN DIV GENERAL
?>
