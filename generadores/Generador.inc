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

/**
 * Interfaz para estandarizar los generadores de datos sintéticos.
 * @author	dadagama
 * @since	22-11-2009
 * @version	1.0
 */
abstract class Generador
{
	/**
	 * Arreglo asociativo que almacena la configuración de los parámetros 
	 * adicionales que necesite el generador.
	 * Necesariamente existen los siguientes valores para cualquier generador:
	 * <br/>rec_porcentaje_nulos: probabilidad de que un valor sea nulo.
	 * <br/>rec_fue_codigo: código que representa el tipo de fuente de datos.
	 * <br/>rec_tia_codigo: código que representa el tipo de acceso a los valores.
	 * @var	Array
	 */
	var $_arreglo_parametros;
	
	/**
	 * Objeto de la clase Conexion para establecer comunicación con alguna fuente
	 * externa de valores si el generador lo requiere. Se inicializa con los
	 * valores establecidos en $_arreglo_parametros
	 * @var	Conexion
	 */
	var $_conexion_fuente_externa;
	
	/**
	 * Objeto de la clase Conexion para establecer comunicación con la BDI y 
	 * obtener de allí configuración adicional que sea necesaria para el 
	 * genrador. 
	 * @var	Conexion
	 */
	var $_conexion_BDI;
	
	/**
	 * Objeto del paquete de clases de distribuciones para generar numeros 
	 * aleatorios que tengan una distribucion especifica 
	 * @var	Distribucion
	 */
	var $_generador_numero_aleatorio;
	
	/**
	 * Objeto del paquete de clases de distribuciones para generar numeros 
	 * aleatorios que tengan una distribucion especifica 
	 * @var	Distribucion
	 */
	var $_generador_probabilidad_nulo;
	
	/**
	 * Objeto de la clase Funcion para generar valores apartir de una funcion
	 * prestablecida.
	 * @var	Funcion
	 */
	var $_funcion;
	
	/**
	 * Decide si este generador debe retornar un valor nulo como dato sintético. 
	 * La probabilidad de que se pueda generar este valor esta condicionada por el
	 * valor de la variable de clase $_arreglo_parametros['rec_porcentaje_nulos'].
	 * La función generar() hace uso de este método.
	 * @see		generar()
	 * @return	boolean Retorna true si el generador debe retornar un valor nulo.
	 * 					False en caso contrario.
	 */
	function _debeGenerarValorNulo()
	{
		if($this->_arreglo_parametros['rec_porcentaje_nulos'])
		{
			//genero un numero aleatoriamente (pivote). Si esta por debajo del
			//porcentaje permitido de nulos, se asume entonces que el resultado
			//deberá ser representación nula. en caso contrario, el generador
			//deberá tomar algun valor.
			if(($this->_generador_probabilidad_nulo->generar()*100) < $this->_arreglo_parametros['rec_porcentaje_nulos'])
				return true;
			else
				return false;
		}
		else
			return false;
	}
	

