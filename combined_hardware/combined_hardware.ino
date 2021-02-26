#define RED_BUTTON 13
int rCurr = HIGH;
int voiceCurr = 0;
int voicesLED[] = {4,0,5,15};

#define YEL_BUTTON 14
int yCurr = HIGH;
int vfCurr = 0;
int vfLED[] = {18,19};  //18 is vol (BLUE), 19 is freq (GREEN)

int xyzPins[] = {25,26,27};

#define SWITCH 32
int solo = 0;  // 0 means solo, 1 means global

void setup() {
  Serial.begin(9600);
  for (int i=0; i < 4; i++){
    pinMode(voicesLED[i], OUTPUT);
  }
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(RED_BUTTON, INPUT);
  pinMode(YEL_BUTTON, INPUT);
  pinMode(32, INPUT_PULLUP);
  solo = digitalRead(SWITCH);
  if (solo==0){
    setSolo();
  }
  else{
    setGlobal();
  }
}

void loop() {

  if (digitalRead(SWITCH) != solo){
    toggleSwitch(digitalRead(SWITCH));
  }

  if (solo == 0){
    
    int rNew = digitalRead(RED_BUTTON);
    if (rNew == LOW and rCurr == 1) {
      cycleVoices();
    }
    rCurr = rNew;

    int yNew = digitalRead(YEL_BUTTON);
    if (yNew == LOW and yCurr == 1) {
      cyclevf();
    }
    yCurr = yNew;
  
  }

  else{
    
  }
  
  int yVal = analogRead(xyzPins[1]);
  int dpst = digitalRead(32);
  Serial.printf("Y: %d\n", yVal);
  Serial.printf("y,r,s: %d,\t%d,\t%d\n", yCurr, rCurr, dpst);
  delay(500);
}

void toggleSwitch(int newVal){
  
  if (newVal == 1){
    setGlobal();
  }
  else{
    setSolo();
  }
  solo = newVal;
}

void setGlobal(){
  for (int i=0; i<4; i++){
      digitalWrite(voicesLED[i],HIGH);
    }
    digitalWrite(vfLED[0], HIGH);
    digitalWrite(vfLED[1], LOW);
}

void setSolo(){
  for (int i=0; i<4; i++){
      if (i==voiceCurr){
        digitalWrite(voicesLED[i],HIGH);
      }
      else{
        digitalWrite(voicesLED[i],LOW);
      }
  }
  for (int i=0; i<2; i++){
     if (i==vfCurr){
       digitalWrite(vfLED[i], HIGH);
     }
     else{
       digitalWrite(vfLED[i], LOW);
     }
  }
}

void cycleVoices(){
  digitalWrite(voicesLED[voiceCurr],LOW);
  voiceCurr++;
  voiceCurr = voiceCurr%4;
  digitalWrite(voicesLED[voiceCurr],HIGH);
}

void cyclevf(){
  digitalWrite(vfLED[vfCurr],LOW);
  vfCurr++;
  vfCurr = vfCurr%2;
  digitalWrite(vfLED[vfCurr],HIGH);
}