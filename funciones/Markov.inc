<?php
/*
    PHP Markov Chain text generator 1.0
    Copyright (c) 2008, Hay Kranen <http://www.haykranen.nl/projects/markov/>
    
    License (MIT / X11 license)    
    
    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:
    
    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.
    
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.
    
    
*/
require_once ("../funciones/Funcion.inc");
class Markov extends Funcion
{

var $_order;
var $_length;
var $_input;
var $_text;
var $_markov_table;

function __construct($order, $length, $input)
{
	$this->_order  = $order;
    $this->_length = $length;
    $this->_text = utf8_encode(file_get_contents("../funciones/text/".$input.".txt"));
    //Darwin Garcia[2010-02-20]: se inicializa la tabla aca para optimizar el proceso.
    if(isset($this->_text)) 
    {
		$this->_markov_table = $this->generate_markov_table($this->_text, $this->_order);
    }
}

function generar()
{
    if(isset($this->_text)) 
    {
        //$markov_table = $this->generate_markov_table($this->_text, $this->_order);
        $markov = $this->generate_markov_text($this->_length, $this->_markov_table, $this->_order);
        if (get_magic_quotes_gpc()) 
        	$markov = stripslashes($markov);
    }
	return addslashes($markov);
}

function generate_markov_table($text, $look_forward) {
    $table = array();
    
    // now walk through the text and make the index table
    for ($i = 0; $i < strlen($text); $i++) {
        $char = substr($text, $i, $look_forward);
        if (!isset($table[$char])) $table[$char] = array();
    }              
    
    // walk the array again and count the numbers
    for ($i = 0; $i < (strlen($text) - $look_forward); $i++) {
        $char_index = substr($text, $i, $look_forward);
        $char_count = substr($text, $i+$look_forward, $look_forward);
        
        if (isset($table[$char_index][$char_count])) {
            $table[$char_index][$char_count]++;
        } else {
            $table[$char_index][$char_count] = 1;
        }                
    } 

    return $table;
}

function generate_markov_text($length, $table, $look_forward) {
    // get first character
    $char = array_rand($table);
    $o = $char;

    for ($i = 0; $i < ($length / $look_forward); $i++) {
        $newchar = $this->return_weighted_char($table[$char]);            
        
        if ($newchar) {
            $char = $newchar;
            $o .= $newchar;
        } else {       
            $char = array_rand($table);
        }
    }
    
    return $o;
}
    

function return_weighted_char($array) {
    if (!$array) return false;
    
    $total = array_sum($array);
    $rand  = mt_rand(1, $total);
    foreach ($array as $item => $weight) {
        if ($rand <= $weight) return $item;
        $rand -= $weight;
    }
}

}
?>