	/**
	 * Se encarga de inicializar las variables de la clase e inicializa la 
	 * conexión con la fuente externa si lo requiere.
	 */
	function _inicializarVariables($arreglo_parametros, &$conexion_BDI)
	{
		$this->_arreglo_parametros = $arreglo_parametros;
		$this->_conexion_BDI = $conexion_BDI;
		//para inicializar acceso por SECUENCIA
		$this->_arreglo_parametros['contador'] = 0;
		require_once ("../distribuciones/DistribucionUniformeAleatoria.inc");
		$this->_generador_probabilidad_nulo = new DistribucionUniformeAleatoria(16807, 0, 2147483641, rand(1,123456789));
		//echo "<br>pruebaxxx".$this->_arreglo_parametros['rec_fue_codigo'];
		switch($this->_arreglo_parametros['rec_fue_codigo'])
		{
			case "1"://none
			break;
			
			case "2"://base de datos
				/*
					------ arreglo_parametros -----
					rec_usu_login
					rec_fue_codigo
					rec_porcentaje_nulos
					rec_nombre_conexion
					rec_nombre_tabla
					rec_nombre_campo
					rec_tia_codigo
					---
					con_servidor
					con_nombre_bd
					con_usuario
					con_password
				*/				
				$sql = "SELECT con_parametros 
						FROM PSDG_conexion 
						WHERE con_nombre = '".$this->_arreglo_parametros['rec_nombre_conexion']."'
						AND con_usu_login = '".$this->_arreglo_parametros['rec_usu_login']."'
						LIMIT 1"; 
				//echo "<br>SQL BD: $sql";
				$this->_conexion_BDI->ejecutarSQL($sql);
				$con_parametros = $this->_conexion_BDI->obtenerFilaComoCadena();
				//echo "<br>-****->$con_parametros";
				$parametros_conexion_fuente_externa = json_decode($con_parametros, true);
				$this->_conexion_fuente_externa = new ConexionBDMySQL($parametros_conexion_fuente_externa);
				$this->_conexion_fuente_externa->conectar();
				break;
				
			case "3"://biblioteca
				/*
					------ arreglo_parametros -----
					rec_usu_login
					rec_fue_codigo
					rec_porcentaje_nulos
					rec_conexion_biblioteca
					rec_tipo_campo_biblioteca
					rec_nombre_campo_independiente
					rec_nombre_campo_biblioteca
					rec_tia_codigo
					---
					con_nombre_biblioteca_tabla	
					con_nombre_campo_tabla_independiente			
				*/
				$sql = "SELECT con_parametros 
						FROM PSDG_conexion 
						WHERE con_nombre = '".$this->_arreglo_parametros['rec_conexion_biblioteca']."'
						AND con_usu_login = '".$this->_arreglo_parametros['rec_usu_login']."'
						LIMIT 1";
				//echo "<br>SQL BIBLLIOTECA: $sql";
				$this->_conexion_BDI->ejecutarSQL($sql);
				$con_parametros = $this->_conexion_BDI->obtenerFilaComoCadena();
				$parametros_conexion_biblioteca = json_decode($con_parametros, true);
				$this->_arreglo_parametros['con_nombre_biblioteca_tabla'] = $parametros_conexion_biblioteca['con_nombre_biblioteca_tabla'];
				$campos_tabla_biblioteca = $this->_conexion_BDI->obtenerNombresCamposTablaBD($this->_arreglo_parametros['con_nombre_biblioteca_tabla']);
				$this->_arreglo_parametros['con_nombre_campo_tabla_independiente'] = $campos_tabla_biblioteca[0][0];
				//se conecta a la BDI, porque alli mismo estan los valores
				$this->_conexion_fuente_externa = $this->_conexion_BDI;
				//se establece el rango una sola vez
				$this->_establecerRangoValoresFuenteExterna($this->_arreglo_parametros['con_nombre_biblioteca_tabla'], $this->_arreglo_parametros['rec_nombre_campo_biblioteca']);
				break;
				
			case "7"://archivo
				/*
					------ arreglo_parametros -----
					rec_usu_login
					rec_fue_codigo
					rec_porcentaje_nulos
					rec_conexion_archivo
					rec_tia_codigo
					---
					con_nombre_archivo_tabla
				*/
				$sql = "SELECT con_parametros 
						FROM PSDG_conexion 
						WHERE con_nombre = '".$this->_arreglo_parametros['rec_conexion_archivo']."'
						AND con_usu_login = '".$this->_arreglo_parametros['rec_usu_login']."'
						LIMIT 1"; 
				//echo "<br>SQL ARCHIVO: $sql";
				$this->_conexion_BDI->ejecutarSQL($sql);
				$con_parametros = $this->_conexion_BDI->obtenerFilaComoCadena();
				$parametros_conexion_archivo = json_decode($con_parametros, true);
				$this->_arreglo_parametros['con_nombre_archivo_tabla'] = $parametros_conexion_archivo['con_nombre_archivo_tabla']; 
				//se conecta a la BDI, porque alli mismo estan los valores
				$this->_conexion_fuente_externa = $this->_conexion_BDI;
				//se establece el rango una sola vez
				$this->_establecerRangoValoresFuenteExterna($this->_arreglo_parametros['con_nombre_archivo_tabla'], 'valor');
			break;

			case "4"://lista de valores
				/*
					------ arreglo_parametros -----
					rec_usu_login
					rec_fue_codigo
					rec_porcentaje_nulos
					rec_nombre_tabla_lista_valores
					rec_tia_codigo
				*/
				//se conecta a la BDI, porque alli mismo estan los valores
				$this->_conexion_fuente_externa = $this->_conexion_BDI;
				//se establece el rango una sola vez
				$this->_establecerRangoValoresFuenteExterna($this->_arreglo_parametros['rec_nombre_tabla_lista_valores'], 'valores');
			break;
			
			case "5"://constante
				/*
					------ arreglo_parametros -----
					rec_usu_login
					rec_fue_codigo
					rec_porcentaje_nulos
					rec_valor_constante
				 */
				$this->_valor_constante = $this->_arreglo_parametros['rec_valor_constante'];
				//no hay conexion externa
			break;
			
			case "9"://funcion
				/*	
					------ arreglo_parametros -----
					rec_usu_login
					rec_fue_codigo
					rec_porcentaje_nulos
					rec_fun_codigo
				*/
				switch($this->_arreglo_parametros['rec_fun_codigo'])
				{
					case 1://luhn bigint
					case 2://luhn varchar
						require_once ("../funciones/Luhn.inc");
						$this->_funcion = new Luhn();
					break;
					
					case 3://gibberish text
					case 4://gibberish varchar
						/*
						 	rec_markov_order
							rec_markov_length
							rec_markov_input
						 */
						require_once ("../funciones/Markov.inc");
						$this->_funcion = new Markov($this->_arreglo_parametros['rec_markov_order'], $this->_arreglo_parametros['rec_markov_length'], $this->_arreglo_parametros['rec_markov_input']);
					break;
				}
				//no hay conexion externa
			break;
						
		}
		if($this->_arreglo_parametros['rec_fup_codigo'] == 1)//Uniforme
		{
			require_once ("../distribuciones/DistribucionUniformeAleatoria.inc");
			$this->_generador_numero_aleatorio = new DistribucionUniformeAleatoria(16807, 0, 2147483641, rand(1,123456789));
		}
		else if($this->_arreglo_parametros['rec_fup_codigo'] == 2)//Normal estandar
		{
			require_once ("../distribuciones/DistribucionNormalEstandar.inc");
			$media = $this->_arreglo_parametros['rec_media'];
			$desviacion = $this->_arreglo_parametros['rec_desviacion_estandar'];
			$this->_generador_numero_aleatorio = new DistribucionNormalEstandar($media, $desviacion);
		}
		else if($this->_arreglo_parametros['rec_fup_codigo'] == 3)//Exponencial
		{
			require_once ("../distribuciones/DistribucionExponencial.inc");
			$lambda = $this->_arreglo_parametros['rec_lambda'];
			$this->_generador_numero_aleatorio = new DistribucionExponencial($lambda);
		}
	}
	
