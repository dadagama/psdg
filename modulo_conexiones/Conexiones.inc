<?php 
/*
 This file is part of PSDG.

    PSDG is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    PSDG is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
    along with PSDG.  If not, see <http://www.gnu.org/licenses/>.

*/


require_once("../conexiones/ConexionBDMySQL.inc");

class Conexiones
{
	var $conexionBDI;	
	var $conexion_de_prueba;
	var $usu_login;
	
	function __construct($parametrosConexion,$login)
	{
		$this->conexionBDI = new ConexionBDMySQL($parametrosConexion);
  		$this->conexionBDI->conectar();
  		$this->usu_login = $login;
	}

	function existeRegistroBDO()
	{
		$sql = "	SELECT con_fue_codigo
					FROM PSDG_conexion
					WHERE con_fue_codigo = '2'
					AND con_usu_login = '".$this->usu_login."'
					AND con_nombre = 'BDO'
					LIMIT 1";

		$this->conexionBDI->ejecutarSQL($sql);
		if($this->conexionBDI->obtenerNumeroFilas() == 1)
			return true;
		else
			return false;
	}
	
	function insertarConexion($con_nombre, $con_tipo, $parametros_conexion)
	{
		//$this->conexionBDI->conectar();//se quito pero no se ha probado nuevamente si realmente no se necesita
		$sql = "	INSERT INTO PSDG_conexion
			VALUES (	'".$con_nombre."',
						'".$this->usu_login."',
						'".$con_tipo."',
						'$parametros_conexion'
			)";
//echo $sql;
		$this->conexionBDI->ejecutarSQL($sql);
		return $this->conexionBDI->obtenerResultset();
	}
	
	function crearTablaConexionExterna($con_nombre, $tipo_conexion, $nombre_archivo, $nombres_campos = "")
	{
		$campos = "";
		if(isset($nombres_campos) && $nombres_campos && $tipo_conexion == "3")
		{
			$nombres = explode(",", $nombres_campos);
			for($x = 0; $x < count($nombres); $x++)
				if($x < count($nombres)-1)
					$campos .= $nombres[$x]." TEXT COLLATE utf8_unicode_ci,";
				else
					$campos .= $nombres[$x]." TEXT COLLATE utf8_unicode_ci";
		}
		else
			$campos = "valor TEXT";
	
		$sql = "	CREATE TABLE ".$this->usu_login."_".$tipo_conexion."_".$con_nombre."
			($campos) ENGINE = InnoDB COMMENT = 'create by $nombre_archivo'";
		//echo $sql;
		$this->conexionBDI->ejecutarSQL($sql);
		return $this->conexionBDI->obtenerResultset();
	}
	
	function insertarValoresEnTabla($con_nombre, $tipo_conexion, $valores)
	{
		foreach($valores as $valor)
			$vals[] = "'".$valor."'";

		$vals = implode(",", $vals);
		$vals = utf8_decode($vals);
		
		$sql = "	INSERT INTO ".$this->usu_login."_".$tipo_conexion."_".$con_nombre."
			VALUES ($vals)";
		//echo "\n".$vals;
		$this->conexionBDI->ejecutarSQL($sql);
		return $this->conexionBDI->obtenerResultset();
	}
	
	function obtenerArregloInfoConexiones()
	{
		$sql = "	SELECT con_nombre, con_fue_codigo
					FROM PSDG_conexion";
		$this->conexionBDI->ejecutarSQL($sql);
		return $this->conexionBDI->obtenerResultadoComoArreglo();
	}
	
	function eliminarConexion($con_nombre,$con_tipo)
	{
		$sql = "DROP TABLE IF EXISTS ".$this->usu_login."_".$con_tipo."_".$con_nombre;
		$this->conexionBDI->ejecutarSQL($sql);

		$sql = "	DELETE 
					FROM PSDG_conexion
					WHERE con_nombre = '".$con_nombre."'
					AND con_fue_codigo = '".$con_tipo."'
					AND con_usu_login = '".$this->usu_login."'";
		$this->conexionBDI->ejecutarSQL($sql);
		return $this->conexionBDI->obtenerResultset();
	}
	
	function conexionValida($con_servidor,$con_usuario_bd,$con_password_bd,$con_nombre_bd)
	{
		$parametros['con_servidor'] = $con_servidor;
		$parametros['con_usuario'] = $con_usuario_bd;
		$parametros['con_password'] = $con_password_bd;
		$parametros['con_nombre_bd'] = $con_nombre_bd;
		$this->conexion_de_prueba = new ConexionBDMySQL($parametros);
		if($this->conexion_de_prueba->conectar())
		{
			$this->conexion_de_prueba->desconectar();
			$this->conexion_de_prueba = "";
			return true;
		}
		else
		{
			return false;
		}
	}
}
?>
