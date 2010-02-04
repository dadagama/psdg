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
////0.00000000001 => lambda para timestamp decentes
//$x = new DistribucionExponencial(0.00000000001);
//for($y=0;$y<50;$y++)
//	echo "<br>".floor($x->generar());
?>
