//Diese Datei ist zum Testen verschiedenster Sachen, aktuell testen von Schreiben und Lesen einer TXT Datei von staufers18

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

struct date{
    int year,month,day;
  };

struct Student{
    char firstname[50];
    char lastname[50];
    char degreeProgram[100];
    int matrikelnumber;
    struct date startdate;
    struct date enddate;
    struct date birthdate;
  };

char new_firstname[50];
char new_lastname[50]; 
char new_degreeProgram[100]; 
int new_matrikelnumber; 
struct date new_startdate;
struct date new_enddate;
struct date new_birthdate;

int main() {
    printf("Vorname:    "); fgets(new_firstname, sizeof(new_firstname), stdin); new_firstname[strcspn(new_firstname, "\n")] = 0;
    printf("Nachname:    "); fgets(new_lastname, sizeof(new_firstname), stdin); new_lastname[strcspn(new_lastname, "\n")] = 0;
    printf("Studiengang:    "); fgets(new_degreeProgram, sizeof(new_firstname), stdin); new_degreeProgram[strcspn(new_degreeProgram, "\n")] = 0;
    printf("Matrikelnummer:    "); scanf("%i",&new_matrikelnumber);
    printf("Startdatum (dd.mm.yyyy):    "); scanf("%i.%i.%i", &new_startdate.day, &new_startdate.month, &new_startdate.year);
    printf("Enddatum (dd.mm.yyyy):    "); scanf("%i.%i.%i", &new_enddate.day, &new_enddate.month, &new_enddate.year);
    printf("Geburtstag (dd.mm.yyyy):    "); scanf("%i.%i.%i", &new_birthdate.day, &new_birthdate.month, &new_birthdate.year);
    printf("\nIhre Eingabe: %s, %s  (%i)  geb. %i.%i.%i studiert von %i.%i.%i bis %i.%i.%i %s\n",new_lastname,new_firstname,new_matrikelnumber,new_birthdate.day,new_birthdate.month, new_birthdate.year, new_startdate.day, new_startdate.month, new_startdate.year, new_enddate.day, new_enddate.month, new_enddate.year, new_degreeProgram);

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
    fprintf(filePointer, "%i.%i.%i    ",new_startdate.day, new_startdate.month, new_startdate.year);
    fprintf(filePointer, "%i.%i.%i    ",new_enddate.day, new_enddate.month, new_enddate.year);
    fprintf(filePointer, "%i.%i.%i    ",new_birthdate.day, new_birthdate.month, new_birthdate.year);

    fclose(filePointer);

    printf("Daten erfolgreich in die Datei geschrieben.\n");
    return 0;
}