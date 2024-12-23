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

typedef struct {
    char vorname[51];
    char nachname[51];
    char studiengang[51];
    int matrikelnummer;
    Datum geburtsdatum, studienbeginn, studienende;
    struct Student* next;
} Student;

void clear_input(void){while ( getchar() != '\n' );} //funktion zum leeren des input buffers, da es sonst zu fehler kommen kann bei falscher eingabe(loop)

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
    if (d.jahr + 18 > 2024) return false;    //muss mindestens 18 jahre alt sein
    return true;
}
bool matrikelnummerEinzigartig(Student *first, int matrikelnummer) {
    Student* current = first;

    if (matrikelnummer < 10000000 || matrikelnummer > 99999999) return false; //matrikelnummer muss 8 stellig sein
    while (current != NULL) {
        if (current->matrikelnummer == matrikelnummer) return false;
        current = current->next;
    }

    return true;
}
bool datumsVergleich(Datum d1, Datum d2) {
    if (d1.jahr < d2.jahr) return true;
    if (d1.jahr > d2.jahr) return false;
    if (d1.monat < d2.monat) return true;
    if (d1.monat > d2.monat) return false;
    if (d1.tag < d2.tag) return true;
    return false;
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
        clear_input();
        if (!validiereName(vorname)) {
            printf("Ungueltiger Vorname. Bitte nur Buchstaben verwenden (max. 50 Zeichen).\n");
        }
    } while (!validiereName(vorname));

    //Nachname validieren
    do {
        printf("Nachname: ");
        scanf("%50s", nachname);
        clear_input();
        if (!validiereName(nachname)) {
            printf("Ungueltiger Nachname. Bitte nur Buchstaben verwenden (max. 50 Zeichen).\n");
        }
    } while (!validiereName(nachname));

    // keine zusätzliche Validierung für Studiengang, da dieser auch Zahlen enthalten kann
    printf("Studiengang: ");
    scanf("%50s", studiengang);

    // Matrikelnummer validieren
    do {
        printf("Matrikelnummer: ");
        scanf("%d", &matrikelnummer);
        clear_input();
        if (!matrikelnummerEinzigartig(first, matrikelnummer)) {
            printf("Matrikelnummer existiert bereits, oder ist nicht 8 Zeichen lang. Bitte eine andere Nummer eingeben.\n");
        }
    } while (!matrikelnummerEinzigartig(first, matrikelnummer));

    // Geburtsdatum validieren
    do {
        printf("Geburtsdatum (dd.mm.jjjj): ");
        scanf("%d.%d.%d", &geburtsdatum.tag, &geburtsdatum.monat, &geburtsdatum.jahr);
        clear_input();
        if (!validiereDatum(geburtsdatum)) {
            printf("Ungueltiges Geburtsdatum. Bitte erneut eingeben.\n");
        }
    } while (!validiereDatum(geburtsdatum));

    // Studienbeginn validieren
    do {
        printf("Studienbeginn (dd.mm.jjjj): ");
        scanf("%d.%d.%d", &studienbeginn.tag, &studienbeginn.monat, &studienbeginn.jahr);
        clear_input();

        if (!datumsVergleich(geburtsdatum, studienbeginn)) {
            printf("Studienbeginn muss nach dem Geburtsdatum liegen. Bitte erneut eingeben.\n");
        }
        if (!validiereDatum(studienbeginn)) {
            printf("Ungueltiges Startdatum. Bitte erneut eingeben.\n");
        }
    } while (!validiereDatum(studienbeginn) || !datumsVergleich(geburtsdatum, studienbeginn));

    // Studienende validieren
    do {
        printf("Studienende (dd.mm.jjjj): ");
        scanf("%d.%d.%d", &studienende.tag, &studienende.monat, &studienende.jahr);
        clear_input();
        if (!datumsVergleich(studienbeginn, studienende)) {
            printf("Studienende muss nach dem Studienbeginn liegen. Bitte erneut eingeben.\n");
        }
        if (!validiereDatum(studienende)) {
            printf("Ungueltiges Enddatum. Bitte erneut eingeben.\n");
        }
    } while (!validiereDatum(studienende) || !datumsVergleich(studienbeginn, studienende));

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

    printf("Student erfolgreich hinzugefuegt.\n");
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

