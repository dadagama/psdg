<?php
	session_start();
		
	$_SESSION['modulo'] = "conexiones";
	if(isset($_SESSION['step']) && $_SESSION['step'] != 1)//para el efecto de aparecer
		$ocultar = "oculto";
		
	$_SESSION['step'] = 1;

	require_once("../modulo_conexiones/Conexiones.inc");
	$objetoConexiones = new Conexiones($_SESSION['conexionBDI'],$_SESSION['usu_login']);
	$conexion_BDO_establecida = $objetoConexiones->existeRegistroBDO();
	
	
	require_once("../herramientas/GeneradorHtml.inc");
	$html = new GeneradorHtml($_SESSION['lang']);
	
	$html->cargarModuloJS("conexiones");
	
	//DIV GENERAL
	$html->tag("div", array("id"=>"div_general_conexiones", "class"=>"tabla $ocultar"));
		$html->tag("div", array("class"=>"fila"));
			$html->tag("div", array("class"=>"celda vertical_arriba"));
	
				//DIV CONEXION
				$html->tag("div", array("id"=>"div_conexion"));
				
					$html->tag("fieldset");
					
						//BOTON AYUDA
						$html->botonAyuda("btn_con_help_1");
					
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
										$html->tag("div", array("class"=>"celda vertical_centro alto_30 ancho_130"));
											$html->tag("label", array("class"=>"etiqueta", "id"=>"lbl_con_tipo"));
												$html->printText("lbl_con_tipo");
											$html->end("label");
										$html->end("div");
										$html->tag("div", array("class"=>"celda vertical_centro alto_30 ancho_130"));
								
										if(!$conexion_BDO_establecida)
											$disable_select = "disabled";

										$html->tag("select", array("class"=>"ancho_130", "id"=>"con_tipo", "title"=>$html->getText('ttp_con_tipo')));
											$html->tag("option", array("value"=>"bd"));
												$html->printText("opt_con_tipo_bd");
											$html->end("option");
											$html->tag("option", array("value"=>"archivo", $disable_select=>$disable_select));
												$html->printText("opt_con_tipo_archivo");
											$html->end("option");
											$html->tag("option", array("value"=>"biblioteca", $disable_select=>$disable_select));
												$html->printText("opt_con_tipo_biblioteca");
											$html->end("option");
										$html->end("select");
										
										$html->end("div");
									$html->end("div");
									
									//CAMPO NOMBRE CONEXION
									$html->tag("div", array("class"=>"fila"));
										$html->tag("div", array("class"=>"celda vertical_centro alto_30 ancho_130"));
											$html->tag("label", array("class"=>"etiqueta", "id"=>"lbl_con_nombre"));
												$html->printText("lbl_con_nombre");
											$html->end("label");
										$html->end("div");
										$html->tag("div", array("class"=>"celda vertical_centro alto_30"));
										if(!$conexion_BDO_establecida)
										{
											$value_input = "BDO";
											$disable_input = "readonly";
										}	
										$html->tag("input", array($disable_input=>$disable_input, "value"=>$value_input, "class"=>"ancho_130", "name"=>"con_nombre", "id"=>"con_nombre", "type"=>"text", "maxlength"=>"20", "title"=>$html->getText('ttp_con_nombre')));

										$html->end("div");
									$html->end("div");

								$html->end("div");
							$html->end("div");
							//FIN FORMULARIO
							
							//TABLA FORMULARIO PARTE ABAJO (DATOS CONEXION)
							$html->tag("div", array("class"=>"fila"));
							
							$html->tag("form", array("name"=>"fm_datos_conexion", "id"=>"fm_datos_conexion"));
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
										$html->tag("div", array("class"=>"celda vertical_centro alto_30 ancho_130"));
											$html->tag("label", array("class"=>"etiqueta", "id"=>"lbl_con_nombre_db"));
												$html->printText("lbl_con_nombre_db");
											$html->end("label");
										$html->end("div");
										$html->tag("div", array("class"=>"celda vertical_centro alto_30"));
											$html->tag("input", array("class"=>"ancho_130", "name"=>"con_nombre_db", "id"=>"con_nombre_db", "type"=>"text", "maxlength"=>"30", "title"=>$html->getText("ttp_con_nombre_db")));
										$html->end("div");
									$html->end("div");
								
									//CAMPO USUARIO CONEXION
									$html->tag("div", array("class"=>"fila"));
										$html->tag("div", array("class"=>"celda vertical_centro alto_30 ancho_130"));
											$html->tag("label", array("class"=>"etiqueta", "id"=>"lbl_con_usuario"));
												$html->printText("lbl_con_usuario");
											$html->end("label");
										$html->end("div");
										$html->tag("div", array("class"=>"celda vertical_centro alto_30"));
											$html->tag("input", array("class"=>"ancho_130", "name"=>"con_usuario", "id"=>"con_usuario", "type"=>"text", "maxlength"=>"30", "title"=>$html->getText("ttp_con_usuario")));
										$html->end("div");
									$html->end("div");
									
									//CAMPO CONTRASEÑA CONEXION
									$html->tag("div", array("class"=>"fila"));
										$html->tag("div", array("class"=>"celda vertical_centro alto_30 ancho_130"));
											$html->tag("label", array("class"=>"etiqueta", "id"=>"lbl_con_password"));
												$html->printText("lbl_con_password");
											$html->end("label");
										$html->end("div");
										$html->tag("div", array("class"=>"celda vertical_centro alto_30"));
											$html->tag("input", array("class"=>"ancho_130", "name"=>"con_password", "id"=>"con_password", "type"=>"password", "maxlength"=>"30", "title"=>$html->getText('ttp_con_password')));
										$html->end("div");
									$html->end("div");
									
									//CAMPO ARCHIVO
									$html->tag("div", array("class"=>"fila oculto", "id"=>"div_con_nombre_archivo"));
										$html->tag("div", array("class"=>"celda vertical_centro alto_30 ancho_130"));
											$html->tag("label", array("class"=>"etiqueta", "id"=>"lbl_con_nombre_archivo"));
												$html->printText("lbl_con_nombre_archivo");
											$html->end("label");
										$html->end("div");
										$html->tag("div", array("class"=>"celda vertical_centro alto_30"));
											$html->tag("input", array("class"=>"ancho_130", "name"=>"con_nombre_archivo", "id"=>"con_nombre_archivo", "type"=>"file", "title"=>$html->getText("ttp_con_nombre_archivo")));
										$html->end("div");
									$html->end("div");
									
									//CAMPO BIBLIOTECA
									$html->tag("div", array("class"=>"fila oculto", "id"=>"div_con_nombre_biblioteca"));
										$html->tag("div", array("class"=>"celda vertical_centro alto_30 ancho_130"));
											$html->tag("label", array("class"=>"etiqueta", "id"=>"lbl_con_nombre_biblioteca"));
												$html->printText("lbl_con_nombre_biblioteca");
											$html->end("label");
										$html->end("div");
										$html->tag("div", array("class"=>"celda vertical_centro alto_30"));
											$html->tag("input", array("class"=>"ancho_130", "name"=>"con_nombre_biblioteca", "id"=>"con_nombre_biblioteca", "type"=>"file", "title"=>$html->getText("ttp_con_nombre_biblioteca")));
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
											$html->tag("input", array("type"=>"button", "value"=>$html->getText("btn_establecer"), "onclick"=>"adicionarConexion();"));
										$html->end("div");
									$html->end("div");
								$html->end("div");
							$html->end("div");
							//FIN BOTON FORMULARIO
							
						$html->end("div");
						//FIN TABLA FORMULARIO
						
					$html->end("fieldset"); 
					$html->end("form"); 
				$html->end("div");
				//FIN DIV CONEXION
				
			$html->end("div");
			
			
			$html->tag("div", array("class"=>"celda vertical_arriba"));
			
				//DIV DE CONEXIONES
				$html->tag("div", array("id"=>"div_conexiones"));
					$html->tag("fieldset");
						
						//BOTON AYUDA
						$html->botonAyuda("btn_con_help_2");
					
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
