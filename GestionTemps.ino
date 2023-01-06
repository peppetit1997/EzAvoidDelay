/*********************************************************************************************************
Exemple d'utilisation de la fonction toggleOutput comme membre de la classe HandlingTime 
Développé par : Pierre-Étienne Petit
Sous licence libre (GNU General Public Licence)  
version:*****Date:**********Note
1.0        2022/12/24       Utilisation de la méthode toggleOutput();
1.1        2022/01/06       Utilisation des méthodes Timer() et smootFade()
***********************************************************************************************************
*/
#include "AvoidDelay.h"  //Extension "header" pour permettre l'utilisation de la classe par le "main".

//Constructeurs des objets led1, led2 et led3.
//(Pin,État initial "LOW" par défault)
AvoidDelay led1(7);
AvoidDelay led2(4);
AvoidDelay led3(13);
AvoidDelay led4(9);
void setup() {
  //Les pins sont instanciées dans le constructeur
}
void loop() {
  led1.timer(8);                  //Temporisation d'une sortie selon un input digital (Entrée digitale, temps de temporisation défaut 5s)
  led2.toggleOutput(2000, 1000);  //Clignotement (Temps "HIGH", Temps "LOW")
  led3.toggleOutput();            //Clignotement (1s "HIGH", 1s "LOW")
  led4.smoothFade(5000);          //Exemple fade sans utilisation de delais
}
