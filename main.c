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

//Funktion zum einlesen eines Studenten(daten), und anschließendes erstellen eines Studenten, bzw. hinzufügen in die Liste
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

//Funktion zum zählen aller Studenten
int countStudents(Student* first) {
    int count = 0;
    Student* current = first;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

//funktion zum ausgeben eines Studenten, mittels matrikelnummer
void printStudent(Student* first) {
    int matrikelnummer;
    printf("Matrikelnummer: ");
    scanf("%d", &matrikelnummer);

    Student* current = first;
    while (current != NULL) {
        if (current->matrikelnummer == matrikelnummer) {
            printf("+------------+------------+-------------+--------------+------------+------------+------------+\n");
            printf("| Vorname    | Nachname   | Studiengang | Matrikelnr.  | Geburtsdat. | Startdat.  | Enddat.    |\n");
            printf("+------------+------------+-------------+--------------+------------+------------+------------+\n");

            printf("| %-10s | %-10s | %-11s | %-12d | %02d.%02d.%4d | %02d.%02d.%4d | %02d.%02d.%4d |\n",
                current->vorname,
                current->nachname,
                current->studiengang,
                current->matrikelnummer,
                current->geburtsdatum.tag, current->geburtsdatum.monat, current->geburtsdatum.jahr,
                current->studienbeginn.tag, current->studienbeginn.monat, current->studienbeginn.jahr,
                current->studienende.tag, current->studienende.monat, current->studienende.jahr);

            printf("+------------+------------+-------------+--------------+------------+------------+------------+\n");
            return;
        }
        current = current->next;
    }
    printf("Student mit Matrikelnummer %d wurde nicht gefunden.\n", matrikelnummer);

}

// Funktion zum auflisten aller Studenten, in "tabellenform"
void printAllStudents(Student* first) {
    Student* current = first;

    // Tabellenkopf ausgeben
    printf("+------------+------------+-------------+--------------+------------+------------+------------+\n");
    printf("| Vorname    | Nachname   | Studiengang | Matrikelnr.  | Geburtsdat. | Startdat.  | Enddat.    |\n");
    printf("+------------+------------+-------------+--------------+------------+------------+------------+\n");

    // Alle Studenten ausgeben, also spaltenweise
    while (current != NULL) {
        printf("| %-10s | %-10s | %-11s | %-12d | %02d.%02d.%4d | %02d.%02d.%4d | %02d.%02d.%4d |\n",
               current->vorname,
               current->nachname,
               current->studiengang,
               current->matrikelnummer,
               current->geburtsdatum.tag, current->geburtsdatum.monat, current->geburtsdatum.jahr,
               current->studienbeginn.tag, current->studienbeginn.monat, current->studienbeginn.jahr,
               current->studienende.tag, current->studienende.monat, current->studienende.jahr);

        current = current->next;
    }

    // Tabellenfuß ausgeben
    printf("+------------+------------+-------------+--------------+------------+------------+Eintraege:%d+\n", countStudents(first));
}

// Funktion zum löschen eines Studenten, mittels matrikelnummer
void deleteStudent(Student** first) {
    int matrikelnummer;
    printf("Matrikelnummer: ");
    scanf("%d", &matrikelnummer);

    //nochmalsfrage zur sicherheit
    char check;
    printf("Sind Sie sicher, dass Sie den Studenten mit der Matrikelnummer %d löschen möchten? (j/n)\n", matrikelnummer);
    scanf(" %c", &check);
    if (check != 'j') {
        printf("Löschen abgebrochen.\n");
        return;
    }

    Student* current = *first;
    Student* previous = NULL;

    while (current != NULL) {
        if (current->matrikelnummer == matrikelnummer) {
            if (previous == NULL) {
                *first = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            printf("Student mit Matrikelnummer %d wurde gelöscht.\n", matrikelnummer);
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("Student mit Matrikelnummer %d wurde nicht gefunden.\n", matrikelnummer);
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
        printf("1: Student hinzufuegen\n2: Studenten Suche(Matrikelnummer)\n3: Studenten entfernen(Matrikelnummer)\n4: Alle Studenten anzeigen\n5: Anzahl aller Studierenden\n6: Programm beenden\n");
        int auswahl;
        scanf("%d", &auswahl);
        switch (auswahl) {
            case 1:
                addStudent(&first, &last);
            break;
            case 2:
                printStudent(first);
            break;
            case 3:
                deleteStudent(&first);
            break;
            case 4:
                printAllStudents(first);
            break;
            case 5:
                printf("Anzahl aller Studierenden: %d\n", countStudents(first));
            break;
            case 6:
                save_to_file(first);
                return 0;

            default:
                printf("Ungültige Eingabe\n");
        }
    }
}

