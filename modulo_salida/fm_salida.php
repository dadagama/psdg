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
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

*/

<?php
	session_start();
		
	$_SESSION['modulo'] = "salida";
	if(isset($_SESSION['step']) && $_SESSION['step'] != 3)//para el efecto de aparecer
		$ocultar = "oculto";
		
	$_SESSION['step'] = 3;

	require_once("../herramientas/GeneradorHtml.inc");
	$html = new GeneradorHtml($_SESSION['lang']);
	$html->cargarModuloJS($_SESSION['modulo']);

	//DIV GENERAL
	$html->tag("div", array("id"=>"sal_div_general", "class"=>"$ocultar"));
		$html->tag("div", array("class"=>"tabla"));	
			$html->tag("div", array("class"=>"fila"));
				$html->tag("div", array("class"=>"celda"));
		
					//DIV TIPOS
					$html->tag("div", array("id"=>"sal_div_tipos"));			
						$html->tag("fieldset");
						
							//BOTON AYUDA
							$html->botonAyuda("sal_btn_help_1");
						
							//TITULO DIV
							$html->tag("legend");
								$html->tag("label");
									$html->printText("sal_lgn_tipo_salida");
								$html->end("label");
							$html->end("legend");
							
							//TABLA FORMULARIO
							$html->tag("div", array("class"=>"tabla"));	
								$html->tag("div", array("class"=>"fila"));
									$html->tag("div", array("class"=>"celda"));
										$html->tag("input", array("id" => "btn_tis_bdo",
																	"onclick"=>"seleccionarSalida(1);", 
																	"type"=>"image", 
																	"src"=>"../imagenes/btn_db_1.png", 
																	"alt"=>"bd_out", 
																	"title"=>$html->getText("sal_ttp_bd"),
																	"onmouseover"=>"this.src='../imagenes/btn_db_2.png'",
																	"onmouseout"=>"this.src='../imagenes/btn_db_1.png'"));
									$html->end("div");
									$html->tag("div", array("class"=>"celda"));
										$html->tag("input", array("id" => "btn_tis_sql",
																	"onclick"=>"alert('no implementado aún');", 
																	"type"=>"image", 
																	"src"=>"../imagenes/btn_text_1.png", 
																	"alt"=>"text_out", 
																	"title"=>$html->getText("sal_ttp_text"),
																	"onmouseover"=>"this.src='../imagenes/btn_text_2.png'",
																	"onmouseout"=>"this.src='../imagenes/btn_text_1.png'"));
									$html->end("div");
								$html->end("div");
								
								$html->tag("div", array("class"=>"fila"));
								
									$html->tag("div", array("class"=>"celda vertical_centro"));
										$html->tag("label", array("class"=>"etiqueta"));
											$html->printText("sal_lbl_bd");
										$html->end("label");
									$html->end("div");
										
									$html->tag("div", array("class"=>"celda vertical_centro"));
										$html->tag("label", array("class"=>"etiqueta alto_30"));
											$html->printText("sal_lbl_text"); 
										$html->end("label");
									$html->end("div");
									
								$html->end("div");
							$html->end("div");
							//FIN TABLA FORMULARIO
							
						$html->end("fieldset"); 
					$html->end("div");
					//FIN DIV CONEXION
					
				$html->end("div");
			$html->end("div");
		$html->end("div");
	$html->end("div");
	//FIN DIV GENERAL
	
	//DIV BOTONES SECUENCIA
	$html->generarBotonesSecuencia("sal", true, true, $ocultar);
	//FIN DIV BOTONES SECUENCIA
?>
