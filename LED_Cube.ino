// Delay time for multiplexing per layer is 1 millisecond

const int numLayers = 4;
const int numCols = 16;
const int layers[] = {A2,A3,A4,A5};
// const int ledPins[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,A0,A1};

const int potPin = A6;
const int dataPin = 8;
const int clockPin = 9;
const int latchPin = 10;

const int trigPin = 6;
const int echoPin = 7;

void turnOffEverything(uint16_t order);
void shiftOutLights();
void display(uint16_t layout0, uint16_t layout1, uint16_t layout2, uint16_t layout3);
void loopThroughAll();
int rainPos[] = {0,0,0,0};
void rain();
void terrible();
void spinningPlane();
void waves();
void distanceSensor();
void slidingSquare();

void setup() {
  pinMode(potPin,INPUT);
  for(int i = 0; i < numLayers; i++) {
    pinMode(layers[i],OUTPUT);
  }
  pinMode(dataPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(latchPin,OUTPUT);

  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  // for(int i = 0; i < numCols; i++) {
  //   pinMode(ledPins[i],OUTPUT);
  // }
  turnOffEverything();
}

void loop() {
  rain();
}

void turnOffEverything() {
  for(int i = 0; i < numLayers; i++) {
    digitalWrite(layers[i],LOW);
  }
  shiftOutLights(0x0000);
}

// A 16-bit integer is given to shift out to the shift registers driving the LED columns
// 1 turns the column one and 0 turns it off
void shiftOutLights(uint16_t order) {
  byte first = order & 0xFF;
  byte second = (order >> 8) & 0xFF;
  digitalWrite(latchPin,LOW);
  shiftOut(dataPin,clockPin,LSBFIRST,first);
  shiftOut(dataPin,clockPin,LSBFIRST,second);
  digitalWrite(latchPin,HIGH);
}

// An image is given to be displayed by shifting out 16 bits for each layer
// The duration is how long to display the given image
void display(uint16_t layout0, uint16_t layout1, uint16_t layout2, uint16_t layout3, int duration) {
  uint16_t layouts[numLayers] = {layout0,layout1,layout2,layout3};
  for(int t = 0; t < duration/4; t++) {
    for(int i = 0; i < numLayers; i++) {
      shiftOutLights(layouts[i]);
      digitalWrite(layers[i],HIGH);
      delay(1);
      digitalWrite(layers[i],LOW);
    }
  }
}

void loopThroughAll() {
  display(0b1111111111111111,0b1111111111111111,0b1111111111111111,0b1111111111111111,1);
}

void terrible() {
  // int timePerLetter = 500;
  // for(int i = 0; i < timePerLetter/4; i++) {
  //   for(int l = 0; l < ledsPerRow; l++) {
  //     if(l == 3) {
  //       lightLeds(0);
  //     } else if (l == 2) {
  //       lightLeds(0b0000000000000111);
  //     } else {
  //       lightLeds(0b0000000000000010);
  //     }
  //     digitalWrite(layers[l],HIGH);
  //     delay(1);
  //     digitalWrite(layers[l],LOW);
  //   }
  // }
  // for(int i = 0; i < timePerLetter/4; i++) {
  //   for(int l = 0; l < ledsPerRow; l++) {
  //     if(l == 2) {
  //       lightLeds(0b0000000000000111);
  //     } else if (l == 1) {
  //       lightLeds(0b0000000000000001);
  //     } else {
  //       lightLeds(0b0000000000001111);
  //     }
  //     digitalWrite(layers[l],HIGH);
  //     delay(1);
  //     digitalWrite(layers[l],LOW);
  //   }
  // }
}

void spinningPlane() {
  int timePerImage = 80;
  int timePerRotation = 2000;

  for(int o = 0; o < timePerRotation; o+=(timePerImage*6)) {
    for(int i = 0; i < timePerImage/4; i++) {
      for(int l = 0; l < numLayers; l++) {
        shiftOutLights(0b0001001001001000);
        digitalWrite(layers[l],HIGH);
        delay(1);
        digitalWrite(layers[l],LOW);
      }
    }
    for(int i = 0; i < timePerImage/4; i++) {
      for(int l = 0; l < numLayers; l++) {
        shiftOutLights(0b0010001001000100);
        digitalWrite(layers[l],HIGH);
        delay(1);
        digitalWrite(layers[l],LOW);
      }
    }
    for(int i = 0; i < timePerImage/4; i++) {
      for(int l = 0; l < numLayers; l++) {
        shiftOutLights(0b0100010000100010);
        digitalWrite(layers[l],HIGH);
        delay(1);
        digitalWrite(layers[l],LOW);
      }
    }
    for(int i = 0; i < timePerImage/4; i++) {
      for(int l = 0; l < numLayers; l++) {
        shiftOutLights(0b1000010000100001);
        digitalWrite(layers[l],HIGH);
        delay(1);
        digitalWrite(layers[l],LOW);
      }
    }
    for(int i = 0; i < timePerImage/4; i++) {
      for(int l = 0; l < numLayers; l++) {
        shiftOutLights(0b0000110000110000);
        digitalWrite(layers[l],HIGH);
        delay(1);
        digitalWrite(layers[l],LOW);
      }
    }
    for(int i = 0; i < timePerImage/4; i++) {
      for(int l = 0; l < numLayers; l++) {
        shiftOutLights(0b0000001111000000);
        digitalWrite(layers[l],HIGH);
        delay(1);
        digitalWrite(layers[l],LOW);
      }
    }
  }

  // Change axis of rotation
  for(int o = 0; o < timePerRotation; o+=(timePerImage*6)) {
    display(0b1111000000000000,0b0000111100000000,0b0000000011110000,0b0000000000001111,timePerImage);
    display(0b0000000000000000,0b1111111100000000,0b0000000011111111,0b0000000000000000,timePerImage);
    display(0b0000000000000000,0b0000000011111111,0b1111111100000000,0b0000000000000000,timePerImage);
    display(0b0000000000001111,0b0000000011110000,0b0000111100000000,0b1111000000000000,timePerImage);
    display(0b0000000011110000,0b0000000011110000,0b0000111100000000,0b0000111100000000,timePerImage);
    display(0b0000111100000000,0b0000111100000000,0b0000000011110000,0b0000000011110000,timePerImage);
  }
}

void waves() {
  int timePerImage = 60;
  display(0b1111011100110001,0b0110001100010000,0b0110001100010000,0b0011000100000000,timePerImage);
  display(0b0111001100011000,0b0011000100000000,0b0011000100000000,0b0001000000001000,timePerImage);
  display(0b0011000110001100,0b0001000000001000,0b0001000000001000,0b0000000010001100,timePerImage);
  display(0b0001100011001110,0b0000000010001100,0b0000000010001100,0b0000100011000110,timePerImage);
  display(0b1000110011101111,0b0000100011000110,0b0000100011000110,0b1000110001100011,timePerImage);
  display(0b1100111011110111,0b1000110001100011,0b1000110001100011,0b1100011000110001,timePerImage);
  display(0b1110111101110011,0b1100011000110001,0b1100011000110001,0b0110001100010000,timePerImage);
}

void slidingSquare() {
  const int stopTime = 500;
  const int moveTime = 500;
  display(0x8888,0x8888,0x8888,0x8888,stopTime);

  display(0x4444,0x8888,0x8888,0x8888,moveTime/5);
  display(0x2222,0x4444,0x8888,0x8888,moveTime/5);
  display(0x1111,0x2222,0x4444,0x8888,moveTime/5);
  display(0x1111,0x1111,0x2222,0x4444,moveTime/5);
  display(0x1111,0x1111,0x1111,0x2222,moveTime/5);
  

  display(0x1111,0x1111,0x1111,0x1111,stopTime);
  
  display(0x2222,0x1111,0x1111,0x1111,moveTime/5);
  display(0x4444,0x2222,0x1111,0x1111,moveTime/5);
  display(0x8888,0x4444,0x2222,0x1111,moveTime/5);
  display(0x8888,0x8888,0x4444,0x2222,moveTime/5);
  display(0x8888,0x8888,0x8888,0x4444,moveTime/5);
}

void rain() {
  for(int i = numLayers-1; i > 0; i--) {
    rainPos[i] = rainPos[i-1];
  }
  rainPos[0] = random(16);
  display(1<<rainPos[0],1<<rainPos[1],1<<rainPos[2],1<<rainPos[3],160);
}

void distanceSensor() {
  const unsigned long timeout = 29000;
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  long distance = pulseIn(echoPin,HIGH,timeout);
}
