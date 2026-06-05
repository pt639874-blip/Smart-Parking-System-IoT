#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

Servo gate;

// Ultrasonic (ENTRY)
int trigPin = 6;
int echoPin = 7;

// IR sensor (EXIT)
int IR2 = 3;

// LEDs
int greenLED = 10;
int redLED = 11;

int totalSlots = 4;
int slot = 4;

bool entryDetected = false;
bool exitDetected = false;

// Ultrasonic function
int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.017;
}

void setup() {
  Serial.begin(9600);

  // OLED init
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found");
    while(true);
  }

  display.clearDisplay();

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(IR2, INPUT_PULLUP);

  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  gate.attach(9);
  gate.write(100); // gate closed

  // Welcome screen
  display.setTextSize(2);
  display.setTextColor(WHITE);

  display.setCursor(0,10);
  display.println("SMART");

  display.setCursor(0,35);
  display.println("PARKING");

  display.display();
  delay(2000);
}

void loop() {

  int d = getDistance();
  int s2 = digitalRead(IR2);

  Serial.print("Distance: "); Serial.print(d);
  Serial.print("  Slot: "); Serial.println(slot);

  // ===== ENTRY =====
  if (d > 5 && d < 15 && !entryDetected) {
    entryDetected = true;

    if (slot > 0) {
      gate.write(0);   // open
      delay(2000);

      slot--;

      gate.write(100); // close
    }
  }

  if (d > 20) entryDetected = false;

  // ===== EXIT =====
  if (s2 == LOW && !exitDetected) {
    exitDetected = true;

    if (slot < totalSlots) {
      gate.write(0);
      delay(2000);

      slot++;

      gate.write(100);
    }
  }

  if (s2 == HIGH) exitDetected = false;

  // ===== LED LOGIC =====
  if (slot > 0) {
    digitalWrite(greenLED, HIGH); // GREEN ON
    digitalWrite(redLED, LOW);    // RED OFF
  } else {
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);   // RED ON
  }

  // ===== OLED DISPLAY =====
  display.clearDisplay();

  display.setTextSize(2);
  display.setCursor(0,0);
  display.println("Slots:");

  display.setCursor(0,30);
  display.print(slot);

  // Show FULL message
  if (slot == 0) {
    display.setTextSize(1);
    display.setCursor(0,55);
    display.println("PARKING FULL");
  }

  display.display();

  delay(200);
}

