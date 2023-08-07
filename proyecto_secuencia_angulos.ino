#include <Wire.h> // Biblioteca para la comunicación I2C
#include <Servo.h> // Biblioteca para controlar los servos

#include <ax12.h>
#include <BioloidController.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

int servo1Pos = 0; // Posición inicial del servo 1
int servo2Pos = 512; // Posición inicial del servo 2
int servo3Pos = 512; // Posición inicial del servo 3
int servo4Pos = 512; // Posición inicial del servo 4
int servo5Pos = 512; // Posición inicial del servo 5
String command = ""; // Variable para almacenar el comando ingresado
int angleE = 0; // Obtener el ángulo

void setup() {
  Wire.begin(); // Inicializa la comunicación I2C
  Wire.onReceive(receiveEvent); // Configura la función para recibir datos por I2C
  SetPosition(1,90);// Conecta el servo 1 al pin 9
  SetPosition(2,512); // Conecta el servo 2 al pin 10
  SetPosition(3,512); // Conecta el servo 3 al pin 11
  SetPosition(4,512); // Conecta el servo 4 al pin 12
  SetPosition(5,512); // Conecta el servo 5 al pin 13

  Serial.begin(9600); // Inicializa la comunicación serial para mostrar mensajes de depuración
    
}

void loop() {
  // Aquí puedes agregar cualquier otro código que necesites para tu proyecto

  // Ejemplo de menú para enviar parámetros a los servos
  if (Serial.available()) {
    char c = Serial.read(); // Leer el siguiente carácter disponible
    
    if (c == '.' ) { // Si no se encuentra el caracter de nueva línea (\n), agregarlo al comando
      Serial.print("IF COMMAND");
      processCommand();
      command = ""; // Reiniciar el comando para futuras lecturas
      Serial.print("command");
    } else { // Si se encuentra el caracter de nueva línea, procesar el comando completo
      Serial.print("aqui 1");
      command += c;
    }
  }
}

void processCommand() {
  Serial.print("aqui 6");
  
  
  if (command.startsWith("s")) {
    int servoNumber = command.substring(1,2).toInt(); // Obtener el número del servo
    int angle = command.substring(3).toInt(); // Obtener el ángulo
    int angleE = map(angle, 0, 180, 0, 1023); // Obtener el ángulo
    Serial.print("aqui 8 ");
    
    
    // Verificar el número del servo y enviar el ángulo correspondiente
    switch (servoNumber) {
      
      case 1:
        angle = constrain(angle, 0, 180); // Limitar el ángulo entre 0 y 180 grados
        servo1.write(angle); // Enviar el ángulo al servo 1
        Serial.print("Servo 1: ");
        Serial.println(angle);
        Serial.print("angleE: ");
        Serial.println(angleE);
        SetPosition(1,angleE); // Conecta el servo 5 al pin 13
        
        break;
        
      case 2:
        angle = constrain(angle, 0, 180);
        servo2.write(angle);
        Serial.print("Servo 2: ");
        Serial.println(angle);
        Serial.println(angleE);
        SetPosition(2,angleE);
        break;
        
      case 3:
        angle = constrain(angle, 0, 180);
        servo3.write(angle);
        Serial.print("Servo 3: ");
        Serial.println(angle);
        Serial.println(angleE);
        SetPosition(3,angleE);
        break;
        
      case 4:
        angle = constrain(angle, 0, 180);
        servo4.write(angle);
        Serial.print("Servo 4: ");
        Serial.println(angle);
        Serial.println(angleE);
        SetPosition(4,angleE);
        break;
      case 5:
        angle = constrain(angle, 0, 180);
        servo5.write(angle);
        Serial.print("Servo 5: ");
        Serial.println(angle);
        Serial.println(angleE);
        SetPosition(5,angleE);
        break;
        
      default:
        Serial.println("Servo inválido. Por favor, selecciona un servo válido.");
        break;
    }
  }
  
  command = ""; // Reiniciar el comando para futuras lecturas
}

void receiveEvent(int bytes) {
  while (Wire.available()) {
    char option = Wire.read(); // Lee la opción seleccionada desde el maestro I2C
    int angle;
    switch (option) {
      case '1':
        if (Wire.available()) {
          angle = Wire.read();
          servo1Pos = constrain(angle, 0, 180);
          servo1.write(servo1Pos);
        }
        break;
      case '2':
        if (Wire.available()) {
          angle = Wire.read();
          servo2Pos = constrain(angle, 0, 180);
          servo2.write(servo2Pos);
        }
        break;
      case '3':
        if (Wire.available()) {
          angle = Wire.read();
          servo3Pos = constrain(angle, 0, 180);
          servo3.write(servo3Pos);
        }
        break;
      case '4':
        if (Wire.available()) {
          angle = Wire.read();
          servo4Pos = constrain(angle, 0, 180);
          servo4.write(servo4Pos);
        }
        break;
      case '5':
        if (Wire.available()) {
          angle = Wire.read();
          servo5Pos = constrain(angle, 0, 180);
          servo5.write(servo5Pos);
        }
        break;
      default:
        break;
    }
  }
}





