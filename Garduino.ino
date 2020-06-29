#define NUM 4

#define DRY_THRESH 250
#define WET_THRESH 180

#define PUMP_INTERVAL 20000
#define SHORT_REST_INTERVAL 60000
#define LONG_REST_INTERVAL 3600000

bool rising[NUM];
u8 step = 0;

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < NUM; i++) {
    rising[i] = false;
  }

  init(2);
  init(3);
  init(4);
  init(5);
  
  Serial.begin(9600);
  Serial.println("Greetings, human");
}

void init(int ppin) {
  pinMode(ppin, OUTPUT);
  digitalWrite(ppin, HIGH);
  step = 0;
}

void loop() {
  check(0, A0, 2);
  check(1, A1, 3);
  check(2, A2, 4);
  check(3, A3, 5);
  step++;
  if (step < 5){
    delay(SHORT_REST_INTERVAL);
  } else {
    delay(LONG_REST_INTERVAL);
    step = 0;
  }
}

// enable pullup; read value.
int read(int apin) {
  pinMode(apin, INPUT_PULLUP);
  delay(1000);
  int val = analogRead(apin);
  pinMode(apin, OUTPUT);
  digitalWrite(apin, LOW);
  return val;
}


void check(int idx, int apin, int ppin) {
  int val = read(apin);

  Serial.print("Plant: ");
  Serial.print(idx);
  Serial.print(" ");
  Serial.print("value: ");
  Serial.print(val);

  if (val == 1023) {
    Serial.println(" out of spec, ignoring");
    return;
  }

  if (val > DRY_THRESH) {
    rising[idx] = true;
  } else if (val <= WET_THRESH) {
    Serial.print(" now wet enough");
    rising[idx] = false;
  }

  if (rising[idx] && val > WET_THRESH) {
    Serial.print(" too dry, watering pin ");
    Serial.print(ppin);
    digitalWrite(ppin, LOW);
    delay(PUMP_INTERVAL);
    digitalWrite(ppin, HIGH);
  }
  Serial.println("");
}
