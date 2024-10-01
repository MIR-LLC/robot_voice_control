#include <SoftwareSerial.h>

const int in1 = 7;             // Пин движения вперёд для колёс с правой стороны
const int in2 = 6;             // Пин движения назад для колёс с правой стороны (+ШИМ)
const int in3 = 5;             // Пин движения вперёд для колёс с левой стороны (+ШИМ)
const int in4 = 4;             // Пин движения назад для колёс с левой стороны
const int ble_rx = 3;          // Bluetooth module RX pin
const int ble_tx = 2;          // Bluetooth module TD pin
const int motion_delay = 550;  // Engine running time

SoftwareSerial mySerial(ble_tx, ble_rx);

void setup() {
  Serial.begin(9600);  // Настраиваем Serial для вывода логов
  mySerial.begin(9600);

  // Инициализируем пины для управления двигателями как выходы
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  if (mySerial.available()) {
    String command = "";
    command = mySerial.readString();
    Serial.println("DATA RECEIVED:");
    Serial.println(command);

    if (command.indexOf("вперед") != -1) {
      moveForward();
    } else if (command.indexOf("назад") != -1) {
      moveBack();
    } else if (command.indexOf("вправо") != -1) {
      moveRight();
    } else if (command.indexOf("влево") != -1) {
      moveLeft();
    }
  }
}

// Движение вперед
void moveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(motion_delay);
  stopMotors();
}

// Движение назад
void moveBack() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(motion_delay);
  stopMotors();
}

// Поворот вправо
void moveRight() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(motion_delay);
  stopMotors();
}

// Поворот влево
void moveLeft() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(motion_delay);
  stopMotors();
}

// Остановка двигателей
void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}