<?php
	session_start();
		
	$_SESSION['modulo'] = "restricciones";
	//if(isset($_SESSION['step']) && $_SESSION['step'] != 2)//para el efecto de aparecer
		$ocultar = "oculto";
	
	$_SESSION['step'] = 2;

	require_once("../herramientas/GeneradorHtml.inc");
	$html = new GeneradorHtml($_SESSION['lang']);

	$html->cargarHerramientaJS("jquery.tree.min");
	$html->cargarModuloJS($_SESSION['modulo']);

	require_once("../modulo_restricciones/Restricciones.inc");
	$objetoRestricciones = new Restricciones($_SESSION['conexionBDI'],$_SESSION['usu_login'],$_SESSION['lang']);
	
	//DIV GENERAL
	$html->tag("div", array("id"=>"res_div_general", "class"=>"tabla $ocultar"));
		$html->tag("div", array("class"=>"fila"));
			$html->tag("div", array("class"=>"celda vertical_arriba ancho_400"));
	
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
						$html->tag("div", array("class"=>"tabla"));
						
							//FORMULARIO
							$html->tag("div", array("class"=>"fila"));
								$html->tag("div", array("class"=>"celda alineacion_izquierda"));
									$html->tag("div", array("id"=>"estructura", "class"=>"texto_arbol tree tree-classic"));
										$objetoRestricciones->construirArbolBDO();
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
			
			
			$html->tag("div", array("class"=>"celda vertical_arriba ancho_624"));
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
						$html->tag("div", array("class"=>"tabla", "id"=>"res_div_detalle"));
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
	$html->tag("div", array("id"=>"res_div_botones_secuencia", "class"=>"tabla $ocultar div_botones_secuencia"));
		$html->tag("div", array("class"=>"fila"));
		
			$html->tag("div", array("class"=>"celda vertical_arriba ancho_1024"));
					$html->tag("input", array("id"=>"res_btn_anterior", "type"=>"image", "src"=>"../imagenes/step_1_ok.png", "onclick"=>"mostrarEtapa('anterior');", "alt"=>$html->getText('res_ttp_anterior'), "title"=>$html->getText('res_ttp_anterior')));
					$html->tag("input", array("id"=>"res_btn_siguiente", "type"=>"image", "src"=>"../imagenes/step_1_off.png", "onclick"=>"mostrarEtapa('siguiente');", "alt"=>$html->getText('res_ttp_siguiente'), "title"=>$html->getText('res_ttp_siguiente')));
			$html->end("div");
			
		$html->end("div");
	$html->end("div");
	//FIN DIV BOTONES SECUENCIA
?>
