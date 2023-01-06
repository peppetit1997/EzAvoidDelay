/********************************************************************************************************************************
Fichier interface contenant les méthode de la classe AvoidDelay
Développé par : Pierre-Étienne Petit
Sous licence libre (GNU General Public Licence)  
version:*****Date:**********Note:
1.0          2022/12/24     Ajout d'une méthode pour alterner l'état d'une sortie selon un temps "HIGH","LOW" et un état initial.
1.1          2022/12/28     Optimisation du constructeur
1.2          2022/01/06     Ajout des méthodes timer() et smoothFade() / utilisation d'héritage de la classe MoTotimerRop
*********************************************************************************************************************************
Références: 
https://www.digikey.com/en/maker/projects/multi-tasking-the-arduino-part-1/b23d9e65c4d342389d20cbd542c46a28 (Exemple de base)
https://www.udemy.com/course/beginning-c-plus-plus-programming/learn/lecture/9535586#reviews (Constructeur)
https://www.udemy.com/course/beginning-c-plus-plus-programming/learn/lecture/9535588#learning-tools (Constructeur)
*********************************************************************************************************************************
*/
#include <Arduino.h>
#include "AvoidDelay.h"

AvoidDelay::AvoidDelay(const uint8_t outputPin, bool outputState = LOW)
  : outputPin{ outputPin }, outputState{ outputState } {
  pinMode(outputPin, OUTPUT);
  accumuledTime = 0;
  digitalWrite(outputPin, outputState);
}
void AvoidDelay ::toggleOutput(unsigned long highTime = 1000, unsigned long lowTime = 1000) {
  if ((outputState == HIGH) && (millis() - accumuledTime >= highTime)) {
    outputState = LOW;
    accumuledTime = millis();
    digitalWrite(outputPin, outputState);
  } else if ((outputState == LOW) && (millis() - accumuledTime >= lowTime)) {
    outputState = HIGH;
    accumuledTime = millis();
    digitalWrite(outputPin, outputState);
  }
}
void AvoidDelay::timer(const uint8_t inputPin, unsigned long timer = 5000) {
  static bool buttonState = digitalRead(inputPin);
  if (buttonState != digitalRead(inputPin) && !running()) {
    setTime(timer);
    digitalWrite(outputPin, !outputState);
  }
  if (expired()) {
    digitalWrite(outputPin, outputState);
  }
}
void AvoidDelay::smoothFade(unsigned long fadeTime = 2000) {
  int ledValue = 128 + 127 * cos(2 * PI / fadeTime * millis());
  analogWrite(outputPin, ledValue);
  Serial.println(ledValue);
}
