#define BLYNK_TEMPLATE_ID "TMPL3HhuHgd_2"      

#define BLYNK_TEMPLATE_NAME "flood monitor"

#define BLYNK_AUTH_TOKEN "n_AwNwRJejmlOjXwgVcBI69ersH5IA_k"  

#define BLYNK_PRINT Serial

#include <WiFi.h>

#include <BlynkSimpleEsp32.h>

#include <Wire.h>

#include <LiquidCrystal_I2C.h>

#include <ESP32Servo.h>

char ssid[] = "Wokwi-GUEST";

char pass[] = "";

#define TRIG_PIN 5

#define ECHO_PIN 18

#define BUZZER_PIN 27

#define SERVO_PIN 13

LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo gateServo;

BlynkTimer timer;

float distanceCm;

String floodStatus = "SAFE";

float readUltrasonicDistance() {

  digitalWrite(TRIG_PIN, LOW);

  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);

  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) return -1;

  return duration * 0.0343 / 2;

}

void buzzerOff() {

  noTone(BUZZER_PIN);

  digitalWrite(BUZZER_PIN, LOW);

}

void buzzerOn() {

  tone(BUZZER_PIN, 1000);

}

void sendToBlynk() {

  if (Blynk.connected()) {

    Blynk.virtualWrite(V0, distanceCm);

    Blynk.virtualWrite(V1, floodStatus);

    if (floodStatus == "SAFE") {

      Blynk.virtualWrite(V2, 0);

    } else {

      Blynk.virtualWrite(V2, 255);

    }

    Serial.print("Sent to Blynk -> Level: ");

    Serial.print(distanceCm, 1);

    Serial.print(" cm | Status: ");

    Serial.println(floodStatus);

  }

}

void updateSystem() {

  distanceCm = readUltrasonicDistance();

  lcd.clear();

  lcd.setCursor(0, 0);

  lcd.print("Level: ");

  if (distanceCm < 0) {

    lcd.print("Error");

  } else {

    lcd.print(distanceCm, 1);

    lcd.print("cm");

  }

  if (distanceCm < 0) {

    floodStatus = "SENSOR ERROR";

    lcd.setCursor(0, 1);

    lcd.print("Sensor Error");

    gateServo.write(0);

    buzzerOn();

    sendToBlynk();

    return;

  }

  if (distanceCm > 80) {

    floodStatus = "SAFE";

    gateServo.write(0);

    buzzerOff();

    lcd.setCursor(0, 1);

    lcd.print("Status: SAFE");

  }

  else if (distanceCm >= 40 && distanceCm <= 80) {

    floodStatus = "ALERT";

    gateServo.write(45);

    tone(BUZZER_PIN, 1000, 300);   // Short beep

    lcd.setCursor(0, 1);

    lcd.print("Status: ALERT");

  }

  else {  // Flood condition

    floodStatus = "FLOOD ALERT";

    gateServo.write(90);

    buzzerOn();

    lcd.setCursor(0, 1);

    lcd.print("FLOOD WARNING");

    // Push Notification

    Blynk.logEvent("FLOOD_ALERT", "🚨 Flood Risk! Level: " + String(distanceCm, 1) + " cm");

  }

  sendToBlynk();

}

void setup() {

  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);

  pinMode(ECHO_PIN, INPUT);

  pinMode(BUZZER_PIN, OUTPUT);

  buzzerOff();

  lcd.init();

  lcd.backlight();

  gateServo.attach(SERVO_PIN);

  gateServo.write(0);

  lcd.setCursor(0, 0);

  lcd.print("Flood Monitor");

  lcd.setCursor(0, 1);

  lcd.print("Starting...");

  delay(1500);

  WiFi.begin(ssid, pass);

  Serial.print("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");

  }

  Serial.println("\nWiFi Connected!");

  Blynk.config(BLYNK_AUTH_TOKEN);

  Blynk.connect(10000);

  if (Blynk.connected()) {

    Serial.println("Blynk Connected");

    lcd.clear();

    lcd.print("System Ready");

  } else {

    Serial.println("Blynk Failed");

  }

  delay(1000);

  timer.setInterval(1000L, updateSystem);

}

void loop() {

  Blynk.run();

  timer.run();

}