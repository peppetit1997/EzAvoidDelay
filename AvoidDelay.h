/********************************************************************************************************************************
Classe pour gérer le temps sur une sortie
Développé par : Pierre-Étienne Petit
Sous licence libre (GNU General Public Licence)  
version:*****Date:**********Note
1.0          2022/12/24     Ajout d'une méthode pour alterner l'état d'une pin selon un temps "On","Off" et un état initial.
1.1          2022/12/28     Optimisation du constructeur
1.2          2022/01/06     Ajout des méthodes timer() et smoothFade() / utilisation d'héritage de la classe MoTotimerRop
*********************************************************************************************************************************
Références: 
https://www.digikey.com/en/maker/projects/multi-tasking-the-arduino-part-1/b23d9e65c4d342389d20cbd542c46a28 (Exemple de base)
https://www.udemy.com/course/beginning-c-plus-plus-programming/learn/lecture/9535586#reviews (Constructeur)
https://www.udemy.com/course/beginning-c-plus-plus-programming/learn/lecture/9535588#learning-tools (Constructeur)
https://github.com/MicroBahner/MobaTools (Classe MoToTimerRop)
*********************************************************************************************************************************
*/
#include "MotoTimer.h"
#ifndef _AVOIDELAY_H_
#define _AVOIDELAY_H_
class AvoidDelay : public MoToTimerRop {
private:
  int outputPin;                //Pin physique sur l'Arduino
  unsigned long highTime;       //Temps où l'on veut la sortie comme "HIGH"
  unsigned long lowTime;        //Temps où l'ont veut la sortie comme "LOW"
  unsigned long accumuledTime;  //Temps accumulé sur un compteur
  bool outputState;             //État de la sortie Initialisée sur "LOW"

public:
  //Constructeur
  AvoidDelay(const uint8_t outputPin, bool outputState = LOW);
  //Méthode à utiliser pour alterner l'état d'une sortie selon un temps donné.
  void toggleOutput(unsigned long highTime = 1000, unsigned long lowTime = 1000);
  //Méthode pour temporiser une sortie sur changement d'état d'une entrée.
  void timer(const uint8_t inputPin, unsigned long timer = 5000);
  //Méthode "Fader" un LED.
  void smoothFade(unsigned long fadeTime = 2000);
};
#endif
