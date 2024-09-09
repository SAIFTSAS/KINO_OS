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
byte rowPins[ROWS] = {10, 9, 8, 7};
byte colPins[COLS] = {5, 4, 3, 2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
//----------Drivers_END----------
//----------Programer----------
//----------Control Public Var---------
String MainMenuBase[] = {"Arimetica", "Videojuego", "Ajustes", "FreeMode"}; //MenuData
String Menu2Base[] = {"Suma", "Resta", "Multipl", "Division"}; //MenuData
int MENU_ITEMSB = 3; //BaseMenuItems / this most come from EEPROM
const int MENU_ITEMS = 4; //MenuItems
int Layout = 1; //MenuPosition
int line = 0; //MenuSelection
int seLine = 0; //SecundaryMenuSelection
String TIC;
boolean Sound = false; //experimental function
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
  case '4':
  if(NewLength>0)lengthDB = NewLength;
  DataB = NewDataBase;
  break;
  case '5':
  if(NewLength>0)lengthDB = NewLength;
  Line = NewLine;
  break;
  case '6':
  DataB = NewDataBase;
  Line = NewLine;
  break;
  case '7':
  if(NewLength>0)lengthDB = NewLength;
  DataB = NewDataBase;
  Line = NewLine;
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
/*void MenuMaker::print() { //print into the screen the options. "This is generic LCD I2C 20X4 SCREEN Drivers"
  lcd.setCursor(0, 0);
  lcd.print(DataB[Line]);
  lcd.setCursor(0, 1);
  lcd.print(DataB[Line + 1]);
  lcd.setCursor(0, 2);
  lcd.print(DataB[Line + 2]);
  lcd.setCursor(0, 3);
  lcd.print(DataB[Line + 3]);
}*/

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
}
void Logistic() {
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
      //freemode();
      Layout = 1;
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
//----------GAME----------
//----------LocalGameVars----------
int X = 15, Y = 1;
long int points;
//----------LocalGameVars_END----------
void printGame() {
  lcd.clear();
  lcd.setCursor(3, Y);
  lcd.print("A");
  lcd.setCursor(X, 1);
  lcd.print("i");
  lcd.setCursor(10, 0);
  lcd.print(points);
  delay(100);
  if (X > 0) X--;
  else if (X == 0) X = 15;
}
void game() {
  EEPROM.get(1, points);
  Y = 1;
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
    if(Sound==true) tone(13, random(4000,5000), 50);
  }
  printGame();
  if (X == 3 && Y == 0) points++; EEPROM.put(1, points);
  if (X == 3 && Y == 1) {
    X == 15;
    Y == 1;
    lcd.clear();
    lcd.print("Game Over");
    delay(300);
  }
}
//----------GAME_END----------
//----------ExperimentalFunctions----------
//----------CONSOLE----------
//----------LocalCONSOLEVars----------
String TT = "DentakuIno///Model/F011N3///Serial//Number/0000000000///Soft//Vert/KINO/OSS/1.6.2///";
short int CCS = 1;
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
        Layout = 1;
        break;
      case '#':
        if (TIC.length() > 0) {  // Ensure there's at least one character in TIC
          TIC.remove(TIC.length() - 1);  // Remove the last character
        }
        lcd.clear();
        break;
      case 'D':

        //Begin Compiler----------------------------------------------

        if (TIC.indexOf("OPEN/ROOT/PTS") != -1) {
          lcd.setCursor(0, 0);
          lcd.clear();
          TIC = "";
          EEPROM.get(1, points);
          lcd.print(points);
        }
        if (TIC.indexOf("OPEN/ROOT/TEM") != -1) {
          int TTLength = TT.length();
          for (int i = 0; i <= TTLength; i++) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(TT.substring(i));
            if (TTLength > 16) {
              delay(200);
            } else {
              delay(1000);
            }
          }
        }
        if (TIC.indexOf("LSBLK") != -1) {
          lcd.setCursor(0, 0);
          lcd.clear();
          TIC = "";
          lcd.print("ROOT/PTS");
          lcd.setCursor(0, 1);
          TIC = "";
          lcd.print("ROOT/TEM");
        }
        if (TIC.indexOf("SANDBOX/ON") != -1) {
          lcd.setCursor(0, 0);
          lcd.clear();
          TIC = "";
          lcd.print("SandBox tools ON");
          MENU_ITEMSB = 4;
          menu.UpdateMenuConfiguration('1',MENU_ITEMSB,'0',0);
        }
        if (TIC.indexOf("SOUND/ON") != -1) {
          lcd.setCursor(0, 0);
          lcd.clear();
          TIC = "";
          lcd.print("Sound is ON");
          Sound=true;
        }
        if (TIC.indexOf("SOUND/OFF") != -1) {
          lcd.setCursor(0, 0);
          lcd.clear();
          TIC = "";
          lcd.print("Sound is OFF");
          Sound=false;
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
        else if (CCS == 3) TIC += '/';
        break;
    }
  }
  int startPos = max(0, (16 - TIC.length()) / 2);
  lcd.setCursor(startPos, 0);
  lcd.print(TIC);
  
}
//----------CONSOLE_END----------
/*
class FreeMode {
  public:
    void control();
    void logic();

  private:
    float C0 = 0; //control0 for carry output
    String C1; //control1 for carry the input
    boolean C2 = false;
    String C3;
    int C4 = 0;
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
            C1 += ",+";
            break;
        }
        break;
      case 'B':
        switch (C8) {
          case 1:
            C1 += ",-";
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
        C1 += '.';
        C2 = true;
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
    }
    if(Sound==true) tone(13, random(4000,5000), 50);
  }
}
void FreeMode::logic() {
  if(C2==true){
    C2=false;
    if(indexOf('/',C1)==-1){
      if(indexOf('*',C1)==-1){
        if(indexOf('+',C1)==-1||indexOf('-',C1)!==-1){
          carrier1 = indexOf(',',C1);
          if(carrier1!=-1){
          C3 = C1.substring(C4,carrier1);
          carrier2 = C3.toInt();
          }
          carrier1 = indexOf('.',C1);
          if(carrier1!=-1){
           if(carrier1!=C1.length()){
            C3 = C1.substring(indexOf(',',C1)+1,carrier1-1);
            if(indexOf(',',C3)!=-1){
              carrier1 = C3.toInt();
            }
           }
          }
        }
        else{
          lcd.print(C1);
        }
      }
      else{
      }
    }
    else{
    }
  }
}
FreeMode fmd;
void freemode(){
  fmd.logic();
}
*/
//Console: The console is a experimental feacture added in 1.2.2 with some basic commands like open / root / tem, open / root / pts, lsblk and sandbox / on.
//FreeMode: Added in 1.2.5 allows you to write operations like you would in any normal calculator, you choose the order, we make the calculations.
//NewLogic: reference to the uptade of each logic part of the code. applied in MenuCreator since 1.2.5
//Sound: added in 1.2.6 allows you to have auditive feedback whenever you press a key.
