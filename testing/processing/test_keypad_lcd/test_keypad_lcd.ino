//Ejemplo de uso del keypad con una pantalla LCD, para mostrar la tecla presionada.
//
//La pantalla tiene integrada el driver I2C, por lo que solo se requieren 4 cables. Dicho
//driver requiere 2 librerias:
//  - Wire.h : Para definir los cables
//  - LiquidCrystal_I2C.h : Para poder operar sobre el I2C.

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5}; 
byte colPins[COLS] = {6, 7, 8, 9}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

//Crea la instancia de I2C (direccionHexa, Columnas, Filas)
//Para saber la address, ver "verify_lcd_address"
LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup(){
  Serial.begin(9600);
  lcd.backlight();  //Da color de fondo a la pantalla
  lcd.init();       //Inicia la pantalla
}

void loop(){
  //Espera tecla del keypad
  char customKey = customKeypad.getKey();
  //Si hay tecla, muestra en el LCD
  if (customKey){
    Serial.println(customKey);  //Muestra la tecal por SerialMonitor
    lcd.clear();                //Limpia la pantalla del LCD
    lcd.setCursor(0, 0);        //Posiciona el cursor en la pantalla (columna, fila)
    lcd.print(customKey);       //Imprime en la pantalla
    if (customKey == '5'){      //Si la tecla es igual a 5, damos un comportamiento determinado
      lcd.clear();
      lcd.setCursor(0, 0); 
      lcd.print("Renglon sup");
      lcd.setCursor(0, 1); 
      lcd.print("Renglon inf");
    }
  }
}
