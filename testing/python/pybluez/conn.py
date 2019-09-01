# Ejemplo de conexion basica a un dispositivo Bluetooth, provisto por la documentacion de pyBluez.
# Se especifica el numero de MAC del dispositivo y un puerto de comunicacion, y se intenta hacer un enlace.

# Se utilizan dos librerias: PyBluez para la conexion en si, y BluetoothError para el Try-Except

import bluetooth
from bluetooth.btcommon import BluetoothError

bd_addr = "98:D3:31:F5:9A:0D"   #HC-05 MAC address
port = 3
sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
try:
    sock.connect((bd_addr, port))
except BluetoothError as e:
    print('Could not connect to the device')

sock.send("hello!!")

sock.close()