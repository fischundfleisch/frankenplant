#include <Adafruit_SleepyDog.h>

const unsigned long DURATION_ON = 13UL * 60UL * 60UL * 1000UL; //globale Konstanten in CAPS
const unsigned long DURATION_OFF  = 11UL * 60UL * 60UL * 1000UL;
const unsigned long HEARTBEAT_FREQ = 10UL * 60UL * 1000UL;
const unsigned long RESET_FREQ = 7UL * 24UL * 60UL * 60UL * 1000UL;
const unsigned int RESET_PIN = 4;
const unsigned int LED_PIN = 5;

unsigned long duration_timer_ = 0;
unsigned long heartbeat_timer_ = 0;
unsigned long reset_timer_ = 0;
bool light_on_ = false;


void setup() {
  pinMode(RESET_PIN, OUTPUT);
  digitalWrite(RESET_PIN, LOW);

  Serial.begin(9600);
  Serial.println("System startet...");
  Serial.println(millis());

  pinMode(LED_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
  light_on_ = true;

}

void loop() {

  unsigned long act_time = millis();
  unsigned long time_span = act_time - duration_timer_;
  unsigned long time_span_heart = act_time - heartbeat_timer_;
  unsigned long time_span_reset = act_time - reset_timer_;

  if (time_span_heart > HEARTBEAT_FREQ) {
    Serial.println(time_span);
    heartbeat_timer_ = millis();
  }

  if (light_on_) {
    if (time_span > DURATION_ON) {
      digitalWrite(LED_PIN, HIGH);
      light_on_ = false;
      duration_timer_ = millis();
      Serial.println("schalte aus");
    }
  }
  else {
    if (time_span > DURATION_OFF) {
      digitalWrite(LED_PIN, LOW);
      light_on_ = true;
      duration_timer_ = millis();
      Serial.println("schalte ein");
    }
  }

  if (time_span_reset > RESET_FREQ) {
    Serial.println(act_time);
    Serial.println("Resetten...");
    Watchdog.enable(15);
    for (;;) {};
    Serial.println("Das passiert nie");
  }
}
