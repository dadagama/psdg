<?php
session_start();
	
if(isset($_REQUEST['usu_login']) && isset($_REQUEST['usu_password']) && isset($_REQUEST['lang']))
{
	//si existe usuario
	if(true)
	{
		require_once ("../controladores/traductor.inc");
		//$traductor = new Traductor($_REQUEST['lang']);
		$_SESSION['lang'] = $_REQUEST['lang'];
		$_SESSION["usu_login"] = $_REQUEST['usu_login'];
		
		echo "<div id='div_conexiones'>
					<fieldset>
						<legend><label>Conexión</label></legend>
						<div class='tabla'>
							<div class='fila'>
								<div class='tabla_centrada'>
									<div class='fila'>
										<div class='celda alto_30'>
											<label class='etiqueta'>Nombre conexión:</label>
										</div>
										<div class='celda alto_30'>
											<input type='text' id='con_nombre' maxlength='50' class='ancho_100'/>
										</div>
									</div>
									<div class='fila'>
										<div class='celda alto_30'>
											<label class='etiqueta'>Usuario:</label>
										</div>
										<div class='celda alto_30'>
											<input type='text' id='con_usuario' maxlength='50' class='ancho_100'/>
										</div>
									</div>
									<div class='fila'>
										<div class='celda alto_30'>
											<label class='etiqueta'>Contraseña:</label>
										</div>
										<div class='celda alto_30'>
											<input type='password' id='con_password' maxlength='50' class='ancho_100'/>
										</div>
									</div>
									<div class='fila'>
										<div class='tabla_centrada'>
											<div class='fila'>
												<div class='celda alto_30'>
													<input type='button' value='Establecer' id='btn_establecer'/>
												</div>
											</div>
										</div>
									</div>
								</div>
							</div>
						</div>
					</fieldset>
				</div>";
	}
	else 
		echo "-1";
		
}
else
	echo "-1";
?>