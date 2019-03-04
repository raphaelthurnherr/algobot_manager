#!/bin/bash
# Indique au système que l'argument qui suit est le programme utilisé pour exécuter ce fichier
# En règle générale, les "#" servent à mettre en commentaire le texte qui suit comme ici

#CREATION D UN NOUVEAU BUILDNUMBER DANS LE FICHIER HEADER
number=$(cut buildNumber.h -c 20-)
newHeader='#define BUILD_CODE '$((number+1))
echo $newHeader > buildNumber.h
echo Build code: \# $((number))  
        
md5sum /home/raph-pnp/Documents/dev/embedded_soft/kehopsManager/dist/Debug/GNU_Omega-Linux/kehopsmanager | cut -c -32 > /home/raph-pnp/Documents/dev/embedded_soft/kehopsManager/dist/Debug/GNU_Omega-Linux/kehopsmanager.md5
echo "Creation fichier MD5..." `cat kehopsmanager.md5`

echo "KEHOPS Manager: Transfere du fichier binaire..."
#rsync -a /home/raph-pnp/Documents/dev/embedded_soft/kehopsManager/dist/Debug/GNU_Omega-Linux/kehopsmanager  root@192.168.3.1:~/
rsync -a /home/raph-pnp/Documents/dev/embedded_soft/kehopsManager/dist/Debug/GNU_Omega-Linux/kehopsmanager  root@192.168.3.1:~/

echo "KEHOPS Manager: Transfere du fichier MD5..."
#rsync -a /home/raph-pnp/Documents/dev/embedded_soft/kehopsManager/dist/Debug/GNU_Omega-Linux/kehopsmanager.md5  root@192.168.3.1:~/

echo "Lancement de l'application Manager via SSH...\n"
#sshpass -p onioneer ssh root@192.168.3.1 "~./kehopsmanager"
 
echo "Fermeture du tunnel SSH"

exit
