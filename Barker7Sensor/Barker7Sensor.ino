int barker[] = {1, 1, 1, 0, 0, 1, 0};

unsigned int cycle = 10;
unsigned int last = 0;
unsigned int cur;

unsigned int start;

unsigned int sumRead;
unsigned int countRead;

unsigned int lastRead[7];
unsigned int newRead;

unsigned int autocorrReads[21];
bool blocked[21];

void setup() {
  // put your setup code here, to run once:
  pinMode(A4, INPUT);
  pinMode(12, INPUT_PULLUP);
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  start = millis();
}

void insShift(unsigned int ins[], unsigned int next, int length){
  for (int i = 0; i < length-1; i++){
    ins[i] = ins[i+1];
  }
  ins[length-1] = next;
}
void insShift(bool ins[], bool next, int length){
  for (int i = 0; i < length-1; i++){
    ins[i] = ins[i+1];
  }
  ins[length-1] = next;
}


int correlation(unsigned int target[], unsigned int measured[], int length){
  unsigned int sum = 0;
  for (int i=0; i<length; i++){
    sum += target[i]*measured[i];
  }
  return sum;
}

bool match(int reads[]){
  int maxes[3];
  for (int i=0; i < 3; i++){
    int max = i*7;
    for (int j=0; j < 6; j++){
      if (reads[max] < reads[i*7+j]){
        max = i*7+j;
      }      
    }
    maxes[i] = max;
  }
  if (((maxes[2]-maxes[1]) == 7) || ((maxes[1]-maxes[0]) == 7)){
    return true;
  }
  return false;
}

bool falses(bool arr[], int length, int thresh){
  int count = 0;
  for (int i=0; i<length; i++){
    if (!arr[i]){
      count++;
    }
  }
  Serial.println(count);
  if (count > thresh){
    return true;
  }
  return false;

}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(12) == 0){
    // tone(2, 1000);
    cur = millis();
    if (cur-last> cycle){
      newRead = sumRead/countRead;      
      insShift(lastRead, newRead, 7);
      insShift(autocorrReads, correlation(barker, lastRead, 7), 21);
      insShift(blocked, match(autocorrReads), 21);
      
      if (falses(blocked, 21, 3) && (cur-start > cycle*21)){
        tone(2, 1000);
      } else {
        noTone(2);
      }
      
      sumRead = 0;
      countRead = 0;
      last = cur;
    } else {
      sumRead += analogRead(A4);
      countRead++;
    }
  } else {
    noTone(2);
    last = millis();
    sumRead = 0;
    countRead = 0;
    memset(lastRead, 0, 7);
    memset(autocorrReads, 0,21);
    memset(blocked, 0,21);
  }
}