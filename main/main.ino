/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPL6WGmkSdhy"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "nGxHCML5rH2-E1BBaJhEojKJG3eOzrqL"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Mi";
char pass[] = "12345678900";

// Define Pin
const int ldrPin = 35;
const int triggerPin_1 = 13;
const int echoPin_1 = 12;
unsigned int duration_1;
unsigned int distance_1;
const int triggerPin_2 = 17;
const int echoPin_2 = 16;
unsigned int duration_2;
unsigned int distance_2;

void setup() {
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  pinMode(triggerPin_1, OUTPUT);
  pinMode(echoPin_1, INPUT);
  pinMode(triggerPin_2, OUTPUT);
  pinMode(echoPin_2, INPUT);
  Serial.begin(9600);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  Blynk.run();
  readLDR();
  readSensor_1();
  readSensor_2();
  Serial.println(" ");
  delay(1000);
}

void readLDR() {
  int analogValue = analogRead(ldrPin);

  Serial.print("Analog Value = ");
  Serial.print(analogValue);   // the raw analog reading

  // We'll have a few threshholds, qualitatively determined
  if (analogValue < 100) {
    Serial.println(" = Gelap");
    Blynk.virtualWrite(V4, 1); // Akan menampilkan 1 di blynk
  } else {
    Serial.println(" = Terang");
    Blynk.virtualWrite(V4, 0); // Akan menampilkan 0 di blynk
  }
  delay(500);
}

void readSensor_1() {
  digitalWrite(triggerPin_1, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin_1, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin_1, LOW);
  duration_1 = pulseIn(echoPin_1, HIGH);
  distance_1 = (duration_1 / 2) / 28.5;
  Serial.print("Sensor 1 = ");
  Serial.print(distance_1);
  Serial.println(" cm");
  Blynk.virtualWrite(V0, distance_1);
  if (distance_1 <= 15) {
    Blynk.virtualWrite(V2, 1);
  }else{
    Blynk.virtualWrite(V2, 0);
  }
}
void readSensor_2() {
  digitalWrite(triggerPin_2, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin_2, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin_2, LOW);
  duration_2 = pulseIn(echoPin_2, HIGH);
  distance_2 = (duration_2 / 2) / 28.5;
  Serial.print("Sensor 2 = ");
  Serial.print(distance_2);
  Serial.println(" cm");
  Blynk.virtualWrite(V1, distance_2);
  if (distance_2 <= 15) {
    Blynk.virtualWrite(V3, 1);
  } else{
    Blynk.virtualWrite(V3, 0);
  }
}