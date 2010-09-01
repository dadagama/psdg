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

function validarCampoNoVacio(campoNoVacio, nombreCampo, mostrarMensaje) 
{
	var letra = false;
	for (var i = 0; i < campoNoVacio.val().length; i++ ) 
	{
		if ( campoNoVacio.val().charAt(i) != " " ) 
		{
			letra = true;
		}
	}
	if(!letra)
	{
		if(mostrarMensaje)
		{
			var mensaje = lang_js[8].replace("%v", nombreCampo);
			alert(mensaje);
		}
		return false;
	}
	else
	{
		return true;
	}
}

function validarTextAreaNoVacio(campoNoVacio, nombreCampo, mostrarMensaje) 
{
	var letra = false;
	for (var i = 0; i < campoNoVacio.value.length; i++ ) 
	{
		if ( campoNoVacio.value.charAt(i) != " " ) 
		{
			letra = true;
		}
	}
	if(!letra)
	{
		if(mostrarMensaje)
		{
			var mensaje = lang_js[8].replace("%v", nombreCampo);
			alert(mensaje);
		}
		return false;
	}
	else
	{
		return true;
	}
}

function validarCampoFecha(campoFecha, nombreCampo, admitirVacio)
{
  //alert("validando "+nombreCampo);
  if (!admitirVacio && !(campoFecha.val().length > 0))
  { 
		var mensaje = lang_js[8].replace("%v", nombreCampo);
		alert(mensaje);
    return false;
  }  
  
  // Crea un string
  var Fecha= new String(campoFecha.val());   
  // Para sacar la fecha de hoy
  var RealFecha= new Date();  
  // Cadena Año
  var Dia= new String(Fecha.substring(Fecha.lastIndexOf("-")+1,Fecha.length));
  // Cadena Mes
  var Mes= new String(Fecha.substring(Fecha.indexOf("-")+1,Fecha.lastIndexOf("-")));
  // Cadena Día
  var Ano= new String(Fecha.substring(0,Fecha.indexOf("-")));
  // Valido el año
  //TIMESTAMP no pueden ser anteriores a 1970 o posteriores a 2037.
  if (isNaN(Ano) || Ano.length<4 || parseInt(Ano, 10) < 1970 || parseInt(Ano, 10) > 2037)
  {
		var mensaje = lang_js[41].replace("%v", nombreCampo);
		alert(mensaje);
    return false;
  }
  // Valido el Mes
  if (isNaN(Mes) || parseInt(Mes, 10)<1 || parseInt(Mes, 10)>12)
  {
		var mensaje = lang_js[42].replace("%v", nombreCampo);
		alert(mensaje);
    return false;
  }
  // Valido el Dia
  if (isNaN(Dia) || parseInt(Dia, 10)<1 || parseInt(Dia, 10)>31)
  {
		var mensaje = lang_js[43].replace("%v", nombreCampo);
		alert(mensaje);
    return false;
  }
  if (parseInt(Mes, 10)==4 || parseInt(Mes, 10)==6 || parseInt(Mes, 10)==9 || parseInt(Mes, 10)==11 || parseInt(Mes, 10)==2) 
  {
    if (parseInt(Mes, 10)==2 && parseInt(Dia, 10) > 28 || parseInt(Dia, 10)>30) 
    {
		var mensaje = lang_js[43].replace("%v", nombreCampo);
		alert(mensaje);
      return false;
    }
  }
  return true;
}

