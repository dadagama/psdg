<?php
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
	 * Número enterno que almacena la cantidad de valores que puede tomar el 
	 * generador, con el fin de establecer las restricciones a los generadores
	 * aleatorios internos.
	 * @var	int
	 */
	var $_numero_valores_posibles;
	
	/**
	 * Número enterno que almacena un contador. permite ubicar la posicion del
	 * siguiente valor a retornar en un generador por secuencia.
	 * @var	int
	 */
	var $_contador;
	
	/**
	 * Bandera que indica si la fuente de datos que utiliza el generador cambia
	 * su cantidad de valores posibles durante la generación
	 * @var	boolean
	 */
	var $_es_fuente_de_rango_dinamico;
	
	/**
	 * Número enterno que almacena la probabilidad de generar un valor nulo.
	 * @var	int
	 */
	var $_porcentaje_nulos;
	
	/**
	 * Número enterno que que identifica el codigo de la fuente de datos a usar 
	 * con el generador.
	 * @var	int
	 */
	var $_fuente_datos;
	
	/**
	 * Cadena que almacena el nombre del usuario que invoca este generador.
	 * @var	string
	 */
	var $_usu_login; 
	
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
		if($this->_porcentaje_nulos)
		{
			//genero un numero aleatoriamente (pivote). Si esta por debajo del
			//porcentaje permitido de nulos, se asume entonces que el resultado
			//deberá ser representación nula. en caso contrario, el generador
			//deberá tomar algun valor.
			require_once ("../distribuciones/DistribucionUniformeAleatoria.inc");
			$generador_numero_aleatorio = new DistribucionUniformeAleatoria(16807, 0, 2147483641, rand(1,123456789));
			$numero_aleatorio = $generador_numero_aleatorio->generar();
			if($numero_aleatorio < $this->_porcentaje_nulos)
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
	function _inicializarVariables($arregloParametros, &$conexion_BDI, $rec_porcentaje_nulos)
	{
		$this->_arreglo_parametros = $arregloParametros;
		$this->_conexion_BDI = $conexion_BDI;
		$this->_porcentaje_nulos = $rec_porcentaje_nulos;
		$this->_fuente_datos = $this->_arreglo_parametros['rec_fue_codigo'];
		$this->_usu_login = $this->_arreglo_parametros['rec_usu_login'];
		//if($this->_arreglo_parametros['rec_tia_codigo'] == 1)
		$this->_contador =  0;
		
		switch($this->_fuente_datos)
		{
			case "1"://none
			break;
			
			case "2"://base de datos
				//restriccion
				//{"rec_nombre_conexion":"BDO","rec_nombre_tabla":"aulas_por_escuela","rec_nombre_campo":"id_escuela","rec_tia_codigo":"1"}
				//conexion
				//{"con_servidor":"localhost","con_nombre_bd":"colegio","con_usuario":"root","con_password":"root"}
				$nombre_conexion = $this->_arreglo_parametros['rec_nombre_conexion'];
				$this->_es_fuente_de_rango_dinamico = true;					
				$sql = "SELECT con_parametros 
						FROM conexion 
						WHERE con_nombre = '$nombre_conexion'
						AND con_usu_login = '".$this->_usu_login."'
						LIMIT 1"; 
				$this->_conexion_BDI->ejecutarSQL($sql);
				$con_parametros = $this->_conexion_BDI->obtenerFilaComoCadena();
				$parametros_conexion_fuente_externa = json_decode($con_parametros, true);
				$this->_conexion_fuente_externa = new ConexionBDMySQL($parametros_conexion_fuente_externa);
				$this->_conexion_fuente_externa->conectar();
				break;
				
			case "3"://biblioteca
				//restriccion
				//{"rec_conexion_biblioteca":"biblio","rec_tipo_campo_biblioteca":"1","rec_nombre_campo_biblioteca":"nivel","rec_tia_codigo":"1"}
				//conexion
				//{"con_nombre_biblioteca_tabla":"demo_3_biblio"}
				$nombre_conexion = $this->_arreglo_parametros['rec_conexion_biblioteca'];
				$this->_es_fuente_de_rango_dinamico = false;
				$sql = "SELECT con_parametros 
						FROM conexion 
						WHERE con_nombre = '$nombre_conexion'
						AND con_usu_login = '".$this->_usu_login."'
						LIMIT 1"; 
				$this->_conexion_BDI->ejecutarSQL($sql);
				$con_parametros = $this->_conexion_BDI->obtenerFilaComoCadena();
				$parametros_conexion_biblioteca = json_decode($con_parametros, true);
				$this->_arreglo_parametros['con_nombre_biblioteca_tabla'] = $parametros_conexion_biblioteca['con_nombre_biblioteca_tabla'];
				break;
				
			case "7"://archivo
				//restriccion
				//{"rec_conexion_archivo":"archivo","rec_tia_codigo:"1"}
				//conexion
				//{"con_nombre_archivo_tabla":"demo_7_archivo"}
				$nombre_conexion = $this->_arreglo_parametros['rec_conexion_archivo'];
				$this->_es_fuente_de_rango_dinamico = false;
				$sql = "SELECT con_parametros 
						FROM conexion 
						WHERE con_nombre = '$nombre_conexion'
						AND con_usu_login = '".$this->_usu_login."'
						LIMIT 1"; 
				$this->_conexion_BDI->ejecutarSQL($sql);
				$con_parametros = $this->_conexion_BDI->obtenerFilaComoCadena();
				$parametros_conexion_archivo = json_decode($con_parametros, true);
				$this->_arreglo_parametros['con_nombre_archivo_tabla'] = $parametros_conexion_archivo['con_nombre_archivo_tabla'];
				//se conecta a la BDI, porque alli mismo estan los valores
				$this->_conexion_fuente_externa = $this->_conexion_BDI;
			break;

			case "4"://lista de valores
				//restriccion
				//{"rec_nombre_tabla_lista_valores":"demo_4_matricula_curso","rec_tia_codigo":"1"}
				//se conecta a la BDI, porque alli mismo estan los valores
				$this->_conexion_fuente_externa = $this->_conexion_BDI;
				$this->_es_fuente_de_rango_dinamico = true;
			break;
			
			case "5"://constante
				$this->_es_fuente_de_rango_dinamico = false;
			break;
			
			case "9"://condicionales
				//creo :S
				$this->_es_fuente_de_rango_dinamico = true;
			break;
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
		if($this->_conexion_fuente_externa && $this->_es_fuente_de_rango_dinamico)
		{
			$sql = "SELECT count($nombre_campo) FROM $nombre_tabla AS rango";
			$this->_conexion_fuente_externa->ejecutarSQL($sql);
			$rango = $this->_conexion_fuente_externa->obtenerFilaComoArreglo();
			$this->_numero_valores_posibles = $rango[0];
		}
	}
	
	/**
	 * Genera un dato sintético representado en forma de cadena que cumple con
	 * las restricciones impuestas en la inicializacion.
	 * @see		inicializarParametros($arregloParametros)
	 * @return	string	Dato sintético generado.
	 */
	function generar()
	{
	//echo "<br>FUENTE: ".$this->_fuente_datos;
		switch($this->_fuente_datos)
		{
			case "1"://none
			break;
			
			case "2"://base de datos
				return $this->_generarDesdeBD();
			break;
			
			case "3"://biblioteca
				return $this->_generarDesdeBiblioteca();
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

			case "9"://condicionales
				return $this->generarDesdeCondicionesAvanzadas();
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
	function _generarDesdeTabla($nombre_tabla, $nombre_campo)
	{
		$this->_establecerRangoValoresFuenteExterna($nombre_tabla, $nombre_campo);
		//echo "<br>_generarDesdeTabla: fue:".$this->_arreglo_parametros['rec_tia_codigo'];
		switch($this->_arreglo_parametros['rec_tia_codigo'])
		{
			case "1"://Secuencial
				$sql = "SELECT $nombre_campo FROM $nombre_tabla LIMIT ".$this->_contador.",1";
				//echo "<br>SECUENCIAL! ".$sql;
				$this->_conexion_fuente_externa->ejecutarSQL($sql);
				//echo "<br>SECUENCIAL! ".$this->_numero_valores_posibles." --".$this->_contador;
				//actualizo posicion contador
				if($this->_contador == $this->_numero_valores_posibles - 1)
					$this->_contador = 0;
				else
					$this->_contador++;
				
				return $this->_conexion_fuente_externa->obtenerFilaComoCadena();
				break;
			
			case "2"://Aleatorio
				$this->_contador = rand(0,$this->_numero_valores_posibles);
				$sql = "SELECT $nombre_campo FROM $nombre_tabla LIMIT ".$this->_contador.",1";
				$this->_conexion_fuente_externa->ejecutarSQL($sql);
				return $this->_conexion_fuente_externa->obtenerFilaComoCadena();
				break;
			
			case "3"://Probabilistico
				if($this->_arreglo_parametros['rec_fup_codigo'] == 1)//Uniforme
				{
					require_once ("../distribuciones/DistribucionUniformeAleatoria.inc");
					$generador_numero_aleatorio = new DistribucionUniformeAleatoria(16807, 0, 2147483641, rand(1,123456789));
					$this->_contador = floor($generador_numero_aleatorio->generar() * $this->_numero_valores_posibles);
				}
				else if($this->_arreglo_parametros['rec_fup_codigo'] == 2)//Normal estandar
				{
					require_once ("../distribuciones/DistribucionNormalEstandar.inc");
					$media = $this->_arreglo_parametros['rec_media'];
					$desviacion = $this->_arreglo_parametros['rec_desviacion'];
					$generador_numero_aleatorio = new DistribucionNormalEstandar($media, $desviacion);
					$this->_contador = -1;
					do
						$this->_contador = $generador_numero_aleatorio->generar();
					while($this->_contador < 0 || $this->_contador >= $this->_numero_valores_posibles);
				}
				else if($this->_arreglo_parametros['rec_fup_codigo'] == 3)//Exponencial
				{
					require_once ("../distribuciones/DistribucionExponencial.inc");
					$lambda = $this->_arreglo_parametros['rec_lambda'];
					$generador_numero_aleatorio = new DistribucionExponencial($lambda);
					$this->_contador = -1;
					do
						$this->_contador = $generador_numero_aleatorio->generar();
					while($this->_contador < 0 || $this->_contador >= $this->_numero_valores_posibles);
				}
				$sql = "SELECT $nombre_campo FROM $nombre_tabla LIMIT ".$this->_contador.",1";
				$this->_conexion_fuente_externa->ejecutarSQL($sql);
				return $this->_conexion_fuente_externa->obtenerFilaComoCadena();
				break;
		}
		//$this->_conexion_fuente_externa->ejecutarSQL($sql);
		//= $this->_conexion_BDI->obtenerFilaComoCadena();
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
		//restriccion
		//{"rec_nombre_tabla_lista_valores":"demo_4_matricula_curso","rec_tia_codigo":"1"}
		$nombre_tabla = $this->_arreglo_parametros['rec_nombre_tabla_lista_valores'];
		//echo "<br>generarDesdeLista! tabla: $nombre_tabla";
		return $this->_generarDesdeTabla($nombre_tabla, "valores");
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
		//restriccion
		//{"rec_conexion_archivo":"archivo","rec_tia_codigo:"1"}
		//conexion
		//{"con_nombre_archivo_tabla":"demo_7_archivo"}
		$nombre_tabla = $this->_arreglo_parametros['con_nombre_archivo_tabla'];
		return $this->_generarDesdeTabla($nombre_tabla, "valor");
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
	function generarDesdeCondicionesAvanzadas()
	{
		//falta
	}
	
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
		//restriccion
		//{"rec_nombre_conexion":"BDO","rec_nombre_tabla":"aulas_por_escuela","rec_nombre_campo":"id_escuela","rec_tia_codigo":"1"}
		//conexion
		//{"con_servidor":"localhost","con_nombre_bd":"colegio","con_usuario":"root","con_password":"root"}
		$nombre_tabla = $this->_arreglo_parametros['rec_nombre_tabla'];
		$nombre_campo = $this->_arreglo_parametros['rec_nombre_campo'];
		return $this->_generarDesdeTabla($nombre_tabla, $nombre_campo);
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
	function _generarDesdeBiblioteca()
	{
		//restriccion
		//{"rec_conexion_biblioteca":"biblio","rec_tipo_campo_biblioteca":"1","rec_nombre_campo_biblioteca":"nivel","rec_tia_codigo":"1"}
		//conexion
		//{"con_nombre_biblioteca_tabla":"demo_3_biblio"}
		$nombre_tabla = $this->_arreglo_parametros['con_nombre_biblioteca_tabla'];
		$nombre_campo = $this->_arreglo_parametros['rec_nombre_campo_biblioteca'];
		return $this->_generarDesdeTabla($nombre_tabla, "valor");
		
		//INCOMPLETO, FALTA DEFINIR DE QUE CAMPO DEPENDE Y ASI MISMO OBTENER 
		//EL VALOR DE LA TABLA... POR ENDE MODIFICAR FIRMA DE METODO
		//_generarDesdeTabla($tabla, $campo, $where);
		//si existe where, es que viene de biblioteca y no se aplica el tia_codigo
		//porque la busqueda es directa.
	}
	
	/**
	 * Se encarga de generar un dato sintético desde un valor constante. La 
	 * función generar() hace uso de este método.
	 * @see		generar()
	 * @return	string	Dato sintético generado. Su valor es la constante
	 * 					definida.
	 */
	abstract function _generarDesdeConstante();
}
?>