	/**
	 * Función auxiliar que actualiza el valor de la variable de clase 
	 * $_numero_valores_posibles, donde se almacena la cantidad de registros de 
	 * la que dispone la tabla de donde se sacaran los valores.
	 * esta fución es utilizada por _generarDesdeTabla();
	 * @see		_generarDesdeTabla()
	 * @param	$nombre_tabla	nombre de la tabla donde se conecta.
	 * @param	$nombre_campo	nombre del campo de la tabla donde se encuentran los 
	 * 							valores.
	 */
	function _establecerRangoValoresFuenteExterna($nombre_tabla, $nombre_campo)
	{
		if($this->_conexion_fuente_externa)
		{
			$sql = "SELECT count($nombre_campo) FROM $nombre_tabla AS rango";
			$this->_conexion_fuente_externa->ejecutarSQL($sql);
			$rango = $this->_conexion_fuente_externa->obtenerFilaComoArreglo();
			$this->_arreglo_parametros['numero_valores_posibles'] = $rango[0];
		}
	}
	
	/**
	 * Genera un dato sintético representado en forma de cadena cumple con
	 * las restricciones impuestas en la inicializacion.
	 * @see		inicializarParametros($arregloParametros)
	 * @return	string	Dato sintético generado.
	 */
	function generar(&$arreglo_memoria="")
	{
		if($this->_debeGenerarValorNulo())
			return "@null";
		//echo "<br>FUENTE: ".$this->_arreglo_parametros['rec_fue_codigo'];
		switch($this->_arreglo_parametros['rec_fue_codigo'])
		{
			case "1"://none
			break;
			
			case "2"://base de datos
				return $this->_generarDesdeBD();
			break;
			
			case "3"://biblioteca
				return $this->_generarDesdeBiblioteca($arreglo_memoria);
			break;
			
			case "4"://lista de valores
				return $this->_generarDesdeLista();
			break;
			
			case "5"://constante
				return $this->_generarDesdeConstante();
			break;

			case "7"://archivo
				return $this->_generarDesdeArchivo();
			break;
			
			case "9"://funcion
				return $this->_generarDesdeFuncion();
			break;
		}
	}
		