function validarRangoFechas(campoFechaInicial, campoFechaFinal, nombreCampoFechaInicial, nombreCampoFechaFinal)
{
  var DiaInicial= new String(campoFechaInicial.val().substring(campoFechaInicial.val().lastIndexOf("-")+1,campoFechaInicial.val().length));
  var MesInicial= new String(campoFechaInicial.val().substring(campoFechaInicial.val().indexOf("-")+1,campoFechaInicial.val().lastIndexOf("-")));
  var AnoInicial= new String(campoFechaInicial.val().substring(0,campoFechaInicial.val().indexOf("-")));
  
  var DiaFinal= new String(campoFechaFinal.val().substring(campoFechaFinal.val().lastIndexOf("-")+1,campoFechaFinal.val().length));
  var MesFinal= new String(campoFechaFinal.val().substring(campoFechaFinal.val().indexOf("-")+1,campoFechaFinal.val().lastIndexOf("-")));
  var AnoFinal= new String(campoFechaFinal.val().substring(0,campoFechaFinal.val().indexOf("-")));
  
  var fechaInicial = new Date();
  var fechaFinal = new Date();
  
  fechaInicial.setFullYear(AnoInicial,MesInicial,DiaInicial);
  fechaFinal.setFullYear(AnoFinal,MesFinal,DiaFinal);

  if(fechaInicial <= fechaFinal)
    return true;
  else
  {
	  var mensaje = lang_js[44].replace("%v1", nombreCampoFechaInicial);
	  mensaje = mensaje.replace("%v2", nombreCampoFechaFinal);
	  alert(mensaje);
    return false;
  }
}


function validarRango(campoInicial, campoFinal, nombreCampoInicial, nombreCampoFinal)
{
  if(parseInt(campoInicial.val()) <= parseInt(campoFinal.val()))
    return true;
  else
  {
	  var mensaje = lang_js[44].replace("%v1", nombreCampoInicial);
	  mensaje = mensaje.replace("%v2", nombreCampoFinal);
	  alert(mensaje);
    return false;
  }
}


function validarInputRangoPermitido(idInput, nombreInput, minimo, maximo, admitirVacio)
{
	if (admitirVacio && !(idInput.val().length > 0))
		return true;
	else if(!admitirVacio && idInput.val().length == 0)
	{
		var mensaje = lang_js[8].replace("%v", nombreInput);
		idInput.focus();
		alert(mensaje);
		return false;
	}
	
	if(idInput.val() >= minimo && idInput.val() <= maximo)
		return true;
	else
	{
		var mensaje = lang_js[45].replace("%v1", nombreInput);
		mensaje = mensaje.replace("%v2", minimo);
		mensaje = mensaje.replace("%v3", maximo);
		idInput.focus();
		alert(mensaje);
		return false;
	}
}

function validarInput(idInput, nombreInput, tipoInput, admitirVacio)
{
  if (admitirVacio && !(idInput.val().length > 0))
    return true;
 
  var filtro = "";
  var error = "";

  switch(tipoInput)
  {
    case "email":
      filtro = /^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,4})+$/;
      error = 30;
    break;
    case "texto":
      filtro = /^(([A-Za-z\ñ]+)(\s){0,})*$/; //cualquier secuencia de letras y espacios en blanco. se debe utilizar trim de php para quitar sobrantes
      error = 31;
    break;
    case "numero":
      filtro = /^\d+$/;//cualquier secuencia de numeros
      error = 32;
    break;
    case "fecha":
      if (!validarCampoFecha(idInput, nombreInput, admitirVacio))
        return false;
      else
        return true;
    break;
    default:
      filtro = "";
      error = 99;
    break;
  }
  if (!admitirVacio && !(idInput.val().length > 0))
  { 
	var mensaje = lang_js[8].replace("%v", nombreInput);
	idInput.focus();
	alert(mensaje);
	return false;
  }  
  else if (!filtro.test(idInput.val()))
  {
	var mensaje = lang_js[error].replace("%v", nombreInput);
	idInput.focus();
	alert(mensaje);
	return false;
  }
  return true;
}

function validarSeleccionComboBox(comboBox, nombreCampo, admitirVacio)
{
  if (comboBox.val() == 0)
  { 
    if(!admitirVacio)
    {
		var mensaje = lang_js[40].replace("%v", nombreCampo);
		comboBox.focus();
		alert(mensaje);
		return false;
    }
    else
      return true;
  }  
  else
    return true;
}
