// --- Code Arduino pour Relais NeuroSky ---
const int RELAY_CONCENTRATION = 2;
const int RELAY_RELAXATION = 3;
const int RELAY_BLINK = 4;

// Variables pour stocker l'état
bool concentState = false;
bool relaxState = false;
bool blinkState = false;

// Timer pour éteindre le relais clignement automatiquement
unsigned long blinkTimer = 0;

void setup() {
  Serial.begin(115200); // Vitesse élevée pour réduire la latence
  
  pinMode(RELAY_CONCENTRATION, OUTPUT);
  pinMode(RELAY_RELAXATION, OUTPUT);
  pinMode(RELAY_BLINK, OUTPUT);

  // Initialisation : tout éteint (HIGH ou LOW selon votre module relais)
  // Souvent les relais sont actifs à LOW. Adaptez si nécessaire.
  digitalWrite(RELAY_CONCENTRATION, HIGH); 
  digitalWrite(RELAY_RELAXATION, HIGH);
  digitalWrite(RELAY_BLINK, HIGH);
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();

    // Protocole simple : 
    // 'C' = Concentration ON, 'c' = OFF
    // 'R' = Relaxation ON,   'r' = OFF
    // 'B' = Clignement (Impulsion)
    
    switch (command) {
      case 'C':
        digitalWrite(RELAY_CONCENTRATION, LOW); // Active
        break;
      case 'c':
        digitalWrite(RELAY_CONCENTRATION, HIGH); // Désactive
        break;
      case 'R':
        digitalWrite(RELAY_RELAXATION, LOW);
        break;
      case 'r':
        digitalWrite(RELAY_RELAXATION, HIGH);
        break;
      case 'B':
        digitalWrite(RELAY_BLINK, LOW);
        blinkTimer = millis();
        blinkState = true;
        break;
    }
  }

  // Gestion de l'impulsion pour le clignement (reste actif 500ms)
  if (blinkState && (millis() - blinkTimer > 500)) {
    digitalWrite(RELAY_BLINK, HIGH);
    blinkState = false;
  }
}
