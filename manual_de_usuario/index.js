function onMouseOver(numero_step)
{
	nombre_step = "step_"+numero_step;
	$('#'+nombre_step).attr("src","../imagenes/step_"+numero_step+"_ok.png");
}

function onMouseOut(numero_step)
{
	nombre_step = "step_"+numero_step;
	if(step_seleccionado != numero_step)
		$('#'+nombre_step).attr("src","../imagenes/step_"+numero_step+"_off.png");
	else
		$('#'+nombre_step).attr("src","../imagenes/step_"+numero_step+"_on.png");
}

function onMouseClic(numero_step)
{
	nombre_step = "step_"+numero_step;
	step_seleccionado = numero_step;
	for(var i = 1; i < 5; i++)
		$('#step_'+i).attr("src","../imagenes/step_"+i+"_off.png");
	$('#'+nombre_step).attr("src","../imagenes/step_"+numero_step+"_on.png");
	//cargar el manual flash en el div_cuerpo
	var width, height = 0;
	if(numero_step == 1) {width = 1001; height = 557;}
	else if(numero_step == 2) {width = 1014; height = 557;}
	else if(numero_step == 3) {width = 1014; height = 557;}
	else if(numero_step == 4) {width = 1014; height = 557;}
	var response='<object classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=7,0,19,0" width="'+width+'" height="'+height+'">    <param name="movie" value="step'+numero_step+'.swf" /> <param name="quality" value="high" />    <EMBED SRC="step'+numero_step+'.swf" WIDTH='+width+' HEIGHT='+height+' quality=low loop=false wmode=transparent TYPE="application/x-shockwave-flash" PLUGINSPAGE="http://www.macromedia.com/shockwave/download/index.cgi?P1_Prod_Version=ShockwaveFlash"> </EMBED> </object>';
	$('#div_cuerpo').html(response);
}
