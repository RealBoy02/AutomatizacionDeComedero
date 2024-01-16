#include "BluetoothSerial.h"
#include <ESP32Servo.h>

Servo servoMotor;
Servo servoMotor1;
char command; // Variable para almacenar comandos Bluetooth

const int trigPin = 5;
const int echoPin = 19;


#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float dcm;

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup() {
  servoMotor.attach(15); // Conecta el servo al pin 15
  servoMotor1.attach(18); // Conecta el servo al pin 15
  Serial.begin(9600);
  SerialBT.begin("Charizards"); // Nombre del dispositivo Bluetooth
  Serial.println("El dispositivo se ha iniciado, ¡ahora puedes emparejarlo por Bluetooth!");

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    command = SerialBT.read();
    if (command == 'w') {
      servoMotor.write(180); // Mover servo a 180 grados
    } else if (command == 'x') {
      servoMotor.write(0);   // Mover servo a 0 grados
    }
    if (command == 'y') {
      servoMotor1.write(180); // Mover servo a 180 grados
    } else if (command == 'z') {
      servoMotor1.write(0);   // Mover servo a 0 grados
    }

  }
    // Resto del código para el sensor ultrasónico
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    dcm = duration * SOUND_SPEED / 2;

    // Código para determinar el nivel del tanque basado en la distancia
    if (dcm > 0 && dcm <= 40) {
      SerialBT.println("El tanque está completamente lleno");
    } else if (dcm > 40 && dcm <= 60) {
      SerialBT.println("El tanque está lleno al 90%");
      SerialBT.println(";");
    } else if (dcm > 60 && dcm <= 80) {
      SerialBT.println("El tanque está lleno al 80%");
      SerialBT.println(";");
    } else if (dcm > 80 && dcm <= 100) {
      SerialBT.println("El tanque está lleno al 70%");
      SerialBT.println(";");
    } else if (dcm > 100 && dcm <= 120) {
      SerialBT.println("El tanque está lleno al 60%");
      SerialBT.println(";");
    } else if (dcm > 120 && dcm <= 140) {
      SerialBT.println("El tanque está lleno al 50%");
      SerialBT.println(";");
    } else if (dcm > 140 && dcm <= 160) {
      SerialBT.println("El tanque está lleno al 40%");
      SerialBT.println(";");
    } else if (dcm > 160 && dcm <= 180) {
      SerialBT.println("El tanque está lleno al 30%");
      SerialBT.println(";");
    } else if (dcm > 180 && dcm <= 200) {
      SerialBT.println("El tanque está lleno al 20%");
      SerialBT.println(";");
    } else if(dcm > 200 && dcm <= 220){
      SerialBT.println("El tanque está lleno al 10%");
      SerialBT.println(";");
    }
      delay(1000);
}
