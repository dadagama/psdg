<?php
	session_start();
		
	$_SESSION['modulo'] = "ejecucion";
	//if(isset($_SESSION['step']) && $_SESSION['step'] != 4)//para el efecto de aparecer
		$ocultar = "oculto";
		
	$_SESSION['step'] = 4;

	require_once("../herramientas/GeneradorHtml.inc");
	$html = new GeneradorHtml($_SESSION['lang']);
	$html->cargarModuloJS($_SESSION['modulo']);

	//DIV GENERAL
	$html->tag("div", array("id"=>"eje_div_general", "class"=>"$ocultar"));
	$html->tag("div", array("class"=>"tabla"));	
		$html->tag("div", array("class"=>"fila"));
			$html->tag("div", array("class"=>"celda vertical_arriba"));
	
				//DIV CONSOLA
				$html->tag("div", array("id"=>"eje_div_consola", "class"=>""));
				$html->tag("fieldset");
					
						//BOTON AYUDA
						$html->botonAyuda("eje_btn_help_1");
					
						//TITULO DIV
						$html->tag("legend");
							$html->tag("label");
								$html->printText("eje_lgn_consola");
							$html->end("label");
						$html->end("legend");
						
						//TABLA CONSOLA
						$html->tag("div", array("class"=>"tabla"));
							$html->tag("div", array("class"=>"fila"));
								$html->tag("div", array("class"=>"celda centrado"));
									$html->tag("input", array("id"=>"eje_btn_iniciar" ,"type"=>"button", "value"=>$html->getText("eje_btn_iniciar"), "onclick"=>"iniciar()", "class"=>"color_letra_campo margin_arriba_10"));
								$html->end("div");
							$html->end("div");
							
							$html->tag("div", array("class"=>"fila"));
								$html->tag("div", array("class"=>"celda centrado"));
									$html->tag("div", array("id"=>"div_log", "class"=>"valor_campo color_letra_campo ancho_100p alto_120 margin_arriba_10"/*, "wrap"=>"soft", "readonly"=>"readonly"*/));
									$html->end("div");
								$html->end("div");
							$html->end("div");
						$html->end("div");
						//FIN TABLA CONSOLA
						
				$html->end("fieldset"); 
				$html->end("div");
				//FIN DIV CONSOLA
				
			$html->end("div");
		$html->end("div");
		
	$html->end("div");
	$html->end("div");
	//FIN DIV GENERAL
	
	//DIV BOTONES SECUENCIA
	$html->generarBotonesSecuencia("eje", true, false, $ocultar);
	//FIN DIV BOTONES SECUENCIA
?>
