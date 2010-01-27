<?php
/**
 * Clase para generar una distribución uniforme de números aleatorios
 * @author	Darwin Garcia (dadagama@gmail.com) - Carlos Guzman(caralbgm@gmail.com)
 * @since	27-11-2009
 * @version	1.0
 */
class DistribucionUniformeAleatoria
{
	var $_multiplicadorA;
	var $_incrementoC;
	var $_moduloM;
	var $_semillaX;
	var $_numero;
	var $_q;
	var $_r;
	
	//Metodo constructor
	function __construct($a = 16807, $c = 0, $m = 2147483641, $x="")
	{
		if($x == "")
			$x = rand(1,123456789);
		//Valores Ideales: (16807, 0, 2147483641, 123456789)
		$this->_multiplicadorA = $a;
		$this->_incrementoC    = $c;
		$this->_moduloM        = $m;
		$this->_semillaX       = $x;
		$this->_q              = (int)((float)(floor($this->_moduloM / $this->_multiplicadorA)));
		$this->_r              = (int)((float)($this->_moduloM % $this->_multiplicadorA));
	}
	
	//Factorizar M evita el OverFlow
	function _factorizarM()
	{
		$this->_q = (int) $this->_moduloM / $this->_multiplicadorA;
		$this->_r = (int) $this->_moduloM % $this->_multiplicadorA;
		$this->_moduloM = $this->_multiplicadorA * $this->_q + $this->_r;
	}
	
	//Generador Linear Congruente
	function generar()
	{
		$this->_semillaX = ($this->_multiplicadorA*($this->_semillaX%$this->_q))-($this->_r*(floor($this->_semillaX/((float)$this->_q))));
		if($this->_semillaX < 0)
			$this->_semillaX = ($this->_multiplicadorA*($this->_semillaX%$this->_q))-($this->_r*(floor(($this->_semillaX)/((float)$this->_q))))+$this->_moduloM;
		return $this->_semillaX/$this->_moduloM;
	}
}
//$x = new DistribucionUniformeAleatoria($a = 16807, $c = 0, $m = 2147483641, rand(1,123456789));
//echo floor($x->generar() * 10);

?>