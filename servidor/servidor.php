<?php
if(isset($_REQUEST['usu_login']) && isset($_REQUEST['usu_password']))
{
	echo "<div id='div_conexiones'>
					<fieldset class='div_formulario'>
						<legend><label>Conexión</label></legend>
						<label class='lbl_formulario'>Nombre conexión:</label>
						<input type='text' id='con_nombre' maxlength='50' class='inp_formulario'/>
						<label class='lbl_formulario'>Usuario:</label>
						<input type='text' id='con_usuario' maxlength='50' class='inp_formulario'/>
						<label class='lbl_formulario'>Contraseña:</label>
						<input type='password' id='con_password' maxlength='50' class='inp_formulario'/>
						<input type='button' value='Establecer' class='boton' id='btn_establecer'/>
					</fieldset>
				</div>";
}
else
	echo "-1";
?>
