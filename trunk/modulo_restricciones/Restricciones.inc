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
					WHERE con_tipo = 'bd'
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
		return $this->conexionBDI->existeRegistro("ret_nombre_tabla", "PSDG_restricciones_tablas", "ret_nombre_tabla = '".$nombre_tabla."'");
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
			$this->html->tag("div", array("class"=>"celda alineacion_derecha vertical_centro alto_30 ancho_200"));
				$this->html->tag("label", array("class"=>"etiqueta"));
					$this->html->printStaticText("Nombre de tabla");//CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR
				$this->html->end("label");
			$this->html->end("div");
			
			$this->html->tag("div", array("class"=>"celda alineacion_izquierda vertical_centro alto_30 ancho_400 valor_campo color_letra_campo paddin_izquierdo_15"));
				$this->html->tag("label", array("id"=>"rec_lbl_nombre_tabla"));
					$this->html->printStaticText($this->arreglo_restricciones['ret_nombre_tabla']);
				$this->html->end("label");
			$this->html->end("div");
		$this->html->end("div");
	
		//NUMERO DE TUPLAS
		$this->html->tag("div", array("class"=>"fila"));
			$this->html->tag("div", array("class"=>"celda alineacion_derecha vertical_centro alto_30 ancho_200"));
				$this->html->tag("label", array("class"=>"etiqueta"));
					$this->html->printStaticText("Cantidad de tuplas");//CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR
				$this->html->end("label");
			$this->html->end("div");
			
			$this->html->tag("div", array("class"=>"celda alineacion_izquierda vertical_centro alto_30 ancho_400 paddin_izquierdo_15"));
				$this->html->tag("input", array("id"=>"rec_txt_numero_tuplas" ,"type"=>"text", "value"=>$numero_tuplas, "class"=>"valor_campo color_letra_campo"));
			$this->html->end("div");
		$this->html->end("div");
		
		//BOTON
		$this->html->tag("div", array("class"=>"fila"));
			$this->html->tag("input", array("id"=>"rec_btn_establecer" ,"type"=>"button", "value"=>"Establecer", "onclick"=>"establecerRestriccionTabla();", "class"=>"color_letra_campo"));//CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR
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
		$sql = "	SELECT rec_fue_codigo, rec_parametros_tipo_fuente, rec_acceso_aleatorio, rec_porcentaje_nulos
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
						$this->html->tag("label", array("class"=>"etiqueta ancho_200"));
							$this->html->printStaticText("Tabla");//CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR
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
						$this->html->tag("label", array("class"=>"etiqueta ancho_200"));
							$this->html->printStaticText("Campo");//CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR
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
						$this->html->tag("label", array("class"=>"etiqueta ancho_200"));
							$this->html->printStaticText("Tipo de dato");//CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR
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
						$this->html->tag("label", array("class"=>"etiqueta ancho_200"));
							$this->html->printStaticText("Permite Nulos");//CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR
						$this->html->end("label");
					$this->html->end("div");
					
					$this->html->tag("div", array("class"=>"celda alineacion_izquierda vertical_centro  valor_campo color_letra_campo"));
						$this->html->tag("label", array("id"=>"rec_lbl_permite_nulos"));
							$this->html->printStaticText($this->arreglo_restricciones['permite_nulos']);
						$this->html->end("label");
					$this->html->end("div");
				$this->html->end("div");
				
				if($this->arreglo_restricciones['tipo_llave'])
				{
					//TIPO DE LLAVE
					$this->html->tag("div", array("class"=>"fila"));
						$this->html->tag("div", array("class"=>"celda alineacion_derecha vertical_centro "));
							$this->html->tag("label", array("class"=>"etiqueta ancho_200"));
								$this->html->printStaticText("Tipo de llave");//CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR
							$this->html->end("label");
						$this->html->end("div");
						
						$this->html->tag("div", array("class"=>"celda alineacion_izquierda vertical_centro  valor_campo color_letra_campo"));
							$this->html->tag("label", array("id"=>"rec_lbl_nombre_campo"));
								$this->html->printStaticText($this->arreglo_restricciones['tipo_llave']);
							$this->html->end("label");
						$this->html->end("div");
					$this->html->end("div");
				}
				
				//VALOR DEFAULT
				$this->html->tag("div", array("class"=>"fila"));
					$this->html->tag("div", array("class"=>"celda alineacion_derecha vertical_centro "));
						$this->html->tag("label", array("class"=>"etiqueta ancho_200"));
							$this->html->printStaticText("Valor por defecto");//CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR
						$this->html->end("label");
					$this->html->end("div");
					
					$this->html->tag("div", array("class"=>"celda alineacion_izquierda vertical_centro  valor_campo color_letra_campo"));
						$this->html->tag("label", array("id"=>"rec_lbl_es_valor_unico"));
							$this->html->printStaticText($this->arreglo_restricciones['valor_default']);
						$this->html->end("label");
					$this->html->end("div");
				$this->html->end("div");
				
				if($this->arreglo_restricciones['extra'])
				{
					//EXTRAS
					$this->html->tag("div", array("class"=>"fila"));
						$this->html->tag("div", array("class"=>"celda alineacion_derecha vertical_centro "));
							$this->html->tag("label", array("class"=>"etiqueta ancho_200"));
								$this->html->printStaticText("Otro");//CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR
							$this->html->end("label");
						$this->html->end("div");
						
						$this->html->tag("div", array("class"=>"celda alineacion_izquierda vertical_centro  valor_campo color_letra_campo"));
							$this->html->tag("label", array("id"=>"rec_lbl_es_sin_signo"));
								$this->html->printStaticText($this->arreglo_restricciones['extra']);
							$this->html->end("label");
						$this->html->end("div");
					$this->html->end("div");
				}
				
			$this->html->end("div");
			
		$this->html->end("fieldset");
		$this->html->end("div");
		$this->html->end("div");
		
		//FIELDSET CONFIGURACION RESTRICCIONES
				
		$this->html->tag("div", array("class"=>"fila"));
		$this->html->tag("div", array("class"=>"celda"));
		$this->html->tag("fieldset");
		
			$this->html->tag("legend");
				$this->html->tag("label");
					$this->html->printText("res_lgn_titulo_restricciones");
				$this->html->end("label");
			$this->html->end("legend");
			
			$this->html->tag("div", array("class"=>"tabla"));
			
				//FUENTE DE DATOS
				$this->html->tag("div", array("class"=>"fila"));
					$this->html->tag("div", array("class"=>"celda alineacion_derecha vertical_centro ancho_50p"));
						$this->html->tag("label", array("class"=>"etiqueta"));
							$this->html->printStaticText("Fuente de datos");//CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR
						$this->html->end("label");
					$this->html->end("div");
					
					$tipo_de_dato = $this->obtenerTipoDeDato($this->arreglo_restricciones['rec_tipo_dato']);
					
					$this->html->tag("div", array("class"=>"celda alineacion_izquierda vertical_centro alto_30 valor_campo color_letra_campo"));
							$this->html->printSelect($this->conexionBDI, "fue_codigo", "fue_nombre", "PSDG_fuentes, PSDG_fuentes_de_tipos", "fdt_fue_codigo = fue_codigo AND fdt_tipo_de_dato = '".$tipo_de_dato."'" , $this->arreglo_restricciones['rec_fue_codigo'], array("class"=>"valor_campo color_letra_campo"), "");
					$this->html->end("div");
				$this->html->end("div");
			
				$porcentaje_nulos = 0;
				if($this->arreglo_restricciones['rec_porcentaje_nulos'])
					$porcentaje_nulos = $this->arreglo_restricciones['rec_porcentaje_nulos'];	
				
				//NULOS
				$this->html->tag("div", array("class"=>"fila"));
					$this->html->tag("div", array("class"=>"celda alineacion_derecha vertical_centro alto_30"));
						$this->html->tag("label", array("class"=>"etiqueta"));
							$this->html->printStaticText("Porcentaje valores nulos");//CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR
						$this->html->end("label");
					$this->html->end("div");
					
					$this->html->tag("div", array("class"=>"celda alineacion_izquierda vertical_centro alto_30 valor_campo color_letra_campo"));
							$this->html->tag("input", array("id"=>"rec_txt_numero_tuplas" ,"type"=>"text", "value"=>$porcentaje_nulos, "class"=>"valor_campo color_letra_campo"));
					$this->html->end("div");
				$this->html->end("div");
				
				switch($this->arreglo_restricciones['rec_fue_codigo'])
				{
					case 1://Archivo
						$this->html->tag("div", array("class"=>"fila"));
							$this->html->tag("div", array("class"=>"celda alineacion_izquierda"));
								$this->html->tag("label", array("class"=>"etiqueta"));
									$this->html->printStaticText("Cantidad de tuplas");//CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR
								$this->html->end("label");
							$this->html->end("div");
							
							$this->html->tag("div", array("class"=>"celda alineacion_izquierda"));
								$this->html->tag("input", array("id"=>"rec_txt_numero_tuplas" ,"type"=>"text", "value"=>$numero_tuplas));
							$this->html->end("div");
						$this->html->end("div");
						break;
					case 2://Base de datos externa
						break;
					case 3://Biblioteca
						break;
					case 4://Lista de valores
						break;
					case 5://Constante
						break;
					case 6://Intervalo
						break;
				}
				
			$this->html->end("div");
			
		$this->html->end("fieldset");
		$this->html->end("div");
		$this->html->end("div");			
	
		//BOTON
		$this->html->tag("div", array("class"=>"fila"));
			$this->html->tag("div", array("class"=>"celda"));
				$this->html->tag("input", array("id"=>"rec_btn_establecer" ,"type"=>"button", "value"=>"Establecer", "onclick"=>"establecerRestriccionTabla();", "class"=>"valor_campo color_letra_campo"));//CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR
			$this->html->end("div");
		$this->html->end("div");
			
