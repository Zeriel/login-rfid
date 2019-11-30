    // Desarrollo final del Cliente. Espera a que el Server establezca la conexion, y comienza la comunicacion arduino-server mediante keypad y bluetooth,
    // y la comunicacion sistema-usuario mediante la pantalla LCD y el buzzer
    
    
    // LIBRERIAS BLUETOOTH
    #include <SoftwareSerial.h>  

    // LIBRERIAS KEYPAD
    #include <Keypad.h>

    // LIBRERIAS LCD
    #include <Wire.h> 
    #include <LiquidCrystal_I2C.h>

    // LIBRERIAS RFID
    #include <MFRC522Extended.h>
    #include <require_cpp11.h>
    #include <deprecated.h>
    #include <MFRC522.h>
    
    #include <SPI.h>
    #include <MFRC522.h>

    // DEFINICIONES PARA BLUETOOTH
    // Defino los pines del Arduino para TX y RX con el bluetooth 

    const int rxpin = 62;  // NINGUNO de los RX del MEGA funcionaba, encontre en StackOverflow que este puerto podria servir como RX, y funciono
    const int txpin = 14; 
    
    char rec = 'A';       // Variable para almacenar lo que lee por BT 
    char conectado = 'n'; // Variable de control, para no leer tarjetas hasta tanto el server no de un mensaje de conexion
      
    // Inicializar el objeto bluetooth, con los pines del arduino 
    SoftwareSerial bluetooth(rxpin, txpin);  
    
    // ---------------------------------------------------

    // DEFINICIONES PARA KEYPAD
    // Se definen variables para las ROWS y las COLUMNS
    const byte ROWS = 4; 
    const byte COLS = 4; 

    //Matriz de acceso, para saber que tecla fue presionada
    char hexaKeys[ROWS][COLS] = {
      {'1', '2', '3', 'A'},
      {'4', '5', '6', 'B'},
      {'7', '8', '9', 'C'},
      {'*', '0', '#', 'D'}
    };

    //Se asignan los pines digitales del arduino para las filas y columnas
    byte rowPins[ROWS] = {47, 45, 43, 41}; 
    byte colPins[COLS] = {39, 37, 35, 33}; 

    // Se genera el objeto keypad con lo anterior declarado
    Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

    // ---------------------------------------------------

    // DEFINICIONES PARA LCD
    LiquidCrystal_I2C lcd(0x3F, 16, 2);
    char limpiar = 's'; // Variable para entrar a un bloque que limpia la pantalla

    // ---------------------------------------------------

    // DEFINICIONES PARA RFID

    #define RST_PIN         5
    #define SS_PIN          53
    
    MFRC522 mfrc522(SS_PIN, RST_PIN);  // Crea la instancia de MFRC522

    char cardID[16];                   // Arreglo para almacenar el ID de la tarjeta

    // ---------------------------------------------------

    // DEFINICIONES PARA PIN (Usa modulo KeyPad)
    char pedirClave = 'n';    // Para entrar en el bloque que espera el ingreso de un PIN
    char pinIngresado = 'n';  // Para repetir hasta que no se ingresen los 3 digitos del PIN
    String pin;               // El PIN, un string de 3 digitos

    // ---------------------------------------------------

    // DEFINICIONES PARA BUZZER
    int buzz = 23;

    // ---------------------------------------------------
    // ---------------------------------------------------
    // ---------------------------------------------------
      
    void setup(){  
      Serial.begin(9600);  
      //Inicializa bluetooth
      bluetooth.begin(9600);  
      //Inicializa LCD 
      lcd.backlight();  //Da color de fondo a la pantalla
      lcd.init();       //Inicia la pantalla
      lcd.clear();         
      lcd.setCursor(0, 0); 
      lcd.print("SIN");
      lcd.setCursor(0, 1); 
      lcd.print("CONEXION");
      //Inicializa RFID
      SPI.begin();          // Inicializa bus SPI
      mfrc522.PCD_Init();   // Inicializa objeto MFRC522
      mfrc522.PCD_DumpVersionToSerial();  // Dump de la info del MFRC522
      //Inicializo Buzzer
      pinMode(buzz, OUTPUT);    //PinMode configurado como SALIDA
      digitalWrite(buzz, LOW);  //Apagado por defecto
    }  

    // ---------------------------------------------------
    // ---------------------------------------------------
      
    void loop(){ 
      //Solo lee tarjetas si esta conectado al bluetooth
      if (conectado == 's'){

        // Bloque que limpia la pantalla en cada iteracion, si hace falta
        if (limpiar == 's'){
          lcd.clear();         
          lcd.setCursor(0, 0); 
          lcd.print("Acercar tag RFID");
          limpiar = 'n';
        }

        // BLOQUE PRINCIPAL -- Si hay tarjetas, inicia proceso de lectura
        if ( mfrc522.PICC_IsNewCardPresent()) {
          // Selecciona la info del tag
          if ( mfrc522.PICC_ReadCardSerial()) {
            // Guardo el ID del tag en el arreglo cardID. El UID es un arreglo de bytes
            sprintf(cardID, "%02x%02x%02x%02x", mfrc522.uid.uidByte[0], mfrc522.uid.uidByte[1], mfrc522.uid.uidByte[2], mfrc522.uid.uidByte[3]);
            // Envio el UID por bluetooth
            bluetooth.print(cardID);
            // Terminamos la lectura de la tarjeta  actual
            mfrc522.PICC_HaltA();
            digitalWrite(buzz, HIGH); //BIP corto, leyo un tag
            delay(250);
            digitalWrite(buzz, LOW);
            delay(250);  
            pedirClave = 's';   
            limpiar = 's';
          }
        }

        // SEGUNDO BLOQUE -- Si ya se ingreso un tag RFID, ahora se pide el PIN asociado al mismo
        if (pedirClave == 's'){
          lcd.clear();         
          lcd.setCursor(0, 0); 
          lcd.print("Ingrese su PIN");
          pinIngresado = 'n';
          pin = "";
          lcd.setCursor(3, 1); 
          lcd.print("->");
          while (pinIngresado == 'n'){
            //Captura cuando se presiona una tecla
            char customKey = customKeypad.getKey();
            
            if (customKey){
              digitalWrite(buzz, HIGH); //Un BIP muy corto, presiono una tecla
              delay(100);
              digitalWrite(buzz, LOW);
              pin += customKey;
              //Pequeño juego para escribir un asterisco por cada caracter que pone, usando el length
              lcd.setCursor(pin.length()+5, 1); 
              lcd.print("*");
            }
            // Control, solo sale del WHILE si ya se ingresaron 3 digitos para el PIN
            if (pin.length() == 3){
              pinIngresado = 's';
            }
          } // Termina WHILE para el ingreso de PIN
          bluetooth.print(pin); // Envia el pin por BT
          pin = "";             // Pone en vacio la variable para el proximo PIN
          lcd.clear();         
          lcd.setCursor(0, 0); 
          lcd.print("Procesando...");
          //Recibo respuesta del Servidor, ya sea por acceso autorizado ('g') o denegado ('d')
          //WHILE hasta que el server mande respuesta
          while (!bluetooth.available()){
          }
          rec = bluetooth.read(); // Lee un caracter por bluetooth
          lcd.clear(); 
          if(rec == 'g'){ // Si es 'g', es acceso autorizado
            lcd.setCursor(0, 0); 
            lcd.print("Acceso");
            lcd.setCursor(0, 1); 
            lcd.print("AUTORIZADO");
            digitalWrite(buzz, HIGH); //Tres BIP cortos, para el acceso autorizado
            delay(100);
            digitalWrite(buzz, LOW);
            delay(100);
            digitalWrite(buzz, HIGH);
            delay(100);
            digitalWrite(buzz, LOW);
            delay(100);
            digitalWrite(buzz, HIGH);
            delay(100);
            digitalWrite(buzz, LOW);
          }
          if(rec == 'd'){ // 'd' es acceso denegado
            lcd.setCursor(0, 0); 
            lcd.print("Acceso");
            lcd.setCursor(0, 1); 
            lcd.print("DENEGADO");
            digitalWrite(buzz, HIGH); //Tres BIP largos, acceso denegado
            delay(250);
            digitalWrite(buzz, LOW);
            delay(150);
            digitalWrite(buzz, HIGH);
            delay(250);
            digitalWrite(buzz, LOW);
            delay(150);
            digitalWrite(buzz, HIGH);
            delay(250);
            digitalWrite(buzz, LOW);
          }
          delay(2000);  // Espero un tiempo para mostrar la validacion al usuario, y reinicia el ciclo pidiendo otro tag
          pedirClave = 'n';
        }
  
  
        //Wait ten milliseconds to decrease unnecessary hardware strain  
        delay(10);  
      }
      //Si no esta conectado, espera el dato de conexion por BT del server
      else{
        //Lectura de datos de entrada por Bluetooth
        if(bluetooth.available()){  
          rec = bluetooth.read(); // read 1 char   
        }    
        if(rec == 'y'){ // Enlace establecido con el Servidor. Estado conectado
          lcd.clear();         
          lcd.setCursor(0, 0); 
          lcd.print("Conectado"); 
          rec = 'A'; // reset rec to A to avoid inf loop
          digitalWrite(buzz, HIGH); //Buzz para cuando se conecta al Bluetooth
          delay(500);
          digitalWrite(buzz, LOW);
          delay(500);
          digitalWrite(buzz, HIGH);
          delay(500);
          digitalWrite(buzz, LOW);
          conectado = 's';
          limpiar = 's';
        }
      }
    }  
