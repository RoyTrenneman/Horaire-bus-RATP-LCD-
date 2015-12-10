#!/bin/bash

none=$(/home/pi/rer_bus/horaire.py |  awk -F"Orleans" '{print $2 }' | grep -i interrompu ) ##Serice non assuré
min=$(/home/pi/rer_bus/horaire.py |  awk -F"Prochains" '{print $2 }' |  awk -F"," '{print $24}' | sed 's/^[ \t]*//;s/[ \t]*$//'| sed s/\"//g | sed s/\'//g | grep -o "^[0-9]\+") 
arret=$(/home/pi/rer_bus/horaire.py |  awk -F"Prochains" '{print $2 }' |  awk -F"," '{print $24}' | sed 's/^[ \t]*//;s/[ \t]*$//'| sed s/\"//g | sed s/\'//g | grep -i arret )
approche=$(/home/pi/rer_bus/horaire.py |  awk -F"Prochains" '{print $2 }' |  awk -F"," '{print $24}' | sed 's/^[ \t]*//;s/[ \t]*$//'| sed s/\"//g | sed s/\'//g |grep -i approche )
if [ -n "$arret"  ]
then
v='200'
elif [ -n "$approche" ]
then
v='201'
elif [ -n "$none" ]
then
v='202'
else
v=$min
fi
if [ "$v" = "" ]
then
exit
else
echo "$v" > /home/pi/Meteo/187.txt
fi
