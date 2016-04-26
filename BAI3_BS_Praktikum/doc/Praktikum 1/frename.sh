

# Gibt die Hilfe zu dem Programm aus.
usage() {
  echo "$0 [OPTIONS] [<STRING>]
  Hängt an alle Dateien im aktuellen Verzeichnis die Zeichenkette an den Dateinamen.
  
  OPTIONS:
  	-h:	Anzeigen dieser Hilfe
  "
}

# Fragt den Benutzer, welcher String den Dateinamen angehängt werden soll.
ask_for_string() {
  echo "Bitte geben Sie die Zeichenkette an, die allen Dateinamen im aktuellen Verzeichnis angehängt werden soll: "
  read theString
}

# Parameter Prüfen
if [ $# -gt 1 ]; then
  usage
  exit 1
fi

# Ermitteln der Parameter
case $1 in
  "-h")
    usage
    exit 0
    ;;
  "")
    ask_for_string
    ;;
  *)
    theString=$1
esac

# Für alle Namen aus der Ausgabe von "ls" benenne die Dateien um
for name in $(ls)
do
  mv $name $name$theString
done

