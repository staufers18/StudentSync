#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(){
  typedef struct Date{
    int year,month,day;
  } date;

  struct Student{
    char firstname[100];
    char lastname[100];
    char degreeProgram[100];
    int matrikelnumber;
    date startdate;
    date enddate;
    date birthdate;
  }



 return 0;
  }
