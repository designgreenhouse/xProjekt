bool safe=true;
int raw_val;

void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(2)) {
    if (safe) {
      safe = false;
      // eerste pulse eerst
      digitalWrite(13, HIGH);           // output pin 13 hoog; eerste pulse
      digitalWrite(12, HIGH);           // output pin 12 hoog; eerste pulse, LED indicator
      delay(20);                        // voor 20 ms
      digitalWrite(13, LOW);            // output pin 13 laag; pauze tussen eerste pulse en main pulse
      digitalWrite(12, LOW);            // output pin 12 laag; pauze tussen eerste pulse en main pulse, LED indicator
      delay(200);                       // voor 200 ms
      raw_val = analogRead(0);          // read out analog pin 0 (potmeter); bereik van output is van 0 to 1023
      raw_val = (1023-raw_val) / 2;            // we willen max ong. 500 ms puntlassen: 1023 / 2 = ong. 500
      digitalWrite(13, HIGH);           // output pin 13 hoog; main pulse
      digitalWrite(12, HIGH);           // output pin 12 hoog; main pulse, LED indicator
      delay(raw_val);                   // de output van de potmeter bepaald de tijd dat er gewacht moet worden
      digitalWrite(13, LOW);            // ook weer laag zetten als ik klaar ben
      digitalWrite(12, LOW);            // ook het LED lampje uit
      delay(1000);                      // nog een seconde extra wachttijd
    }
  }
  if (!digitalRead(2)) {
        delay(10);
    safe = true;
  }
}

// 20 ms eerste pulse lang,
// delay tussen eerst en tweede is 200 ms,
// de main pulse is van 0 tot 500 ms.

// Permission issue on Ubuntu 17 solved (example for Ina notebook):
// ls -l /dev/ttyACM0
// sudo usermod -a -G dialout ina
// sudo chmod a+rw /dev/ttyACM0
