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
		
	$_SESSION['modulo'] = "restricciones";
	//if(isset($_SESSION['step']) && $_SESSION['step'] != 2)//para el efecto de aparecer
		$ocultar = "oculto";
	
	$_SESSION['step'] = 2;

	require_once("../herramientas/GeneradorHtml.inc");
	$html = new GeneradorHtml($_SESSION['lang']);

	$html->cargarHerramientaJS("jquery.tree.min");
	$html->cargarHerramientaJS("jquery-spin");
	$html->cargarModuloJS($_SESSION['modulo']);

	require_once("../modulo_restricciones/Restricciones.inc");
	$objetoRestricciones = new Restricciones($_SESSION['conexionBDI'],$_SESSION['usu_login'],$_SESSION['lang']);
	
	//DIV GENERAL
	$html->tag("div", array("id"=>"res_div_general", "class"=>"tabla $ocultar"));
		$html->tag("div", array("class"=>"fila"));
			$html->tag("div", array("class"=>"celda vertical_arriba ancho_512"));
	
				//DIV ESTRUCTURA
				$html->tag("div", array("id"=>"res_div_estructura_bd"));
				
					$html->tag("fieldset");
					
						//BOTON AYUDA
						$html->botonAyuda("res_btn_help_1");
					
						//TITULO DIV
						$html->tag("legend");
							$html->tag("label");
								$html->printText("res_lgn_estructura_bd");
							$html->end("label");
						$html->end("legend");
						
						//TABLA ESTRUCTURA
						$html->tag("div", array("class"=>"tabla margin_arriba_10"));
						
							//FORMULARIO
							$html->tag("div", array("class"=>"fila"));
								$html->tag("div", array("class"=>"celda alineacion_izquierda"));
									$html->tag("div", array("id"=>"estructura", "class"=>"texto_arbol tree tree-classic"));
										//$objetoRestricciones->construirArbolBDO();
									$html->end("div");
								$html->end("div");
							$html->end("div");
							//FIN FORMULARIO
							
						$html->end("div");
						//FIN TABLA ESTRUCTURA
						
					$html->end("fieldset"); 

				$html->end("div");
				//FIN DIV ESTRUCTURA
			$html->end("div");
			
			
			$html->tag("div", array("class"=>"celda vertical_arriba ancho_512"));
				//DIV DETALLE
				$html->tag("div", array("id"=>"res_div_detalle_externo"));
					$html->tag("fieldset");
					
						//BOTON AYUDA
						$html->botonAyuda("res_btn_help_2");
					
						$html->tag("legend");
							$html->tag("label");
								$html->printText("res_lgn_detalle");
							$html->end("label");
						$html->end("legend");
						//TABLA
						$html->tag("div", array("class"=>"tabla margin_arriba_10", "id"=>"res_div_detalle"));
						$html->end("div");	
						//FIN TABLA
					$html->end("fieldset");
				$html->end("div");
				//FIN DIV DETALLE
			$html->end("div");
			
			
		$html->end("div");
	$html->end("div");
	//FIN DIV GENERAL
	
	//DIV BOTONES SECUENCIA
	$html->generarBotonesSecuencia("res", true, true, $ocultar);
	//FIN DIV BOTONES SECUENCIA
?>
