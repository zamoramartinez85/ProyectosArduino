
#include <Ethernet.h>
#include <SPI.h>
#include <RestClient.h>

//https://www.youtube.com/watch?v=F-2H-oc9q6Q

//* Ethernet shield usa los pins 10, 11, 12, 13

RestClient client = RestClient("zamorapinero.es");
String placa = "prueba";
String datos="";
int valor = 32;
String response;
byte mac[] = {
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02
};

void enviarDatos(){
  Serial.println(datos);

  response = "";
  Serial.println("La respuesta es: " + response);
  int statusCode = client.get("/arduinoWeb/guardarDatos.php?placa=david&valor=23", &response);
  Serial.println("La respuesta es: " + response);
  Serial.print("Status code from server: ");
  Serial.println(statusCode);
  Serial.print("Response body from server: ");
  Serial.println(response);

  delay(5000);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  /*
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for (;;)
      ;
  }
  */
  Serial.println("Conectando");
  client.dhcp();
  Serial.println("Ha conectado");
}

void loop() {
  // put your main code here, to run repeatedly:
  while (true){
    Serial.println("Entra en el bucle while");
    enviarDatos();
    delay(10000);
  }
}
