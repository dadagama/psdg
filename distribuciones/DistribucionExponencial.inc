<?php
require_once "DistribucionUniformeAleatoria.inc";
class DistribucionExponencial
{
	var $x;
	var $_lambda;
	var $_distribucionUniforme;
	
	function __construct($lam)
	{
		//lam > 0
		$this->_lambda = $lam;
		$this->_distribucionUniforme = new DistribucionUniformeAleatoria(16807, 0, 2147483641, rand());
	}
	
	function generar()
	{
		$numeroAleatorio = $this->_distribucionUniforme->generar();
		$a = ((-1) * log($numeroAleatorio)) / $this->_lambda;
		return $a;
	}
}
//$x = new DistribucionExponencial(1);
//echo $x->generar();
?>
