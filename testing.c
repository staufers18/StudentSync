//Diese Datei ist zum Testen verschiedenster Sachen, aktuell testen von Schreiben und Lesen einer TXT Datei von staufers18

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

typedef struct date{
    int day;
    int month;
    int year;
  } date;

struct Student{
    char firstname[50];
    char lastname[50];
    char degreeProgram[100];
    int matrikelnumber;
    date startdate;
    date enddate;
    date birthdate;
  };

char new_firstname[50];
char new_lastname[50]; 
char new_degreeProgram[100]; 
int new_matrikelnumber; 
date new_startdate;
date new_enddate;
date new_birthdate;

char start_buffer[11];
char end_buffer[11];
char birth_buffer[11];

int main() {
    printf("Vorname:    "); fgets(new_firstname, sizeof(new_firstname), stdin); new_firstname[strcspn(new_firstname, "\n")] = 0;
    printf("Nachname:    "); fgets(new_lastname, sizeof(new_firstname), stdin); new_lastname[strcspn(new_lastname, "\n")] = 0;
    printf("Studiengang:    "); fgets(new_degreeProgram, sizeof(new_firstname), stdin); new_degreeProgram[strcspn(new_degreeProgram, "\n")] = 0;
    printf("Matrikelnummer:    "); scanf("%i",&new_matrikelnumber);
    
    printf("Startdatum (dd.mm.yyyy):    "); 
    if (fgets(start_buffer, sizeof(start_buffer), stdin) != NULL) {
      sscanf(start_buffer, "%2d.%2d.%4d", &new_startdate.day, &new_startdate.month, &new_startdate.year);
    } else { 
      printf("Fehler beim Lesen der Eingabe\n"); 
    }

    printf("Enddatum (dd.mm.yyyy):    "); 
    if (fgets(end_buffer, sizeof(end_buffer), stdin) != NULL) {
      sscanf(end_buffer, "%2d.%2d.%4d", &new_enddate.day, &new_enddate.month, &new_enddate.year);
    }  else { 
      printf("Fehler beim Lesen der Eingabe\n"); 
    } 

    printf("Enddatum (dd.mm.yyyy):    "); 
    if (fgets(birth_buffer, sizeof(birth_buffer), stdin) != NULL) {
      sscanf(birth_buffer, "%2d.%2d.%4d", &new_birthdate.day, &new_birthdate.month, &new_birthdate.year);
    }  else { 
      printf("Fehler beim Lesen der Eingabe\n"); 
    } 
    
    printf("\nIhre Eingabe: %s, %s  (%i)  geb. %02i.%02i.%04i studiert von %02i.%02i.%04i bis %02i.%02i.%04i %s\n",new_lastname,new_firstname,new_matrikelnumber,new_birthdate.day,new_birthdate.month, new_birthdate.year, new_startdate.day, new_startdate.month, new_startdate.year, new_enddate.day, new_enddate.month, new_enddate.year, new_degreeProgram);

    FILE *filePointer;

    filePointer = fopen("students.txt", "w");

    if (filePointer == NULL) {
        printf("Die Datei konnte nicht geöffnet werden.\n");
        return 1;
    }

    fprintf(filePointer, "%i    ",new_matrikelnumber);
    fprintf(filePointer, "%s    ",new_lastname);
    fprintf(filePointer, "%s    ",new_firstname);
    fprintf(filePointer, "%s    ",new_degreeProgram);
    fprintf(filePointer, "%02i.%02i.%04i    ",new_startdate.day, new_startdate.month, new_startdate.year);
    fprintf(filePointer, "%02i.%02i.%04i    ",new_enddate.day, new_enddate.month, new_enddate.year);
    fprintf(filePointer, "%02i.%02i.%04i    ",new_birthdate.day, new_birthdate.month, new_birthdate.year);

    fclose(filePointer);

    printf("Daten erfolgreich in die Datei geschrieben.\n");
    return 0;
}