const int ledPin = 2;

// 时间定义（单位：ms）
const unsigned long shortOn = 200;   // 短闪时长
const unsigned long longOn = 600;   // 长闪时长
const unsigned long between = 200;   // 两次闪烁间隔
const unsigned long charGap = 500;   // 字母间间隔
const unsigned long wordGap = 2000;  // 完整SOS结束后的长停顿

// SOS序列：S(短短短) → 间隔 → O(长长长) → 间隔 → S(短短短)
enum State {
  IDLE,
  S_SHORT1_ON, S_SHORT1_OFF,
  S_SHORT2_ON, S_SHORT2_OFF,
  S_SHORT3_ON, S_SHORT3_OFF,
  CHAR_GAP1,
  O_LONG1_ON, O_LONG1_OFF,
  O_LONG2_ON, O_LONG2_OFF,
  O_LONG3_ON, O_LONG3_OFF,
  CHAR_GAP2,
  S2_SHORT1_ON, S2_SHORT1_OFF,
  S2_SHORT2_ON, S2_SHORT2_OFF,
  S2_SHORT3_ON, S2_SHORT3_OFF,
  WORD_GAP
};

State currentState = IDLE;
unsigned long previousMillis = 0;
bool ledState = LOW;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(115200);
  Serial.println("SOS sequence started");
}

void loop() {
  unsigned long currentMillis = millis();

  switch (currentState) {
    case IDLE:
      previousMillis = currentMillis;
      currentState = S_SHORT1_ON;
      break;

    case S_SHORT1_ON:
      digitalWrite(ledPin, HIGH);
      if (currentMillis - previousMillis >= shortOn) {
        previousMillis = currentMillis;
        digitalWrite(ledPin, LOW);
        currentState = S_SHORT1_OFF;
      }
      break;
    case S_SHORT1_OFF:
      if (currentMillis - previousMillis >= between) {
        previousMillis = currentMillis;
        currentState = S_SHORT2_ON;
      }
      break;

    case S_SHORT2_ON:
      digitalWrite(ledPin, HIGH);
      if (currentMillis - previousMillis >= shortOn) {
        previousMillis = currentMillis;
        digitalWrite(ledPin, LOW);
        currentState = S_SHORT2_OFF;
      }
      break;
    case S_SHORT2_OFF:
      if (currentMillis - previousMillis >= between) {
        previousMillis = currentMillis;
        currentState = S_SHORT3_ON;
      }
      break;

    case S_SHORT3_ON:
      digitalWrite(ledPin, HIGH);
      if (currentMillis - previousMillis >= shortOn) {
        previousMillis = currentMillis;
        digitalWrite(ledPin, LOW);
        currentState = S_SHORT3_OFF;
      }
      break;
    case S_SHORT3_OFF:
      if (currentMillis - previousMillis >= between) {
        previousMillis = currentMillis;
        currentState = CHAR_GAP1;
      }
      break;

    case CHAR_GAP1:
      if (currentMillis - previousMillis >= charGap) {
        previousMillis = currentMillis;
        currentState = O_LONG1_ON;
      }
      break;

    case O_LONG1_ON:
      digitalWrite(ledPin, HIGH);
      if (currentMillis - previousMillis >= longOn) {
        previousMillis = currentMillis;
        digitalWrite(ledPin, LOW);
        currentState = O_LONG1_OFF;
      }
      break;
    case O_LONG1_OFF:
      if (currentMillis - previousMillis >= between) {
        previousMillis = currentMillis;
        currentState = O_LONG2_ON;
      }
      break;

    case O_LONG2_ON:
      digitalWrite(ledPin, HIGH);
      if (currentMillis - previousMillis >= longOn) {
        previousMillis = currentMillis;
        digitalWrite(ledPin, LOW);
        currentState = O_LONG2_OFF;
      }
      break;
    case O_LONG2_OFF:
      if (currentMillis - previousMillis >= between) {
        previousMillis = currentMillis;
        currentState = O_LONG3_ON;
      }
      break;

    case O_LONG3_ON:
      digitalWrite(ledPin, HIGH);
      if (currentMillis - previousMillis >= longOn) {
        previousMillis = currentMillis;
        digitalWrite(ledPin, LOW);
        currentState = O_LONG3_OFF;
      }
      break;
    case O_LONG3_OFF:
      if (currentMillis - previousMillis >= between) {
        previousMillis = currentMillis;
        currentState = CHAR_GAP2;
      }
      break;

    case CHAR_GAP2:
      if (currentMillis - previousMillis >= charGap) {
        previousMillis = currentMillis;
        currentState = S2_SHORT1_ON;
      }
      break;

    case S2_SHORT1_ON:
      digitalWrite(ledPin, HIGH);
      if (currentMillis - previousMillis >= shortOn) {
        previousMillis = currentMillis;
        digitalWrite(ledPin, LOW);
        currentState = S2_SHORT1_OFF;
      }
      break;
    case S2_SHORT1_OFF:
      if (currentMillis - previousMillis >= between) {
        previousMillis = currentMillis;
        currentState = S2_SHORT2_ON;
      }
      break;

    case S2_SHORT2_ON:
      digitalWrite(ledPin, HIGH);
      if (currentMillis - previousMillis >= shortOn) {
        previousMillis = currentMillis;
        digitalWrite(ledPin, LOW);
        currentState = S2_SHORT2_OFF;
      }
      break;
    case S2_SHORT2_OFF:
      if (currentMillis - previousMillis >= between) {
        previousMillis = currentMillis;
        currentState = S2_SHORT3_ON;
      }
      break;

    case S2_SHORT3_ON:
      digitalWrite(ledPin, HIGH);
      if (currentMillis - previousMillis >= shortOn) {
        previousMillis = currentMillis;
        digitalWrite(ledPin, LOW);
        currentState = S2_SHORT3_OFF;
      }
      break;
    case S2_SHORT3_OFF:
      if (currentMillis - previousMillis >= between) {
        previousMillis = currentMillis;
        currentState = WORD_GAP;
      }
      break;

    case WORD_GAP:
      if (currentMillis - previousMillis >= wordGap) {
        previousMillis = currentMillis;
        currentState = IDLE;
        Serial.println("SOS cycle completed");
      }
      break;
  }
}