#include <Arduino.h>
#include <WebServer.h>
#include "pagina.h"

extern WebServer servidor;

void paginaPrincipal() {
  String pagina = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">

<style>
body{
  font-family:Arial;
  margin:0;
  height:100vh;
  display:flex;
  justify-content:center;
  align-items:center;
}
.titulo{
  position:fixed;
  top:20px;
  width:100%;
  text-align:center;
}
.controle{
  text-align:center;
}
button{
  width:130px;
  height:80px;
  border:none;
  background:#ff8888;
  margin:10px;
}
button:active{
  background:#66dd66;
}
.seta-cima{
  clip-path:polygon(50% 0%,100% 40%,70% 40%,70% 100%,30% 100%,30% 40%,0% 40%);
}
.seta-baixo{
  clip-path:polygon(30% 0%,70% 0%,70% 60%,100% 60%,50% 100%,0% 60%,30% 60%);
}
.seta-esquerda{
  clip-path:polygon(0% 50%,40% 0%,40% 30%,100% 30%,100% 70%,40% 70%,40% 100%);
}
.seta-direita{
  clip-path:polygon(100% 50%,60% 0%,60% 30%,0% 30%,0% 70%,60% 70%,60% 100%);
}
.meio{
  display:flex;
  justify-content:center;
  gap:35px;
}
</style>

</head>

<body>

<h1 class="titulo">Controle do Falcon</h1>

<div class="controle">

<div>
<button class="seta-cima"
ontouchstart="andar('frente')"
ontouchend="parar()"
onmousedown="andar('frente')"
onmouseup="parar()">
</button>
</div>

<div class="meio">

<button class="seta-esquerda"
ontouchstart="andar('esquerda')"
ontouchend="parar()"
onmousedown="andar('esquerda')"
onmouseup="parar()">
</button>

<button class="seta-direita"
ontouchstart="andar('direita')"
ontouchend="parar()"
onmousedown="andar('direita')"
onmouseup="parar()">
</button>

</div>

<div>

<button class="seta-baixo"
ontouchstart="andar('atras')"
ontouchend="parar()"
onmousedown="andar('atras')"
onmouseup="parar()">
</button>

</div>

</div>

<script>

let socket = new WebSocket("ws://" + location.hostname + ":81/");

function andar(comando){
  if(socket.readyState === WebSocket.OPEN){
    socket.send(comando);
  }
}

function parar(){
  if(socket.readyState === WebSocket.OPEN){
    socket.send("parar");
  }
}

</script>

</body>
</html>

)rawliteral";

  servidor.send(200, "text/html", pagina);
}