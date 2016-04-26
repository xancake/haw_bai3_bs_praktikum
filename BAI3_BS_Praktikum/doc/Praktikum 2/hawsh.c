#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int startsWith(const char *str, const char *pre) {
	int lenpre = strlen(pre);
	int lenstr = strlen(str);
	return lenstr < lenpre ? 0 : strncmp(pre, str, lenpre) == 0;
}

int main () {
    char currentPath[1024];
    
    char username[100];
    getlogin_r(username, sizeof(username));
    
    int maxCommandLength = 1024;
    char command[maxCommandLength];
    
    bool running = true;
    
    while(running) {
	// Aktuelles Verzeichnis in "currentPath" schreiben
	getcwd(currentPath, sizeof(currentPath));
	
	printf("%s - Was willst du, %s: ", currentPath, username);
	
	fgets(command, maxCommandLength, stdin);		// Eingabe Lesen
	command[strlen(command)-1] = '\0';			// Zeilenumbruch entfernen
	
	if(strcmp("quit", command) == 0) {
	    running = false;
	} else if(strcmp("version", command) == 0) {
	    printf("HAW-Shell Version 0.1 - Lars Nielsen, Robert Scheffel");
	} else if(strcmp("help", command) == 0) {
	    char helpmsg[1000];
	    strcpy(helpmsg, "HAW-Shell Build-in Befehle\n");
	    strcat(helpmsg, "quit\tBeendet die HAW-Shell\n");
	    strcat(helpmsg, "version\tGibt die Version und Autoren der HAW-Shell aus\n");
	    strcat(helpmsg, "help\tGibt diese Hilfe aus\n");
	    strcat(helpmsg, "/[pfad]\tWechselt in das angegebene Verzeichnis");
	    printf("%s", helpmsg);
	} else if(startsWith(command, "/")) {
	    if(chdir(command) == 0) {
		printf("Wechsel zu Verzeichnis: %s", command);
		
	    } else {
		printf("Der angegebene Pfad existiert nicht!");
	    }
	} else {
	    int waitForChild = command[strlen(command)-1] != '&';
	    if(!waitForChild) {
		command[strlen(command)-1] = '\0';
	    }
	    // Erzeugung des Kindprozess.
	    int pid = fork();
	    if(pid < 0) {
		printf("Es konnte nicht geforked werden!\n");
	    } else if(pid > 0) {
		if(waitForChild) {
		    printf("Warte auf Kindprozess (%i)\n", pid);
		    int status;
		    // Warten auf Kindprozess
		    waitpid(pid, &status, 0);
		}
	    } else {
		// execlp ersetzt bei erfolgreicher Ausführung das aktuelle Programm im Kindprozess.
		// Deswegen braucht bei Erfolg die Schleife nicht beendet werden (running = 0).
		// Im Fehlerfall muss jedoch die Schleife manuell beendet werden. 
		execlp(command, command, NULL);
		printf("Fehler beim Ausführen des Befehls '%s'!\n", command);
		running = false;
		}
	    }
	}
	printf("\n");
    }
    return 0;
}
