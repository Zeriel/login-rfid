// Sketch de conexion con el Servidor Python. Desde Python, se comienza la comunicaccion,
// y segun los caracteres ingresados por el SerialMonitor, se genera una respuesta desde
// el Servidor.

#include <SoftwareSerial.h>  
  
// Define los pines RX y TX para el HC-05  
const int rxpin = 22;  
const int txpin = 24;  
  
// Variables para almacenar datos de entrada  
char rec= 'A';  
char serialInput;
  
// Instanciacion del bluetooth 
SoftwareSerial bluetooth(rxpin, txpin);  
  
void setup(){  
  // El Serial es solo para las pruebas, no es necesario
  Serial.begin(9600);  
  Serial.println("Serial ready");  
  // Inicializo el bluetooth 
  bluetooth.begin(9600);  
  bluetooth.println("Bluetooth ready");  
}  
  
void loop(){ 
  // Valido si no ingreso algo por Monitor Serie
  if (Serial.available() > 0) {
    serialInput = Serial.read();  // Leo el caracter ingresado por Serial

    if (serialInput == 'c'){
      Serial.println("Enviando");
      bluetooth.println('c');
      delay(10); 
    }
    else if (serialInput == 'e'){
      Serial.println("Enviando");
      bluetooth.println('e');
      delay(10); 
    }
    else{
      Serial.println("Opcion no existente");
      delay(10); 
    }
  }
    
  // Valido si no ingreso algo por Bluetooth
  if(bluetooth.available()){  
    rec = bluetooth.read(); // Leo el caracter ingresado por Bluetooth
    //Serial.println(rec);  // Valido lo que llego por Bluetooth imprimiendolo por Serial  
  }     
  if(rec == 'g'){       
    Serial.println("Acceso autorizado"); // Valido por Serial
    rec = 'A'; // Cambio el valor de "rec" para que no vuelva a entrar en el if
  }  
  // Espero 10 ms para que se acomode el hardware y no haga interferencia
    delay(10);  
}  