//		$this->html->end("div");	
//		$this->html->end("div");
//		$this->html->end("div");
		//FIN FORMULARIO
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
	
	function actualizarRestriccionCampo($nombre_tabla, $numero_tuplas)
	{
		/*if($numero_tuplas == 0)
			$sql = "	DELETE FROM PSDG_restricciones_tablas 
						WHERE ret_nombre_tabla = '".$nombre_tabla."'
						AND ret_usu_login = '".$this->usu_login."'";
		else if($this->conexionBDI->existeRegistro("ret_nombre_tabla", "PSDG_restricciones_tablas", "ret_nombre_tabla = '".$nombre_tabla."'"))
			$sql = "	UPDATE PSDG_restricciones_tablas 
						SET ret_numero_tuplas_a_generar = $numero_tuplas 
						WHERE ret_nombre_tabla = '".$nombre_tabla."' 
						AND ret_usu_login = '".$this->usu_login."'";
		else
			$sql = "INSERT INTO PSDG_restricciones_tablas(ret_usu_login,ret_nombre_tabla,ret_numero_tuplas_a_generar) VALUES('".$this->usu_login."', '$nombre_tabla', $numero_tuplas)";
		//echo $sql;
		$this->conexionBDI->ejecutarSQL($sql); */
	}
}
?>
