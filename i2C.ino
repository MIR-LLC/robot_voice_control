#define ESP_SLAVE_ADDR       0x36
#include <Wire.h>

void setup() {
 Wire.begin(ESP_SLAVE_ADDR);   // Устанавливаем адрес slave устройства I2C
 Wire.onReceive(receiveEvent); // Если произошло какое либо событие
 Serial.begin(9600);           // Вывод в лог
 
 /* инициализируем все пины для управления двигателями как outputs. 
 В данном примере управление скоростью отсутствует. Для управления скоростью снимите перемычки на драйвере ENA и ENB, содините их с платой, инициализируйте
 */
 pinMode(9, OUTPUT);           // пин управления правым двигателем
 pinMode(8, OUTPUT);           // пин управления правым двигателем
 pinMode(11, OUTPUT);           // пин управления левым двигателем
 pinMode(10, OUTPUT);           // пин управления левым двигателем
}

void loop() {
  //внутри основной функции ничего нет, т.к. управление осуществляется по прерыванию (по команде от модуля)
  delay(100);
}

/* I2C - протокол с использованием технолгии master-slave устройств
   В данной конфигурации роль платы ардуино - slave (ведомого устройства)
   Роль AI-модуля - мастер (главное устройство, которое отправляет всем устройствам slave команды)
*/
void receiveEvent(int howMany) {
 String command; //Объявление переменной, в которую будем записывать пришедшую команду
 
  // Считываем в цикле все пришедшие символы в переменную command
  while (1 < Wire.available()) { 
    char c = Wire.read();  
    command += c;  
  }
    char x = Wire.read();    // последний байт
    command += x;

  Serial.println(command); //проверка считывания команды в serial monitor в среде разработки
  
  //далее идет поиск подстроки приходящей команды. В зависимости от пришедшей команды выбирается действие для двигателей.

  if (command.indexOf("вперед") != -1) { 
    /*далее вы можете реализовать управление двигателями любым удобным способом.
    Здесь это сделано напрямую, с помощью подчи управляющих сигналов на пины управления, соединенных с драйвером двигателей.
    Вы можете использовать различные библиотеки для расширения возможностей (например, для управления скоростью)
    */
    //подано напряжение на левый и правый двигатель, они крутятся в одну сторону, затем напряжение снимается - двигатели останавливаются
    //экспериментируйте со временем работы двигателей, или их скоростью (если подключили управление скоростью)
    digitalWrite(9, HIGH);  
    digitalWrite(8, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
	  delay(500000);
    //двигатели выключаем
	  digitalWrite(9,LOW);
	  digitalWrite(8, LOW);
    digitalWrite(10,LOW);
	  digitalWrite(11, LOW);
  }
  
  if (command.indexOf("назад") != -1) { 
    //для движения назад меняем полярность приложенного напряжения на двигателях
    digitalWrite(9, LOW);
    digitalWrite(8, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
	  delay(100000);
	  digitalWrite(9,LOW);
	  digitalWrite(8, LOW);	  
    digitalWrite(10,LOW);
	  digitalWrite(11, LOW);
  }

    if (command.indexOf("старт") != -1) { 
    digitalWrite(9, HIGH);  
    digitalWrite(8, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    //вариант реализации команды - движение без остановки, до получения другой команды. 
    //Будьте острожны, при работающих двигятелях модуль может не услышать вашу команду
  }

    if (command.indexOf("стоп") != -1) { 
	  digitalWrite(9,LOW);
	  digitalWrite(8, LOW);	  
    digitalWrite(10,LOW);
	  digitalWrite(11, LOW);
  }

    if (command.indexOf("вправо") != -1) { 
    digitalWrite(9, LOW);  
    digitalWrite(8, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
	  delay(30000);
	  digitalWrite(9,LOW);
	  digitalWrite(8, LOW);	  
    digitalWrite(10,LOW);
	  digitalWrite(11, LOW);
  }

    if (command.indexOf("влево") != -1) { 
    digitalWrite(9, HIGH);  
    digitalWrite(8, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
	  delay(30000);
	  digitalWrite(9,LOW);
	  digitalWrite(8, LOW);	  
    digitalWrite(10,LOW);
	  digitalWrite(11, LOW);
  }

    if (command.indexOf("домой") != -1) { 
 //можете придумать команду сами )
  }

    if (command.indexOf("медленно") != -1) { 
  }

    if (command.indexOf("быстро") != -1) { 
  }
}

