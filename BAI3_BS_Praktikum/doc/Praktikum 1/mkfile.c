#include <stdio.h>
#include <string.h>

int main () {
	// Einlesen des Dateinamens
	printf("Bitte geben Sie den Dateinamen an: ");
	char name[30];
	fgets(name, 30, stdin);		// Eingabe Lesen
	name[strlen(name)-1] = '\0';	// Zeilenumbruch entfernen
	printf("Name der neuen Datei: %s\n", name);
	
	// Anlegen der Datei
	int file = creat(name, 700);
	if(file == -1) {
		printf("Fehler beim Anlegen der Datei!\n");
		return 1;
	} else {
		printf("Die Datei %s wurde erfolgreich angelegt!\n", name);
		return 0;
	}
}
