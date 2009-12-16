<?php
	session_start();
	$_SESSION['modulo'] = "login";
	
	if(!isset($_SESSION['lang']))
		$_SESSION['lang'] = "en";
	
	require_once("../herramientas/GeneradorHtml.inc");
	$html = new GeneradorHtml($_SESSION['lang']);
	
	$html->cargarModuloJS("login");
	
	//DIV SESION
	$html->tag("div", array("id"=>"div_sesion"));
		$html->tag("fieldset");
		
			//TITULO DIV
			$html->tag("legend");
				$html->tag("label", array("id"=>"lbl_login"));
					$html->printText("lbl_login");
				$html->end("label");
			$html->end("legend");
			
			//TABLA FORMULARIO
			$html->tag("div", array("class"=>"tabla"));
			
				//FORMULARIO
				$html->tag("div", array("class"=>"fila"));
				$html->tag("div", array("class"=>"tabla_centrada"));
					
					//CAMPO NOMBRE USUARIO
					$html->tag("div", array("class"=>"fila"));
						$html->tag("div", array("class"=>"celda alto_30 ancho_100"));
							$html->tag("label", array("id"=>"lbl_usu_login", "class"=>"etiqueta"));
								$html->printText("lbl_usu_login");
							$html->end("label");
						$html->end("div");
						$html->tag("div", array("class"=>"celda alto_30"));
							$html->tag("input", array("class"=>"ancho_100", "id"=>"usu_login", "type"=>"text", "maxlength"=>"20", "title"=>$html->getText('ttp_usu_login')));
						$html->end("div");
					$html->end("div");
					
					//CAMPO CONTRASEÑA
					$html->tag("div", array("class"=>"fila"));
						$html->tag("div", array("class"=>"celda alto_30 ancho_100"));
							$html->tag("label", array("id"=>"lbl_usu_password", "class"=>"etiqueta"));
								$html->printText("lbl_usu_password");
							$html->end("label");
						$html->end("div");
						$html->tag("div", array("class"=>"celda alto_30"));
							$html->tag("input", array("class"=>"ancho_100", "id"=>"usu_password", "type"=>"password", "maxlength"=>"20", "title"=>$html->getText('ttp_usu_password')));
						$html->end("div");
					$html->end("div");
					
				$html->end("div");	
				$html->end("div");
				//FIN FORMULARIO
	
				//IDIOMAS - BANDERAS
				$html->tag("div", array("class"=>"fila"));
				$html->tag("div", array("class"=>"tabla_centrada"));
	
					//SELECTORES DE IDIOMAS
					$html->tag("div", array("class"=>"fila"));
						$html->tag("div", array("class"=>"celda centrado ancho_50"));
							if($_SESSION['lang'] == "en") $checked = "checked"; else $checked = "";
							$html->tag("input", array("id"=>"chk_lang_en", "name"=>"chk_lang", "type"=>"radio", "value"=> "en", "title"=>$html->getText('ttp_chk_lang_en')), array($checked));
						$html->end("div");
						
						$html->tag("div", array("class"=>"celda centrado ancho_50"));
							if($_SESSION['lang'] == "es") $checked = "checked"; else $checked = "";
							$html->tag("input", array("id"=>"chk_lang_es", "name"=>"chk_lang", "type"=>"radio", "value"=> "es", "title"=>$html->getText('ttp_chk_lang_es')), array($checked));
						$html->end("div");
					$html->end("div");
					//FIN SELECTOR DE IDIOMAS	
					
					//BANDERAS DE IDIOMAS
					$html->tag("div", array("class"=>"fila"));
						$html->tag("div", array("class"=>"celda centrado ancho_50"));
							$html->tag("img", array("id"=>"img_lang_en", "src"=>"../imagenes/en.png", "alt"=>$html->getText('ttp_chk_lang_en'), "title"=>$html->getText('ttp_chk_lang_en')));
						$html->end("div");
						$html->tag("div", array("class"=>"celda centrado ancho_50"));
							$html->tag("img", array("id"=>"img_lang_es", "src"=>"../imagenes/es.png", "alt"=>$html->getText('ttp_chk_lang_es'), "title"=>$html->getText('ttp_chk_lang_es')));
						$html->end("div");
					$html->end("div");
					//FIN BANDERAS DE IDIOMAS
					
				$html->end("div");
				$html->end("div");
				//FIN IDIOMAS - BANDERAS
				
				//BOTON FORMULARIO
				$html->tag("div", array("class"=>"fila"));
				$html->tag("div", array("class"=>"tabla_centrada"));
					
					$html->tag("div", array("class"=>"fila"));
						$html->tag("div", array("class"=>"celda alto_30"));
							$html->tag("input", array("id"=>"btn_login", "type"=>"button", "value"=>$html->getText("btn_login"), "title"=>$html->getText("btn_login")));
						$html->end("div");
					$html->end("div");
					
				$html->end("div");
				$html->end("div");
				//FIN BOTON FORMULARIO
				
			$html->end("div");
			//FIN TABLA FORMULARIO
		
		$html->end("fieldset"); 
	$html->end("div");
	//FIN DIV SESION
?>
			