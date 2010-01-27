<?php
require_once "DistribucionUniformeAleatoria.inc";
class DistribucionNormalEstandar
{
//	var $_fr = array();	//rango de F(a)
//	var $_fa = array();	//rango de a
	var $_distribucionUniforme;
	var $_media;
	var $_desviacion_tipica;
	
	function __construct($media = 0, $desviacion_tipica = 1)
	{
		$this->_distribucionUniforme = new DistribucionUniformeAleatoria(16807, 0, 2147483641, rand(1,123456789));
		$this->_media = $media;
		$this->_desviacion_tipica = $desviacion_tipica;
	}
	
//	function _ubicarEnRango($numero)
//	{
//		if($numero >= 0.999999999 && $numero < 1)
//		{
//			$this->_fr[0] = 0.999999999;
//			$this->_fr[1] = 1;
//			$this->_fa[0] = 6;
//			$this->_fa[1] = 7;
//		}
//		else if($numero >= 0.9999997 && $numero < 0.999999999)
//		{
//			$this->_fr[0] = 0.9999997;
//			$this->_fr[1] = 0.999999999;
//			$this->_fa[0] = 5;
//			$this->_fa[1] = 6;
//		}
//		else if($numero >= 0.99997 && $numero < 0.9999997)
//		{
//			$this->_fr[0] = 0.99997;
//			$this->_fr[1] = 0.9999997;
//			$this->_fa[0] = 4;
//			$this->_fa[1] = 5;
//		}
//		else if($numero >= 0.9987 && $numero < 0.99997)
//		{
//			$this->_fr[0] = 0.9987;
//			$this->_fr[1] = 0.99997;
//			$this->_fa[0] = 3;
//			$this->_fa[1] = 4;
//		}
//		else if($numero >= 0.9772 && $numero < 0.9987)
//		{
//			$this->_fr[0] = 0.9772;
//			$this->_fr[1] = 0.9987;
//			$this->_fa[0] = 2;
//			$this->_fa[1] = 3;
//		}
//		else if($numero >= 0.8413 && $numero < 0.9772)
//		{
//			$this->_fr[0] = 0.8413;
//			$this->_fr[1] = 0.9772;
//			$this->_fa[0] = 1;
//			$this->_fa[1] = 2;
//		}
//		else if($numero >= 0.5 && $numero < 0.8413)
//		{
//			$this->_fr[0] = 0.5;
//			$this->_fr[1] = 0.8413;
//			$this->_fa[0] = 0;
//			$this->_fa[1] = 1;
//		}
//		else if($numero >= 0.1586 && $numero < 0.5)
//		{
//			$this->_fr[0] = 0.1586;
//			$this->_fr[1] = 0.5;
//			$this->_fa[0] = -1;
//			$this->_fa[1] = 0;
//		}
//		else if($numero >= 0.0228 && $numero < 0.1586)
//		{
//			$this->_fr[0] = 0.0228;
//			$this->_fr[1] = 0.1586;
//			$this->_fa[0] = -2;
//			$this->_fa[1] = -1;
//		}
//		else if($numero >= 0.0013 && $numero < 0.0228)
//		{
//			$this->_fr[0] = 0.0013;
//			$this->_fr[1] = 0.0228;
//			$this->_fa[0] = -3;
//			$this->_fa[1] = -2;
//		}
//		else if($numero >= 0.00003 && $numero < 0.0013)
//		{
//			$this->_fr[0] = 0.00003;
//			$this->_fr[1] = 0.0013;
//			$this->_fa[0] = -4;
//			$this->_fa[1] = -3;
//		}
//		else if($numero >= 0.0000003 && $numero < 0.00003)
//		{
//			$this->_fr[0] = 0.0000003;
//			$this->_fr[1] = 0.00003;
//			$this->_fa[0] = -5;
//			$this->_fa[1] = -4;
//		}
//		else if($numero >= 0.000000003 && $numero < 0.0000003)
//		{
//			$this->_fr[0] = 0.000000003;
//			$this->_fr[1] = 0.0000003;
//			$this->_fa[0] = -6;
//			$this->_fa[1] = -5;
//		}
//		else if($numero >= 0 && $numero < 0.000000003)
//		{
//			$this->_fr[0] = 0;
//			$this->_fr[1] = 0.000000003;
//			$this->_fa[0] = -7;
//			$this->_fa[1] = -6;
//		}
//	}
//	
	function generar()
	{
		$numeroAleatorio = $this->_distribucionUniforme->generar();
		$numeroAleatorio2 = $this->_distribucionUniforme->generar();
//		$this->_ubicarEnRango($numeroAleatorio);
//		$lambda = ($this->_fr[1] - $numeroAleatorio) / ($this->_fr[1] - $this->_fr[0]);
//		$a = ($lambda * $this->_fa[0]) + (1 - $lambda) * $this->_fa[1];
		
		////////////////////////////////////////////////////////////////////////
		//                                                                    //
		//                        BOX MULLER FORMULA:                         //
		//                                                                    //
		//  SQRT(-2*LN( RAND() ) )  *  SIN(2*PI()*RAND())  * MyStdDev+MyMean  //
		//                                                                    //
		////////////////////////////////////////////////////////////////////////
		
		$parte1 = -2 * log($numeroAleatorio);
		$parte2 = sin(2 * pi() *  $numeroAleatorio2);
		$box_muller = sqrt($parte1) * $parte2 * $this->_desviacion_tipica  + $this->_media;

		return $box_muller;
	}
}
?>