<?php
	session_start();
		
	$_SESSION['modulo'] = "restricciones";
	if(isset($_SESSION['step']) && $_SESSION['step'] != 2)//para el efecto de aparecer
		$ocultar = "oculto";
		
	$_SESSION['step'] = 2;

	require_once("../herramientas/GeneradorHtml.inc");
	$html = new GeneradorHtml($_SESSION['lang']);
	$html->cargarModuloJS($_SESSION['modulo']);

	//DIV GENERAL
	$html->tag("div", array("id"=>"res_div_general", "class"=>"tabla $ocultar"));
		$html->tag("div", array("class"=>"fila"));
			$html->tag("div", array("class"=>"celda vertical_arriba"));
	
				//DIV CONEXION
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
						
						//TABLA FORMULARIO
						$html->tag("div", array("class"=>"tabla"));
						
							//FORMULARIO
							$html->tag("div", array("class"=>"fila"));
								$html->tag("div", array("class"=>"tabla_centrada"));
								
								$html->end("div");
							$html->end("div");
							//FIN FORMULARIO
							
						$html->end("div");
						//FIN TABLA FORMULARIO
						
					$html->end("fieldset"); 

				$html->end("div");
				//FIN DIV CONEXION
				
			$html->end("div");
		$html->end("div");
	$html->end("div");
	//FIN DIV GENERAL
	
	//DIV BOTONES SECUENCIA
	$html->tag("div", array("id"=>"res_div_botones_secuencia", "class"=>"tabla $ocultar div_botones_secuencia"));
		$html->tag("div", array("class"=>"fila"));
		
			$html->tag("div", array("class"=>"celda vertical_arriba"));
					$html->tag("input", array("id"=>"res_btn_anterior", "type"=>"image", "src"=>"../imagenes/step_1_ok.png", "onclick"=>"mostrarEtapa('anterior');", "alt"=>$html->getText('res_ttp_anterior'), "title"=>$html->getText('res_ttp_anterior')));
					$html->tag("input", array("id"=>"res_btn_siguiente", "type"=>"image", "src"=>"../imagenes/step_1_off.png", "onclick"=>"mostrarEtapa('siguiente');", "alt"=>$html->getText('res_ttp_siguiente'), "title"=>$html->getText('res_ttp_siguiente')));
			$html->end("div");
			
		$html->end("div");
	$html->end("div");
	//FIN DIV BOTONES SECUENCIA
?>