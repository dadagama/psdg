<?php 

require_once("../conexiones/ConexionBDMySQL.inc");
require_once("../herramientas/GeneradorHtml.inc");
	
class Restricciones
{
	var $conexionBDI;
	var $conexionBDO;		
	var $usu_login;
	var $html;
	var $arreglo_restricciones;
	
	function __construct($parametrosConexion, $login, $lang)
	{
		$this->conexionBDI = new ConexionBDMySQL($parametrosConexion);
  		$this->conexionBDI->conectar();
  		$this->usu_login = $login;
  		$this->inicializarConexionBDO();
  		$this->html = new GeneradorHtml($lang);
	}
	
	function inicializarConexionBDO()
	{
		$sql = "	SELECT con_parametros
					FROM PSDG_conexion
					WHERE con_fue_codigo = '2'
					AND con_usu_login = '".$this->usu_login."'
					AND con_nombre = 'BDO'
					LIMIT 1";

		$this->conexionBDI->ejecutarSQL($sql);
		$con_parametros = $this->conexionBDI->obtenerResultadoComoCadena();
		$arreglo_parametros = json_decode($con_parametros, true);
		$this->conexionBDO = new ConexionBDMySQL($arreglo_parametros);
		$this->conexionBDO->conectar();
	}
	
	function construirArbolBDO()
	{
		$sql = "SHOW TABLES";
		$this->conexionBDO->ejecutarSQL($sql);
		$nombres_tablas = $this->conexionBDO->obtenerResultadoComoArreglo();
		
		$this->html->tag("ul");
		
		foreach($nombres_tablas AS $indice => $nombre_tabla)
		{
//			$sql = "SELECT * FROM ".$nombre_tabla[0]." LIMIT 1";
			
			$this->html->tag("li", array("rel"=>"tabla"));
				$this->html->tag("a", array("onclick"=>"mostrarDetalleTabla('".$nombre_tabla[0]."');"));
					$this->html->tag("ins");
						$this->html->printStaticText("&nbsp;");
					$this->html->end("ins");
					$this->html->tag("label", array("class"=>"color_letra_campo"));
						$this->html->printStaticText($nombre_tabla[0]);
					$this->html->end("label");
				$this->html->end("a");
				
				if($this->tieneRestriccionTablaEstablecida($nombre_tabla[0]))
				{
					$sql = "DESCRIBE ".$nombre_tabla[0];
					$this->conexionBDO->ejecutarSQL($sql); 
					while ($arreglo_meta_datos_campo = $this->conexionBDO->obtenerFilaComoArregloAsociativo())
//					foreach($arreglo_meta_datos_columnas AS $numero_columna => $objeto_meta)
					{
						switch($arreglo_meta_datos_campo['Key'])
						{
							case "PRI":	$rel = "llave_primaria"; break;
							case "UNI":	$rel = "unico"; break;
							case "MUL":	$rel = "llave_foranea"; break;
							default: $rel = "campo"; break;
						}

						if(!$arreglo_meta_datos_campo['Default'])
							$arreglo_meta_datos_campo['Default'] = "null";
							
						$this->html->tag("ul");
							$this->html->tag("li", array("rel"=>$rel));
								$this->html->tag("a", array("onclick"=>"mostrarDetalleCampo('".$nombre_tabla[0]."'
																												,'".$arreglo_meta_datos_campo['Field']."'
																												,'".$arreglo_meta_datos_campo['Type']."'
																												,'".$arreglo_meta_datos_campo['Null']."'
																												,'".$arreglo_meta_datos_campo['Key']."'
																												,'".$arreglo_meta_datos_campo['Default']."'
																												,'".$arreglo_meta_datos_campo['Extra']."');")); 
									$this->html->tag("ins");
										$this->html->printStaticText("&nbsp;");
									$this->html->end("ins");
									$this->html->tag("label", array("class"=>"color_letra_campo"));
										$this->html->printStaticText($arreglo_meta_datos_campo['Field']);
									$this->html->end("label");
								$this->html->end("a");
							$this->html->end("li");
						$this->html->end("ul");
					}
				}
			$this->html->end("li");
		}
		$this->html->end("ul");
	}
	
	function tieneRestriccionTablaEstablecida($nombre_tabla)
	{
		return $this->conexionBDI->existeRegistro("ret_nombre_tabla", "PSDG_restricciones_tablas", "ret_nombre_tabla = '".$nombre_tabla."' AND ret_usu_login = '".$this->usu_login."'");
	}
	
	function cargarRestriccionesTabla($nombre_tabla)
	{
		$this->arreglo_restricciones = array();
		$sql = "	SELECT ret_numero_tuplas_a_generar
					FROM PSDG_restricciones_tablas
					WHERE ret_nombre_tabla = '".$nombre_tabla."'
					AND ret_usu_login = '".$this->usu_login."'";
		//echo $sql;
		$this->conexionBDI->ejecutarSQL($sql);
		if($this->conexionBDI->obtenerNumeroFilas())
			$this->arreglo_restricciones = $this->conexionBDI->obtenerFilaComoArregloAsociativo();
		$this->arreglo_restricciones['ret_nombre_tabla'] = $nombre_tabla;
	}
	
	function crearFormularioRestriccionesTabla()
	{
		$numero_tuplas = 0;
		if($this->arreglo_restricciones['ret_numero_tuplas_a_generar'])
			$numero_tuplas = $this->arreglo_restricciones['ret_numero_tuplas_a_generar'];		
			
		//FORMULARIO
		//NOMBRE DE TABLA
		$this->html->tag("div", array("class"=>"fila"));
		$this->html->tag("div", array("class"=>"celda ancho_512"));
		$this->html->tag("div", array("class"=>"tabla"));	
					$this->html->tag("div", array("class"=>"fila"));
						$this->html->tag("div", array("class"=>"celda alineacion_derecha vertical_centro ancho_50p"));
							$this->html->tag("label", array("class"=>"etiqueta"));
								$this->html->printText("ret_lbl_nombre_tabla");//CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR
							$this->html->end("label");
						$this->html->end("div");
						
						$this->html->tag("div", array("class"=>"celda alineacion_izquierda vertical_centro alto_30 valor_campo color_letra_campo"));
							$this->html->tag("label", array("id"=>"rec_lbl_nombre_tabla") );
								$this->html->printStaticText($this->arreglo_restricciones['ret_nombre_tabla']);
							$this->html->end("label");
						$this->html->end("div");
					$this->html->end("div");
				
					//NUMERO DE TUPLAS
					$this->html->tag("div", array("class"=>"fila"));
						$this->html->tag("div", array("class"=>"celda alineacion_derecha vertical_centro ancho_50p"));
							$this->html->tag("label", array("class"=>"etiqueta"));
								$this->html->printText("ret_lbl_cantidad_tuplas");//CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR
							$this->html->end("label");
						$this->html->end("div");
						
						$this->html->tag("div", array("class"=>"celda alineacion_izquierda vertical_centro alto_30 valor_campo color_letra_campo"));
							$this->html->tag("input", array("id"=>"rec_txt_numero_tuplas" ,"type"=>"text", "value"=>$numero_tuplas, "class"=>"valor_campo color_letra_campo ancho_50", "maxlength"=>"5"));
						$this->html->end("div");
					$this->html->end("div");
		$this->html->end("div");
		$this->html->end("div");
		$this->html->end("div");
		
		//BOTON
		$this->html->tag("div", array("class"=>"fila"));
			$this->html->tag("div", array("class"=>"celda vertical_centro centrado ancho_512"));
				$this->html->tag("input", array("id"=>"rec_btn_establecer" ,"type"=>"button", "value"=>"Establecer", "onclick"=>"establecerRestriccionTabla();", "class"=>"color_letra_campo margin_arriba_10"));//CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR
			$this->html->end("div");
		$this->html->end("div");
		//FIN FORMULARIO
	}
	
	function precondicionesEstablecidas($nombre_tabla)
	{
		$parametros_conexion_BDO = $this->conexionBDO->obtenerParametrosConexion();
		$nombre_BDO = $parametros_conexion_BDO['con_nombre_bd'];
		//consulto si la tabla tiene campos foraneos
		$sql = "	SELECT REFERENCED_TABLE_NAME
					FROM REFERENTIAL_CONSTRAINTS 
					WHERE TABLE_NAME = '".$nombre_tabla."'
					AND CONSTRAINT_SCHEMA = '".$nombre_BDO."'";
		//miro si las tablas a las q pertenecen las foraneas ya tienen restricciones
		//establecidas
		$this->conexionBDO->establecer_bd("information_schema");
		$this->conexionBDO->ejecutarSQL($sql);
		$tablas_sin_restringir = array();
		$cumple_restricciones = true;
		while ($tabla_referenciada = $this->conexionBDO->obtenerFilaComoArreglo())
		{
			$esta_establecida = $this->tieneRestriccionTablaEstablecida($tabla_referenciada[0]);
			if(!$esta_establecida)
			{
				$tablas_sin_restringir[] = $tabla_referenciada[0];
			}
		}
		$this->conexionBDO->restablecer_bd_original();
		return implode(",", $tablas_sin_restringir);
	}
	
	function eliminarRestriccionesTablasRelacionadas($nombre_tabla)
	{
		$parametros_conexion_BDO = $this->conexionBDO->obtenerParametrosConexion();
		$nombre_BDO = $parametros_conexion_BDO['con_nombre_bd'];
		//consulto las tablas que dependan de esta por llaves foraneas
		$sql = "	SELECT TABLE_NAME
					FROM REFERENTIAL_CONSTRAINTS 
					WHERE REFERENCED_TABLE_NAME = '".$nombre_tabla."'
					AND CONSTRAINT_SCHEMA = '".$nombre_BDO."'";
		//miro si las tablas a las q pertenecen las foraneas ya tienen restricciones
		//establecidas
		$this->conexionBDO->establecer_bd("information_schema");
		$this->conexionBDO->ejecutarSQL($sql);
		while ($tabla_relacionada = $this->conexionBDO->obtenerFilaComoArreglo())
		{
			$esta_establecida = $this->tieneRestriccionTablaEstablecida($tabla_relacionada[0]);
			if($esta_establecida)
			{
				$sql = "	DELETE FROM PSDG_restricciones_tablas 
							WHERE ret_nombre_tabla = '".$tabla_relacionada[0]."'
							AND ret_usu_login = '".$this->usu_login."'";
				$this->conexionBDI->ejecutarSQL($sql); 
			}
		}
		$this->conexionBDO->restablecer_bd_original();
	}
	
	function actualizarRestriccionTabla($nombre_tabla, $numero_tuplas)
	{
		if($numero_tuplas == 0)
		{
			$this->eliminarRestriccionesTablasRelacionadas($nombre_tabla);
			$sql = "	DELETE FROM PSDG_restricciones_tablas 
						WHERE ret_nombre_tabla = '".$nombre_tabla."'
						AND ret_usu_login = '".$this->usu_login."'";
		}
		else if($this->tieneRestriccionTablaEstablecida($nombre_tabla))
			$sql = "	UPDATE PSDG_restricciones_tablas 
						SET ret_numero_tuplas_a_generar = $numero_tuplas 
						WHERE ret_nombre_tabla = '".$nombre_tabla."' 
						AND ret_usu_login = '".$this->usu_login."'";
		else
			$sql = "INSERT INTO PSDG_restricciones_tablas(ret_usu_login,ret_nombre_tabla,ret_numero_tuplas_a_generar) VALUES('".$this->usu_login."', '$nombre_tabla', $numero_tuplas)";
		//echo $sql;
		$this->conexionBDI->ejecutarSQL($sql); 
	}
	
	function cargarRestriccionesCampo($nombre_tabla, $nombre_campo, $tipo_dato, $permite_nulos, $tipo_llave, $valor_default, $extra)
	{
		$this->arreglo_restricciones = array();
		$sql = "	SELECT rec_fue_codigo, rec_parametros_tipo_fuente, rec_porcentaje_nulos, rec_es_foranea
					FROM PSDG_restricciones_campos
					WHERE rec_nombre_tabla = '".$nombre_tabla."'
					AND rec_nombre_campo = '".$nombre_campo."'
					AND rec_usu_login = '".$this->usu_login."'";
		//echo $sql;
		$this->conexionBDI->ejecutarSQL($sql);
		if($this->conexionBDI->obtenerNumeroFilas())
			$this->arreglo_restricciones = $this->conexionBDI->obtenerFilaComoArregloAsociativo();
		$this->arreglo_restricciones['rec_nombre_tabla'] = $nombre_tabla;
		$this->arreglo_restricciones['rec_nombre_campo'] = $nombre_campo;
		$this->arreglo_restricciones['rec_tipo_dato'] = $tipo_dato;
		$this->arreglo_restricciones['permite_nulos'] = $permite_nulos;
		$this->arreglo_restricciones['tipo_llave'] = $tipo_llave;
		$this->arreglo_restricciones['valor_default'] = $valor_default;
		$this->arreglo_restricciones['extra'] = $extra;
	}
	
	function crearFormularioRestriccionesCampo()
	{	
		//FORMULARIO
		$this->html->tag("div", array("class"=>"fila"));
		$this->html->tag("div", array("class"=>"celda ancho_512"));
		$this->html->tag("fieldset");
		
			$this->html->tag("legend");
				$this->html->tag("label");
					$this->html->printText("res_lgn_info_detalle");
				$this->html->end("label");
			$this->html->end("legend");
			
			$this->html->tag("div", array("class"=>"tabla"));
			
				//NOMBRE DE TABLA
				$this->html->tag("div", array("class"=>"fila"));
					$this->html->tag("div", array("class"=>"celda alineacion_derecha vertical_centro ancho_50p"));
						$this->html->tag("label", array("class"=>"etiqueta"));
							$this->html->printText("rec_lbl_nombre_tabla");
						$this->html->end("label");
					$this->html->end("div");
					
					$this->html->tag("div", array("class"=>"celda alineacion_izquierda vertical_centro valor_campo color_letra_campo"));
						$this->html->tag("label", array("id"=>"rec_lbl_nombre_tabla"));
							$this->html->printStaticText($this->arreglo_restricciones['rec_nombre_tabla']);
						$this->html->end("label");
					$this->html->end("div");
				$this->html->end("div");
		
				//NOMBRE DE CAMPO
				$this->html->tag("div", array("class"=>"fila"));
					$this->html->tag("div", array("class"=>"celda alineacion_derecha vertical_centro "));
						$this->html->tag("label", array("class"=>"etiqueta"));
							$this->html->printText("rec_lbl_nombre_campo");
						$this->html->end("label");
					$this->html->end("div");
					
					$this->html->tag("div", array("class"=>"celda alineacion_izquierda vertical_centro ancho_200 valor_campo color_letra_campo"));
						$this->html->tag("label", array("id"=>"rec_lbl_nombre_campo"));
							$this->html->printStaticText($this->arreglo_restricciones['rec_nombre_campo']);
						$this->html->end("label");
					$this->html->end("div");
				$this->html->end("div");
				
				//TIPO DE DATO
				$this->html->tag("div", array("class"=>"fila"));
					$this->html->tag("div", array("class"=>"celda alineacion_derecha vertical_centro "));
						$this->html->tag("label", array("class"=>"etiqueta"));
							$this->html->printText("rec_lbl_tipo_dato");
						$this->html->end("label");
					$this->html->end("div");
					
					$this->html->tag("div", array("class"=>"celda alineacion_izquierda vertical_centro  valor_campo color_letra_campo"));
						$this->html->tag("label", array("id"=>"rec_lbl_tipo_dato"));
							$this->html->printStaticText($this->arreglo_restricciones['rec_tipo_dato']);
						$this->html->end("label");
					$this->html->end("div");
				$this->html->end("div");
				
				//PERMITE NULOS
				$this->html->tag("div", array("class"=>"fila"));
					$this->html->tag("div", array("class"=>"celda alineacion_derecha vertical_centro "));
						$this->html->tag("label", array("class"=>"etiqueta"));
							$this->html->printText("rec_lbl_permite_nulos");
						$this->html->end("label");
					$this->html->end("div");
					
					$this->html->tag("div", array("class"=>"celda alineacion_izquierda vertical_centro  valor_campo color_letra_campo"));
						$this->html->tag("label", array("id"=>"rec_lbl_permite_nulos"));
							$this->html->printText("res_nulo_".$this->arreglo_restricciones['permite_nulos']);
						$this->html->end("label");
					$this->html->end("div");
				$this->html->end("div");
				
				if($this->arreglo_restricciones['tipo_llave'])
				{
					$arreglo_tipos_llave = $this->obtenerTiposLlave($this->arreglo_restricciones['rec_nombre_tabla'], $this->arreglo_restricciones['rec_nombre_campo']);
					$arreglo_traducido = $this->html->traducirArreglo($arreglo_tipos_llave);
					$tipos_llave = implode(",", $arreglo_traducido);
					
					//TIPO DE LLAVE
					$this->html->tag("div", array("class"=>"fila"));
						$this->html->tag("div", array("class"=>"celda alineacion_derecha vertical_centro "));
							$this->html->tag("label", array("class"=>"etiqueta"));
								$this->html->printText("rec_lbl_tipo_llave");
							$this->html->end("label");
						$this->html->end("div");
						
						$this->html->tag("div", array("class"=>"celda alineacion_izquierda vertical_centro  valor_campo color_letra_campo"));
							$this->html->tag("label", array("id"=>"rec_lbl_tipo_llave"));
								$this->html->printText($tipos_llave);
							$this->html->end("label");
						$this->html->end("div");
					$this->html->end("div");
				}
				
				//VALOR DEFAULT
				$this->html->tag("div", array("class"=>"fila"));
					$this->html->tag("div", array("class"=>"celda alineacion_derecha vertical_centro "));
						$this->html->tag("label", array("class"=>"etiqueta"));
							$this->html->printText("rec_lbl_valor_default");
						$this->html->end("label");
					$this->html->end("div");
					
					$this->html->tag("div", array("class"=>"celda alineacion_izquierda vertical_centro  valor_campo color_letra_campo"));
						$this->html->tag("label", array("id"=>"rec_lbl_valor_default"));
							$this->html->printText($this->arreglo_restricciones['valor_default']);
						$this->html->end("label");
					$this->html->end("div");
				$this->html->end("div");
				
				if($this->arreglo_restricciones['extra'])
				{
					//EXTRAS
					$this->html->tag("div", array("class"=>"fila"));
						$this->html->tag("div", array("class"=>"celda alineacion_derecha vertical_centro "));
							$this->html->tag("label", array("class"=>"etiqueta"));
								$this->html->printText("rec_lbl_extras");
							$this->html->end("label");
						$this->html->end("div");
						
						$this->html->tag("div", array("class"=>"celda alineacion_izquierda vertical_centro  valor_campo color_letra_campo"));
							$this->html->tag("label", array("id"=>"rec_lbl_extras"));
								$this->html->printText($this->arreglo_restricciones['extra']);
							$this->html->end("label");
						$this->html->end("div");
					$this->html->end("div");
				}
				
			$this->html->end("div");
			
		$this->html->end("fieldset");
		$this->html->end("div");
		$this->html->end("div");
		
		//FIELDSET CONFIGURACION RESTRICCIONES
		
		////////////////////////////////////// CONSULTA DE INFORMACION PREVIA SI EXISTE
		
		$tipo_de_dato = $this->obtenerTipoDeDato($this->arreglo_restricciones['rec_tipo_dato']);
		
		if($es_foranea = $this->arreglo_restricciones['rec_es_foranea'])
		{
			$readonly = "readonly";
			$blur = "this.blur();";
		}
		debug($this->arreglo_restricciones,'$this->arreglo_restricciones');
		$porcentaje_nulos = 0;
		if($this->arreglo_restricciones['rec_porcentaje_nulos'])
			$porcentaje_nulos = $this->arreglo_restricciones['rec_porcentaje_nulos'];	

		if($this->arreglo_restricciones['rec_parametros_tipo_fuente'])
		{
			$parametros_json = $this->arreglo_restricciones['rec_parametros_tipo_fuente'];
			$parametros_conexion = json_decode($parametros_json, true);
		}
			
		////////////////////////////////////// FIN CONSULTA DE INFORMACION PREVIA SI EXISTE		
			
		$this->html->tag("div", array("class"=>"fila"));
		$this->html->tag("div", array("class"=>"celda"));
		$this->html->tag("fieldset", array("class"=>"margin_arriba_10"));
		
			$this->html->tag("legend");
				$this->html->tag("label");
					$this->html->printText("res_lgn_titulo_restricciones");
				$this->html->end("label");
			$this->html->end("legend");
			
			$this->html->tag("div", array("class"=>"tabla"));
			
				if($this->arreglo_restricciones['permite_nulos'] == "NO")
					$permite_nulos = "readonly";
					
				//NULOS
				$this->html->tag("div", array("class"=>"fila"));
					$this->html->tag("div", array("class"=>"celda alineacion_derecha vertical_centro alto_30"));
						$this->html->tag("label", array("class"=>"etiqueta"));
							$this->html->printText("rec_lbl_porcentaje_nulos");
						$this->html->end("label");
					$this->html->end("div");
					
					$this->html->tag("div", array("class"=>"celda alineacion_izquierda vertical_centro alto_30 valor_campo color_letra_campo"));
							$this->html->tag("input", array("id"=>"rec_porcentaje_nulos", "type"=>"text", "maxlength"=>"3", "value"=>$porcentaje_nulos, "class"=>"valor_campo color_letra_campo ancho_35", $permite_nulos=>$permite_nulos));
					$this->html->end("div");
				$this->html->end("div");
			
				//DIV FUENTE DE DATOS
				$this->html->tag("div", array("class"=>"fila"));
					$this->html->tag("div", array("class"=>"celda alineacion_derecha vertical_centro ancho_50p"));
						$this->html->tag("label", array("class"=>"etiqueta"));
							$this->html->printText("rec_lbl_fuente_datos");
						$this->html->end("label");
					$this->html->end("div");
					
					$this->html->tag("div", array("class"=>"celda alineacion_izquierda vertical_centro alto_30 valor_campo color_letra_campo")); 
						$this->html->printSelect($this->conexionBDI, "fue_codigo", "fue_nombre", "PSDG_fuentes, PSDG_fuentes_de_tipos", "fdt_fue_codigo = fue_codigo AND fdt_tipo_de_dato = '".$tipo_de_dato."'" , $this->arreglo_restricciones['rec_fue_codigo'], array("id"=>"rec_fue_codigo", "onchange"=>"actualizarFormularioFuenteDeDatos();", "class"=>"valor_campo color_letra_campo ancho_150", $readonly=>$readonly, "onFocus"=>$blur), "");
					$this->html->end("div");
				$this->html->end("div");
				//FIN DIV FUENTE DE DATOS

			$this->html->end("div");
			
				
				//FIELDSET SETUP FUENTE DATOS 
				$this->html->tag("form", array("name"=>"fm_parametros_tipo_fuente", "id"=>"fm_parametros_tipo_fuente"));
				$this->html->tag("fieldset", array("class"=>"margin_arriba_10"));
				
					$this->html->tag("legend");
						$this->html->tag("label");
							$this->html->printText("res_lgn_titulo_setup_fuente");
						$this->html->end("label");
					$this->html->end("legend");
					
					$this->html->tag("div", array("class"=>"tabla", "id"=>"rec_tabla_restricciones"));	

//					switch($this->arreglo_restricciones['rec_fue_codigo'])
//					{
//						case 1://Ninguna
//							break;
//
//						case 2://Base de datos
							$this->html->tag("div", array("class"=>"fila", "id"=>"rec_tabla_bd"));
							$this->html->tag("div", array("class"=>"celda"));
							$this->html->tag("div", array("class"=>"tabla"));	
							
									$this->html->tag("div", array("class"=>"fila"));
										$this->html->tag("div", array("class"=>"celda alineacion_derecha vertical_centro ancho_50p alto_30"));
											$this->html->tag("label", array("class"=>"etiqueta"));
												$this->html->printText("rec_lbl_conexion_bd");
											$this->html->end("label");
										$this->html->end("div");
										
										$this->html->tag("div", array("class"=>"celda alineacion_izquierda vertical_centro alto_30 valor_campo color_letra_campo"));
											$this->html->printSelect($this->conexionBDI, "con_nombre", "con_nombre", "PSDG_conexion", "con_usu_login = '".$this->usu_login."' AND con_fue_codigo = '2'", $parametros_conexion['rec_nombre_conexion'], array("name"=>"rec_nombre_conexion", "id"=>"rec_nombre_conexion", "class"=>"valor_campo color_letra_campo ancho_150", "onchange"=>"actualizarCampoTablasBD();", $readonly=>$readonly, "onFocus"=>$blur), "", "select_seleccione", false);
										$this->html->end("div");
									$this->html->end("div");
								
									$this->html->tag("div", array("class"=>"fila"));
										$this->html->tag("div", array("class"=>"celda alineacion_derecha vertical_centro alto_30"));
											$this->html->tag("label", array("class"=>"etiqueta"));
												$this->html->printText("rec_lbl_nombre_tabla");
											$this->html->end("label");
										$this->html->end("div");
										
										$this->html->tag("div", array("class"=>"celda alineacion_izquierda vertical_centro alto_30 valor_campo color_letra_campo"));
										/*si hay una conexion seleccionada apenas se carga el formulario
										 * es porque tambien hay una tabla seleccionada, debo buscar las tablas donde
										 * apunta la conexion
										 */	
											$this->html->tag("select", array("name"=>"rec_nombre_tabla", "id"=>"rec_nombre_tabla", "class"=>"valor_campo color_letra_campo ancho_150", "onchange"=>"actualizarCampoCamposBD();", $readonly=>$readonly, "onFocus"=>$blur));
												//if($parametros_conexion['rec_nombre_conexion'])
													$this->actualizarCampoTablasBD($parametros_conexion['rec_nombre_conexion'], $parametros_conexion['rec_nombre_tabla']);
											$this->html->end("select");
										$this->html->end("div");
									$this->html->end("div");
									
									$this->html->tag("div", array("class"=>"fila"));
										$this->html->tag("div", array("class"=>"celda alineacion_derecha vertical_centro alto_30"));
											$this->html->tag("label", array("class"=>"etiqueta"));
												$this->html->printText("rec_lbl_nombre_campo");
											$this->html->end("label");
										$this->html->end("div");
										
										$this->html->tag("div", array("class"=>"celda alineacion_izquierda vertical_centro alto_30 valor_campo color_letra_campo"));
											$this->html->tag("select", array("name"=>"rec_nombre_campo", "id"=>"rec_nombre_campo", "class"=>"valor_campo color_letra_campo ancho_150", $readonly=>$readonly, "onFocus"=>$blur));
												//if($parametros_conexion['rec_nombre_tabla'])
													$this->actualizarCampoCamposBD($parametros_conexion['rec_nombre_conexion'], $parametros_conexion['rec_nombre_tabla'], $parametros_conexion['rec_nombre_campo'], $parametros_conexion['rec_nombre_campo']);
											$this->html->end("select");
										$this->html->end("div");
									$this->html->end("div");
							$this->html->end("div");
							$this->html->end("div");
							$this->html->end("div");
//							break;
//
//						case 3://Biblioteca
							$this->html->tag("div", array("class"=>"fila", "id"=>"rec_tabla_biblioteca"));
							$this->html->tag("div", array("class"=>"celda"));
							$this->html->tag("div", array("class"=>"tabla"));	
										$this->html->tag("div", array("class"=>"fila"));
											$this->html->tag("div", array("class"=>"celda alineacion_derecha vertical_centro ancho_50p alto_30"));
												$this->html->tag("label", array("class"=>"etiqueta"));
													$this->html->printText("rec_lbl_conexion_biblioteca");
												$this->html->end("label");
											$this->html->end("div");
											
											$this->html->tag("div", array("class"=>"celda alineacion_izquierda vertical_centro alto_30 valor_campo color_letra_campo"));
												$this->html->printSelect($this->conexionBDI, "con_nombre", "con_nombre", "PSDG_conexion", "con_usu_login = '".$this->usu_login."' AND con_fue_codigo = '3'", $parametros_conexion['rec_conexion_biblioteca'], array("name"=>"rec_conexion_biblioteca", "id"=>"rec_conexion_biblioteca", "class"=>"valor_campo color_letra_campo ancho_150", "onchange"=>"actualizarCampoCamposBiblioteca();"), "", "select_seleccione", false);
											$this->html->end("div");
										$this->html->end("div");
										//{"rec_conexion_biblioteca":"bib1","rec_tipo_campo_biblioteca":"1","rec_nombre_campo_biblioteca":"nivel","rec_tia_codigo":"1"}
										$this->html->tag("div", array("class"=>"fila"));
											$this->html->tag("div", array("class"=>"celda alineacion_derecha vertical_centro alto_30"));
												$this->html->tag("label", array("class"=>"etiqueta"));
													$this->html->printText("rec_lbl_tipo_campo_biblioteca");
												$this->html->end("label");
											$this->html->end("div");
											
											$this->html->tag("div", array("class"=>"celda alineacion_izquierda vertical_centro alto_30 valor_campo color_letra_campo"));
												$this->html->printSelect($this->conexionBDI, "tcb_codigo", "tcb_nombre", "PSDG_tipo_campo_biblioteca", "", $parametros_conexion['rec_tipo_campo_biblioteca'], array("name"=>"rec_tipo_campo_biblioteca", "id"=>"rec_tipo_campo_biblioteca", "class"=>"valor_campo color_letra_campo ancho_150", "onchange"=>"actualizarCampoCamposBiblioteca();"), "", "", true);
											$this->html->end("div");
										$this->html->end("div");
										
										$this->html->tag("div", array("class"=>"fila"));
											$this->html->tag("div", array("class"=>"celda alineacion_derecha vertical_centro alto_30"));
												$this->html->tag("label", array("class"=>"etiqueta"));
													$this->html->printText("rec_lbl_nombre_campo_biblioteca");
												$this->html->end("label");
											$this->html->end("div");
											
											$this->html->tag("div", array("class"=>"celda alineacion_izquierda vertical_centro alto_30 valor_campo color_letra_campo"));
												$this->html->tag("select", array("name"=>"rec_nombre_campo_biblioteca", "id"=>"rec_nombre_campo_biblioteca", "class"=>"valor_campo color_letra_campo ancho_150"));
												//($nombre_conexion, $tipo_campo)
													$this->actualizarCampoCamposBiblioteca($parametros_conexion['rec_conexion_biblioteca'], $parametros_conexion['rec_tipo_campo_biblioteca'], $parametros_conexion['rec_nombre_campo_biblioteca']);
												$this->html->end("select");
											$this->html->end("div");
										$this->html->end("div");
							$this->html->end("div");
							$this->html->end("div");
							$this->html->end("div");
//							break;
//
//						case 4://Lista de valores
							$this->html->tag("div", array("class"=>"fila", "id"=>"rec_tabla_lista"));
							$this->html->tag("div", array("class"=>"celda"));
							$this->html->tag("div", array("class"=>"tabla"));	
										$this->html->tag("div", array("class"=>"fila"));
											$this->html->tag("div", array("class"=>"celda alineacion_derecha vertical_centro ancho_50p alto_30"));
												$this->html->tag("label", array("class"=>"etiqueta"));
													$this->html->printText("rec_lbl_lista_valores");
												$this->html->end("label");
											$this->html->end("div");
											
											$this->html->tag("div", array("class"=>"celda alineacion_izquierda vertical_centro alto_30 valor_campo color_letra_campo"));
												$this->html->tag("textarea", array("name"=>"rec_lista_valores", "id"=>"rec_lista_valores", "class"=>"valor_campo color_letra_campo ancho_150 alto_120", "wrap"=>"off"));
													$lista_valores = $this->obtenerValoresTablaListaDeValores($parametros_conexion['rec_nombre_tabla_lista_valores']);
													$this->html->printStaticText($lista_valores);
												$this->html->end("textarea");
											$this->html->end("div");
										$this->html->end("div");
							$this->html->end("div");
							$this->html->end("div");
							$this->html->end("div");
//							break;
//
//						case 5://Constante
							$valor_constante = "0";
							if($parametros_conexion['rec_valor_constante'])
								$valor_constante = $parametros_conexion['rec_valor_constante'];	
								
							$this->html->tag("div", array("class"=>"fila", "id"=>"rec_tabla_constante"));
							$this->html->tag("div", array("class"=>"celda"));
							$this->html->tag("div", array("class"=>"tabla"));	
										$this->html->tag("div", array("class"=>"fila"));
											$this->html->tag("div", array("class"=>"celda alineacion_derecha vertical_centro ancho_50p alto_30"));
												$this->html->tag("label", array("class"=>"etiqueta"));
													$this->html->printText("rec_lbl_valor_constante");
												$this->html->end("label");
											$this->html->end("div");
											
											$this->html->tag("div", array("class"=>"celda alineacion_izquierda vertical_centro alto_30 valor_campo color_letra_campo"));
												$this->html->tag("input", array("name"=>"rec_valor_constante", "id"=>"rec_valor_constante", "type"=>"text", "value"=>$valor_constante, "class"=>"valor_campo color_letra_campo ancho_150"));
											$this->html->end("div");
										$this->html->end("div");
							$this->html->end("div");
							$this->html->end("div");
							$this->html->end("div");
//							break;
//
//						case 6://Intervalo
							$valor_desde = 0;
							$valor_hasta = 0;
							if(isset($parametros_conexion['rec_valor_desde']) && isset($parametros_conexion['rec_valor_hasta']))
							{
								$valor_desde = $parametros_conexion['rec_valor_desde'];
								$valor_hasta = $parametros_conexion['rec_valor_hasta'];
							}	
								
							$this->html->tag("div", array("class"=>"fila", "id"=>"rec_tabla_intervalo"));
							$this->html->tag("div", array("class"=>"celda"));
							$this->html->tag("div", array("class"=>"tabla"));	
										$this->html->tag("div", array("class"=>"fila"));
											$this->html->tag("div", array("class"=>"celda alineacion_derecha vertical_centro ancho_50p alto_30"));
												$this->html->tag("label", array("class"=>"etiqueta"));
													$this->html->printText("rec_lbl_desde");
												$this->html->end("label");
											$this->html->end("div");
											
											$this->html->tag("div", array("class"=>"celda alineacion_izquierda vertical_centro alto_30 valor_campo color_letra_campo"));
												$this->html->tag("input", array("name"=>"rec_valor_desde", "id"=>"rec_valor_desde", "type"=>"text", "value"=>$valor_desde, "class"=>"valor_campo color_letra_campo ancho_70"));
											$this->html->end("div");
										$this->html->end("div");
										
										$this->html->tag("div", array("class"=>"fila"));	
											$this->html->tag("div", array("class"=>"celda alineacion_derecha vertical_centro ancho_50p alto_30"));
												$this->html->tag("label", array("class"=>"etiqueta"));
													$this->html->printText("rec_lbl_hasta");
												$this->html->end("label");
											$this->html->end("div");
											
											$this->html->tag("div", array("class"=>"celda alineacion_izquierda vertical_centro alto_30 valor_campo color_letra_campo"));
												$this->html->tag("input", array("name"=>"rec_valor_hasta", "id"=>"rec_valor_hasta", "type"=>"text", "value"=>$valor_hasta, "class"=>"valor_campo color_letra_campo ancho_70"));
											$this->html->end("div");
										$this->html->end("div");
							$this->html->end("div");
							$this->html->end("div");
							$this->html->end("div");
//							break;
//
//						case 7://Archivo

							$this->html->tag("div", array("class"=>"fila", "id"=>"rec_tabla_archivo"));
							$this->html->tag("div", array("class"=>"celda"));
							$this->html->tag("div", array("class"=>"tabla"));
										$this->html->tag("div", array("class"=>"fila"));
											$this->html->tag("div", array("class"=>"celda alineacion_derecha vertical_centro ancho_50p alto_30"));
												$this->html->tag("label", array("class"=>"etiqueta"));
													$this->html->printText("rec_lbl_conexion_archivo");
												$this->html->end("label");
											$this->html->end("div");
											
											$this->html->tag("div", array("class"=>"celda alineacion_izquierda vertical_centro alto_30 valor_campo color_letra_campo"));
												$this->html->printSelect($this->conexionBDI, "con_nombre", "con_nombre", "PSDG_conexion", "con_usu_login = '".$this->usu_login."' AND con_fue_codigo = '7'", $parametros_conexion['con_nombre'], array("name"=>"rec_conexion_archivo", "id"=>"rec_conexion_archivo", "class"=>"valor_campo color_letra_campo ancho_150"), "", "select_seleccione", false);
											$this->html->end("div");
										$this->html->end("div");
							$this->html->end("div");
							$this->html->end("div");
							$this->html->end("div");
//							break;


//                case 8://Secuencial
                     debug($parametros_conexion,'$parametros_conexion');
                     $valor_secuencial = "0";
                     $delta_secuencial = "0";
                     if($parametros_conexion['rec_valor_secuencial'])
                        $valor_secuencial = $parametros_conexion['rec_valor_secuencial'];   
                        
                     if($parametros_conexion['rec_delta_secuencial'])
                        $delta_secuencial = $parametros_conexion['rec_delta_secuencial']; 


                     $this->html->tag("div", array("class"=>"fila", "id"=>"rec_tabla_secuencial"));
                     $this->html->tag("div", array("class"=>"celda"));
                     $this->html->tag("div", array("class"=>"tabla"));  
                              $this->html->tag("div", array("class"=>"fila"));
                                 $this->html->tag("div", array("class"=>"celda alineacion_derecha vertical_centro ancho_50p alto_30"));
                                    $this->html->tag("label", array("class"=>"etiqueta"));
                                       $this->html->printText("rec_lbl_valor_secuencial");
                                    $this->html->end("label");
                                 $this->html->end("div");
                                 
                                 $this->html->tag("div", array("class"=>"celda alineacion_izquierda vertical_centro alto_30 valor_campo color_letra_campo"));
                                    $this->html->tag("input", array("name"=>"rec_valor_secuencial", "id"=>"rec_valor_constante", "type"=>"text", "value"=>$valor_secuencial, "class"=>"valor_campo color_letra_campo ancho_150"));
                                 $this->html->end("div");

                              $this->html->end("div");
                              $this->html->tag("div", array("class"=>"fila"));

                                $this->html->tag("div", array("class"=>"celda alineacion_derecha vertical_centro ancho_50p alto_30"));
                                    $this->html->tag("label", array("class"=>"etiqueta"));
                                       $this->html->printText("rec_lbl_delta_secuencial");
                                    $this->html->end("label");
                                 $this->html->end("div");

                                $this->html->tag("div", array("class"=>"celda alineacion_izquierda vertical_centro alto_30 valor_campo color_letra_campo"));
                                    $this->html->tag("input", array("name"=>"rec_delta_secuencial", "id"=>"rec_valor_constante", "type"=>"text", "value"=>$delta_secuencial, "class"=>"valor_campo color_letra_campo ancho_150"));
                                 $this->html->end("div");

                              $this->html->end("div");
                     $this->html->end("div");
                     $this->html->end("div");
                     $this->html->end("div");
//                   break;

//					}

					//PROBABILIDADES
					$this->html->tag("div", array("class"=>"fila", "id"=>"rec_probabilidades"));
					$this->html->tag("div", array("class"=>"celda"));
					$this->html->tag("div", array("class"=>"tabla"));
								$this->html->tag("div", array("class"=>"fila"));
								$this->html->tag("div", array("class"=>"celda"));
								$this->html->tag("div", array("class"=>"tabla"));
											$this->html->tag("div", array("class"=>"fila"));
												$this->html->tag("div", array("class"=>"celda alineacion_derecha vertical_centro ancho_50p alto_30"));
													$this->html->tag("label", array("class"=>"etiqueta"));
														$this->html->printText("rec_lbl_tia_codigo");
													$this->html->end("label");
												$this->html->end("div");
												
												$this->html->tag("div", array("class"=>"celda alineacion_izquierda vertical_centro alto_30 valor_campo color_letra_campo"));
													$this->html->printSelect($this->conexionBDI, "tia_codigo", "tia_nombre", "PSDG_tipo_acceso", "", $parametros_conexion['rec_tia_codigo'], array("name"=>"rec_tia_codigo", "id"=>"rec_tia_codigo", "class"=>"valor_campo color_letra_campo ancho_150", "onchange"=>"actualizarVisibilidadCampoFuncionProbabilidad();"), "", "", true);
												$this->html->end("div");
											$this->html->end("div");
								$this->html->end("div");
								$this->html->end("div");
								$this->html->end("div");
								
								$this->html->tag("div", array("class"=>"fila", "id"=>"rec_fila_funcion_probabilidad"));
								$this->html->tag("div", array("class"=>"celda"));
								$this->html->tag("div", array("class"=>"tabla"));
											$this->html->tag("div", array("class"=>"fila"));
												$this->html->tag("div", array("class"=>"celda alineacion_derecha vertical_centro ancho_50p alto_30"));
													$this->html->tag("label", array("class"=>"etiqueta"));
														$this->html->printText("rec_lbl_fup_codigo");
													$this->html->end("label");
												$this->html->end("div");
												
												$this->html->tag("div", array("class"=>"celda alineacion_izquierda vertical_centro alto_30 valor_campo color_letra_campo"));
													$this->html->printSelect($this->conexionBDI, "fup_codigo", "fup_nombre", "PSDG_funcion_probabilidad", "", $parametros_conexion['rec_fup_codigo'], array("name"=>"rec_fup_codigo", "id"=>"rec_fup_codigo", "class"=>"valor_campo color_letra_campo ancho_150"), "", "", true);
												$this->html->end("div");
											$this->html->end("div");
								$this->html->end("div");
								$this->html->end("div");
								$this->html->end("div");
								
					$this->html->end("div");
					$this->html->end("div");
					$this->html->end("div");

				$this->html->end("fieldset");
				//FIN FIELDSET SETUP FUENTE DATOS 
			$this->html->end("div");

		$this->html->end("fieldset");
		$this->html->end("div");
		$this->html->end("div");			
		//FIN FORMULARIO
		
//		if(!$read_only)
//		{
			//BOTON
			$this->html->tag("div", array("class"=>"fila"));
				$this->html->tag("div", array("class"=>"celda"));
					$this->html->tag("input", array("name"=>"rec_btn_establecer","id"=>"rec_btn_establecer", "type"=>"button", "value"=>"Establecer", "onclick"=>"establecerRestriccionCampo();", "class"=>"valor_campo color_letra_campo margin_arriba_10"));
				$this->html->end("div");
			$this->html->end("div");
			$this->html->end("form");
//		}	
	}
	
	function actualizarCampoTablasBD($nombre_conexion="", $opcion_seleccionada="")
	{
		$arreglo_nombres_tablas = "";
		if($nombre_conexion)
		{
			$sql = "SELECT con_parametros
					FROM PSDG_conexion
					WHERE con_nombre = '$nombre_conexion'
					AND con_usu_login = '".$this->usu_login."'
					AND con_fue_codigo = '2'
					LIMIT 1";
			$this->conexionBDI->ejecutarSQL($sql);
			$con_parametros = $this->conexionBDI->obtenerResultadoComoCadena();
			$arreglo_parametros = json_decode($con_parametros, true);
			//establezco la conexion con la bd de la conexion
			$conexion_auxiliar = new ConexionBDMySQL($arreglo_parametros);
			$conexion_auxiliar->conectar();
			$arreglo_nombres_tablas = $conexion_auxiliar->obtenerNombresTablasBD();
		}
		$this->html->arregloAOpciones($arreglo_nombres_tablas,$opcion_seleccionada,"select_seleccione", false);
	}
	
	function actualizarCampoCamposBD($nombre_conexion, $nombre_tabla, $campo_deshabilitado, $opcion_seleccionada="")
	{
		$arreglo_nombres_campos = "";
		if($nombre_conexion)
		{
			$sql = "SELECT con_parametros
					FROM PSDG_conexion
					WHERE con_nombre = '$nombre_conexion'
					AND con_usu_login = '".$this->usu_login."'
					AND con_fue_codigo = '2'
					LIMIT 1";
			$this->conexionBDI->ejecutarSQL($sql);
			$con_parametros = $this->conexionBDI->obtenerResultadoComoCadena();
			$arreglo_parametros = json_decode($con_parametros, true);
			//establezco la conexion con la bd de la conexion
			$conexion_auxiliar = new ConexionBDMySQL($arreglo_parametros);
			$conexion_auxiliar->conectar();
			$arreglo_nombres_campos = $conexion_auxiliar->obtenerNombresCamposTablaBD($nombre_tabla);
		}
		$this->html->arregloAOpciones($arreglo_nombres_campos,$opcion_seleccionada ,"select_seleccione", false, $campo_deshabilitado);
	}
	
	function actualizarCampoCamposBiblioteca($nombre_conexion, $tipo_campo, $opcion_seleccionada="")
	{
		$arreglo_nombres_campos = "";
		if($nombre_conexion)
		{
			$sql = "SELECT con_parametros
					FROM PSDG_conexion
					WHERE con_nombre = '$nombre_conexion'
					AND con_usu_login = '".$this->usu_login."'
					AND con_fue_codigo = '3'
					LIMIT 1";
			$this->conexionBDI->ejecutarSQL($sql);
			//echo $sql;
			$con_parametros = $this->conexionBDI->obtenerResultadoComoCadena();
			$arreglo_parametros = json_decode($con_parametros, true);
			$arreglo_nombres_campos = $this->conexionBDI->obtenerNombresCamposTablaBD($arreglo_parametros['con_nombre_biblioteca_tabla']);
			if($tipo_campo == 1)//primario o independiente
				 $arreglo_nombres_campos = array($arreglo_nombres_campos[0]); 
			else//secundarios o dependientes
				unset($arreglo_nombres_campos[0]);
		}
		$this->html->arregloAOpciones($arreglo_nombres_campos,$opcion_seleccionada ,"", false, $campo_deshabilitado);
	}
	
	function obtenerTiposLlave($rec_nombre_tabla, $rec_nombre_campo)
	{
		$parametros_conexion_BDO = $this->conexionBDO->obtenerParametrosConexion();
		$nombre_BDO = $parametros_conexion_BDO['con_nombre_bd'];
		//consulto si es una llave foranea
		$sql = "	SELECT CONSTRAINT_TYPE
					FROM TABLE_CONSTRAINTS, KEY_COLUMN_USAGE
					WHERE TABLE_CONSTRAINTS.TABLE_NAME = KEY_COLUMN_USAGE.TABLE_NAME
					AND TABLE_CONSTRAINTS.CONSTRAINT_NAME = KEY_COLUMN_USAGE.CONSTRAINT_NAME
					AND TABLE_CONSTRAINTS.TABLE_SCHEMA = KEY_COLUMN_USAGE.TABLE_SCHEMA
					AND TABLE_CONSTRAINTS.CONSTRAINT_SCHEMA = '".$nombre_BDO."'
					AND TABLE_CONSTRAINTS.TABLE_NAME = '".$rec_nombre_tabla."'
					AND KEY_COLUMN_USAGE.COLUMN_NAME = '".$rec_nombre_campo."'";
		//echo $sql;
		$this->conexionBDO->establecer_bd("information_schema");
		$this->conexionBDO->ejecutarSQL($sql);
		$arreglo_tipos = array();
		while($tipo_llave = $this->conexionBDO->obtenerFilaComoArreglo())
			$arreglo_tipos[] = "rec_lbl_".$tipo_llave[0];
		$this->conexionBDO->restablecer_bd_original();
		return $arreglo_tipos;
	}
	
	function obtenerTipoDeDato($tipo_de_dato_extendido)
	{
		$posicion_parentesis = stripos($tipo_de_dato_extendido, "(");
		if($posicion_parentesis)
			$tipo_dato = substr($tipo_de_dato_extendido, 0, $posicion_parentesis);
		else
			$tipo_dato = $tipo_de_dato_extendido;
			  
		return $tipo_dato;	
	}
	
	function actualizarRestriccionCampo($rec_nombre_tabla, $rec_nombre_campo, $rec_fue_codigo="", $rec_parametros_tipo_fuente="", $rec_porcentaje_nulos = "0")
	{
		if($rec_fue_codigo == 1)//si se selecciona fuente NINGUNA, borro la restriccion, si no existe no pasa nada 0 rows affected
		{
			//borro tambien dependencia de tablas si tenia
			$sql = "	DELETE FROM PSDG_dependencias_de_tablas 
						WHERE det_nombre_tabla_dependiente = '".$rec_nombre_tabla."'
						AND det_depende_de = '".$rec_nombre_campo."'
						AND det_usu_login = '".$this->usu_login."'";
			$this->conexionBDI->ejecutarSQL($sql);
			$sql = "	DELETE FROM PSDG_restricciones_campos 
						WHERE rec_nombre_tabla = '".$rec_nombre_tabla."'
						AND rec_nombre_campo = '".$rec_nombre_campo."'
						AND rec_usu_login = '".$this->usu_login."'";
		}			
		else if($this->conexionBDI->existeRegistro("rec_nombre_campo", "PSDG_restricciones_campos", "rec_nombre_campo = '".$rec_nombre_campo."' AND rec_nombre_tabla = '".$rec_nombre_tabla."' AND rec_usu_login = '".$this->usu_login."'"))//si existe restriccion la actualizo
			$sql = "	UPDATE PSDG_restricciones_campos 
						SET rec_fue_codigo = '$rec_fue_codigo',
						rec_parametros_tipo_fuente = '$rec_parametros_tipo_fuente',
						rec_porcentaje_nulos = '$rec_porcentaje_nulos'
						WHERE rec_nombre_tabla = '".$rec_nombre_tabla."'
						AND rec_nombre_campo = '".$rec_nombre_campo."'
						AND rec_usu_login = '".$this->usu_login."'";
		else //si seleccione fuente y no existe restriccion, la inserto
			$sql = "INSERT INTO PSDG_restricciones_campos(	rec_usu_login, 
															rec_nombre_tabla,
															rec_nombre_campo,
															rec_fue_codigo,
															rec_parametros_tipo_fuente,
															rec_porcentaje_nulos,
															rec_es_foranea)
			 		VALUES(	'".$this->usu_login."', 
			 				'".$rec_nombre_tabla."', 
							'".$rec_nombre_campo."',
							'".$rec_fue_codigo."',
							'".$rec_parametros_tipo_fuente."',
							'".$rec_porcentaje_nulos."',
							'0')";
		//echo $sql;
		$this->conexionBDI->ejecutarSQL($sql);
	}
	
