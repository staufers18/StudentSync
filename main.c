#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct {
    int tag;
    int monat;
    int jahr;
} Datum;

typedef struct Student {
    char vorname[51];
    char nachname[51];
    char studiengang[51];
    int matrikelnummer;
    Datum geburtsdatum, studienbeginn, studienende;
    struct Student* next;
} Student;

//validierungs Funktionen
bool validiereName(const char* name) {
    if (strlen(name) < 1 || strlen(name) > 50) return false;
    for (int i = 0; i < strlen(name); i++) {
        if (!isalpha(name[i])) return false;
    }
    return true;
}
bool validiereDatum(Datum d) {
    if (d.jahr < 1900 || d.jahr > 2100) return false;   //jahr muss zwischen 1900 und 2100 liegen
    if (d.monat < 1 || d.monat > 12) return false;     //monat muss zwischen 1 und 12 liegen
    if (d.tag < 1 || d.tag > 31) return false;          //tag muss zwischen 1 und 31 liegen
    if ((d.monat == 4 || d.monat == 6 || d.monat == 9 || d.monat == 11) && d.tag > 30) return false;    //monate mit 30 tagen
    if (d.monat == 2) {
        bool schaltjahr = (d.jahr % 4 == 0 && d.jahr % 100 != 0) || (d.jahr % 400 == 0);
        if (schaltjahr && d.tag > 29) return false;
        if (!schaltjahr && d.tag > 28) return false;
    }
    if (d.jahr + 18 < 2024) return true;    //muss mindestens 18 jahre alt sein
    return true;
}
bool matrikelnummerEinzigartig(Student *first, int matrikelnummer) {
    Student* current = first;
    while (current != NULL) {
        if (current->matrikelnummer == matrikelnummer) return false;
        current = current->next;
    }
    return true;
}

// Funktion dient zum erstellen eines neuen Studenten und gibt einen Pointer auf den erstellten Studenten zurück
Student* create_Student(char* vorname, char* nachname, char* studiengang, int matrikelnummer, Datum geburtsdatum, Datum studienbeginn, Datum studienende) {
    Student* student = malloc(sizeof(Student));
    if (student == NULL) {
        printf("Speicher konnte nicht allokiert werden\n");
        return NULL;
    }

    strcpy(student->vorname, vorname);
    strcpy(student->nachname, nachname);
    strcpy(student->studiengang, studiengang);
    student->matrikelnummer = matrikelnummer;
    student->geburtsdatum = geburtsdatum;
    student->studienbeginn = studienbeginn;
    student->studienende = studienende;
    student->next = NULL;
    return student;
}

//Funktion zum einlesen eines Studenten, und ansdchließendes erstellen eines Studenten
Student* inputStudent(Student* first) {
    char vorname[51], nachname[51], studiengang[51];
    int matrikelnummer;
    Datum geburtsdatum, studienbeginn, studienende;

    // Vorname validieren
    do {
        printf("Vorname: ");
        scanf("%50s", vorname);
        if (!validiereName(vorname)) {
            printf("Ungültiger Vorname. Bitte nur Buchstaben verwenden (max. 50 Zeichen).\n");
        }
    } while (!validiereName(vorname));

    //Nachname validieren
    do {
        printf("Nachname: ");
        scanf("%50s", nachname);
        if (!validiereName(nachname)) {
            printf("Ungültiger Nachname. Bitte nur Buchstaben verwenden (max. 50 Zeichen).\n");
        }
    } while (!validiereName(nachname));

    // Studiengang validieren (keine zusätzliche Validierung)
    printf("Studiengang: ");
    scanf("%50s", studiengang);

    // Matrikelnummer validieren
    do {
        printf("Matrikelnummer: ");
        scanf("%d", &matrikelnummer);
        if (!matrikelnummerEinzigartig(first, matrikelnummer)) {
            printf("Matrikelnummer existiert bereits. Bitte eine andere Nummer eingeben.\n");
        }
    } while (!matrikelnummerEinzigartig(first, matrikelnummer));

    // Geburtsdatum validieren
    do {
        printf("Geburtsdatum (dd.mm.jjjj): ");
        scanf("%d.%d.%d", &geburtsdatum.tag, &geburtsdatum.monat, &geburtsdatum.jahr);
        if (!validiereDatum(geburtsdatum)) {
            printf("Ungültiges Geburtsdatum. Bitte erneut eingeben.\n");
        }
    } while (!validiereDatum(geburtsdatum));

    // Studienbeginn validieren
    do {
        printf("Studienbeginn (dd.mm.jjjj): ");
        scanf("%d.%d.%d", &studienbeginn.tag, &studienbeginn.monat, &studienbeginn.jahr);
        if (!validiereDatum(studienbeginn)) {
            printf("Ungültiges Startdatum. Bitte erneut eingeben.\n");
        }
    } while (!validiereDatum(studienbeginn));

    // Studienende validieren
    do {
        printf("Studienende (dd.mm.jjjj): ");
        scanf("%d.%d.%d", &studienende.tag, &studienende.monat, &studienende.jahr);
        if (!validiereDatum(studienende)) {
            printf("Ungültiges Enddatum. Bitte erneut eingeben.\n");
        }
    } while (!validiereDatum(studienende));

    return create_Student(vorname, nachname, studiengang, matrikelnummer, geburtsdatum, studienbeginn, studienende);
}
void addStudent(Student** first, Student** last) {
    Student* newStudent = inputStudent(*first);

    if (newStudent == NULL) {
        printf("Fehler beim Erstellen des Studenten.\n");
        return;
    }

    if (*first == NULL) {
        *first = newStudent;
        *last = newStudent;
    } else {
        (*last)->next = newStudent;
        *last = newStudent;
    }

    printf("Student erfolgreich hinzugefügt.\n");
}