	/**
	 * Función auxiliar que genera un dato sintético apartir de una tabla.<br/>
	 * Utiliza el objeto de la clase $_conexion_fuente_externa para obtener los
	 * valores de la tabla.<br/>
	 * Si es secuencial se generarán empezando desde el primer registro de la 
	 * tabla. Si se llega al último registro y se necesitan generar más valores, 
	 * se siguen generando partiendo nuevamente desde el primer registro de la
	 * tabla. La función generar() hace uso de este método.
	 * @see		generar()
	 * @param	$nombre_tabla	nombre de la tabla donde se conecta.
	 * @param	$nombre_campo	nombre del campo de la tabla donde se encuentran los 
	 * 							valores.
	 * @return	string	Dato sintético generado. Su valor es uno de los 
	 * 					registros contenidos en la tabla.
	 */
	function _generarDesdeTabla($nombre_tabla, $nombre_campo, $where="")
	{
		//si es fuente BD, el rango de valores es dinamico en cada iteracion
		//se debe recalcular
		if($this->_arreglo_parametros['rec_fue_codigo'] == "2")
			$this->_establecerRangoValoresFuenteExterna($nombre_tabla, $nombre_campo);
		//echo "<br>_generarDesdeTabla: $nombre_tabla -> $nombre_campo : ";
		//print_r($this->_arreglo_parametros);
		if($where)//es campo dependiente de biblioteca
		{
			$sql = "SELECT $nombre_campo FROM $nombre_tabla WHERE $where LIMIT 1";
			//echo "<br>$sql";
			$this->_conexion_fuente_externa->ejecutarSQL($sql);
			return $this->_conexion_fuente_externa->obtenerFilaComoCadena();
		}
		else
		{
			switch($this->_arreglo_parametros['rec_tia_codigo'])
			{
				case "1"://Secuencial
					$sql = "SELECT $nombre_campo FROM $nombre_tabla LIMIT ".$this->_arreglo_parametros['contador'].",1";
					//echo "<br>SECUENCIAL! ".$sql;
					$this->_conexion_fuente_externa->ejecutarSQL($sql);
					//echo "<br>SECUENCIAL! ".$this->_arreglo_parametros['numero_valores_posibles']." --".$this->_arreglo_parametros['contador'];
					//actualizo posicion contador
					if($this->_arreglo_parametros['contador'] == $this->_arreglo_parametros['numero_valores_posibles'] - 1)
						$this->_arreglo_parametros['contador'] = 0;
					else
						$this->_arreglo_parametros['contador']++;
					
					return $this->_conexion_fuente_externa->obtenerFilaComoCadena();
					break;
				
				case "2"://Aleatorio
					$this->_arreglo_parametros['contador'] = rand(0,$this->_arreglo_parametros['numero_valores_posibles'] - 1);
					$sql = "SELECT $nombre_campo FROM $nombre_tabla LIMIT ".$this->_arreglo_parametros['contador'].",1";
					//echo "<br>".$sql;
					$this->_conexion_fuente_externa->ejecutarSQL($sql);
					return $this->_conexion_fuente_externa->obtenerFilaComoCadena();
					break;
				
				case "3"://Probabilistico
					if($this->_arreglo_parametros['rec_fup_codigo'] == 1)//Uniforme
					{
						$this->_arreglo_parametros['contador'] = floor($this->_generador_numero_aleatorio->generar() * $this->_arreglo_parametros['numero_valores_posibles']);
					}
					else if($this->_arreglo_parametros['rec_fup_codigo'] == 2)//Normal estandar
					{
						do
							$this->_arreglo_parametros['contador'] = floor($this->_generador_numero_aleatorio->generar());
						while($this->_arreglo_parametros['contador'] < 0 || $this->_arreglo_parametros['contador'] >= $this->_arreglo_parametros['numero_valores_posibles']);
					}
					else if($this->_arreglo_parametros['rec_fup_codigo'] == 3)//Exponencial
					{
						do
							$this->_arreglo_parametros['contador'] = floor($this->_generador_numero_aleatorio->generar());
						while($this->_arreglo_parametros['contador'] < 0 || $this->_arreglo_parametros['contador'] >= $this->_arreglo_parametros['numero_valores_posibles']);
					}
					$sql = "SELECT $nombre_campo FROM $nombre_tabla LIMIT ".$this->_arreglo_parametros['contador'].",1";
//					echo "************".$sql;
					$this->_conexion_fuente_externa->ejecutarSQL($sql);
					return $this->_conexion_fuente_externa->obtenerFilaComoCadena();
					break;
			}
		}
	}
	
