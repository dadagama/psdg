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
