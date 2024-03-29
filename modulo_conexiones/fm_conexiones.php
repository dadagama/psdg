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
		
	$_SESSION['modulo'] = "conexiones";
	if(isset($_SESSION['step']) && $_SESSION['step'] != 1)//para el efecto de aparecer
		$ocultar = "oculto";
		
	$_SESSION['step'] = 1;

	require_once("../herramientas/GeneradorHtml.inc");
	$html = new GeneradorHtml($_SESSION['lang']);
	$html->cargarHerramientaJS("ajaxupload");
	$html->cargarModuloJS("conexiones");

	//DIV GENERAL
	$html->tag("div", array("id"=>"con_div_general", "class"=>"tabla $ocultar"));
		$html->tag("div", array("class"=>"fila"));
			$html->tag("div", array("class"=>"celda vertical_arriba ancho_512"));
	
				//DIV CONEXION
				$html->tag("div", array("id"=>"con_div_conexion"));
				
					$html->tag("fieldset");
					
						//BOTON AYUDA
						$html->botonAyuda("con_btn_help_1");
					
						//TITULO DIV
						$html->tag("legend");
							$html->tag("label");
								$html->printText("con_lgn_configurar_conexion");
							$html->end("label");
						$html->end("legend");
						
						//TABLA FORMULARIO PARTE ARRIBA
						$html->tag("div", array("class"=>"tabla"));
						
							//FORMULARIO
							$html->tag("div", array("class"=>"fila"));
								$html->tag("div", array("class"=>"tabla_centrada"));
								
									//CAMPO TIPO CONEXION
									$html->tag("div", array("class"=>"fila"));
										$html->tag("div", array("class"=>"alineacion_derecha celda vertical_centro alto_30 ancho_140"));
											$html->tag("label", array("class"=>"etiqueta", "id"=>"con_lbl_tipo"));
												$html->printText("con_lbl_tipo");
											$html->end("label");
										$html->end("div");
										 
										$html->tag("div", array("class"=>"alineacion_derecha celda vertical_centro alto_30 ancho_140"));
											$html->tag("select", array("class"=>"ancho_140", "id"=>"con_fue_codigo", "title"=>$html->getText('con_ttp_tipo'), "onchange"=>"actualizarFormulario();"));
												$html->tag("option", array("value"=>"2"));
													$html->printText("con_opt_tipo_bd");
												$html->end("option");
												$html->tag("option", array("value"=>"7", $disable_select=>$disable_select));
													$html->printText("con_opt_tipo_archivo");
												$html->end("option");
												$html->tag("option", array("value"=>"3", $disable_select=>$disable_select));
													$html->printText("con_opt_tipo_biblioteca");
												$html->end("option");
											$html->end("select");
										$html->end("div");
									$html->end("div");
									
									//CAMPO NOMBRE CONEXION
									$html->tag("div", array("class"=>"fila"));
										$html->tag("div", array("class"=>"alineacion_derecha celda vertical_centro alto_30 ancho_140"));
											$html->tag("label", array("class"=>"etiqueta", "id"=>"con_lbl_nombre"));
												$html->printText("con_lbl_nombre");
											$html->end("label");
										$html->end("div");
	
										$html->tag("div", array("class"=>"celda vertical_centro alto_30"));
											$html->tag("input", array("class"=>"ancho_140", "name"=>"con_nombre", "id"=>"con_nombre", "type"=>"text", "maxlength"=>"20", "title"=>$html->getText('con_ttp_nombre')));
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
										$html->printText("con_lgn_datos_conexion");
									$html->end("label");
								$html->end("legend");
							
								$html->tag("div", array("class"=>"tabla_centrada", "id"=>"con_div_datos_conexion"));
									
									//DIV CONEXION BD
									$html->tag("div", array("class"=>"fila", "id"=>"con_div_bd"));
										$html->tag("div", array("class"=>"celda"));
											$html->tag("div", array("class"=>"tabla"));
												//CAMPO SERVIDOR
												$html->tag("div", array("class"=>"fila"));
													$html->tag("div", array("class"=>"alineacion_derecha celda vertical_centro alto_30 ancho_140"));
														$html->tag("label", array("class"=>"etiqueta", "id"=>"con_lbl_servidor"));
															$html->printText("con_lbl_servidor");
														$html->end("label");
													$html->end("div");
													$html->tag("div", array("class"=>"celda vertical_centro alto_30"));
														$html->tag("input", array("class"=>"ancho_140", "name"=>"con_servidor", "id"=>"con_servidor", "type"=>"text", "title"=>$html->getText("con_ttp_servidor")));
													$html->end("div");
												$html->end("div");
											
												//CAMPO DB CONEXION
												$html->tag("div", array("class"=>"fila"));
													$html->tag("div", array("class"=>"alineacion_derecha celda vertical_centro alto_30 ancho_140"));
														$html->tag("label", array("class"=>"etiqueta", "id"=>"con_lbl_nombre_bd"));
															$html->printText("con_lbl_nombre_bd");
														$html->end("label");
													$html->end("div");
													$html->tag("div", array("class"=>"celda vertical_centro alto_30"));
														$html->tag("input", array("class"=>"ancho_140", "name"=>"con_nombre_bd", "id"=>"con_nombre_bd", "type"=>"text", "maxlength"=>"30", "title"=>$html->getText("con_ttp_nombre_bd")));
													$html->end("div");
												$html->end("div");
											
												//CAMPO USUARIO CONEXION
												$html->tag("div", array("class"=>"fila"));
													$html->tag("div", array("class"=>"alineacion_derecha celda vertical_centro alto_30 ancho_140"));
														$html->tag("label", array("class"=>"etiqueta", "id"=>"con_lbl_usuario"));
															$html->printText("con_lbl_usuario");
														$html->end("label");
													$html->end("div");
													$html->tag("div", array("class"=>"celda vertical_centro alto_30"));
														$html->tag("input", array("class"=>"ancho_140", "name"=>"con_usuario", "id"=>"con_usuario", "type"=>"text", "maxlength"=>"30", "title"=>$html->getText("con_ttp_usuario")));
													$html->end("div");
												$html->end("div");
												
												//CAMPO CONTRASEÑA CONEXION
												$html->tag("div", array("class"=>"fila"));
													$html->tag("div", array("class"=>"alineacion_derecha celda vertical_centro alto_30 ancho_140"));
														$html->tag("label", array("class"=>"etiqueta", "id"=>"con_lbl_password"));
															$html->printText("con_lbl_password");
														$html->end("label");
													$html->end("div");
													$html->tag("div", array("class"=>"celda vertical_centro alto_30"));
														$html->tag("input", array("class"=>"ancho_140", "name"=>"con_password", "id"=>"con_password", "type"=>"password", "maxlength"=>"30", "title"=>$html->getText('con_ttp_password')));
													$html->end("div");
												$html->end("div");
												
											$html->end("div");
											
											//BOTON FORMULARIO
											$html->tag("div", array("class"=>"tabla"));
												$html->tag("div", array("class"=>"fila"));
													$html->tag("div", array("class"=>"celda vertical_centro alto_30 centrado"));
														$html->tag("input", array("id"=>"con_btn_establecer", "type"=>"button", "value"=>$html->getText("con_btn_establecer"), "onclick"=>"adicionarConexion();"));
													$html->end("div");
												$html->end("div");
											$html->end("div");	
											//FIN BOTON FORMULARIO
											
										$html->end("div");	
									$html->end("div");	
									//FIN DIV CONEXION BD
									
									//DIV ARCHIVO
									$html->tag("div", array("class"=>"fila", "id"=>"con_div_archivo"));
									
										//CAMPO SEPARADOR
										$html->tag("div", array("class"=>"fila"));
											$html->tag("div", array("class"=>"alineacion_derecha celda vertical_centro alto_30 ancho_140"));
												$html->tag("label", array("class"=>"etiqueta", "id"=>"con_lbl_separador"));
													$html->printText("con_lbl_separador");
												$html->end("label");
											$html->end("div");
											$html->tag("div", array("class"=>"alineacion_izquierda celda vertical_centro alto_30"));
												$html->tag("input", array("class"=>"ancho_35", "maxlength"=>"2", "name"=>"con_separador", "id"=>"con_separador", "type"=>"text", "title"=>$html->getText("con_ttp_separador")));
											$html->end("div");
										$html->end("div");	
										
										//CAMPO ARCHIVO
										$html->tag("div", array("class"=>"fila"));
											$html->tag("div", array("class"=>"alineacion_derecha celda vertical_centro alto_30 ancho_140"));
												$html->tag("label", array("class"=>"etiqueta", "id"=>"con_lbl_nombre_archivo"));
													$html->printText("con_lbl_nombre_archivo");
												$html->end("label");
											$html->end("div");
											$html->tag("div", array("class"=>"celda vertical_centro alto_30"));
												$html->tag("input", array("class"=>"ancho_140", "size"=>"6", "name"=>"con_nombre_archivo", "id"=>"con_nombre_archivo", "type"=>"file", "title"=>$html->getText("con_ttp_nombre_archivo")));
											$html->end("div");
										$html->end("div");
										
									$html->end("div");
									//FIN DIV ARCHIVO
									
									//DIV BIBLIOTECA
									$html->tag("div", array("class"=>"fila", "id"=>"con_div_biblioteca"));
										//CAMPO BIBLIOTECA
										$html->tag("div", array("class"=>"fila"));
											$html->tag("div", array("class"=>"alineacion_derecha celda vertical_centro alto_30 ancho_140"));
												$html->tag("label", array("class"=>"etiqueta", "id"=>"con_lbl_nombre_biblioteca"));
													$html->printText("con_lbl_nombre_biblioteca");
												$html->end("label");
											$html->end("div");
											$html->tag("div", array("class"=>"celda vertical_centro alto_30"));
												$html->tag("input", array("class"=>"ancho_140", "size"=>"6", "name"=>"con_nombre_biblioteca", "id"=>"con_nombre_biblioteca", "type"=>"file", "title"=>$html->getText("con_ttp_nombre_biblioteca")));
											$html->end("div");
										$html->end("div");
									$html->end("div");
									//FIN DIV BIBLIOTECA
									
								$html->end("div");
							$html->end("fieldset"); 
							$html->end("div");
							

							
						$html->end("div");
						//FIN TABLA FORMULARIO
						
					$html->end("fieldset"); 
					$html->end("form"); 
				$html->end("div");
				//FIN DIV CONEXION
				
			$html->end("div");
			
			
			$html->tag("div", array("class"=>"celda vertical_arriba ancho_512"));
				$html->tag("div", array("class"=>"tabla"));

					//DIV DE CONEXIONBDO
					$html->tag("div", array("class"=>"fila"));						
					$html->tag("div", array("class"=>"celda"));
						$html->tag("div", array("id"=>"con_div_bdo"));
							$html->tag("fieldset");
						
								//BOTON AYUDA
								$html->botonAyuda("con_btn_help_3");
					
								$html->tag("legend");
									$html->tag("label");
										$html->printText("con_lgn_conexiones_bdo_establecida");
									$html->end("label");
								$html->end("legend");
						
								//TABLA
								$html->tag("div", array("class"=>"tabla", "id"=>"con_div_conexion_bdo"));
								$html->end("div");	
								//FIN TABLA
						
							$html->end("fieldset");
						$html->end("div");
					$html->end("div");
					$html->end("div");
					//FIN DIV DE CONEXIONBDO


					//DIV DE CONEXIONES
					$html->tag("div", array("class"=>"fila"));						
					$html->tag("div", array("class"=>"celda"));
						$html->tag("div", array("id"=>"con_div_conexiones"));
							$html->tag("fieldset");
						
								//BOTON AYUDA
								$html->botonAyuda("con_btn_help_2");
					
								$html->tag("legend");
									$html->tag("label");
										$html->printText("con_lgn_conexiones_establecidas");
									$html->end("label");
								$html->end("legend");
						
								//TABLA
								$html->tag("div", array("class"=>"tabla", "id"=>"con_div_conexiones_establecidas"));
								$html->end("div");	
								//FIN TABLA
						
							$html->end("fieldset");
						$html->end("div");
					$html->end("div");
					$html->end("div");
					//FIN DIV DE CONEXIONES
					
				$html->end("div");
			$html->end("div");
			
		$html->end("div");
	$html->end("div");
	//FIN DIV GENERAL
	
	//DIV BOTONES SECUENCIA
	$html->generarBotonesSecuencia("con", false, true, $ocultar);
	//FIN DIV BOTONES SECUENCIA
?>