	/**
	 *Se encarga de generar un dato sintético apartir de los valores de la lista.
	 * <br/>Si es secuencial se generarán empezando desde el primer valor de la 
	 * lista. Si se llega al último valor y se necesitan generar más valores, 
	 * se siguen generando partiendo nuevamente desde el primer valor de la
	 * lista. La función generar() hace uso de este método.
	 * @see		generar()
	 * @return	string	Dato sintético generado.
	 */
	function _generarDesdeLista()
	{
		/*
			------ arreglo_parametros -----
			rec_usu_login
			rec_fue_codigo
			rec_porcentaje_nulos
			rec_nombre_tabla_lista_valores
			rec_tia_codigo
		*/
		//echo "<br>generarDesdeLista! tabla: $nombre_tabla";
		return $this->_generarDesdeTabla($this->_arreglo_parametros['rec_nombre_tabla_lista_valores'], "valores");
	}
		
	/**
	 * Se encarga de generar un dato sintético utilizando el objeto de la clase 
	 * $_conexion_fuente_externa para valores provenientes de un archivo.y apartir
	 * de las restricciones establecidas en la variable de la clase
	 * $_arreglo_parametros['esSecuencial'] para determinar si se debe acceder de
	 * manera secuencial ó aleatoria a los valores del archivo. Si es secuencial
	 * se generarán empezando desde la primera palabra del archivo. Si se llega 
	 * la última palabra y se necesitan generar más valores, se siguen generando 
	 * partiendo nuevamente desde la primera palabra del archivo. La función 
	 * generar() hace uso de este método.
	 * @see		generar()
	 * @return	string	Dato sintético generado. Su valor es una palabra 
	 * 					contenida en el archivo.
	 */
	function _generarDesdeArchivo()
	{
		/*
			------ arreglo_parametros -----
			rec_usu_login
			rec_fue_codigo
			rec_porcentaje_nulos
			rec_conexion_archivo
			rec_tia_codigo
			---
			con_nombre_archivo_tabla
		*/
		return $this->_generarDesdeTabla($this->_arreglo_parametros['con_nombre_archivo_tabla'], "valor");
	}
	
	/**
	 * Se encarga de generar un dato sintético utilizando el objeto de la clase 
	 * $_conexion_fuente_externa para establecer las conexión con la tabla que 
	 * contiene los valores para las restricciones condicionales. La función
	 * generar() hace uso de este método.
	 * @see		generar()
	 * @return	string	Dato sintético generado. Su valor es el primero de la 
	 * 					lista de valores que satisface la condición establecida.
	 */
//	function generarDesdeCondicionesAvanzadas()
//	{
//		//:S
//	}
	
