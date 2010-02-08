<?php
/*
 This file is part of PSDG.

    PSDG is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
    along with PSDG.  If not, see <http://www.gnu.org/licenses/>.

*/

session_start();

if(isset($_REQUEST['usu_login']) && isset($_REQUEST['usu_password']) && isset($_REQUEST['lang']))
{
	require_once("../conexiones/ConexionBDMySQL.inc");
	
	$parametrosConexion['con_servidor'] = "localhost";
	$parametrosConexion['con_usuario'] = "root";
	$parametrosConexion['con_password'] = "root";
	$parametrosConexion['con_nombre_bd'] = "BDI";
	
	$_SESSION['conexionBDI'] = $parametrosConexion;

	$conexionBDI = new ConexionBDMySQL($_SESSION['conexionBDI']);
  	$conexionBDI->conectar();
	$sql = "	SELECT usu_login
				FROM PSDG_usuario
				WHERE usu_login = '".$_REQUEST['usu_login']."'
				AND usu_password = sha1('".$_REQUEST['usu_password']."')
				LIMIT 1";
	$conexionBDI->ejecutarSQL($sql);

	if($conexionBDI->obtenerNumeroFilas() == 1)
	{
		$_SESSION['lang'] = $_REQUEST['lang'];
		$_SESSION["usu_login"] = $_REQUEST['usu_login'];
		
		require_once("../modulo_conexiones/fm_conexiones.php");
	}
	else 
		echo "-1";
		
}
else
	echo "-1";
?>
