//----------Drivers----------
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <EEPROM.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); //LCD Drivers
const byte ROWS = 4; //KeyPad Drivers
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
const byte rowPins[ROWS] = {10, 9, 8, 7};
const byte colPins[COLS] = {5, 4, 3, 2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
//----------Drivers_END----------
//----------Programer----------
//----------Control Public Var---------
const String MainMenuBase[] = {"Arimetica", "Videojuego", "Ajustes", "FreeMode"}; //MenuData
const String Menu2Base[] = {"Suma", "Resta", "Multipl", "Division"}; //MenuData
int MENU_ITEMSB = 3; //BaseMenuItems / this most come from EEPROM
const int MENU_ITEMS = 4; //MenuItems
int Layout = 1; //MenuPosition
int line = 0; //MenuSelection
int seLine = 0; //SecundaryMenuSelection
String TIC;
boolean Sound = false; //experimental function
const String Tasks_ID[2][4] = {
  {"id_AA", "id_AB" , "id_AC" , "id_AD"},
  {"id_BA", "id_BB" , "id_BC" , "id_BD"}
};
String My_Task[2][4];

//----------Control Public Var_END---------
//----------Menu Control----------
class MenuMaker {
  public:
    MenuMaker(String DataBase[], int length);
    void print();
    void control();
    int returnLine();
    void UpdateMenuConfiguration(char A, int length, String *DataBA, int line);
  private:
    int lengthDB; //Containt the dataBase length
    int Line; //containt the line position in the menu
    String *DataB; //containt the dataBase or menu information
};

MenuMaker::MenuMaker(String DataBase[], int length) { //configurate base menu or defaul functions
  DataB = DataBase;
  lengthDB = length;
  Line = 0;
}

void MenuMaker::UpdateMenuConfiguration(char toConfigurate, int NewLength, String *NewDataBase, int NewLine) {
  switch(toConfigurate){ //control how many of them want to configurate
  case '1':
  if(NewLength>0)lengthDB = NewLength; //modify length pf the menu
  break;
  case '2':
  DataB = NewDataBase; //modify the data to show
  break;
  case '3':
  Line = NewLine; //modify which part of the menu you are on
  break;
  }
}

void MenuMaker::print() { //print into the screen the options. "This is generic LCD I2C 16X2 SCREEN Drivers"
  lcd.setCursor(0, 0);
  lcd.print(DataB[Line]);
  lcd.setCursor(0, 1);
  if (Line != lengthDB - 1) lcd.print(DataB[Line + 1]);
  else lcd.print(DataB[0]);
}

void MenuMaker::control() {
  char key = keypad.getKey();
  if (key) {
    switch (key) {
      case 'B':
        if (Line < lengthDB) Line++;
        break;
      case 'A':
        if (Line > -1) Line--;
        break;
      case '#':
        if (Layout != 3) Layout = Layout + 1;
        break;
      case '*':
        if (Layout != 1) Layout = Layout - 1;
        break;
    }
    if (Line < 0) Line = lengthDB - 1; //prevention measurements for negative or overload
    if (Line >= lengthDB) Line = 0;
    if(Sound==true) tone(13, random(4000,5000), 50);
    lcd.clear();
  }
}
int MenuMaker::returnLine() {
  return Line;
}
//----------Menu Control_END----------

//------------------------------------

//----------ALU----------
class ArimeticLogicUnit {
  public:
    ArimeticLogicUnit(char Kind);
    void ALU(char Operator, float A, float B, float C, float D);
    void NumberCase();
    void operatorS(char OperatorB);
    float getSolv();

  private:
    char KIND;
    float At;
    float Bt;
    float Ct;
    float Dt;
    float Solv;
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
void ArimeticLogicUnit::ALU(char Operator, float A, float B, float C, float D) {
      At = A;
      Bt = B;
      Ct = C;
      Dt = D;
  switch (KIND) {
    case 'M':
      break;
    case 'B':
      switch (Operator) {
        case 'S':
          Solv = At + Bt;
          break;
        case 'R':
          Solv = At - Bt;
          break;
        case 'D':
          if (Bt != 0.00) Solv = At / Bt;
          else Solv = 409;
          break;
        case 'M':
          Solv = At * Bt;
          break;
        case 'P':
          Solv = pow(At, Bt);
          break;
        case 'r':
          Solv = pow(At, 1 / Bt);
          break;
      }
      break;
    case 'T':
      switch (Operator) {
        case 'V':
          Solv = At * Bt * Ct;
          break;
      }
      break;
    case 'P':
      break;
  }
}
void ArimeticLogicUnit::NumberCase() {
  char key = keypad.getKey();
  if (key) {
    switch (key) {
      case '0':
        if (CD != true) {
          CA = CA * 10;
        }
        else {
          CE = CE / 10;
          CA = CA * CE;
        }
        break;
      case '1':
        if (CD != true) {
          CA = CA * 10 + 1;
        }
        else {
          CE = CE / 10;
          CA = CA + 1 * CE;
        }
        break;
      case '2':
        if (CD != true) {
          CA = CA * 10 + 2;
        }
        else {
          CE = CE / 10;
          CA = CA + 2 * CE;
        }
        break;
      case '3':
        if (CD != true) {
          CA = CA * 10 + 3;
        }
        else {
          CE = CE / 10;
          CA = CA + 3 * CE;
        }
        break;
      case '4':
        if (CD != true) {
          CA = CA * 10 + 4;
        }
        else {
          CE = CE / 10;
          CA = CA + 4 * CE;
        }
        break;
      case '5':
        if (CD != true) {
          CA = CA * 10 + 5;
        }
        else {
          CE = CE / 10;
          CA = CA + 5 * CE;
        }
        break;
      case '6':
        if (CD != true) {
          CA = CA * 10 + 6;
        }
        else {
          CE = CE / 10;
          CA = CA + 6 * CE;
        }
        break;
      case '7':
        if (CD != true) {
          CA = CA * 10 + 7;
        }
        else {
          CE = CE / 10;
          CA = CA + 7 * CE;
        }
        break;
      case '8':
        if (CD != true) {
          CA = CA * 10 + 8;
        }
        else {
          CE = CE / 10;
          CA = CA + 8 * CE;
        }
        break;
      case '9':
        if (CD != true) {
          CA = CA * 10 + 9;
        }
        else {
          CE = CE / 10;
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
        return;
        break;
      case '#':
        CB =  true;
        break;
      case 'C':
        if (CD != true) {
          if (CA != 0 && CA >= 10) CA = int(CA = CA / 10);
          else CA = 0;
        }
        else {
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
    if(Sound==true) tone(13, random(4000,5000), 50);
  }
  if (CA > 9999999) CA = 0;
}
void ArimeticLogicUnit::operatorS(char OperatorB) {
  switch (KIND) {
    case 'M':
      while (CB != true && CC == 1) {
        NumberCase();
        lcd.setCursor(0, 0);
        lcd.print("ING A");
        lcd.setCursor(0, 1);
        lcd.print(CA); // state 1
      }
      CC = 2;
      CB = false;
      CD = false;
      CE = 1.0;
      carrier1 = CA;
      CA = 0;
      ALU(OperatorB, carrier1, 0, 0, 0);
      lcd.clear();
      while (CC == 2) {
        NumberCase();
        lcd.setCursor(0, 0);
        lcd.print("SOLV");
        lcd.setCursor(0, 1);
        lcd.print(Solv); // state 2
      }
      break;
    case 'B':
      while (CB != true && CC == 1) {
        NumberCase();
        lcd.setCursor(0, 0);
        lcd.print("ING A");
        lcd.setCursor(0, 1);
        lcd.print(CA);
      }
      CB = false;
      carrier1 = CA;
      CA = 0;
      CD = false;
      CE = 1.0;
      CC = 2; // state 1
      lcd.clear();
      while (CB != true && CC == 2) {
        NumberCase();
        lcd.setCursor(0, 0);
        lcd.print("ING B");
        lcd.setCursor(0, 1);
        lcd.print(CA); // state 2
      }
      CC = 3;
      CB = false;
      carrier2 = CA;
      CA = 0;
      CD = false;
      CE = 1.0;
      ALU(OperatorB, carrier1, carrier2, 0, 0);
      lcd.clear();
      while (CC == 3) {
        NumberCase();
        lcd.setCursor(0, 0);
        lcd.print("SOLV");
        lcd.setCursor(0, 1);
        lcd.print(Solv); // state 3
      }
      break;
    case 'T':
      while (CB != true && CC == 1) {
        NumberCase();
        lcd.setCursor(0, 0);
        lcd.print("ING A");
        lcd.setCursor(0, 1);
        lcd.print(CA);
      }
      CB = false;
      carrier1 = CA;
      CA = 0;
      CD = false;
      CE = 1.0;
      CC = 2; // state 1
      lcd.clear();
      while (CB != true && CC == 2) {
        NumberCase();
        lcd.setCursor(0, 0);
        lcd.print("ING B");
        lcd.setCursor(0, 1);
        lcd.print(CA); // state 2
      }
      CC = 3;
      CB = false;
      carrier2 = CA;
      CA = 0;
      CD = false;
      CE = 1.0;
      lcd.clear();
      while (CB != true && CC == 3) {
        NumberCase();
        lcd.setCursor(0, 0);
        lcd.print("ING C");
        lcd.setCursor(0, 1);
        lcd.print(CA); // state 3
      }
      CC = 4;
      CB = false;
      carrier3 = CA;
      CA = 0;
      CD = false;
      CE = 1.0;
      ALU(OperatorB, carrier1, carrier2, carrier3, 0);
      lcd.clear();
      while (CC == 4) {
        NumberCase();
        lcd.setCursor(0, 0);
        lcd.print("SOLV");
        lcd.setCursor(0, 1);
        lcd.print(Solv); // state 4
      }
      break;
    case 'P':
      while (CB != true && CC == 1) {
        NumberCase();
        lcd.setCursor(0, 0);
        lcd.print("ING A");
        lcd.setCursor(0, 1);
        lcd.print(CA);
      }
      CB = false;
      carrier1 = CA;
      CA = 0;
      CD = false;
      CE = 1.0;
      CC = 2; // state 1
      lcd.clear();
      while (CB != true && CC == 2) {
        NumberCase();
        lcd.setCursor(0, 0);
        lcd.print("ING B");
        lcd.setCursor(0, 1);
        lcd.print(CA); // state 2
      }
      CC = 3;
      CB = false;
      carrier2 = CA;
      CA = 0;
      CD = false;
      CE = 1.0;
      lcd.clear();
      while (CB != true && CC == 3) {
        NumberCase();
        lcd.setCursor(0, 0);
        lcd.print("ING C");
        lcd.setCursor(0, 1);
        lcd.print(CA); // state 3
      }
      CC = 4;
      CB = false;
      carrier3 = CA;
      CA = 0;
      CD = false;
      CE = 1.0;
      lcd.clear();
      while (CB != true && CC == 4) {
        NumberCase();
        lcd.setCursor(0, 0);
        lcd.print("ING D");
        lcd.setCursor(0, 1);
        lcd.print(CA); // state 4
      }
      CC = 5;
      CB = false;
      carrier4 = CA;
      CA = 0;
      CD = false;
      CE = 1.0;
      lcd.clear();
      ALU(OperatorB, carrier1, carrier2, carrier3, carrier4);
      lcd.clear();
      while (CC == 5) {
        NumberCase();
        lcd.setCursor(0, 0);
        lcd.print("SOLV");
        lcd.setCursor(0, 1);
        lcd.print(Solv); // state 5
      }
      break;
  }
}
float ArimeticLogicUnit::getSolv() {
  return Solv;
}
//----------ALU_END----------
//----------Programer_END----------
//----------Boot----------
ArimeticLogicUnit Malu('M');
ArimeticLogicUnit Balu('B');
ArimeticLogicUnit Talu('T');
ArimeticLogicUnit Palu('P');
MenuMaker menu(MainMenuBase, MENU_ITEMSB);
MenuMaker menuAri(Menu2Base, MENU_ITEMS);
void setup() {
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  analogWrite(12,120);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  int A = EEPROM.read(0);
  if(A!=1){
  lcd.setCursor(0,0);
  lcd.print("Bienvenido/a");
  delay(5000);
  lcd.clear();
  lcd.print("SAIFT");
  delay(2000);
  EEPROM.write(0,1);
  lcd.clear();
  }else{
  lcd.setCursor(0, 0);
  lcd.print("KINO OS");
  delay(random(100, 1000));
  menu.print();
  }
}
void loop() {
  Logistic();
  analogWrite(12,255);
}
bool usedSec(int startRow, int startCol, int numFilas, int numColumnas) {
  for (int i = startRow; i < startRow + numFilas; i++) {
    for (int j = startCol; j < startCol + numColumnas; j++) {
      if (My_Task[i][j] == "") {  // Si encontramos un 0, la sección no está completamente en uso
        return false;
      }
    }
  }
  return true;  // Si no se encontró ningún 0, la sección está completamente en uso
}

void Logistic() {
  for (int col = 0; col < 4; col++) {
    if (usedSec(0, col, 1, 1)) {
      return;
    } else {
      My_Task[0][col] = Tasks_ID[0][col];
      col = 4;
    }
  }
  if (Layout == 1) {
    menu.print();
    menu.control();
    line = menu.returnLine();
  }
  if (Layout == 2) {
    switch (line) {
      case 0:
        menuAri.print();
        menuAri.control();
        break;
      case 1:
        game();
        break;
      case 2:
        console();
        break;
      case 3:
      freemode();
      //Layout = 1;
        break;
    }
  }
  if (Layout == 3) {
    switch (line) {
      case 0:
        seLine = menuAri.returnLine();
        switch (seLine) {
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
        break;
    }
  }
}
//----------Boot_END----------
//----------GAME_Kino_Launcher----------
//----------LocalGameVars----------
int X = 15, Y = 1;
long int points;
bool gameOver = false;
//----------LocalGameVars_END----------
void printGame() {
  lcd.clear();
  lcd.setCursor(3, Y);
  lcd.print("A");
  lcd.setCursor(X, 1);
  lcd.print("i");
  lcd.setCursor(10, 0);
  lcd.print(points);
}
void game() {
  if (!gameOver) {
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
          return;
      }
      if (Sound) tone(13, random(4000, 5000), 50);
    }
    if (X > 0) {
      X--;
    } else {
      X = 15;
    }
    if (X == 3 && Y == 0) {
      points++;
      EEPROM.put(1, points);
    }
    printGame();
    if (X == 3 && Y == 1) {
      lcd.clear();
      lcd.print("Game Over");
      delay(300);
      X = 15;
      Y = 1;
      gameOver = true;
    }
    delay(100);
  } else {
    EEPROM.get(1, points);
    gameOver = false;
  }
}
//----------GAME_END_Kino_Launcher----------
//----------GAME_KNO_Launcher----------

//Need a compiler

//----------GAME_END_KNO_Launcher----------
//----------ExperimentalFunctions----------
//----------CONSOLE----------
//----------LocalCONSOLEVars----------
String TT = "DentakuIno/Model/F011N3/Serial/Number/0000000000/Soft/Vert/KINO/OSS/1.6.5/";
short int CCS = 1;
String pos = "root";
int subDpos[6] = {0,0,1,1,2,2}; // [0] to [1] para root, [2] to [3] para kino & [4] to [5] para data
String subD[3] = {"HOME ","LOGS","APPDATA"}; 
//----------LocalCONSOLEVars_END----------
void console() {
  char key = keypad.getKey();
  if (key) {
    switch (key) {
      case 'A':
        CCS = 1;
        lcd.setCursor(15, 1);
        lcd.print("A");
        break;
      case 'B':
        CCS = 2;
        lcd.setCursor(15, 1);
        lcd.print("J");
        break;
      case 'C':
        CCS = 3;
        lcd.setCursor(15, 1);
        lcd.print("S");
        break;
      case '*':
        lcd.clear();
        Layout = 1;
        return;
        break;
      case '#':
        if (TIC.length() > 0) {  // Ensure there's at least one character in TIC
          TIC.remove(TIC.length() - 1);  // Remove the last character
        }
        lcd.clear();
        break;
      case 'D':

        //Begin Compiler----------------------------------------------
        if(pos == "root"){
        if (TIC.indexOf("CD") != -1) {
          if(TIC.indexOf("ROOT", 2) != -1){
            pos = "root";
          }
          else if(TIC.indexOf("KINO", 2) != -1){
            pos = "kino";
          }
          else if(TIC.indexOf("DATA", 2) != -1){
            pos = "data";
          }
          if(TIC.indexOf("HOME", 2) != -1){
            pos = "root/home";
          }
        }
        if (TIC.indexOf("LI") != -1) {
          lcd.setCursor(0,1);
          if(subDpos[0]!=subDpos[1]){ 
          for(int i=0; i < 2; i++){
          lcd.print(subD[subDpos[i]]);
          }
        }else if(subDpos[0]==subDpos[1]){
          lcd.print(subD[subDpos[0]]);
        }
        }

        if(TIC.indexOf("APP INSTALL") != -1){
          if(TIC.indexOf("SOUND", 10) != -1){
          lcd.setCursor(0,1);
          lcd.print("Downloading...");
          delay(1000);
          lcd.clear();
          lcd.setCursor(0,1);
          lcd.print("Sucefull");
          Sound = true;
          }
          if(TIC.indexOf("TRYAL", 10) != -1){
          lcd.setCursor(0,1);
          lcd.print("Downloading...");
          delay(1000);
          lcd.clear();
          lcd.setCursor(0,1);
          lcd.print("Sucefull");
          menu.UpdateMenuConfiguration('1', 1, nullptr, 0);
          }
          if(TIC.indexOf("AKNO", 10) != -1){
          lcd.setCursor(0,1);
          lcd.print("Downloading...");
          delay(1000);
          lcd.clear();
          lcd.setCursor(0,1);
          lcd.print("Not Found");
          }
        }

        }
        if(pos == "kino"){
          if (TIC.indexOf("CD") != -1) {
          if(TIC.indexOf("ROOT", 2) != -1){
            pos = "root";
          }
          else if(TIC.indexOf("KINO", 2) != -1){
            pos = "kino";
          }
          else if(TIC.indexOf("DATA", 2) != -1){
            pos = "data";
          }
          if(TIC.indexOf("LOGS", 2) != -1){
            pos = "root/logs";
          }
        }
        if (TIC.indexOf("LS") != -1) {
          lcd.setCursor(0,1);
          if(subDpos[2]!=subDpos[3]){ 
          for(int i=0; i < 2; i++){
          lcd.print(subD[subDpos[i+2]]);
          }
        }else if(subDpos[2]==subDpos[3]){
          lcd.print(subD[subDpos[2]]);
        }
        }
        }
        if(pos == "data"){
          if (TIC.indexOf("CD") != -1) {
          if(TIC.indexOf("ROOT", 2) != -1){
            pos = "root";
          }
          else if(TIC.indexOf("KINO", 2) != -1){
            pos = "kino";
          }
          else if(TIC.indexOf("DATA", 2) != -1){
            pos = "data";
          }
          if(TIC.indexOf("APPDATA", 2) != -1){
            pos = "root/appdata";
          }
        }
        if (TIC.indexOf("LS") != -1) {
          lcd.setCursor(0,1);
          if(subDpos[4]!=subDpos[5]){ 
          for(int i=0; i < 2; i++){
          lcd.print(subD[subDpos[i+4]]);
          }
        }else if(subDpos[4]==subDpos[5]){
          lcd.print(subD[subDpos[4]]);
        }
        }
        }
        if(pos == "root/home"||pos == "kino/logs"||pos == "data/appdata"){
          if (TIC.indexOf("CD") != -1) {
          if(TIC.indexOf("ROOT", 2) != -1){
            pos = "root";
          }
          else if(TIC.indexOf("KINO", 2) != -1){
            pos = "kino";
          }
          else if(TIC.indexOf("DATA", 2) != -1){
            pos = "data";
          }
        }
        if (TIC.indexOf("LS") != -1) {
          lcd.setCursor(0,1);
          lcd.print("no data");
          }
        }
        if (TIC.indexOf("PROS") != -1) {
          lcd.setCursor(0,1);
          lcd.print("Consoling:1.2m i");
          }
        if (TIC.indexOf("KILL I") != -1) {
          lcd.clear();
          Layout = 1;
          return;
          }
        //End Compiler-------------------------------------------------
        break;
    }
  }
  if (key) { 
    if(Sound==true) tone(13, random(4000,5000), 50);
  }
  if (CCS == 1 || CCS == 2 || CCS == 3) {
    switch (key) {
      case '1':
        if (CCS == 1) TIC += 'A';
        else if (CCS == 2) TIC += 'J';
        else if (CCS == 3) TIC += 'S';
        break;
      case '2':
        if (CCS == 1) TIC += 'B';
        else if (CCS == 2) TIC += 'K';
        else if (CCS == 3) TIC += 'T';
        break;
      case '3':
        if (CCS == 1) TIC += 'C';
        else if (CCS == 2) TIC += 'L';
        else if (CCS == 3) TIC += 'U';
        break;
      case '4':
        if (CCS == 1) TIC += 'D';
        else if (CCS == 2) TIC += 'M';
        else if (CCS == 3) TIC += 'V';
        break;
      case '5':
        if (CCS == 1) TIC += 'E';
        else if (CCS == 2) TIC += 'N';
        else if (CCS == 3) TIC += 'W';
        break;
      case '6':
        if (CCS == 1) TIC += 'F';
        else if (CCS == 2) TIC += 'O';
        else if (CCS == 3) TIC += 'X';
        break;
      case '7':
        if (CCS == 1) TIC += 'G';
        else if (CCS == 2) TIC += 'P';
        else if (CCS == 3) TIC += 'Y';
        break;
      case '8':
        if (CCS == 1) TIC += 'H';
        else if (CCS == 2) TIC += 'Q';
        else if (CCS == 3) TIC += 'Z';
        break;
      case '9':
        if (CCS == 1) TIC += 'I';
        else if (CCS == 2) TIC += 'R';
        else if (CCS == 3) TIC += ' ';
        break;
    }
  }
  int startPos = max(0, (16 - TIC.length()) / 2);
  lcd.setCursor(startPos, 0);
  lcd.print(TIC);
  
}
//----------CONSOLE_END----------

class FreeMode {
  public:
    void control();
    void logic();

  private:
    float C0 = 0; //control0 for carry output
    String C1; //control1 for carry input
    boolean C2 = false;
    String C3;
    int C4 = 0;
    int C8 = 1;
    long carrier1 = 0;
    long carrier2 = 0;
};
void FreeMode::control() {
  char key = keypad.getKey();
  if (key) {
    switch (key) {
      case 'A':
        switch (C8) {
          case 1:
            C1 += "+";
            break;
        }
        break;
      case 'B':
        switch (C8) {
          case 1:
            C1 += "-";
            break;
        }
        break;
      case 'C':
        switch (C8) {
          case 1:
            C3 += "*";
            break;
        }
        break;
      case 'D':
        switch (C8) {
          case 1:
            C1 += "/";
            break;
        }
      case '#':
        C2 = true;
        break;
      case '*':
        lcd.clear();
        Layout -= 1;
        return;
        break;

      //numberlogicsection------------------------------------------------------

      case '0':
        C1 += "0";
        break;
      case '1':
        C1 += "1";
        break;
      case '2':
        C1 += "2";
        break;
      case '3':
        C1 += "3";
        break;
      case '4':
        C1 += "4";
        break;
      case '5':
        C1 += "5";
        break;
      case '6':
        C1 += "6";
        break;
      case '7':
        C1 += "7";
        break;
      case '8':
        C1 += "8";
        break;
      case '9':
        C1 += "9";
        break;
    }
    if(Sound==true) tone(13, random(4000,5000), 50);
  }
  if(C2!=true){
  lcd.setCursor(0,0);
  lcd.print(C1);
  }
}
void FreeMode::logic() {
  if(C2==true){
  C4 =  C1.indexOf("+");
  if(C4!=-1){
    C3 = C1.substring(0,C4);
    C1.remove(0,C4+1);
  }
  carrier1 = C3.toInt();
  carrier2 = C1.toInt();
  C0 = carrier2 + carrier1;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(C0);
  C1 = "";
  C3 = "";
  }
  C2 = false;
}
FreeMode fmd;
void freemode(){
  fmd.control();
  fmd.logic();
}

String AKNO_COMP(String Data){
}

//Console: The console is a experimental feacture added in 1.4.2 with some basic commands like CD ROOT KINO DATA, LS, APP INSTALL. 1.2m consoling.
//FreeMode: Added in 1.6.4 allows you to write operations like you would in any normal calculator, you choose the order, we make the calculations.
//NewLogic: reference to the uptade of each logic part of the code. applied in MenuCreator since 1.2.5
//Sound: added in 1.5.6 allows you to have auditive feedback whenever you press a key.
/*
Oficial Kino OSS 2 beta 1.7 code, many functions were added, but in this seccions you will found what will come in the next version.

Consoling 1.3m, will include all minimal functions for any system, also including a few more apps.
AmperDown
*/