	/**
	 * Se encarga de generar un dato sintético utilizando el objeto de la clase 
	 * $_conexion_fuente_externa para valores provenientes de una BD. 
	 * Si es secuencial se generarán empezando desde el primer registro de la 
	 * tabla. Si se llega al último registro y se necesitan generar más valores, 
	 * se siguen generando partiendo nuevamente desde el primer registro de la
	 * tabla. La función generar() hace uso de este método.
	 * @see		generar()
	 * @return	string	Dato sintético generado. Su valor es un registro 
	 * 					contenido en la tabla de la BD.
	 */
	function _generarDesdeBD()
	{
		/*
			------ arreglo_parametros -----
			rec_usu_login
			rec_fue_codigo
			rec_porcentaje_nulos
			rec_nombre_conexion
			rec_nombre_tabla
			rec_nombre_campo
			rec_tia_codigo
			---
			con_servidor
			con_nombre_bd
			con_usuario
			con_password
		*/				
		return $this->_generarDesdeTabla($this->_arreglo_parametros['rec_nombre_tabla'], $this->_arreglo_parametros['rec_nombre_campo']);
	}
	
	/**
	 * Se encarga de generar un dato sintético utilizando el objeto de la clase 
	 * $_conexion_fuente_externa para valores provenientes de una biblioteca. 
	 * Si es secuencial se generarán empezando desde el primer registro de la 
	 * biblioteca. Si se llega al último registro y se necesitan generar más 
	 * valores, se siguen generando partiendo nuevamente desde el primer 
	 * registro de la biblioteca. La función generar() hace uso de este método.
	 * @see		generar()
	 * @return	string	Dato sintético generado. Su valor es un registro 
	 * 					contenido en la biblioteca.
	 */
	function _generarDesdeBiblioteca(&$arreglo_memoria)
	{
		/*
			------ arreglo_parametros -----
			rec_usu_login
			rec_fue_codigo
			rec_porcentaje_nulos
			rec_conexion_biblioteca
			rec_tipo_campo_biblioteca
			rec_nombre_campo_independiente
			rec_nombre_campo_biblioteca
			rec_tia_codigo
			---
			con_nombre_biblioteca_tabla			
			con_nombre_campo_tabla_independiente		
		*/
		
//		$sql = "SELECT rec_parametros_tipo_fuente 
//				FROM PSDG_restricciones_campos 
//				WHERE rec_usu_login = '".$this->_arreglo_parametros['rec_usu_login']."'
//				AND rec_nombre_campo = '".$this->_arreglo_parametros['rec_nombre_campo_independiente']."'";
//	echo "<pre>";	
//	print_r($this->_arreglo_parametros);
		//rec_nombre_campo_biblioteca biblioteca 
		$this->_conexion_BDI->ejecutarSQL($sql);
		if($this->_arreglo_parametros['rec_nombre_campo_independiente'])
			$where = $this->_arreglo_parametros['con_nombre_campo_tabla_independiente']." = '".$arreglo_memoria[$this->_arreglo_parametros['rec_nombre_campo_independiente']]."'";
		//INCOMPLETO, FALTA DEFINIR DE QUE CAMPO DEPENDE Y ASI MISMO OBTENER 
		//EL VALOR DE LA TABLA... POR ENDE MODIFICAR FIRMA DE METODO
		//_generarDesdeTabla($tabla, $campo, $where);
		//si existe where, es que viene de biblioteca y no se aplica el tia_codigo
		//porque la busqueda es directa.
//		echo "<br>WHERE!! $where";
		return $this->_generarDesdeTabla($this->_arreglo_parametros['con_nombre_biblioteca_tabla'], $this->_arreglo_parametros['rec_nombre_campo_biblioteca'], $where);		
	}
	
	/**
	 * Se encarga de generar un dato sintético desde un valor constante. La 
	 * función generar() hace uso de este método.
	 * @see		generar()
	 * @return	string	Dato sintético generado. Su valor es la constante
	 * 					definida.
	 */
	function _generarDesdeConstante()
	{
		/*
			------ arreglo_parametros -----
			rec_usu_login
			rec_fue_codigo
			rec_porcentaje_nulos
			rec_valor_constante
		 */
		return $this->_arreglo_parametros['rec_valor_constante'];
	}
	
	/**
	 * Se encarga de generar un dato sintético apartir de una funcion. 
	 * La función generar() hace uso de este método.
	 * @see		generar()
	 * @return string	Dato sintético generado.
	 */
	function _generarDesdeFuncion()
	{
		return $this->_funcion->generar();
	}
}
?>
