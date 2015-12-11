# Explication
le script Horaire.sh doit etre idealement executé toute les min par un cron.
Il doit etre customisé suivant l'arret désiré (dans mon cas c'est le bus187 a destination de Porte Orleans).
Je n'ai pas mis de variable "path", attention aux chemins si vous faites un cron.

Parser.py est a customiser aussi suivant la ligne de bus désirée et la station d'arret:
http://wap.ratp.fr/siv/schedule?service=next&reseau=bus&referer=station&lineid=B187&stationname=mairie+de+cachan&submitAction=Valider'


