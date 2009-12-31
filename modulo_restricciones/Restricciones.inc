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
				
				foreach($arreglo_meta_datos_columnas AS $numero_columna => $objeto_meta)
				{
					if($objeto_meta->primary_key)
						$rel = "llave";
					else if($objeto_meta->unique_key)
						$rel = "ok";
					else if($objeto_meta->multiple_key)
						$rel = "error";
					else
						$rel = "campo";
						
					$this->html->tag("ul");
						$this->html->tag("li", array("rel"=>$rel));
							$this->html->tag("a", array("onclick"=>"mostrarDetalleCampo('".$nombre_tabla[0]."','".$objeto_meta->name."','".$objeto_meta->type."');"));
								$this->html->tag("ins");
									$this->html->printStaticText("&nbsp;");
								$this->html->end("ins");
								$this->html->tag("label");
									$this->html->printStaticText($objeto_meta->name);
								$this->html->end("label");
							$this->html->end("a");
						$this->html->end("li");
					$this->html->end("ul");
				} 
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
	
	function actualizarRestriccionTabla($nombre_tabla, $numero_tuplas)
	{
		if($numero_tuplas == 0)
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
		$this->conexionBDI->ejecutarSQL($sql); 
	}
	
	function cargarRestriccionesCampo($nombre_tabla, $nombre_campo, $tipo_dato)
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
				$this->html->tag("label", array("id"=>"rec_lbl_nombre_campo"));
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
				$this->html->tag("label", array("id"=>"rec_lbl_nombre_campo"));
					$this->html->printStaticText($this->arreglo_restricciones['rec_tipo_dato']);
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
