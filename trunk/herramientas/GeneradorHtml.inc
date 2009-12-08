<?php
public class GeneradorHtml
{
	function div($id="", $name="", $class="")
	{
		echo "<div id='$id' name='$name' class='$class'>";
	}
	
	function label($id="", $name="", $class="")
	{
		echo "<label id='$id' name='$name' class='$class'>";
	}

	function fieldset($id="", $name="", $class="")
	{
		echo "<fieldset id='$id' name='$name' class='$class'>";
	}
	
	function legend($id="", $name="", $class="")
	{
		echo "<legend id='$id' name='$name' class='$class'>";
	}
	
	function input($id="", $name="", $class="", $type="", $value="", $disabled="")
	{
		echo "<input id='$id' name='$name' class='$class' type='$type' value='$value' $disabled>";
	}
	
	function form($id="", $name="", $class="", $action="", $method="")
	{
		echo "<form id='$id' name='$name' class='$class' action='$action' method='$method'>";
	}

	function select($id="", $name="", $class="", $multiple="", $size="1", $disabled="")
	{
		echo "<select id='$id' name='$name' class='$class' $multiple size='$size' $disabled>";
	}
	
	function optgroup($label="")
	{
		echo "<optgroup label='$label'>";
	}
	
	function option($value="", $selected="", $disabled="")
	{
		echo "<option value='$value' $selected $disabled>";
	}
	
	function textarea($disabled="")
	{
		echo "<textarea $disabled>";
	}
	
	function br()
	{
		echo "<br/>";
	}
	
	function li()
	{
		echo "<li>";
	}

	function ol()
	{
		echo "<ol>";
	}
	
	function ul()
	{
		echo "<ul/>";
	}
	
	function fin($tipo)
	{
		echo "</$tipo>";
	}
}
?>