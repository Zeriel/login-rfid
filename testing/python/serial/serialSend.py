# Intento de comunicacion por Serial, requiere conectar manualmente el HC-05 a la PC antes de ejecutar.
# Esto no fue probado, ya que se logro hacer funcionar el pyBluez. Era una alternativa en caso de fallar.

import serial

s = serial.Serial("COM3",9600,timeout = 2)

s.write(bytes("hello!",'utf-8'))