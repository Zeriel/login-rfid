    //Ejemplo casi completo del Sistema. Espera a que el Server establezca la conexion, y comienza la comunicacion arduino-server mediante keypad y bluetooth,
    //y la comunicacion sistema-usuario mediante la pantalla LCD
    
    
    //LIBRERIAS BLUETOOTH
    #include <SoftwareSerial.h>  

    //LIBRERIAS KEYPAD
    #include <Keypad.h>

    //LIBRERIAS LCD
    #include <Wire.h> 
    #include <LiquidCrystal_I2C.h>

    // DEFINICIONES PARA BLUETOOTH
    //Define the pins used for receiving  
    //and transmitting information via Bluetooth  
    const int rxpin = 50;  
    const int txpin = 51;  
      
    //Variable to store input value  
    char rec= 'A';  
    char serialInput;
    char conectado = 'n';
      
    //Connect the Bluetooth module  
    SoftwareSerial bluetooth(rxpin, txpin);  

    //DEFINICIONES PARA KEYPAD
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
    byte rowPins[ROWS] = {47, 45, 43, 41}; 
    byte colPins[COLS] = {39, 37, 35, 33}; 

    // Se genera el objeto keypad con lo anterior declarado
    Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

    //DEFINICIONES PARA LCD
    LiquidCrystal_I2C lcd(0x3F, 16, 2);
    char limpiar = 's';
      
    void setup(){  
      //Initialize Serial for debugging purposes  
      Serial.begin(9600);  
      Serial.println("Serial ready");  
      //Initialize the bluetooth  
      bluetooth.begin(9600);  
      bluetooth.println("Bluetooth ready");  
      lcd.backlight();  //Da color de fondo a la pantalla
      lcd.init();       //Inicia la pantalla
      lcd.clear();         
      lcd.setCursor(0, 0); 
      lcd.print("ESPERANDO");
      lcd.setCursor(0, 1); 
      lcd.print("CONEXION");
    }  
      
    void loop(){ 
      if (limpiar == 's' && conectado == 's'){
        lcd.clear();         
        lcd.setCursor(0, 0); 
        lcd.print("Ingrese caracter");
        limpiar = 'n';
      }
      //Valido si no ingreso algo por Monitor Serie
      char customKey = customKeypad.getKey();
      if (customKey == 'C'){
        customKey= 'S';
        lcd.clear();         
        lcd.setCursor(0, 0); 
        lcd.print("Enviando C");
        bluetooth.println('c');
        delay(10); 
      }
      else if (customKey == '0'){
        lcd.clear();         
        lcd.setCursor(0, 0); 
        lcd.print("Enviando 0");
        bluetooth.println('e');
        delay(10); 
      }
        
      if(bluetooth.available()){  
        rec = bluetooth.read(); // read 1 char  
        Serial.println(rec);    // Printout throught Serial the Char just read.  
      }    
      if(rec == 'y'){ // If rec char is Z            
        lcd.clear();         
        lcd.setCursor(0, 0); 
        lcd.print("Conectado"); 
        rec = 'A'; // reset rec to A to avoid inf loop  
        delay(2000);
        limpiar = 's';  
        conectado = 's';
      }
       
      if(rec == 'g'){ // If rec char is Z            
        lcd.clear();         
        lcd.setCursor(0, 0); 
        lcd.print("Acceso"); 
        lcd.setCursor(0, 1); 
        lcd.print("Autorizado");
        rec = 'A'; // reset rec to A to avoid inf loop  
        delay(2000);
        limpiar = 's';  
      }  
      //Wait ten milliseconds to decrease unnecessary hardware strain  
        delay(10);  
    }  
