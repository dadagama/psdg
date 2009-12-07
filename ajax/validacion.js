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
			var mensaje = lang_js[4].replace("%v", nombreCampo);
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
  if (!admitirVacio && !(campoFecha.value.length > 0))
  { 
    alert("El campo ["+nombreCampo+"] no puede estar vacío.");
    return false;
  }  
  
  // Crea un string
  var Fecha= new String(campoFecha.value);   
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
    alert("El año del campo ["+nombreCampo+"] no es válido.");
    return false;
  }
  // Valido el Mes
  if (isNaN(Mes) || parseInt(Mes, 10)<1 || parseInt(Mes, 10)>12)
  {
    alert("El mes del campo ["+nombreCampo+"] no es válido.");
    return false;
  }
  // Valido el Dia
  if (isNaN(Dia) || parseInt(Dia, 10)<1 || parseInt(Dia, 10)>31)
  {
    alert("El día del campo ["+nombreCampo+"] no es válido.");
    return false;
  }
  if (parseInt(Mes, 10)==4 || parseInt(Mes, 10)==6 || parseInt(Mes, 10)==9 || parseInt(Mes, 10)==11 || parseInt(Mes, 10)==2) 
  {
    if (parseInt(Mes, 10)==2 && parseInt(Dia, 10) > 28 || parseInt(Dia, 10)>30) 
    {
      alert("El día del campo ["+nombreCampo+"] no es válido.");
      return false;
    }
  }
  return true;
}

function validarRangoFechas(campoFechaInicial, campoFechaFinal, nombreCampoFechaInicial, nombreCampoFechaFinal)
{
  var DiaInicial= new String(campoFechaInicial.value.substring(campoFechaInicial.value.lastIndexOf("-")+1,campoFechaInicial.value.length));
  var MesInicial= new String(campoFechaInicial.value.substring(campoFechaInicial.value.indexOf("-")+1,campoFechaInicial.value.lastIndexOf("-")));
  var AnoInicial= new String(campoFechaInicial.value.substring(0,campoFechaInicial.value.indexOf("-")));
  
  var DiaFinal= new String(campoFechaFinal.value.substring(campoFechaFinal.value.lastIndexOf("-")+1,campoFechaFinal.value.length));
  var MesFinal= new String(campoFechaFinal.value.substring(campoFechaFinal.value.indexOf("-")+1,campoFechaFinal.value.lastIndexOf("-")));
  var AnoFinal= new String(campoFechaFinal.value.substring(0,campoFechaFinal.value.indexOf("-")));
  
  var fechaInicial = new Date();
  var fechaFinal = new Date();
  
  fechaInicial.setFullYear(AnoInicial,MesInicial,DiaInicial);
  fechaFinal.setFullYear(AnoFinal,MesFinal,DiaFinal);

  if(fechaInicial<fechaFinal)
    return true;
  else
  {
    alert("El campo ["+nombreCampoFechaInicial+"] debe contener una fecha menor a la del campo ["+nombreCampoFechaFinal+"]");
    return false;
  }
}


function validarInput(idInput, nombreInput, tipoInput, admitirVacio)
{
  if (admitirVacio && !(idInput.value.length > 0))
    return true;
 
  var filtro = "";
  var error = "";

  switch(tipoInput)
  {
    case "email":
      filtro = /^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,4})+$/;
      error = "no es una dirección válida.";
    break;
    case "texto":
      filtro = /^(([A-Za-z\ñ]+)(\s){0,})*$/; //cualquier secuencia de letras y espacios en blanco. se debe utilizar trim de php para quitar sobrantes
      error = "solo puede contener letras.";
    break;
    case "numero":
      filtro = /^\d+$/;//cualquier secuencia de numeros
      error = "solo puede contener números.";
    break;
    case "cedulaONit":
      filtro = /^\d+(\-\d+){0,1}$/;//cualquier secuencia de numeros, o numeros separados por un guion y mas numeros
      error = "solo puede contener números.";
    break;
    case "numeroSeperadorComa":
      filtro = /^\d+(\,\d+)*$/;//cualquier secuencia de numeros y la coma para separar
      error = "solo puede contener números separados por comas.";
    break;
    case "numeroSeperadorGuion":
      filtro = /^\d+(\-\d+)*$/;//cualquier secuencia de numeros y el guión para separar
      error = "solo puede contener números separados por guiones.";
    break;
    case "telefono":
      filtro = /^(\(\d+\)){0,1}\d+(\-(\(\d+\)){0,1}\d+)*$/;//[(##)]########[-######]
      error = "solo puede contener números separados por guiones.";
    break;
    case "fecha":
      if (!validarCampoFecha(idInput, nombreInput, admitirVacio))
        return false;
      else
        return true;
    break;
    default:
      filtro = "";
      error = "error.";
    break;
  }
  if (!admitirVacio && !(idInput.value.length > 0))
  { 
    alert("Contenido del campo ["+nombreInput+"] no puede esta vacío");
    return false;
  }  
  else if (!filtro.test(idInput.value))
  {
    alert("Contenido del campo ["+nombreInput+"] "+error+"\nElimine cualquier espacio antes y despues del campo.");
    idInput.focus();
    return false;
  }
  return true;
}

function validarSeleccionComboBox(comboBox, nombreCampo, admitirVacio)
{
  if (comboBox.selectedIndex == 0)
  { 
    if(!admitirVacio)
    {
      alert("Debe escoger una opción en el campo ["+nombreCampo+"].");
      return false;
    }
    else
      return true;
  }  
  else
    return true;
}