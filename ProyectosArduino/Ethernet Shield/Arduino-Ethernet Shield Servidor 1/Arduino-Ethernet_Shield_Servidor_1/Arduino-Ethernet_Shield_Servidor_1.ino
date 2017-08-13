/*
  Ethernet Monitor Analogo
 Este programa usa el Módulo Ethernet de Arduino para monitorear las entradas analógicas A0-A5
 
 Conexiones:
 * Ethernet shield usa los pins 10, 11, 12, 13
 * Monitorea los pines Analogos de A0 a A5
 
Se debe conectar el módulo a la red local y se debe asignar una IP fija que no coincida
con los equipos de la red que ya están funcionando pero dede estar dentro de la SubRed.
puedes monitorear la IP de dentro de la ventana de comandos CMD con el comando ipconfig
*/

#include <SPI.h>
#include <Ethernet.h>
                               // Introduzca una dirección MAC y la dirección IP para el controlador
byte mac[] = { 
0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,1,50);   // Esta dirección IP debe ser cambiada obligatoriamente 
                              // dependiendo de la subred del Área Local y es la que 
                              // se usará para conectarse por el Navegador.

EthernetServer server(80);    // Puerto 80 por defecto para HTTP

void setup() {
  Ethernet.begin(mac, ip);    //inicializa la conexión Ethernet y el servidor
  server.begin();
}

void loop() {
  EthernetClient cliente = server.available(); // Inicializa cliente como servidor ethernet
  if (cliente) {
    boolean currentLineIsBlank = true;
    while (cliente.connected()) {
      if (cliente.available()) {
        char c = cliente.read();
        if (c == '\n' && currentLineIsBlank) { 
          cliente.println("HTTP/1.1 200 OK");
          cliente.println("Content-Type: text/html");   // Envia el encabezado en codigo HTML estandar
          cliente.println("Connection: close"); 
          cliente.println("Refresh: 3");                // refresca la página automáticamente cada 3 segundos
          cliente.println();
          cliente.println("<!DOCTYPE HTML>"); 
          cliente.println("<html>");
          cliente.println("<HEAD>");
          cliente.println("<TITLE>Ethernet Monitor</TITLE>");
          cliente.println("</HEAD>");
          cliente.println("<BODY>");
          cliente.println("<hr />");
          cliente.println("<H1>Lecturas a trav&eacute;s de Arduino</H1>");
          cliente.println("<br />");  
          cliente.println("<H2>Monitorea A0-A5</H2>");
          cliente.println("<br />");  
          cliente.println("Lectura Analoga Ethernet");  
          cliente.println("<br />");
          cliente.println("<br />");
          for (int puertoAnalogo = 0; puertoAnalogo < 6; puertoAnalogo++) {
            int lecturaSensor = analogRead(puertoAnalogo);   // Lee los 6 puertos analogos de A0 a A5
            cliente.print("Lectura en entrada anal&oacute;gica ");
            cliente.print(puertoAnalogo);
            cliente.print(":  ");
            cliente.print(lecturaSensor);
            cliente.println("<br />");       
          }
          cliente.println("<br />");            
          cliente.println("</html>");
          break;
        }
        if (c == '\n') {
           currentLineIsBlank = true;
        } 
        else if (c != '\r') {
           currentLineIsBlank = false;
        }
      }
    }
   delay(15);           // Da tiempo al Servidor para que reciba los datos 15ms
   cliente.stop();      // cierra la conexión
  }
}