	function establecerRestriccionesForaneas($nombre_tabla, $numero_tuplas)
	{
		if($numero_tuplas == 0)//si se elimino restriccion tabla
		{
			//se eliminan restricciones de los campos de esta tabla
			//se eliminan restricciones de campos que dependan de esta tabla
			$sql = "DELETE FROM PSDG_restricciones_campos 
					WHERE rec_usu_login = '".$this->usu_login."'
					AND (rec_nombre_tabla = '".$nombre_tabla."'
						OR rec_parametros_tipo_fuente LIKE '{\"rec_nombre_conexion\":\"BDO\",\"rec_nombre_tabla\":\"$nombre_tabla\"%')";
			$this->conexionBDI->ejecutarSQL($sql);
			
			//se eliminan las dependencias (interna) de campos de esta tabla
			$sql = "DELETE FROM PSDG_dependencias_de_campos
					WHERE dec_usu_login = '".$this->usu_login."'
					AND dec_nombre_tabla = '".$nombre_tabla."'";
			$this->conexionBDI->ejecutarSQL($sql);
			
			//se eliminan las dependencias de tablas
			$sql = "DELETE FROM PSDG_dependencias_de_tablas
					WHERE det_usu_login = '".$this->usu_login."'
					AND (det_nombre_tabla_dependiente  = '".$nombre_tabla."'
						OR det_depende_de = '".$nombre_tabla."')";
			$this->conexionBDI->ejecutarSQL($sql);
		}
		else
		{
			//miro si ya no estan establecidas antes, para no hacerlo otra vez
			$sql = "SELECT rec_es_foranea 
					FROM PSDG_restricciones_campos 
					WHERE rec_es_foranea = 1
					AND rec_usu_login = '".$this->usu_login."'
					AND rec_nombre_tabla = '".$nombre_tabla."' LIMIT 1";
			$this->conexionBDI->ejecutarSQL($sql);
			$num_foraneas = $this->conexionBDI->obtenerNumeroFilas();
			 
			if($num_foraneas == 0)
			{
				$parametros_conexion_BDO = $this->conexionBDO->obtenerParametrosConexion();
				$nombre_BDO = $parametros_conexion_BDO['con_nombre_bd'];
				//consulto el campo y la tabla a la que apuntan las llaves foraneas
				//de la BDO
				$sql = "	SELECT TABLE_NAME, COLUMN_NAME, REFERENCED_TABLE_NAME, REFERENCED_COLUMN_NAME
							FROM KEY_COLUMN_USAGE
							WHERE CONSTRAINT_SCHEMA = '".$nombre_BDO."'
							AND TABLE_NAME = '".$nombre_tabla."'
							AND REFERENCED_TABLE_NAME IS NOT NULL
							AND REFERENCED_COLUMN_NAME IS NOT NULL";
				$this->conexionBDO->establecer_bd("information_schema");
				$this->conexionBDO->ejecutarSQL($sql);
				
				while ($info_campo_referenciado = $this->conexionBDO->obtenerFilaComoArreglo())
				{
					
					$sql = "INSERT INTO PSDG_restricciones_campos(	rec_usu_login, 
																	rec_nombre_tabla,
																	rec_nombre_campo,
																	rec_fue_codigo,
																	rec_parametros_tipo_fuente,
																	rec_porcentaje_nulos,
																	rec_es_foranea)
					 		VALUES(	'".$this->usu_login."', 
					 				'".$info_campo_referenciado[0]."', 
									'".$info_campo_referenciado[1]."',
									'2',
									'{\"rec_nombre_conexion\":\"BDO\",\"rec_nombre_tabla\":\"".$info_campo_referenciado[2]."\",\"rec_nombre_campo\":\"".$info_campo_referenciado[3]."\",\"rec_tia_codigo\":\"2\"}',
									'0',
									'1')";
					$this->conexionBDI->ejecutarSQL($sql);
					$sql = "INSERT INTO PSDG_dependencias_de_tablas(det_usu_login,
																	det_nombre_tabla_dependiente, 
																	det_depende_de)
							VALUES ('".$this->usu_login."', 
									'".$info_campo_referenciado[0]."', 
									'".$info_campo_referenciado[2]."')";
					$this->conexionBDI->ejecutarSQL($sql);
				}
				$this->conexionBDO->restablecer_bd_original();
			}
		}
	}
	
	function crearTablaListaDeValores($rec_lista_valores, $rec_nombre_tabla_origen, $rec_nombre_campo_origen)
	{
		$nombre_tabla = $this->usu_login."_4_".$rec_nombre_tabla_origen."_".$rec_nombre_campo_origen;
		$sql = "CREATE TABLE IF NOT EXISTS ".$nombre_tabla."
				(valores TEXT COLLATE utf8_unicode_ci) ENGINE = InnoDB COMMENT = 'create by list: ($rec_nombre_tabla_origen"."->"."$rec_nombre_campo_origen)'";
		$this->conexionBDI->ejecutarSQL($sql);
		$arreglo_valores = explode("\n",$rec_lista_valores);
		$sql = "DELETE FROM $nombre_tabla";
		$this->conexionBDI->ejecutarSQL($sql);
		$this->insertarValoresEnTablaListaDeValores($arreglo_valores, $rec_nombre_tabla_origen, $rec_nombre_campo_origen);
		return $nombre_tabla;
	}
	
	function eliminarTablaListaDeValores($rec_nombre_tabla_origen, $rec_nombre_campo_origen)//si existe
	{
		$sql = "DROP TABLE IF EXISTS ".$this->usu_login."_4_".$rec_nombre_tabla_origen."_".$rec_nombre_campo_origen;
		$this->conexionBDI->ejecutarSQL($sql);
	}
	
	function insertarValoresEnTablaListaDeValores($arreglo_valores, $rec_nombre_tabla_origen, $rec_nombre_campo_origen)
	{
		foreach($arreglo_valores as $valor)
		{		
			$sql = "INSERT INTO ".$this->usu_login."_4_".$rec_nombre_tabla_origen."_".$rec_nombre_campo_origen."(valores)
					VALUES ('$valor')";
			$this->conexionBDI->ejecutarSQL($sql);
		}
	}
	
	function obtenerValoresTablaListaDeValores($nombre_tabla_lista_valores)
	{
		$sql = "SELECT valores FROM $nombre_tabla_lista_valores";
		$this->conexionBDI->ejecutarSQL($sql);
		if($this->conexionBDI->obtenerResultset())
		{
			$arreglo_valores = $this->conexionBDI->obtenerResultadoComoArreglo();
			$valores = Array();
			foreach ($arreglo_valores AS $pos => $valor)
				$valores[] = $valor[0];
			return implode("@br2n", $valores);
		}
		else
			return "";
	}
	
	function crearDependenciaDeTabla($det_nombre_tabla_dependiente, $det_depende_de)
	{
		$num_registros = $this->conexionBDI->existeRegistro("det_nombre_tabla_dependiente", "PSDG_dependencias_de_tablas", "det_usu_login='".$this->usu_login."' AND det_nombre_tabla_dependiente='".$det_nombre_tabla_dependiente."' AND det_depende_de='".$det_depende_de."'");
		if($num_registros == 0)
		{
			$sql = "INSERT INTO PSDG_dependencias_de_tablas(det_usu_login, det_nombre_tabla_dependiente, det_depende_de)
					VALUES ('".$this->usu_login."', '$det_nombre_tabla_dependiente', '$det_depende_de')";
			$this->conexionBDI->ejecutarSQL($sql);
		}
	}
	
	function crearDependenciaDeCampo($dec_nombre_tabla, $dec_nombre_campo_dependiente, $dec_depende_de)
	{
		$num_registros = $this->conexionBDI->existeRegistro("dec_nombre_campo_dependiente", "PSDG_dependencias_de_campos", "dec_usu_login='".$this->usu_login."' AND dec_nombre_tabla='".$dec_nombre_tabla."' AND dec_nombre_campo_dependiente='".$dec_nombre_campo_dependiente."' AND dec_depende_de='".$dec_depende_de."'");
		if($num_registros == 0)
		{
			$sql = "INSERT INTO PSDG_dependencias_de_campos(dec_usu_login, dec_nombre_tabla, dec_nombre_campo_dependiente, dec_depende_de)
					VALUES ('".$this->usu_login."', '$dec_nombre_tabla', '$dec_nombre_campo_dependiente', '$dec_depende_de')";
			$this->conexionBDI->ejecutarSQL($sql);
		}
	}
}
?>
