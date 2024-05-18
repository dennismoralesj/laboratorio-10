#include <Servo.h>

Servo myServo;  // Crea un objeto de tipo Servo

int servoPin = A0;  // Pin al que está conectado el servo
int angle = 90;     // Ángulo inicial del servo
int speed = 50;     // Velocidad inicial (0 a 100)

void setup() {
  Serial.begin(9600);  // Inicia la comunicación serial a 9600 baudios
  myServo.attach(servoPin);  // Asigna el pin al servo
  myServo.write(angle);  // Establece el ángulo inicial
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();  // Lee el comando desde la comunicación serial

    // Si se recibe la letra 'D', gira el servo a la derecha
    if (command == 'D') {
      int targetAngle = angle + 180;  // Incrementa el ángulo
      if (targetAngle > 180) targetAngle = 180;  // Limita el ángulo máximo
      moveServo(targetAngle);
      angle = targetAngle;
    }
    // Si se recibe la letra 'I', gira el servo a la izquierda
    else if (command == 'I') {
      int targetAngle = angle - 180;  // Decrementa el ángulo
      if (targetAngle < 0) targetAngle = 0;  // Limita el ángulo mínimo
      moveServo(targetAngle);
      angle = targetAngle;
    }
    // Si se recibe la letra 'V', el siguiente valor es la velocidad
    else if (command == 'V') {
      while (Serial.available() == 0);  // Espera a que llegue el siguiente byte
      int newSpeed = Serial.parseInt();  // Lee el nuevo valor de velocidad
      if (newSpeed >= 0 && newSpeed <= 100) {
        speed = newSpeed;  // Asigna la nueva velocidad
      }
    }
    // Si se recibe la letra 'G', el siguiente valor es el ángulo
    else if (command == 'G') {
      while (Serial.available() == 0);  // Espera a que llegue el siguiente byte
      int newAngle = Serial.parseInt();  // Lee el nuevo valor del ángulo
      if (newAngle >= 0 && newAngle <= 180) {
        moveServo(newAngle);
        angle = newAngle;
      }
    }
  }
}

void moveServo(int targetAngle) {
  int currentAngle = myServo.read();  // Lee el ángulo actual del servo
  int step = (targetAngle > currentAngle) ? 1 : -1;  // Determina la dirección del movimiento

  while (currentAngle != targetAngle) {
    currentAngle += step;  // Ajusta el ángulo actual en pequeños pasos
    myServo.write(currentAngle);  // Envía el ángulo al servo
    delay(map(speed, 0, 100, 20, 1));  // Ajusta el delay según la velocidad
  }
}