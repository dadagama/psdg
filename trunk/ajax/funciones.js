var doc;
doc=$(document);
doc.ready(inicializarEventos);

function inicializarEventos()
{
  var btn_login;
  btn_login = $("#btn_login");
  btn_login.click(iniciar_sesion);
}

function iniciar_sesion()
{
  alert('hola');
  $("#div_sesion").slideToggle("slow");
}

function inicioEnvio()
{
  var v=$("#detalles");
  v.html('enviando...');
}

function llegadaDatos(datos)
{
  var v=$("#detalles");
  v.html(datos);
}

function problemas()
{
  var v=$("#detalles");
  v.html('error');
}
