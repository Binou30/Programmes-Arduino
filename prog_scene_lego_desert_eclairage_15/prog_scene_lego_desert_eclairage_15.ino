// --- Déclaration des broches ---
const int ledjaunecoffrepin = 10;
const int boutonledjaunecoffrepin = 8;
const int ledjaunelampadairepin = 6;
const int boutonledjaunelampadairepin = 2;

const int ledrougemissile1pin = 9;
const int ledrougemissile2pin = 11;
const int boutonmissilepin = 7;

// --- Variables LED coffre (pulsation) ---
bool cycleledjaunecoffre = false;
bool dernieretatboutonledjaunecoffre = HIGH;
unsigned long derniertempsledjaunecoffre = 0;
int niveauledjaunecoffre = 0;
int sensledjaunecoffre = 1;

// --- Variables LED lampadaire (ON/OFF) ---
bool etatledlampadaire = false;
bool dernieretatboutonledlampadaire = HIGH;

// --- Variables missiles (clignotement aléatoire) ---
bool missilesactifs = false;
bool dernieretatboutonmissile = HIGH;
unsigned long derniertempsmissile = 0;

const int boutonmoteurpin = 5;
const int moteurpin = 3;
int etatboutonmoteur = 0;

bool etatmoteur = false;
bool dernieretatboutonmoteur = HIGH;

void setup() {
  pinMode(ledjaunecoffrepin, OUTPUT);
  pinMode(boutonledjaunecoffrepin, INPUT_PULLUP);

  pinMode(ledjaunelampadairepin, OUTPUT);
  pinMode(boutonledjaunelampadairepin, INPUT_PULLUP);

  pinMode(ledrougemissile1pin, OUTPUT);
  pinMode(ledrougemissile2pin, OUTPUT);
  pinMode(boutonmissilepin, INPUT_PULLUP);

  pinMode(moteurpin, OUTPUT);
  pinMode(boutonmoteurpin, INPUT_PULLUP);
  analogWrite(moteurpin, 0);

  randomSeed(analogRead(A0)); // initialise le générateur aléatoire

}

void loop() {
  // --- GESTION LED COFFRE (pulsation) ---
  bool etatBoutonCoffre = digitalRead(boutonledjaunecoffrepin);

  if (dernieretatboutonledjaunecoffre == HIGH && etatBoutonCoffre == LOW) {
    cycleledjaunecoffre = !cycleledjaunecoffre;
    delay(200);
  }
  dernieretatboutonledjaunecoffre = etatBoutonCoffre;

  if (cycleledjaunecoffre) {
    unsigned long maintenant = millis();
    if (maintenant - derniertempsledjaunecoffre > 5) {
      derniertempsledjaunecoffre = maintenant;

      niveauledjaunecoffre += sensledjaunecoffre;
      if (niveauledjaunecoffre >= 255) sensledjaunecoffre = -1;
      else if (niveauledjaunecoffre <= 0) sensledjaunecoffre = 1;

      analogWrite(ledjaunecoffrepin, niveauledjaunecoffre);
    }
  } else {
    analogWrite(ledjaunecoffrepin, 0);
  }

  // --- GESTION LED LAMPADAIRE (ON/OFF) ---
  bool etatBoutonLampadaire = digitalRead(boutonledjaunelampadairepin);

  if (dernieretatboutonledlampadaire == HIGH && etatBoutonLampadaire == LOW) {
    etatledlampadaire = !etatledlampadaire;
    digitalWrite(ledjaunelampadairepin, etatledlampadaire ? HIGH : LOW);
    delay(200);
  }
  dernieretatboutonledlampadaire = etatBoutonLampadaire;


  // --- GESTION MISSILES (clignotement aléatoire) ---
  bool etatBoutonMissile = digitalRead(boutonmissilepin);

  if (dernieretatboutonmissile == HIGH && etatBoutonMissile == LOW) {
    missilesactifs = !missilesactifs;
    if (!missilesactifs) {
      digitalWrite(ledrougemissile1pin, LOW);
      digitalWrite(ledrougemissile2pin, LOW);
    }
    delay(200);
  }
  dernieretatboutonmissile = etatBoutonMissile;

  if (missilesactifs) {
    unsigned long maintenant = millis();
    if (maintenant - derniertempsmissile > random(100, 400)) {
      derniertempsmissile = maintenant;

      // Choisir aléatoirement une ou deux LEDs à allumer brièvement
      int tir = random(0, 3); // 0 = aucune, 1 = LED 1, 2 = LED 2, 3 = les deux

      digitalWrite(ledrougemissile1pin, (tir == 1 || tir == 3) ? HIGH : LOW);
      digitalWrite(ledrougemissile2pin, (tir == 2 || tir == 3) ? HIGH : LOW);
    }
  }

  bool etatBoutonMoteur = digitalRead(boutonmoteurpin);

  if (dernieretatboutonmoteur == HIGH && etatBoutonMoteur == LOW) {
    etatmoteur = !etatmoteur;
    delay(200);
  }
  dernieretatboutonmoteur = etatBoutonMoteur;

  if (etatmoteur) {
    analogWrite(moteurpin, 15); // basse vitesse
  } else {
    analogWrite(moteurpin, 0);  // OFF
  }
}
