// lab 1C: please fix the program
#include <stdio.h>
#include <string.h>

// By Student: To make the program clearer, I decided to use struct.
struct grade{
    char *grd;
    double polyusc;
    double othersc;
};
void initializestruct(struct grade *a){
    a->grd=NULL;
    a->polyusc=100;  // 100 for unset score/ invalid grade
    a->othersc=100;
}
int checkinsert(char *cu){  // check whether the grade is valid to add to struct
    if(strlen(cu)>2)return 0;   // situations like A++/C++ is invalid
    switch(cu[0]){
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'F':return 1;   // grade begins with A/B/C/D/F is valid
        default: return 0;   // other grades are invalid
    }
}
void givefeedback(double avescore){  // give feed back according to average score
    printf("Feedback: ");
    if(avescore<2.0)printf("Poor\n");
    else if (avescore<3.0)printf("Average\n");
    else if (avescore<3.5)printf("Good\n");
    else printf("Excellent\n");
}
int main(int argc, char *argv[])
{
    struct grade grades[10];
    for(int i=0;i<10;i++)initializestruct(&grades[i]);  // Initialize the struct
    char input[512];
    fgets(input,512,stdin);  // get the input
    // printf("%llu", strlen(input));
    char *current;
    char *delims={" \n"};
    current=strtok(input,delims);       // use strtok to split the input by space or \n
    //current=strtok(NULL,delims);    // skip the first "GPA" string
    int validnum=0;
    while(current!=NULL){
        //printf("%s\n",current);
        int status=checkinsert(current);
        if(status){  // if return 1, then add to struct
            grades[validnum].grd= strdup(current);
            validnum++;
        }
        current=strtok(NULL,delims);
    }
    //for(int i=0;i<validnum;i++)printf("%s %lf %lf\n",grades[i].grd,grades[i].polyusc,grades[i].othersc);

    // PolyU System
    printf("\nPolyU System:\n");
    for (int i = 0; i <validnum; i++) {       // PolyU system calculation
        double in_gp, sum_gp = 0.0;
        char in_grade;
        in_grade = grades[i].grd[0]; // get the first character
        switch (in_grade) {
            case 'A': in_gp = 4.0; break;
            case 'B': in_gp = 3.0; break;
            case 'C': in_gp = 2.0; break;
            case 'D': in_gp = 1.0; break;
            case 'F': in_gp = 0.0; break;
            default: printf("Wrong grade %s\n",argv[i]);
        }
        if(strlen(grades[i].grd)==2){       // situations of +/-
            if (grades[i].grd[1] == '+') in_gp += 0.3;
            if (grades[i].grd[1] == '-') {
                if(in_grade=='D')in_gp=100.0;  // if D-, then invalid
                else in_gp -= 0.3;
            }
        }
        sum_gp = sum_gp + in_gp;
        grades[i].polyusc=sum_gp;
    }
    for(int i=0;i<validnum;i++){
        if(grades[i].polyusc!=100)printf("Grade for subject %d is %s, GP %.1f\n",i+1,grades[i].grd,grades[i].polyusc);
        else printf("Grade for subject %d is %s, invalid\n",i+1,grades[i].grd);
    }
    int polyuvalid=0;
    double polyuavgscore=0.0;
    for(int i=0;i<validnum;i++){
        if(grades[i].polyusc!=100){
            polyuvalid++;
            polyuavgscore+=grades[i].polyusc;
        }
    }
    polyuavgscore=polyuavgscore/polyuvalid;
    printf("Your GPA for %d valid subjects is %.2f\n",polyuvalid,polyuavgscore);
    givefeedback(polyuavgscore);

    // Other System
    printf("Other System:\n");
    for (int i = 0; i <validnum; i++) {       // Other system calculation
        double in_gp, sum_gp = 0.0;
        char in_grade;
        in_grade = grades[i].grd[0]; // get the first character
        switch (in_grade) {
            case 'A': in_gp = 11; break;
            case 'B': in_gp = 8; break;
            case 'C': in_gp = 5; break;
            case 'D': in_gp = 2; break;
            case 'F': in_gp = 0.0; break;
            default: printf("Wrong grade %s\n",argv[i]);
        }
        if(strlen(grades[i].grd)==2){       // situations of +/-
            if (grades[i].grd[1] == '+') in_gp += 1;
            if (grades[i].grd[1] == '-') in_gp -= 1;
        }
        sum_gp = sum_gp + in_gp;
        grades[i].othersc=sum_gp;
    }
    for(int i=0;i<validnum;i++){
        if(grades[i].othersc!=100)printf("Grade for subject %d is %s, GP %.0f\n",i+1,grades[i].grd,grades[i].othersc);
        else printf("Grade for subject %d is %s, invalid\n",i+1,grades[i].grd);
    }
    int othervalid=0;
    double otheravgscore=0.0;
    for(int i=0;i<validnum;i++){
        if(grades[i].othersc!=100){
            othervalid++;
            otheravgscore+=grades[i].othersc;
        }
    }
    otheravgscore=otheravgscore/othervalid;
    printf("Your GPA for %d valid subjects is %.2f\n",othervalid,otheravgscore);
    givefeedback(otheravgscore);

}