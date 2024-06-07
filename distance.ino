
#include <NewPing.h>

#define SONAR_NUM 2      // Number of sensors.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.
const int pwrpin = 12;
NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(4, 3, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping.
  NewPing(7,6, MAX_DISTANCE),
};

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  digitalWrite(pwrpin, HIGH);
  pinMode(LED_BUILTIN, OUTPUT);
}
void loop() {
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through each sensor and display results.
    delay(500); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    Serial.print("sensor");
    Serial.print(i+1);
    Serial.print(" = ");
    Serial.print(sonar[i].ping_cm());
    Serial.print("cm  ");
    Serial.print(sonar[1].ping_cm() - sonar[0].ping_cm());
  }
  int delta = sonar[1].ping_cm() - sonar[0].ping_cm();
  int lwr = sonar[0].ping_cm();
  int upr = sonar[1].ping_cm();
  bool step = 0;
  if(delta > 10 || upr > 25){
    digitalWrite(pwrpin, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.print(" ");
    Serial.print("x");
    if(lwr < 20){
      step = 1;
    }    digitalWrite(LED_BUILTIN, HIGH);
  }
  else{
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(pwrpin, LOW);
  }
  Serial.println();
}