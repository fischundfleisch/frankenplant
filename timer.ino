const unsigned long DURATION_ON = 15 * 60 * 60 * 1000; //globale Konstanten in CAPS
const unsigned long DURATION_OFF  = 9 * 60 * 60 * 1000;
const unsigned long HEARTBEAT_FREQ = 10*60*1000;
const unsigned int LED_PIN = 5;

unsigned long act_time_ = 0;
bool light_on_ = false;


void setup() {
  Serial.begin(9600);
  Serial.println("System startet...");

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  light_on_ = true;

  act_time_ = millis();
}

void loop() {

unsigned long time_span = millis() - act_time_;

  if (time_span > HEARTBEAT_FREQ){
    Serial.println("!");
  }
  
  if (light_on_) {
    if (time_span > DURATION_ON) {
      digitalWrite(LED_PIN, LOW);
      light_on_ = false;
      act_time_ = millis();
    }
  }
  else {
    if (time_span > DURATION_OFF) {
      digitalWrite(LED_PIN, HIGH);
      light_on_ = true;
      act_time_ = millis();
    }
  }
}
