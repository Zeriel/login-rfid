# RECIBIR DATA: data = sock.recv(1024)
# ENVIAR DATA: sock.send(data)

#Glosario de data en chars:
#   - g : GrantedAccess
#   - d : DeniedAccess
#   - e : EndConnection

import bluetooth
from bluetooth.btcommon import BluetoothError
import time
from datetime import datetime
import mysql.connector

# Conecto con la base de datos
cnx = mysql.connector.connect(user='root', password='root',
                              host='127.0.0.1',
                              database='db_rfid')

cursor = cnx.cursor(buffered=True)

# Datos de conexion al HC-05
bd_addr = "98:D3:31:F5:9A:0D"
port = 1

# Intento conectar
print("Conectando...")

try:
    # Intento conectar al MAC y puerto especificados arriba
    sock = bluetooth.BluetoothSocket( bluetooth.RFCOMM )
    sock.connect((bd_addr, port))
    print("Conectado!")
    # Si logra conectar, envio mensaje al Arduino para que empiece a leer RFID
    data = "y"
    sock.send(data)
    close_bt = False
    # Un loop infinito, para que siga leyendo datos
    while not close_bt:
        print("Esperando credenciales...")
        # El primer recv solo devolvia el primer char por algun motivo,
        # haciendo una concatenacion con un segundo recv se arregla
        data = sock.recv(1024)
        data += sock.recv(1024)
        tagId = data.decode("utf-8") 
        print("Mando tarjeta: " + tagId)
        print("Esperando PIN")
        data = sock.recv(1024)
        data += sock.recv(1024)
        tagPin = data.decode("utf-8") 
        print("Mando PIN: " + tagPin)

        # Obtengo el ID del usuario dueño de ese tag

        query = ("SELECT * FROM usuarios "
         "WHERE tag_id = %s")
        cursor.execute(query, (tagId,))


        if cursor.rowcount != 0:
            result_set = cursor.fetchall()
            for row in result_set:
                id_user = row[0]
        else:
            id_user = -1    # No existe un usuario con ese tag

        # Valido si los datos son correctos
        
        query = ("SELECT * FROM usuarios "
         "WHERE tag_id = %s AND tag_clave = %s")
        cursor.execute(query, (tagId, tagPin))

        timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        
        # Si no devuelve nada, no existe
        if cursor.rowcount == 0:
            sock.send('d')
            # Inserto en la DB
            query = ("INSERT INTO log_accesos (pudo_ingresar, id_usuario)"
                "VALUES (0, '%s')")
            cursor.execute(query, (id_user,))
            cnx.commit()

        # Existe, login correcto
        else:
            sock.send('g')
            # Inserto en la DB
            query = ("INSERT INTO log_accesos (pudo_ingresar, id_usuario)"
                "VALUES (1, '%s')")
            cursor.execute(query, (id_user,))
            cnx.commit()
        #if dataString == "e":
        #    print("Apagar")
        #    close_bt = True
        

    sock.close()
    cursor.close()
    cnx.close()
except BluetoothError as e:
    print('No pudo conectarse')
    cursor.close()
    cnx.close()
