# Resumen
Sistema de acceso mediante tecnología RFID, diseñado para la cátedra de Sistemas de Transmisión Inalámbrica de la UTN FRLP.

# Descripción
El Sistema se basa en un sensor remoto para detectar una tarjeta o tag de acceso RFID, y un Servicor Local que procesa los datos enviados y valida el acceso. La transferencia de datos se realiza mediante bluetooth.

El usuario debe identificarse con una tarjeta/tag RFID y clave numérica de 3 digitos. El Servidor validará esta información y retornará el resultado, que se le mostrará al usuario mediante una pantalla LCD y un beep-code.

# Tecnologías empleadas
## Sensor remoto:
El sensor remoto consta de un Arduino MEGA conectado a multiples módulos:
  - **RFID RC522:** La base del Sistema, sensor de lectura/escritura de medios RFID para identificación.
  - **KeyPad 3x4/4x4:** Teclado para el ingreso de una clave asociada a la tarjeta.
  - **HC-05 ZS040:** Dispositivo Bluetooth para la comunicación entre los sensores y el Servidor.
  - **Pantalla LCD 1602 con I2C:** Pantalla que realiza la interacción entre el usuario y el Sistema.
  - **Buzzer:** Dispositivo para asistir a la pantalla LCD en la comunicación con el usuario mediante códigos beep.


## Servidor Local:
El Servidor que procesa la información se basa en un programa Python, que valida los datos recibidos por bluetooth con una Base de Datos y retorna el resultado. Para la comunicación Bluetooth, se emplea la librería PyBLuez bajo un entorno Linux Mint.

# Versiones de software
Al momento de hacer este proyecto, utilice las siguientes especificaciones:
  - **SO:** Linux Mint 19.2 "Tina".
  - **Python:** Versión 3.7.2
  - **Arduino IDE:** Versión 1.8.9
