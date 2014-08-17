
///
/// --- Déclaration des variables GLOBALES

/// *** Brochage du 74HC595
//Broche connectée au ST_CP du 74HC595 (PIN 12)
const int verrou = 11;
//Broche connectée au SH_CP du 74HC595 (PIN 11)
const int horloge = 12;
//Broche connectée au DS du 74HC595 (PIN 14)
const int data = 10;

// *** Brochage dues interrupteurs
const int button = 2;


// --- Définition des différents caractères à transmettre pour afficher un chiffre
// --- Définis par correspondance binaire
// aevc brochage suivant au niveau du 74HC595
// 74 -> segment du 5101AS à Katode Commune
// Q0 -> a
// Q1 -> b    etc...
// Q7 -> pt
// pour aficher le point, il suffit de faire +1 à la valeur à transmettre
// donc pour afficher un 5 : il faut allumer les segments : a,c,d,f,g
// Segments   a b c d e f g pt
// Q(x)       0 1 2 3 4 5 6 7
// Val.Bin    1 0 1 1 0 1 1 0
// Val Dec    182
// Voilou tout simplement
const char seg_1 = 96; 
const char seg_2 = 218; 
const char seg_3 = 242; 
const char seg_4 = 102; 
const char seg_5 = 182; 
const char seg_6 = 190; 
const char seg_7 = 224; 
const char seg_8 = 254; 
const char seg_9 = 246; 
const char seg_0 = 252;
const char seg_clear = 0; 


boolean bClear = false ;




///
/// --- Fonction "setup"
void setup() {
  // on met la broche du bouton en INPUT_PULLUP
  // de cetta manière l'état logique du bouton (LOW , HIGH) correspond à l'état pysique LOW:enfoncé
  pinMode(button,INPUT_PULLUP) ;
  //On met les broches du 74HC en sortie
  pinMode(verrou, OUTPUT);
  pinMode(horloge, OUTPUT);
  pinMode(data, OUTPUT);
}



void loop() {
  int buttonStatus = digitalRead(button) ;
  int randNumber = 0 ;
  int randIter = 0;
  
  // si le bonton a été appuyé
  if (buttonStatus == LOW) {
    // init du générateur de nombre aléatoires
    randomSeed(analogRead(0));
    delay(50);
    randIter = random(0 , 32763);
    randomSeed(randIter);
    delay(50);
    // on généère un nombre aléatoire
    randIter = random(80, 100);
    // on fait des boucles pour initaliser le dé
    for (int i=0 ; i < randIter ; i++) {
      randNumber = random(0, 9);
      display_5101_74HC(randNumber) ;
      delay(50);
    }
    delay(5000);
    bClear = false ;
  }
  
  // on clear...
  if (!bClear) {
    int cpt = 99 ;
    display_5101_74HC(cpt) ;
    bClear = true ;
  }
  
  // on fait une pause de 100ms
  delay(100);
}



void display_5101_74HC(int digit) {
  // direction d'écriture...
  // pour écrire de Q7 vers Q0 : LSBFIRST
  // pour écrire de Q0 vers Q7 : MSBFIRST
  boolean WriteDir = LSBFIRST ;
  
   //On active le verrou le temps de transférer les données
  digitalWrite(verrou, LOW);
  switch (digit) {
    case 0 :
      //on envoi toutes les données grâce à shiftOut (octet inversée avec '~' pour piloter les LED à l'état bas)
      shiftOut(data, horloge, WriteDir, seg_0);
      break ;
      
    case 1 :
      shiftOut(data, horloge, WriteDir, seg_1);
      break ;
      
    case 2 :
      shiftOut(data, horloge, WriteDir, seg_2);
      break ;
      
    case 3 :
      shiftOut(data, horloge, WriteDir, seg_3);
      break ;
      
    case 4 :
      shiftOut(data, horloge, WriteDir, seg_4);
      break ;
      
    case 5 :
      shiftOut(data, horloge, WriteDir, seg_5);
      break ;
      
    case 6 :
      shiftOut(data, horloge, WriteDir, seg_6);
      break ;
      
    case 7 :
      shiftOut(data, horloge, WriteDir, seg_7);
      break ;
      
    case 8 :
      shiftOut(data, horloge, WriteDir, seg_8);
      break ;
      
    case 9 :
      shiftOut(data, horloge, WriteDir, seg_9);
      break ;
      
    default :
      shiftOut(data, horloge, WriteDir, seg_clear);
      break ;
  }  
    //et enfin on relâche le verrou
  digitalWrite(verrou, HIGH);

}



