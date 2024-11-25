//Diese Datei ist zum Testen verschiedenster Sachen, aktuell testen von Schreiben und Lesen einer TXT Datei von staufers18

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

typedef struct Date{
    int year,month,day;
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

int main() {
    printf("Vorname:    "); scanf("%s",&new_firstname[50]);
    printf("Nachname:    "); scanf("%s",&new_lastname[50]);
    printf("Studiengang:    "); scanf("%s",&new_degreeProgram[100]);
    printf("Matrikelnummer:    "); scanf("%i",&new_matrikelnumber);
    printf("Startdatum (dd,mm,yyyy):    "); scanf("%2i,%2i,%4i", &new_startdate.day, &new_startdate.month, &new_startdate.year);
    printf("Enddatum (dd,mm,yyyy):    "); scanf("%2i,%2i,%4i", &new_enddate.day, &new_enddate.month, &new_enddate.year);
    printf("Geburtstag (dd,mm,yyyy):    "); scanf("%2i,%2i,%4i", &new_birthdate.day, &new_birthdate.month, &new_birthdate.year);
    
    struct Student new;
    for(int index = 0; index < 50; index++){
        new.firstname[index] = new_firstname[index];
        new.lastname[index] = new_lastname[index];
        new.degreeProgram[index] = new_degreeProgram[index];
    }
    new.matrikelnumber = new_matrikelnumber;
    new.startdate = new_startdate;
    new.enddate = new_enddate;
    new.birthdate = new_birthdate;

    FILE *filePointer;

    filePointer = fopen("students.txt", "w");
    if (filePointer == NULL) {
        printf("Die Datei konnte nicht geöffnet werden.\n");
        return 1;
    }

    fprintf(filePointer, "%i    ",new.matrikelnumber);
    fprintf(filePointer, "%s    ",new.lastname);
    fprintf(filePointer, "%s    ",new.firstname);
    fprintf(filePointer, "%s    ",new.degreeProgram);
    fprintf(filePointer, "%2i.%2i.%4i    ",new.startdate.day, new.startdate.month, new.startdate.year);
    fprintf(filePointer, "%2i.%2i.%4i    ",new.enddate.day, new.enddate.month, new.enddate.year);
    fprintf(filePointer, "%2i.%2i.%4i    ",new.birthdate.day, new.birthdate.month, new.birthdate.year);

    fclose(filePointer);

    printf("Daten erfolgreich in die Datei geschrieben.\n");
    return 0;
}