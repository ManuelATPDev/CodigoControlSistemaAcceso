const int rele_alarma = 2;
const int boton_na_timbre = 3;
const int sensor_impacto = 4;
const int sensor_infrarrojo_interior = 5;
const int sensor_infrarrojo_exterior = 6;
const int esp32cam_exterior = 7;
const int esp32cam_interior = 8;
const int rele_puerta = 9;
int activar_alarma = 0;
int valor_temporal_boton = 0;
int valor_real_boton;
int valor_real_sensor_impacto;
int valor_real_esp32cam_interior;
int valor_real_esp32cam_exterior;
int valor_real_sensor_infrarrojo_interior;
int valor_real_sensor_infrarrojo_exterior;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(rele_alarma,OUTPUT);
  pinMode(rele_puerta,OUTPUT);
  pinMode(boton_na_timbre,INPUT);
  pinMode(sensor_impacto,INPUT);
  pinMode(esp32cam_interior,INPUT);
  pinMode(esp32cam_exterior,INPUT);
  pinMode(sensor_infrarrojo_interior,INPUT);
  pinMode(sensor_infrarrojo_exterior,INPUT);

  activar_alarma = 0;
  digitalWrite(rele_alarma,HIGH);
  digitalWrite(rele_puerta, HIGH);
}

void loop() {

// puerta
  valor_real_esp32cam_interior = digitalRead(esp32cam_interior);
  valor_real_esp32cam_exterior = digitalRead(esp32cam_exterior);
  delay(10);
  //Serial.println(valor_real_sensor_impacto);
  //Serial.println();
  if((valor_real_esp32cam_interior == HIGH  || valor_real_esp32cam_exterior == HIGH) && activar_alarma == 0){
    digitalWrite(rele_puerta, LOW);
    delay(5100);
    digitalWrite(rele_puerta, HIGH);
  }

// Sensor de Impacto
  valor_real_sensor_impacto = digitalRead(sensor_impacto);
  delay(10);
  //Serial.println(valor_real_sensor_impacto);
  //Serial.println();
  if(valor_real_sensor_impacto == HIGH  && activar_alarma == 0){
    digitalWrite(rele_alarma,LOW);
    activar_alarma = 1;
    delay(300);
  }

// Sensor Infrarrojo
  valor_real_sensor_infrarrojo_interior = digitalRead(sensor_infrarrojo_interior);
  valor_real_sensor_infrarrojo_exterior = digitalRead(sensor_infrarrojo_exterior);
  delay(50);
  //Serial.println(valor_real_sensor_infrarrojo_interior);
  //Serial.println();
  if((valor_real_sensor_infrarrojo_interior == HIGH || valor_real_sensor_infrarrojo_exterior == HIGH) && activar_alarma == 0){
    digitalWrite(rele_alarma,LOW);
    activar_alarma = 1;
    delay(300);
  }

// Boton
  valor_real_boton = digitalRead(boton_na_timbre);
  delay(50);
  // Serial.println(valor_real_boton);
  // Serial.println();
  if(valor_real_boton == 1 && valor_temporal_boton == 0){
    if(activar_alarma == 0){
      digitalWrite(rele_alarma,LOW);
      activar_alarma = 1;
      delay(30);
    } else{
      digitalWrite(rele_alarma,HIGH);
      activar_alarma = 0;
      delay(30);
    }
    
  }
  valor_temporal_boton = valor_real_boton;
  // Serial.println("activar alarma: ");
  // Serial.println(activar_alarma);
  // Serial.println();
  //delay(500);
}
