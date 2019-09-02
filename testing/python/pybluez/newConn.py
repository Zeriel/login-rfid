# Interaccion ida/vuelta con un arduino

# RECIBIR DATA: data = sock.recv(1024)
# ENVIAR DATA: sock.send(data)

#Glosario de data en chars:
#   - c : CheckThisData
#   - g : GrantedAccess
#   - d : DeniedAccess
#   - e : EndConnection

import bluetooth
from bluetooth.btcommon import BluetoothError

# Datos de conexion
bd_addr = "98:D3:31:F5:9A:0D"
port = 1

# Cartel de espera
print("Conectando...")

try:
    # Intenta conectarse al numero de MAC y puerto especificados
    sock = bluetooth.BluetoothSocket( bluetooth.RFCOMM )
    sock.connect((bd_addr, port))
    print("Conectado!")
    # El Arduino espera un "y" para confirmar que el Servidor establecio la conexion
    data = "y"
    close_bt = False
    # Mientras el arduino no envie "e", se espera un input
    while not close_bt:
        print("Esperando credenciales")
        data = sock.recv(1024)
        dataString = data.decode("utf-8") 
        if dataString == "c":
            print("Mando credenciales")
            data = "g"
            sock.send(data)
        if dataString == "e":
            print("Apagar")
            close_bt = True

    sock.close()
except BluetoothError as e:
    print('No pudo conectarse')
