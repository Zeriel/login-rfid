# Ejemplo de busqueda de dispositivos Bluetooth cercanos, provisto por la documentacion de pyBluez.
# Se muestran el numero de MAC y nombre de todos los dispositivos disponibles detectados

# Se utiliza solamente la libreria de pyBluez

import bluetooth

print("performing inquiry...")

nearby_devices = bluetooth.discover_devices(
        duration=8, lookup_names=True, flush_cache=True, lookup_class=False)

print("found %d devices" % len(nearby_devices))

for addr, name in nearby_devices:
    try:
        print("  %s - %s" % (addr, name))
    except UnicodeEncodeError:
        print("  %s - %s" % (addr, name.encode('utf-8', 'replace')))