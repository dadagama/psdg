<?php
require_once ("../distribuciones/DistribucionUniformeAleatoria.inc");
require_once ("../funciones/Funcion.inc");
class Luhn extends Funcion
{

	/*
	 Javascript credit card number generator
	 Copyright (C) 2006 Graham King graham@darkcoding.net
	
	 This program is free software; you can redistribute it and/or
	 modify it under the terms of the GNU General Public License
	 as published by the Free Software Foundation; either version 2
	 of the License, or (at your option) any later version.
	
	 This program is distributed in the hope that it will be useful,
	 but WITHOUT ANY WARRANTY; without even the implied warranty of
	 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	 GNU General Public License for more details.
	
	 You should have received a copy of the GNU General Public License
	 along with this program; if not, write to the Free Software
	 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
	
	 www.darkcoding.net
	
	 PHP version by Darwin David García Maya 
	 [dadagama@gmail.com]
	 */
	
	var $generador_random;

	var $visaPrefixList = array(
	    "4539",
	    "4556",
	    "4916",
	    "4532",
	    "4929",
	    "40240071",
	    "4485",
	    "4716",
	    "4" 
	);
	
	var $mastercardPrefixList = array(
	    "51",
	    "52",
	    "53",
	    "54",
	    "55"
	);
	
	var $amexPrefixList = array(
	    "34",
	    "37"
	);
	
	var $discoverPrefixList = array("6011");
	
	var $dinersPrefixList = array(
	    "300",
	    "301",
	    "302",
	    "303",
	    "36",
	    "38"
	);
	
	var $enRoutePrefixList = array(
	    "2014",
	    "2149"
	);
	
	var $jcbPrefixList16 = array(
	    "3088",
	    "3096",
	    "3112",
	    "3158",
	    "3337",
	    "3528"
	);
	
	var $jcbPrefixList15 = array(
	    "2100",
	    "1800"
	);
	
	var $voyagerPrefixList = array("8699");
	
	
	function __construct()
	{
		$this->generador_random = new DistribucionUniformeAleatoria(16807, 0, 2147483641, rand(1,123456789));
	}
	
	function strrev($str)
	{
		if(!$str) 
			return '';
		$revstr='';
		for($i = strlen($str)-1; $i >= 0; $i--)
			$revstr .= substr($str, $i, 1);
		return $revstr;
	}
	
	/*
	 'prefix' is the start of the CC number as a string, any number of digits.
	 'length' is the length of the CC number to generate. Typically 13 or 16
	 */
	function completed_number($prefix, $length) 
	{
		$ccnumber = $prefix;
		//echo "<br>[completed_number] prefix = $prefix";
		// generate digits
		while ( strlen($ccnumber) < ($length - 1) ) 
			$ccnumber .= floor($this->generador_random->generar() * 10);
		//echo "<br>[completed_number] ccnumber = $ccnumber";
		// reverse number and convert to int
		$reversedCCnumberString = $this->strrev($ccnumber);
		//echo "<br>[completed_number] reversedCCnumberString = $reversedCCnumberString";
		$reversedCCnumber = array();
		for ($i = 0; $i < strlen($reversedCCnumberString); $i++ )
			$reversedCCnumber[$i] = intval( substr($reversedCCnumberString, $i, 1) );
		//print_r($reversedCCnumber);
		
		// calculate sum
		$sum = 0;
		$pos = 0;
		while ( $pos < $length - 1 ) 
		{
			//echo "<br>[completed_number] while  ( $pos < $length - 1 ) ";
			$odd = $reversedCCnumber[ $pos ] * 2;
			if ( $odd > 9 )
				$odd -= 9;
			
			$sum += $odd;
			
			if ( $pos != ($length - 2) )		
				$sum += $reversedCCnumber[ $pos +1 ];
				
			$pos += 2;
		}
		
		// calculate check digit
		$checkdigit = (( floor($sum/10) + 1) * 10 - $sum) % 10;
		$ccnumber .= $checkdigit;
		return $ccnumber;
	}
	
	function credit_card_number(&$prefixList, $length) 
	{
		$randomArrayIndex = floor($this->generador_random->generar() * count($prefixList));
		//echo "<br>randomArrayIndex = $randomArrayIndex";
		$ccnumber = $prefixList[ $randomArrayIndex ];
		//echo "<br>ccnumber = $ccnumber";
		$result = $this->completed_number($ccnumber, $length);
		return $result;
	}
	
	function generar()
	{
		$tipo;
		/*generar alguno de los tipos de tarjeta*/
		switch(floor($this->generador_random->generar() * 9))
		{
			case 0:	$tipo = $this->visaPrefixList; break;
			case 1:	$tipo = $this->mastercardPrefixList; break;
			case 2:	$tipo = $this->amexPrefixList; break;
			case 3:	$tipo = $this->discoverPrefixList; break;
			case 4:	$tipo = $this->dinersPrefixList; break;
			case 5:	$tipo = $this->enRoutePrefixList;  break;
			case 6:	$tipo = $this->jcbPrefixList16; break;
			case 7:	$tipo = $this->jcbPrefixList15; break;
			case 8:	$tipo = $this->voyagerPrefixList; break;
		}
		/*se generaran los numeros estandar de 16 digitos*/
		//echo "<pre>"; print_r($tipo);
		return $this->credit_card_number($tipo, 16);
	}
}
//$xx = new Luhn();
//echo "<br>".$xx->generar();
?>