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
			$sql = "SELECT * FROM ".$nombre_tabla[0]." LIMIT 1";
			$this->conexionBDO->ejecutarSQL($sql); 
			$arreglo_meta_datos_columnas = $this->conexionBDO->obtenerArregloMetaDatosColumnas();
			
			$this->html->tag("li", array("rel"=>"tabla"));
				$this->html->tag("a", array("onclick"=>"mostrarDetalleTabla('".$nombre_tabla[0]."');"));
					$this->html->tag("ins");
						$this->html->printStaticText("&nbsp;");
					$this->html->end("ins");
					$this->html->tag("label");
						$this->html->printStaticText($nombre_tabla[0]);
					$this->html->end("label");
				$this->html->end("a");
				
				/*foreach($arreglo_meta_datos_columnas AS $numero_columna => $objeto_meta)
				{
					if($objeto_meta->primary_key)
						$rel = "llave_primaria";
					else if($objeto_meta->unique_key)
						$rel = "unico";
					else if($objeto_meta->multiple_key)
						$rel = "llave_foranea";
					else
						$rel = "campo";
						
					$this->html->tag("ul");
						$this->html->tag("li", array("rel"=>$rel));
							$this->html->tag("a", array("onclick"=>"alert('".$objeto_meta->def."'); mostrarDetalleCampo('".$nombre_tabla[0]."'
																											,'".$objeto_meta->name."'
																											,'".$objeto_meta->type."'
																											,'".$objeto_meta->max_length."'
																											,'".!$objeto_meta->not_null."'
																											,'".!$objeto_meta->primary_key."'
																											,'".!$objeto_meta->unique_key."'
																											,'".$objeto_meta->unsigned."'
																											,'".$objeto_meta->def."');")); 
								$this->html->tag("ins");
									$this->html->printStaticText("&nbsp;");
								$this->html->end("ins");
								$this->html->tag("label");
									$this->html->printStaticText($objeto_meta->name);
								$this->html->end("label");
							$this->html->end("a");
						$this->html->end("li");
					$this->html->end("ul");
				} */
			$this->html->end("li");
		}
		$this->html->end("ul");
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
			$this->html->tag("div", array("class"=>"celda alineacion_izquierda"));
				$this->html->tag("label");
					$this->html->printStaticText("Nombre de tabla");//CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR
				$this->html->end("label");
			$this->html->end("div");
			
			$this->html->tag("div", array("class"=>"celda alineacion_izquierda"));
				$this->html->tag("label", array("id"=>"rec_lbl_nombre_tabla"));
					$this->html->printStaticText($this->arreglo_restricciones['ret_nombre_tabla']);
				$this->html->end("label");
			$this->html->end("div");
		$this->html->end("div");
	
		//NUMERO DE TUPLAS
		$this->html->tag("div", array("class"=>"fila"));
			$this->html->tag("div", array("class"=>"celda alineacion_izquierda"));
				$this->html->tag("label");
					$this->html->printStaticText("Cantidad de tuplas");//CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR
				$this->html->end("label");
			$this->html->end("div");
			
			$this->html->tag("div", array("class"=>"celda alineacion_izquierda"));
				$this->html->tag("input", array("id"=>"rec_txt_numero_tuplas" ,"type"=>"text", "value"=>$numero_tuplas));
			$this->html->end("div");
		$this->html->end("div");
		
		//BOTON
		$this->html->tag("div", array("class"=>"fila"));
			$this->html->tag("input", array("id"=>"rec_btn_establecer" ,"type"=>"button", "value"=>"Establecer", "onclick"=>"establecerRestriccionTabla();"));//CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR
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
			$esta_establecida = $this->conexionBDI->existeRegistro("ret_nombre_tabla", "PSDG_restricciones_tablas", "ret_nombre_tabla = '".$tabla_referenciada[0]."'");
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
			$esta_establecida = $this->conexionBDI->existeRegistro("ret_nombre_tabla", "PSDG_restricciones_tablas", "ret_nombre_tabla = '".$tabla_relacionada[0]."'");
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
		else if($this->conexionBDI->existeRegistro("ret_nombre_tabla", "PSDG_restricciones_tablas", "ret_nombre_tabla = '".$nombre_tabla."'"))
			$sql = "	UPDATE PSDG_restricciones_tablas 
						SET ret_numero_tuplas_a_generar = $numero_tuplas 
						WHERE ret_nombre_tabla = '".$nombre_tabla."' 
						AND ret_usu_login = '".$this->usu_login."'";
		else
			$sql = "INSERT INTO PSDG_restricciones_tablas(ret_usu_login,ret_nombre_tabla,ret_numero_tuplas_a_generar) VALUES('".$this->usu_login."', '$nombre_tabla', $numero_tuplas)";
		//echo $sql;
		$this->conexionBDI->ejecutarSQL($sql); 
	}
	
	function cargarRestriccionesCampo($nombre_tabla, $nombre_campo, $tipo_dato, $longitud, $permite_nulos, $es_llave_primaria, $es_valor_unico, $es_sin_signo, $valor_default)
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
		$this->arreglo_restricciones['longitud'] = $longitud;
		$this->arreglo_restricciones['permite_nulos'] = $permite_nulos;
		$this->arreglo_restricciones['es_llave_primaria'] = $es_llave_primaria;
		$this->arreglo_restricciones['es_valor_unico'] = $es_valor_unico;
		$this->arreglo_restricciones['es_sin_signo'] = $es_sin_signo;
		$this->arreglo_restricciones['valor_default'] = $valor_default;
	}
	
	function crearFormularioRestriccionesCampo()
	{	
		//FORMULARIO
		//NOMBRE DE TABLA
		$this->html->tag("div", array("class"=>"fila"));
			$this->html->tag("div", array("class"=>"celda alineacion_izquierda"));
				$this->html->tag("label");
					$this->html->printStaticText("Tabla");//CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR
				$this->html->end("label");
			$this->html->end("div");
			
			$this->html->tag("div", array("class"=>"celda alineacion_izquierda"));
				$this->html->tag("label", array("id"=>"rec_lbl_nombre_tabla"));
					$this->html->printStaticText($this->arreglo_restricciones['rec_nombre_tabla']);
				$this->html->end("label");
			$this->html->end("div");
		$this->html->end("div");

		//NOMBRE DE CAMPO
		$this->html->tag("div", array("class"=>"fila"));
			$this->html->tag("div", array("class"=>"celda alineacion_izquierda"));
				$this->html->tag("label");
					$this->html->printStaticText("Campo");//CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR
				$this->html->end("label");
			$this->html->end("div");
			
			$this->html->tag("div", array("class"=>"celda alineacion_izquierda"));
				$this->html->tag("label", array("id"=>"rec_lbl_nombre_campo"));
					$this->html->printStaticText($this->arreglo_restricciones['rec_nombre_campo']);
				$this->html->end("label");
			$this->html->end("div");
		$this->html->end("div");
		
		//TIPO DE DATO
		$this->html->tag("div", array("class"=>"fila"));
			$this->html->tag("div", array("class"=>"celda alineacion_izquierda"));
				$this->html->tag("label");
					$this->html->printStaticText("Tipo de dato");//CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR
				$this->html->end("label");
			$this->html->end("div");
			
			$this->html->tag("div", array("class"=>"celda alineacion_izquierda"));
				$this->html->tag("label", array("id"=>"rec_lbl_tipo_dato"));
					$this->html->printStaticText($this->arreglo_restricciones['rec_tipo_dato']."(".$this->arreglo_restricciones['longitud'].")");
				$this->html->end("label");
			$this->html->end("div");
		$this->html->end("div");
		
		//DEFAULT
		$this->html->tag("div", array("class"=>"fila"));
			$this->html->tag("div", array("class"=>"celda alineacion_izquierda"));
				$this->html->tag("label");
					$this->html->printStaticText("Valor por defecto");//CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR
				$this->html->end("label");
			$this->html->end("div");
			
			$this->html->tag("div", array("class"=>"celda alineacion_izquierda"));
				$this->html->tag("label", array("id"=>"rec_lbl_valor_default"));
					$this->html->printStaticText($this->arreglo_restricciones['valor_default']);
				$this->html->end("label");
			$this->html->end("div");
		$this->html->end("div");
		
		//PERMITE NULOS
		$this->html->tag("div", array("class"=>"fila"));
			$this->html->tag("div", array("class"=>"celda alineacion_izquierda"));
				$this->html->tag("label");
					$this->html->printStaticText("Permite Nulos");//CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR
				$this->html->end("label");
			$this->html->end("div");
			
			$this->html->tag("div", array("class"=>"celda alineacion_izquierda"));
				$this->html->tag("label", array("id"=>"rec_lbl_permite_nulos"));
					$this->html->printStaticText($this->arreglo_restricciones['permite_nulos']);
				$this->html->end("label");
			$this->html->end("div");
		$this->html->end("div");
		
		//LLAVE PRIMARIA
		$this->html->tag("div", array("class"=>"fila"));
			$this->html->tag("div", array("class"=>"celda alineacion_izquierda"));
				$this->html->tag("label");
					$this->html->printStaticText("Llave primaria");//CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR
				$this->html->end("label");
			$this->html->end("div");
			
			$this->html->tag("div", array("class"=>"celda alineacion_izquierda"));
				$this->html->tag("label", array("id"=>"rec_lbl_nombre_campo"));
					$this->html->printStaticText(!$this->arreglo_restricciones['es_llave_primaria']);
				$this->html->end("label");
			$this->html->end("div");
		$this->html->end("div");
		
		//VALOR UNICO
		$this->html->tag("div", array("class"=>"fila"));
			$this->html->tag("div", array("class"=>"celda alineacion_izquierda"));
				$this->html->tag("label");
					$this->html->printStaticText("Es valor unico");//CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR
				$this->html->end("label");
			$this->html->end("div");
			
			$this->html->tag("div", array("class"=>"celda alineacion_izquierda"));
				$this->html->tag("label", array("id"=>"rec_lbl_es_valor_unico"));
					$this->html->printStaticText(!$this->arreglo_restricciones['es_valor_unico']);
				$this->html->end("label");
			$this->html->end("div");
		$this->html->end("div");
		
		//PERMITIR SIGNO
		$this->html->tag("div", array("class"=>"fila"));
			$this->html->tag("div", array("class"=>"celda alineacion_izquierda"));
				$this->html->tag("label");
					$this->html->printStaticText("Permite Signo");//CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR
				$this->html->end("label");
			$this->html->end("div");
			
			$this->html->tag("div", array("class"=>"celda alineacion_izquierda"));
				$this->html->tag("label", array("id"=>"rec_lbl_es_sin_signo"));
					$this->html->printStaticText(!$this->arreglo_restricciones['es_sin_signo']);
				$this->html->end("label");
			$this->html->end("div");
		$this->html->end("div");
		
		//FUENTE DE DATOS
		$this->html->tag("div", array("class"=>"fila"));
			$this->html->tag("div", array("class"=>"celda alineacion_izquierda"));
				$this->html->tag("label");
					$this->html->printStaticText("Fuente de datos");//CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR
				$this->html->end("label");
			$this->html->end("div");
			
			$this->html->tag("div", array("class"=>"celda alineacion_izquierda"));
					$this->html->printSelect($this->conexionBDI, "fue_codigo", "fue_nombre", "PSDG_fuentes", "", $this->arreglo_restricciones['rec_fue_codigo'], "", "");
			$this->html->end("div");
		$this->html->end("div");
		
		switch($this->arreglo_restricciones['rec_fue_codigo'])
		{
			case 1://Archivo
				$this->html->tag("div", array("class"=>"fila"));
					$this->html->tag("div", array("class"=>"celda alineacion_izquierda"));
						$this->html->tag("label");
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
		
		$porcentaje_nulos = 0;
		if($this->arreglo_restricciones['rec_porcentaje_nulos'])
			$porcentaje_nulos = $this->arreglo_restricciones['rec_porcentaje_nulos'];		
		
		//NULOS
		$this->html->tag("div", array("class"=>"fila"));
			$this->html->tag("div", array("class"=>"celda alineacion_izquierda"));
				$this->html->tag("label");
					$this->html->printStaticText("Porcentaje valores nulos");//CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR
				$this->html->end("label");
			$this->html->end("div");
			
			$this->html->tag("div", array("class"=>"celda alineacion_izquierda"));
					$this->html->tag("input", array("id"=>"rec_txt_numero_tuplas" ,"type"=>"text", "value"=>$porcentaje_nulos));
			$this->html->end("div");
		$this->html->end("div");
		
		//BOTON
		$this->html->tag("div", array("class"=>"fila"));
			$this->html->tag("input", array("id"=>"rec_btn_establecer" ,"type"=>"button", "value"=>"Establecer", "onclick"=>"establecerRestriccionTabla();"));//CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR
		$this->html->end("div");
		//FIN FORMULARIO
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
