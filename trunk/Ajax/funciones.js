var x;
x=$(document);
x.ready(inicializarEventos);

function inicializarEventos()
{
  var x;
  x=$("#btn_login");
  x.click(presionEnlace);
}

function presionEnlace()
{
  var v = $("#usu_login").attr("value");
  alert('login='+v);
  $.ajax({
           async:true,
           type: "POST",
           dataType: "html",
           contentType: "application/x-www-form-urlencoded",
           url:"index2.php",
           data:"usu_login="+v,
           beforeSend:inicioEnvio,
           success:llegadaDatos,
           timeout:10000,
           error:problemas
         });
  return false;
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
