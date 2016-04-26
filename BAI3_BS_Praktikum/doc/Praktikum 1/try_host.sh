

# Gibt die Hilfe zu dem Programm aus.
usage() {
  echo "$0 [OPTIONS] [<HOST>|<IP>]
  Pingt fortlaufend einen Rechner und gibt dabei aus, ob dieser erreichbar ist.
  Wird kein kein Host/IP angegeben, wird der Benutzer danach gefragt.
  
  OPTIONS:
  	-h:	Anzeigen dieser Hilfe
  	-s <sec>: Legt fest, in welchem Intervall gepingt werden soll
  "
}

# Fragt den Benutzer, welcher host gepingt werden soll.
ask_for_host() {
  echo "Bitte geben sie den Host an: "
  read host
}

# Parameter Prüfen
if [ $# -ne 0 -a $# -ne 1 -a $# -ne 3 ]; then
  usage
  exit 1
fi

# Ermitteln der Parameter
sec=10
case $1 in
  "-h")
    usage
    exit 0
    ;;
  "-s")
    if [ $# -eq 3 ]; then
      sec=$2
      host=$3
    else
      usage
      exit 1
    fi
    ;;
  "")
    ask_for_host
    ;;
  *)
    host=$1
esac

# Ausführen des Befehls
while true
do
  ping -c 1 $host >/dev/null
  if [ $? -eq 0 ]; then
    echo "$host OK"
  else
    echo "$host FAILED"
  fi
  sleep $sec
done