// Funktion zum auflisten aller Studenten, in "tabellenform" und alphabetisch nach nachnamen sortiert
void printAllStudents(Student* first) {
    if (first == NULL) {
        printf("Keine Studenten vorhanden.\n");
        return;
    }

    // Kopiere die Liste in ein temporäres Array zur leichteren Sortierung
    int count = countStudents(first);
    Student** array = malloc(count * sizeof(Student*));
    if (!array) {
        printf("Speicherfehler.\n");
        return;
    }
    Student* current = first;
    for (int i = 0; i < count; i++) {
        array[i] = current;
        current = current->next;
    }

    // Bubble Sort nach nachnamen
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcasecmp(array[j]->nachname, array[j + 1]->nachname) > 0) {
                Student* temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }

    // Tabellenkopf ausgeben
    printf("+------------+------------+-------------+--------------+------------+------------+------------+\n");
    printf("| Vorname    | Nachname   | Studiengang | Matrikelnr.  | Geburtsdat. | Startdat.  | Enddat.    |\n");
    printf("+------------+------------+-------------+--------------+------------+------------+------------+\n");

    // Sortierte Studenten ausgeben
    for (int i = 0; i < count; i++) {
        printf("| %-10s | %-10s | %-11s | %-12d | %02d.%02d.%4d | %02d.%02d.%4d | %02d.%02d.%4d |\n",
               array[i]->vorname,
               array[i]->nachname,
               array[i]->studiengang,
               array[i]->matrikelnummer,
               array[i]->geburtsdatum.tag, array[i]->geburtsdatum.monat, array[i]->geburtsdatum.jahr,
               array[i]->studienbeginn.tag, array[i]->studienbeginn.monat, array[i]->studienbeginn.jahr,
               array[i]->studienende.tag, array[i]->studienende.monat, array[i]->studienende.jahr);
    }

    // Tabellenfuß ausgeben
    printf("+------------+------------+-------------+--------------+------------+------------+Eintraege:[%d]\n", count);

    //speicher freigeben von der liste
    free(array);
}
// Funktion zum löschen eines Studenten, mittels matrikelnummer
void deleteStudent(Student** first) {
    int matrikelnummer;
    printf("Matrikelnummer: ");
    scanf("%d", &matrikelnummer);

    //nochmalsfrage zur sicherheit
    char check;
    printf("Sind Sie sicher, dass Sie den Studenten mit der Matrikelnummer %d loeschen moechten? (j/n)\n", matrikelnummer);
    scanf(" %c", &check);
    if (check != 'j') {
        printf("Loeschen abgebrochen.\n");
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
            printf("Student mit Matrikelnummer %d wurde geloescht.\n", matrikelnummer);
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
        FILE *savefile = fopen("students.csv", "w");
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
    return first;
}

void save_to_file(Student *first) {
    FILE* savefile = fopen("students.csv", "w");

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
}



int main() {
    Student* first = read_from_file();
    Student* last = first;

    // Finde das letzte Element der Liste nach dem Laden aus der Datei
    while (last && last->next != NULL) {
        last = last->next;
    }

    printf("+------------+------------+-------------+--------------+------------+------------+------------+\n"
           "|               Willkommen bei StudentSync Ihrem Studentenverwaltungsprogramm                 |\n"
           "+------------+------------+-------------+--------------+------------+------------+------------+\n");

    while (true) {
        printf("\n");
        printf("+------------+------------+-------------+\n");
        printf("|              StudentSync              |\n");
        printf("+------------+------------+-------------+\n");
        printf("| 1 | Student hinzufuegen                |\n");
        printf("| 2 | Studenten suchen (Matrikelnummer) |\n");
        printf("| 3 | Studenten entfernen (Matrikelnummer)|\n");
        printf("| 4 | Alle Studenten anzeigen           |\n");
        printf("| 5 | Anzahl aller Studierenden         |\n");
        printf("| 6 | Programm beenden                  |\n");
        printf("+------------+------------+-------------+\n");
        printf("Bitte waehlen Sie eine Option: ");

        int auswahl;
        scanf("%d", &auswahl);

        // Checkt ob Eingabe ein Zahl zwischen 1 und 6 ist
        if (auswahl < 1 || auswahl > 6) {
            clear_input();
        }

        switch (auswahl) {
            case 1:
                printf("| Student hinzufuegen - Fuegen Sie einen neuen Studenten zur Liste hinzu. |\n");
                addStudent(&first, &last);
            break;
            case 2:
                printf("| Studenten suchen - Finden Sie einen Studenten per Matrikelnummer |\n");
                printStudent(first);
            break;
            case 3:
                printf("| Studenten entfernen - Entfernen Sie einen Studenten per Matrikelnummer |\n");
                deleteStudent(&first);
            break;
            case 4:
                printf("| Tabelle aller hinterlegten Studenten |\n");
                printAllStudents(first);
            break;
            case 5:
                printf("\nAnzahl aller Studierenden: %d\n\n", countStudents(first));
            break;
            case 6:
                save_to_file(first);
                printf(     "+------------+------------+-------------+--------------+------------+------------+------------+\n"
                                "                      Danke fuer die Nutzung von StudentSync. Auf Wiedersehen!                 \n");
                return 0;

            default:
                printf("Ungueltige Eingabe, bitte geben Sie eine Gueltige Optionsnummer ein.(1-6)\n");
        }
    }
}

