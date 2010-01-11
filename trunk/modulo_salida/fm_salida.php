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
	$html->tag("div", array("id"=>"sal_div_general", "class"=>"tabla $ocultar"));
		$html->tag("div", array("class"=>"fila"));
			$html->tag("div", array("class"=>"celda vertical_arriba ancho_512"));
	
				//DIV CONEXION
				$html->tag("div", array("id"=>"sal_div_tipos"));
				
					$html->tag("fieldset");
					
						//BOTON AYUDA
						$html->botonAyuda("sal_btn_help_1");
					
						//TITULO DIV
						$html->tag("legend");
							$html->tag("label");
								$html->printText("sal_lgn_estructura_bd");
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
	$html->tag("div", array("id"=>"sal_div_botones_secuencia", "class"=>"tabla $ocultar div_botones_secuencia"));
		$html->tag("div", array("class"=>"fila"));
		
			$html->tag("div", array("class"=>"celda vertical_arriba ancho_1024"));
					$html->tag("input", array("id"=>"res_btn_anterior", "type"=>"image", "src"=>"../imagenes/btn_back_1.png", "onmouseover"=>"this.src='../imagenes/btn_back_2.png'", "onmouseout"=>"this.src='../imagenes/btn_back_1.png'", "onclick"=>"mostrarEtapa('anterior');", "alt"=>$html->getText('res_ttp_anterior'), "title"=>$html->getText('res_ttp_anterior')));
					$html->tag("input", array("id"=>"res_btn_siguiente", "type"=>"image", "src"=>"../imagenes/btn_next_1.png", "onmouseover"=>"this.src='../imagenes/btn_next_2.png'", "onmouseout"=>"this.src='../imagenes/btn_next_1.png'", "onclick"=>"mostrarEtapa('siguiente');", "alt"=>$html->getText('res_ttp_siguiente'), "title"=>$html->getText('res_ttp_siguiente')));
			$html->end("div");
			
		$html->end("div");
	$html->end("div");
	//FIN DIV BOTONES SECUENCIA
?>
