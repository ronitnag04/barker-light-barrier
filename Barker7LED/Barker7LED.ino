
bool barker[] = {true, true, true, false, false, true, false};
int pos = 0;
int cycle = 10;
int last = 0;
int cur;


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(4, OUTPUT);
  pinMode(9, INPUT_PULLUP);
}

// the loop function runs over and over again forever
void loop(){
  if (digitalRead(9) == 0){
    cur = millis();
    if (cur-last > cycle){
      if (barker[pos]){
        digitalWrite(4, HIGH);
      } else {
        digitalWrite(4, LOW);
      }
      last = cur;
      pos++;
      if (pos > 6){
        pos = 0;
      }
    }
  } else {
    pos = 0;
    last = millis();
    digitalWrite(4, LOW);
  }
  
}
