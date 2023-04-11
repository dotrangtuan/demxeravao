

int latchPin = 8;
int latchPin2 = 5;
//chân SH_CP của 74HC595
int clockPin = 12;
int clockPin2 = 7;
//Chân DS của 74HC595
int dataPin = 11;
int dataPin2 = 6;

//mảng có 10 số (từ 0-9) và 
const byte Seg[10] = {
  0b11000000,//0 - các thanh từ a-f sáng
  0b11111001,//1 - chỉ có 2 thanh b,c sáng
  0b10100100,//2
  0b10110000,//3
  0b10011001,//4
  0b10010010,//5
  0b10000010,//6
  0b11111000,//7
  0b10000000,//8
  0b10010000,//9
};

// khởi tạo số xe vào ra ban đầu
int carIn = 0;
int carOut = 0;

void countCarIn() {
  carIn ++ ;
}
void countCarOut() {
  carOut ++;
}


void HienThiLED7doan(unsigned long Giatri, byte SoLed = 2, boolean choose = 1) {
  if (choose == 1) { // xe vao
      byte *array= new byte[SoLed];
    for (byte i = 0; i < SoLed; i++) {
      //Lấy các chữ số từ phải quá trái
      array[i] = (byte)(Giatri % 10UL);
      Giatri = (unsigned long)(Giatri /10UL);
    }
    digitalWrite(latchPin, LOW);
    for (int i = SoLed - 1; i >= 0; i--)
      shiftOut(dataPin, clockPin, MSBFIRST, Seg[array[i]]); 
    
    digitalWrite(latchPin, HIGH);
    free(array);
  }
  if (choose == 0) { // xe ra 
      byte *array= new byte[SoLed];
    for (byte i = 0; i < SoLed; i++) {
      //Lấy các chữ số từ phải quá trái
      array[i] = (byte)(Giatri % 10UL);
      Giatri = (unsigned long)(Giatri /10UL);
    }
    digitalWrite(latchPin2, LOW);
    for (int i = SoLed - 1; i >= 0; i--)
      shiftOut(dataPin2, clockPin2, MSBFIRST, Seg[array[i]]); 
    
    digitalWrite(latchPin2, HIGH);
    free(array);
  }
  
}

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin2, OUTPUT);
  pinMode(clockPin2, OUTPUT);
  pinMode(dataPin2, OUTPUT);
  // put your setup code here, to run once:
//  pinMode(2, INPUT_PULLUP);
//  pinMode(3, INPUT_PULLUP);
  attachInterrupt(0, countCarIn, RISING);
  attachInterrupt(1, countCarOut, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
  HienThiLED7doan(carIn, 2, 1);
  HienThiLED7doan(carOut, 2, 0);
}
