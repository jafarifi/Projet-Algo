#include <MKRWAN.h>

LoRaModem modem;

String appEui = "a8610a3435317a0f";
String appKey = "10101010101010101010101010101010";

void setup() {
  randomSeed(analogRead(0)); // Initialisation du générateur de nombres aléatoires avec une valeur aléatoire
  Serial.begin(115200); // Initialise la communication série à 115200 bauds
  while (!Serial);

  if (!modem.begin(EU868)) {
    Serial.println("Failed to start module");
    while (1) {}
  };
  Serial.print("Your module version is: ");
  Serial.println(modem.version());
  Serial.print("Your device EUI is: ");
  Serial.println(modem.deviceEUI());

  int connected = modem.joinOTAA(appEui, appKey);
  if (!connected) {
    Serial.println("Something went wrong; are you indoor? Move near a window and retry");
    while (1) {}
  }

  pinMode(LED_BUILTIN, OUTPUT);
  modem.minPollInterval(60);
}

void loop() {
  Serial.print("\n\n Coordonnees \n\n");

  int coordonneeX = random(-250, 250); // Génère un nombre aléatoire entre -250 et 200 pour la coordonnée X
  int coordonneeY = random(-250, 250); // Génère un nombre aléatoire entre -250 et 200 pour la coordonnée Y
  int Temperature = random(37,5, 38); // Génère une température aléatoire entre 35 et 40
  int BPM = random(14, 40); // Génère des battements aléatoires
  int Frequence_respiratoire = random(14, 40); // Génère des fréquences respiratoires aléatoires

  String Message = "Petit Tonerre:" + String(coordonneeX) + ":" + String(coordonneeY) + ":" + String(Temperature) + ":" + String(BPM) + ":" + String(Frequence_respiratoire);
  Serial.println(Message); // Concaténer les variables coordonneeX et coordonneeY

  modem.beginPacket();
  modem.print(Message);
  modem.endPacket();
  Serial.println("Message envoyé : " + Message);

  digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(10000);
}