// Funktion zum auflisten aller Studenten
void printAllStudents(Student* first) {
    Student* current = first;
    while (current != NULL) {
        printf("Vorname: %s\nNachname: %s\nStudiengang: %s\nMatrikelnummer: %i\nGeburtsdatum: %i.%i.%i\nStudienbeginn: %i.%i.%i\nStudienende: %i.%i.%i\n\n", current->vorname, current->nachname, current->studiengang, current->matrikelnummer, current->geburtsdatum.tag, current->geburtsdatum.monat, current->geburtsdatum.jahr, current->studienbeginn.tag, current->studienbeginn.monat, current->studienbeginn.jahr, current->studienende.tag, current->studienende.monat, current->studienende.jahr);
        current = current->next;
    }
}


//Funktionen zum einlesen und speichern von Studenten
Student* read_from_file(void) {
    FILE *savefile = fopen("students.csv", "r");
    if (savefile == NULL) {
        printf("Datei konnte nicht geöffnet werden\n");
        return NULL;
    }

    Student* first = NULL;
    Student* last = NULL;
    char puffer[256];

    while (fgets(puffer, sizeof(puffer), savefile)) {
        char vorname[51], nachname[51], studiengang[51];
        int matrikelnummer, geburtsdatum_tag, geburtsdatum_monat, geburtsdatum_jahr;
        int studienbeginn_tag, studienbeginn_monat, studienbeginn_jahr;
        int studienende_tag, studienende_monat, studienende_jahr;

        if (sscanf(puffer, "%50[^,],%50[^,],%50[^,],%d,%d.%d.%d,%d.%d.%d,%d.%d.%d",
           vorname, nachname, studiengang, &matrikelnummer,
           &geburtsdatum_tag, &geburtsdatum_monat, &geburtsdatum_jahr,
           &studienbeginn_tag, &studienbeginn_monat, &studienbeginn_jahr,
           &studienende_tag, &studienende_monat, &studienende_jahr) == 13) {

            Student* student = create_Student(vorname, nachname, studiengang, matrikelnummer,
                                              (Datum) {geburtsdatum_tag, geburtsdatum_monat, geburtsdatum_jahr},
                                              (Datum) {studienbeginn_tag, studienbeginn_monat, studienbeginn_jahr},
                                              (Datum) {studienende_tag, studienende_monat, studienende_jahr});

            if (first == NULL) {
                first = student;
                last = student;
            } else {
                last->next = student;
                last = student;
            }
           } else {
               printf("Folgende Zeile ist eventuell falsch formatiert: %s\n", puffer);
           }
    }

    fclose(savefile); // Datei schließen
    printf("Studenten wurden erfolgreich geladen.\n");
    return first;
}

void save_to_file(Student *first) {
    FILE* savefile = fopen("students.csv", "w");
    if (savefile == NULL) {
        printf("Datei konnte nicht geöffnet werden\n");
        return;
    }

    Student* current = first;
    while (current != NULL) {
        fprintf(savefile, "%s,%s,%s,%d,%d.%d.%d,%d.%d.%d,%d.%d.%d\n",
            current->vorname, current->nachname, current->studiengang, current->matrikelnummer,
            current->geburtsdatum.tag, current->geburtsdatum.monat, current->geburtsdatum.jahr,
            current->studienbeginn.tag, current->studienbeginn.monat, current->studienbeginn.jahr,
            current->studienende.tag, current->studienende.monat, current->studienende.jahr);
        current = current->next;
    }

    fclose(savefile); // Datei schließen
    printf("Studenten wurden erfolgreich gespeichert.\n");
}



int main() {
    Student* first = read_from_file();
    Student* last = first;

    // Finde das letzte Element der Liste nach dem Laden aus der Datei
    while (last && last->next != NULL) {
        last = last->next;
    }

    while (true) {
        printf("1: Student hinzufügen\n2: Alle Studenten anzeigen\n3: Programm beenden\n");
        int auswahl;
        scanf("%d", &auswahl);
        switch (auswahl) {
            case 1:
                addStudent(&first, &last);
            break;
            case 2:
                printAllStudents(first);
            break;
            case 3:
                save_to_file(first);
            return 0;
            default:
                printf("Ungültige Eingabe\n");
        }
    }
}

