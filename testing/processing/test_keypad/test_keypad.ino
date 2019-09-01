//Ejemplo de uso de un keypad 4x4, con la libreria correspondiente

//Se incluye la libreria
#include <Keypad.h>

//Se definen variables para las ROWS y las COLUMNS
const byte ROWS = 4; 
const byte COLS = 4; 

//Matriz de acceso, para saber que tecla fue presionada
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

/* Se asignan los pines digitales del arduino para las filas y columnas */
byte rowPins[ROWS] = {2, 3, 4, 5}; 
byte colPins[COLS] = {6, 7, 8, 9}; 

// Se genera el objeto keypad con lo anterior declarado
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(9600);
}
  
void loop(){
  //Captura cuando se presiona una tecla
  char customKey = customKeypad.getKey();
  
  //Si se presiono, la muestra en pantalla
  if (customKey){
    Serial.println(customKey);
  }
}
