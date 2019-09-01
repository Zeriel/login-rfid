# Sistema de acceso por RFID
Sistema de acceso mediante tecnología RFID, diseñado para la cátedra de Sistemas de Transmisión Inalámbrica de la UTN FRLP.

# Descripción del Sistema
El Sistema se basa en un sensor remoto para detectar una tarjeta o tag de acceso RFID, y un Servicor Local que procesa los datos enviados y valida el acceso. La transferencia de datos se realiza mediante bluetooth.

El usuario debe identificarse con una tarjeta/tag RFID y clave numérica de 3 digitos. El Servidor validará esta información y retornará el resultado, que se le mostrará al usuario mediante una pantalla LCD y un beep-code.

# Tecnologías empleadas
- Sensor remoto:
El sensor remoto consta de un Arduino MEGA conectado a multiples módulos:


- Servidor Local:
El Servidor que procesa la información se basa en un programa Python, que valida los datos recibidos por bluetooth con una Base de Datos y retorna el resultado. Para la comunicación Bluetooth, se emplea la librería PyBLuez bajo un entorno Linux Mint.
