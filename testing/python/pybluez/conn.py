# Ejemplo de conexion basica a un dispositivo Bluetooth, provisto por la documentacion de pyBluez.
# Se especifica el numero de MAC del dispositivo y un puerto de comunicacion, y se intenta hacer un enlace.

# Se utilizan tres librerias:
#           - PyBluez para la conexion en si
#           - BluetoothError para el Try-Except
#           - Time, para hacer que dure la conexion Bluetooth

import time
import bluetooth
from bluetooth.btcommon import BluetoothError

bd_addr = "98:D3:31:F5:9A:0D"   #HC-05 MAC address
port = 3
sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
# Intenta conectarse
try:
    sock.connect((bd_addr, port))

    sock.send("Hello!")

    print('Pudo conectarse')

    # Hago esperar 10 segundos, para verificar que la conexion existe (led del HC-05)
    time.sleep(10)

    sock.close

    print('Termino la conexion')
except BluetoothError as e:
    print('No pudo conectarse')