<?php 

require_once("../conexiones/ConexionBDMySQL.inc");
require_once("../herramientas/GeneradorHtml.inc");
	
class Restricciones
{
	var $conexionBDI;
	var $conexionBDO;		
	var $usu_login;
	var $html;
	
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
						$rel = "ok";
					else
						$rel = "campo";
						
					$this->html->tag("ul");
						$this->html->tag("li", array("rel"=>$rel));
							$this->html->tag("a", array("onclick"=>"mostrarDetalleCampo('".$objeto_meta->name."');"));
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
}
?>
