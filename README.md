# Resumen
Sistema de acceso mediante tecnología RFID, diseñado para la cátedra de Sistemas de Transmisión Inalámbrica de la UTN FRLP en el 2019.

# Descripción
El Sistema se basa en un sensor remoto para detectar una tarjeta o tag de acceso RFID (cliente), y un Servicor Local que procesa los datos enviados y valida el acceso. La transferencia de datos se realiza mediante bluetooth.

El usuario debe identificarse con una tarjeta/tag RFID y clave numérica de 3 digitos. El Servidor validará esta información con una Base de Datos local y retornará el resultado, que se le mostrará al usuario mediante una pantalla LCD y un beep-code.

# Instalación
## Sensor remoto o cliente:
Dentro del direcotrio "main/arduino", cargar el código en el Arduino.

## Servidor local
En la computadora que hace de Server, instalar un motor de Base de Datos, y ejecutar las consultas SQL dentro del directorio "main/mysql". Editar el archivo "insert-usuarios.sql" con los datos de usuarios y tarjetas asociadas deseado.

En el directorio "main/python", editar el archivo "server.py" con los datos de la Base de Datos y módulo Bluetooth empleado, y ejecutar el mismo desde Python para iniciar el Servidor.

# Tecnologías empleadas
## Sensor remoto o Cliente:
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
  - **Base de Datos:** MySQL Versión 5.7.27
