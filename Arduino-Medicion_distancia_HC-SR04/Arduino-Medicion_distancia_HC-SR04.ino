/*
Programa usando HC-SR04 para medición de distancias

David Zamora para Javier Carrillo
19/08/217
*/


//Pines
int Trig = 3; //Emisor de onda sonora
int Echo = 4; //Recepto de onda sonora

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  
}

void loop() {

  long duracion;
  long distancia;

  digitalWrite(Trig, LOW);
  delayMicroseconds(4);   //Paramos durante 4 microsegundos el pulso de sonido para saber que iniciamos desde vacío.
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);   //Lanzamos un pulso de sonido durante 10 microsegundos.
  digitalWrite(Trig, LOW);
  //De forma automática se envían 8 pulsos de 40khz creando la onda de sonido

  duracion = pulseIn(Echo, HIGH); //Recibimos el tiempo (en microsegundos) que tarda en volver el eco de la onda sonora.

  //Dividimos entre dos para saber el tiempo que se tarda en llegar al obstáculo.
  duracion = duracion/2;
  
  //Recordamos que la velocidad del sonido en condciones normales es de 343 m/s
  /*
  343 metros / 1 segundo = 1cm / 29.2 microsegundos  
  */

  //Hacemos una regla de tres para calcular la distancia al objeto
  /*
  distancia = (duracion microsegundos * 1 cm) / 29.2 microsegundos
  */
  
  distancia = duracion / 29;  //Redondeamos, sólo se puede trabajar con enteros
  
  Serial.print("La distancia es de: ");
  Serial.println(distancia);
  delay(200);
  
}
