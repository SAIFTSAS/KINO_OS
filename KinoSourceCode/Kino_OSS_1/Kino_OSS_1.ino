//----------Drivers----------
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); //LCD Drivers
const byte ROWS = 4; //KeyPad Drivers
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {10, 9, 8, 7};
byte colPins[COLS] = {5, 4, 3, 2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
//----------Drivers_END----------
//----------Programer----------
//----------Control Public Var---------
String MainMenuBase[] = {"Arimetica", "Videojuego", "Ajustes"}; //MenuData
String Menu2Base[] = {"Suma", "Resta", "Multipl", "Division"}; //MenuData
const int MENU_ITEMSB = 3; //BaseMenuItems
const int MENU_ITEMS = 4; //MenuItems
int Layout = 1; //MenuPosition
int line = 0; //MenuSelection
int seLine = 0; //SecundaryMenuSelection
//----------Control Public Var_END---------
//----------Menu Control----------
class MenuControl {
  public:
    MenuControl(String DataBase[], int length);
    void print();
    void control();
    int returnLine();
  private:
    int lengthDB;
    int Line;
    String *DataB;
};

MenuControl::MenuControl(String DataBase[], int length) {
  DataB = DataBase;
  lengthDB = length;
  Line = 0;
}

void MenuControl::print() {
  lcd.setCursor(0, 0);
  lcd.print(DataB[abs(Line)]);
  lcd.setCursor(0, 1);
  if (Line != lengthDB - 1) lcd.print(DataB[abs(Line + 1)]);
  else lcd.print(DataB[0]);
}

void MenuControl::control() {
  char key = keypad.getKey();
  if (key) {
    switch (key) {
      case 'B':
        if (Line < lengthDB) Line++;
        break;
      case 'A':
        if (Line >= 0) Line--;
        break;
      case '#':
        if (Layout != 3) Layout = Layout + 1;
        lcd.clear();
        break;
      case '*':
        if (Layout != 1) Layout = Layout - 1;
        lcd.clear();
        break;
    }
    if (Line < 0) Line = lengthDB - 1;
    if (Line >= lengthDB) Line = 0;
    lcd.clear();
  }
}
int MenuControl::returnLine(){
  return Line;
}
//----------Menu Control_END----------
//----------ALU----------
class ArimeticLogicUnit {
  public:
    ArimeticLogicUnit(char Kind);
    void ALU(char Operator);
    void EALU(float A, float B, float C, float D);
    void NumberCase();
    void operatorS(char OperatorB);


  private:
  char KIND;
  int NUM;
  float At;
  float Bt;
  float Ct;
  float Dt;
  float Sol;
  const float pi = 3.1416;
  //control----------
  float CA = 0;
  boolean CB = false;
  short int CC = 1;
  boolean CD = false;
  float CE = 1.0;
  float carrier1;
  float carrier2;
  float carrier3;
  float carrier4;
};
ArimeticLogicUnit::ArimeticLogicUnit(char Kind) {
  KIND = Kind;
}
void ArimeticLogicUnit::ALU(char Operator){
switch(KIND){
  case 'M':
  break;
  case 'B':
  switch(Operator){
    case 'S':
    Sol = At + Bt;
    break;
    case 'R':
    Sol = At - Bt;
    break;
    case 'D':
    if (Bt!=0.00) Sol = At / Bt;
    else Sol = 409;
    break;
    case 'M': 
    Sol = At * Bt;
    break;
    case 'P':
    Sol = pow(At , Bt);
    break;
    case 'r':
    Sol = pow(At , 1 / Bt);
    break;
  }
  break;
  case 'T':
  switch(Operator){
    case 'V':
    Sol = At * Bt * Ct;
    break;
  }
  break;
  case 'P':
  break;
}
}
void ArimeticLogicUnit::EALU(float A, float B, float C, float D){
  switch(KIND){
    case 'M':
    At = A;
    break;
    case 'B':
  At = A;
  Bt = B;
    break;
    case 'T':
    At = A;
    Bt = B;
    Ct = C;
    break;
    case 'P':
    At = A;
    Bt = B;
    Ct = C;
    Dt = D;
    break;
  }
}
void ArimeticLogicUnit::NumberCase(){
  char key = keypad.getKey();
  if (key) {
    switch (key) {
      case '0':
      if(CD!=true){
      CA = CA * 10;
      }
      else{
      CE = CE/10;
      CA = CA * CE;
      }
      break;
      case '1':
      if(CD!=true){
      CA = CA * 10 + 1;
      }
      else{
      CE = CE/10;
      CA = CA + 1 * CE;
      }
      break;
      case '2':
      if(CD!=true){
      CA = CA * 10 + 2;
      }
      else{
      CE = CE/10;
      CA = CA + 2 * CE;
      }
      break;
      case '3':
      if(CD!=true){
      CA = CA * 10 + 3;
      }
      else{
      CE = CE/10;
      CA = CA + 3 * CE;
      }
      break;
      case '4':
      if(CD!=true){
      CA = CA * 10 + 4;
      }
      else{
      CE = CE/10;
      CA = CA + 4 * CE;
      }
      break;
      case '5':
      if(CD!=true){
      CA = CA * 10 + 5;
      }
      else{
      CE = CE/10;
      CA = CA + 5 * CE;
      }
      break;
      case '6':
      if(CD!=true){
      CA = CA * 10 + 6;
      }
      else{
      CE = CE/10;
      CA = CA + 6 * CE;
      }
      break;
      case '7':
      if(CD!=true){
      CA = CA * 10 + 7;
      }
      else{
      CE = CE/10;
      CA = CA + 7 * CE;
      }
      break;
      case '8':
      if(CD!=true){
      CA = CA * 10 + 8;
      }
      else{
      CE = CE/10;
      CA = CA + 8 * CE;
      }
      break;
      case '9':
      if(CD!=true){
      CA = CA * 10 + 9;
      }
      else{
      CE = CE/10;
      CA = CA + 9 * CE;
      }
      break;
      case '*':
      CA = 0;
      CB = false;
      CC = 1;
      CD = false;
      CE = 1.0;
      carrier1 = 0;
      carrier2 = 0;
      carrier3 = 0;
      carrier4 = 0;
      lcd.clear();
      Layout = 1;
      break;
      case '#':
      CB =  true;
      break;
      case 'C':
      if(CD != true){
      if (CA !=0&&CA>=10) CA = int(CA = CA / 10);
      else CA = 0;
      }
      else{
        String CA_str = String(CA, 10);
          int pos = CA_str.indexOf('.');
          if (pos != -1) {
            CA_str = CA_str.substring(0, pos);
            CA = CA_str.toFloat();
            CD = false;
            CE = 1.0;
          }
      }
      break;
      case 'D':
      CA = CA * (-1);
      break;
      case 'A':
        CD = true;
      break;
    }
    lcd.clear();
  }
  if(CA>9999999) CA = 0;
}
void ArimeticLogicUnit::operatorS(char OperatorB){ 
  switch(KIND){
    case 'M':
      while(CB != true&&CC==1){
        NumberCase();
        lcd.setCursor(0,0);
        lcd.print("ING A");
        lcd.setCursor(0,1);
        lcd.print(CA); // state 1
       }
       CC = 2;
       CB = false;
       CD = false;
       CE = 1.0;
       carrier1 = CA;
       CA = 0;
       EALU(carrier1,0,0,0);
       ALU(OperatorB);
       lcd.clear();
       while(CC==2){
       NumberCase();
       lcd.setCursor(0,0);
       lcd.print("SOLV");
       lcd.setCursor(0,1);
       lcd.print(Sol); // state 2
       }
    break;
    case 'B':
       while(CB != true&&CC==1){
        NumberCase();
        lcd.setCursor(0,0);
        lcd.print("ING A");
        lcd.setCursor(0,1);
        lcd.print(CA);
       }
       CB = false;
       carrier1 = CA;
       CA = 0;
       CD = false;
       CE = 1.0;
       CC = 2; // state 1
       lcd.clear();
       while(CB != true&&CC==2){
        NumberCase();
        lcd.setCursor(0,0);
        lcd.print("ING B");
        lcd.setCursor(0,1);
        lcd.print(CA); // state 2
       }
       CC = 3;
       CB = false;
       carrier2 = CA;
       CA = 0;
       CD = false;
       CE = 1.0;
       EALU(carrier1,carrier2,0,0);
       ALU(OperatorB);
       lcd.clear();
       while(CC==3){
       NumberCase();
       lcd.setCursor(0,0);
       lcd.print("SOLV");
       lcd.setCursor(0,1);
       lcd.print(Sol); // state 3
       }
    break;
    case 'T':
       while(CB != true&&CC==1){
        NumberCase();
        lcd.setCursor(0,0);
        lcd.print("ING A");
        lcd.setCursor(0,1);
        lcd.print(CA);
       }
       CB = false;
       carrier1 = CA;
       CA = 0;
       CD = false;
       CE = 1.0;
       CC = 2; // state 1
       lcd.clear();
       while(CB != true&&CC==2){
        NumberCase();
        lcd.setCursor(0,0);
        lcd.print("ING B");
        lcd.setCursor(0,1);
        lcd.print(CA); // state 2
       }
       CC = 3;
       CB = false;
       carrier2 = CA;
       CA = 0;
       CD = false;
       CE = 1.0;
       lcd.clear();
       while(CB != true&&CC==3){
        NumberCase();
        lcd.setCursor(0,0);
        lcd.print("ING C");
        lcd.setCursor(0,1);
        lcd.print(CA); // state 3
       }
       CC = 4;
       CB = false;
       carrier3 = CA;
       CA = 0;
       CD = false;
       CE = 1.0;
       EALU(carrier1,carrier2,carrier3,0);
       ALU(OperatorB);
       lcd.clear();
       while(CC==4){
       NumberCase();
       lcd.setCursor(0,0);
       lcd.print("SOLV");
       lcd.setCursor(0,1);
       lcd.print(Sol); // state 4
       }
    break;
    case 'P':
       while(CB != true&&CC==1){
        NumberCase();
        lcd.setCursor(0,0);
        lcd.print("ING A");
        lcd.setCursor(0,1);
        lcd.print(CA);
       }
       CB = false;
       carrier1 = CA;
       CA = 0;
       CD = false;
       CE = 1.0;
       CC = 2; // state 1
       lcd.clear();
       while(CB != true&&CC==2){
        NumberCase();
        lcd.setCursor(0,0);
        lcd.print("ING B");
        lcd.setCursor(0,1);
        lcd.print(CA); // state 2
       }
       CC = 3;
       CB = false;
       carrier2 = CA;
       CA = 0;
       CD = false;
       CE = 1.0;
       lcd.clear();
       while(CB != true&&CC==3){
        NumberCase();
        lcd.setCursor(0,0);
        lcd.print("ING C");
        lcd.setCursor(0,1);
        lcd.print(CA); // state 3
       }
       CC = 4;
       CB = false;
       carrier3 = CA;
       CA = 0;
       CD = false;
       CE = 1.0;
       lcd.clear();
       while(CB != true&&CC==4){
        NumberCase();
        lcd.setCursor(0,0);
        lcd.print("ING D");
        lcd.setCursor(0,1);
        lcd.print(CA); // state 4
       }
       CC = 5;
       CB = false;
       carrier4 = CA;
       CA = 0;
       CD = false;
       CE = 1.0;
       lcd.clear();
       EALU(carrier1,carrier2,carrier3,carrier4);
       ALU(OperatorB);
       lcd.clear();
       while(CC==5){
       NumberCase();
       lcd.setCursor(0,0);
       lcd.print("SOLV");
       lcd.setCursor(0,1);
       lcd.print(Sol); // state 5
       }
    break;
  }
}
//----------ALU_END----------
//----------Programer_END----------
//----------Boot----------
ArimeticLogicUnit Malu('M');
ArimeticLogicUnit Balu('B');
ArimeticLogicUnit Talu('T');
ArimeticLogicUnit Palu('P');
MenuControl menu(MainMenuBase, MENU_ITEMSB);
MenuControl menuAri(Menu2Base, MENU_ITEMS);
void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  lcd.setCursor(0,0);
  lcd.print("KINO OS");
  delay(random(100,1000));
  menu.print();
}
void loop() {
  Logistic();
}
void Logistic() {
  if (Layout == 1){
  menu.print();
  menu.control();
  line = menu.returnLine();
  }
  if (Layout == 2) {
    switch(line){
    case 0:
    menuAri.print();
    menuAri.control();
    break;
    case 1:
    game();
    break;
    case 2:
    configuration();
    break;
    }
  }
  if (Layout == 3) {
  switch(line){
    case 0:
    seLine = menuAri.returnLine();
    switch(seLine){
    case 0:
    Balu.operatorS('S');
    break;
    case 1:
    Balu.operatorS('R');
    break;
    case 2:
    Balu.operatorS('M');
    break;
    case 3:
    Balu.operatorS('D');
    break;
    }
    break;
    }
  }
}
//----------Boot_END----------
//----------Configuration----------
void configuration(){
  //nothing to do
  lcd.print("404");
  delay(500);
  lcd.clear();
  Layout = 1;
}
//----------Configuration_END----------
//----------GAME----------
//----------LocalGameVars----------
  int X = 15,Y = 1;
  long int points;
//----------LocalGameVars_END----------
void printGame(){
  lcd.clear();
  lcd.setCursor(3,Y);
  lcd.print("A");
  lcd.setCursor(X,1);
  lcd.print("i");
  lcd.setCursor(10,0);
  lcd.print(points);
  delay(100);
  if(X>0) X--;
  else if(X==0) X = 15;
}
void game(){
  Y=1;
  char key = keypad.getKey();
  if (key) {
    switch (key) {
      case 'A':
      Y = 0;
      break;
      case '*':
      X = 15;
      Y = 1;
      lcd.clear();
      Layout = 1;
      break;
    }
  }
  printGame();
  if(X==3&&Y==0) points++;
  if(X==3&&Y==1){
    X==15;
    Y==1;
    lcd.clear();
    lcd.print("Game Over");
    delay(300);
  }
}
//----------GAME_END----------
