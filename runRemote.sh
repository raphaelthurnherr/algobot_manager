#!/bin/bash
# Indique au système que l'argument qui suit est le programme utilisé pour exécuter ce fichier
# En règle générale, les "#" servent à mettre en commentaire le texte qui suit comme ici


md5sum /home/raph-pnp/NetBeansProjects/algobotManager/dist/Debug/GNU_Omega-Linux/algobotmanager | cut -c -32 > /home/raph-pnp/NetBeansProjects/algobotManager/dist/Debug/GNU_Omega-Linux/algobotmanager.md5
echo "Creation fichier MD5..." `cat algobotmanager.md5`

echo "Algobot Manager: Transfere du fichier binaire..."
#rsync -a /home/raph/NetBeansProjects/algobot_onionOmega/dist/Debug/GNU_Omega-Linux/algobot_onionomega  root@192.168.3.1:~/algobot
rsync -a /home/raph-pnp/NetBeansProjects/algobotManager/dist/Debug/GNU_Omega-Linux/algobotmanager  root@192.168.3.1:~/

echo "Algobot Manager: Transfere du fichier MD5..."
rsync -a /home/raph-pnp/NetBeansProjects/algobotManager/dist/Debug/GNU_Omega-Linux/algobotmanager.md5  root@192.168.3.1:~/

echo "Lancement de l'application Manager via SSH...\n"
#sshpass -p onioneer ssh root@192.168.3.1 "~/algobot/./algobot_onionomega"
 
echo "Fermeture du tunnel SSH"

exit
