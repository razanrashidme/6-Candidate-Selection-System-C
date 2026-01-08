#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_OF_APPLICANTS 7  // number of applicants


struct Applicant {
    int id;
    char name[40];
    char education[20];
    int experience;
    char major[20];
    float GPA;
    char state[20];
    float points;
};


struct Applicant* list;


void addApplicant() {

    list = (struct Applicant*) malloc(NUM_OF_APPLICANTS * sizeof(struct Applicant));
    if (list == NULL) {
        printf("Error allocating memory for applicants.\n");
        return;
    }

    FILE* fp = fopen("Applicant.txt", "r");
    if (fp == NULL) {
        printf("Error opening the file\n");
        free(list);
        return;
    }


    char buffer[200];
    fgets(buffer, sizeof(buffer), fp);  // Skip first line
    fgets(buffer, sizeof(buffer), fp);  // Skip second line

    int i = 0;
    // Read applicants' data into the array
    while (fscanf(fp, "%d %s %s %d %s %f %s",
                  &list[i].id,
                  list[i].name,
                  list[i].education,
                  &list[i].experience,
                  list[i].major,
                  &list[i].GPA,
                  list[i].state) == 7) {
        list[i].points = 0;  // Initialize Points to 0
        i++;
        if (i >= NUM_OF_APPLICANTS) {
            break;  // Stop reading
        }
                  }

    fclose(fp);
     /*
    //(To make sure it's working)
    printf("\n%d Applicant records read\n\n", NUM_OF_APPLICANTS);
    printf("Applicant ID | Name | Education | Experience | Major | GPA | Points | State\n");

    int j;
    for (j = 0; j < NUM_OF_APPLICANTS; j++) {
        printf("%d %s %s %d %s %.2f %.2f %s\n",
               list[j].id,
               list[j].name,
               list[j].education,
               list[j].experience,
               list[j].major,
               list[j].GPA,
               list[j].points,
               list[j].state);
    }*/


}//end of add


    void calculatePoints() {
    int i ;
        for ( i = 0; i < NUM_OF_APPLICANTS; i++) {
            if (strcmp(list[i].education, "MSc") == 0)
                list[i].points = list[i].GPA + list[i].experience + 10;
            else
                list[i].points = list[i].GPA + list[i].experience;
        }
    }//end of calc


void setApplicantState(char* MajorList[]){

   int i, j;
   int maxApplicant= -1;
   float maxPoints= -1.0;

   for(i= 0;i<NUM_OF_APPLICANTS;i++){
     for(j= 0;MajorList[j] != NULL;j++){
        int match= 1;
        for(int k= 0; list[i].major[k] != '\0' || MajorList[j][k] != '\0'; k++){
           if(list[i].major[k] != MajorList[j][k]){
            match = 0;
            break;
               }
          }

            if(match){
                strcpy(list[i].state, "Candidate");
                if(list[i].points> maxPoints){
                    maxPoints= list[i].points;
                    maxApplicant= i;
                }
                
                else if(list[i].points == maxPoints && maxApplicant == -1){
                    maxApplicant= i;
                }
                
                break;
           }
        }
    }

    if(maxApplicant!= -1){
        strcpy(list[maxApplicant].state, "Assigned");
   }
}

void writeAssignedApplicants(){
 FILE* fp =fopen("Output_Applicants.txt","w");
if(fp == NULL){
    printf("can't open the output file \n");
    return;
}
fprintf(fp,"THE APPLICANTS LIST : \n");
fprintf(fp,"ID\t\tName\t\tEducation\t\tExperience\t\tMajor\t\tGPA\t\tState\n");
for (int i=0 ;i< NUM_OF_APPLICANTS ;i++){
 fprintf(fp,"%d\t\t%s\t\t%s\t\t%d\t\t%s\t\t%.2f\t\t%s\n",list[i].id,list[i].name,list[i].education,list[i].experience,list[i].major,list[i].GPA, list[i].state);
}
fprintf(fp, "\nThe Candidates List is:\n");
fprintf(fp, "ID\t\tName\t\tEducation\t\tMajor\t\tPoints\t\tState\n");
for (int i = 0; i < NUM_OF_APPLICANTS; i++) {
if (strcmp(list[i].state, "Candidate") == 0) { // here i mean if the state in equal to candidate
fprintf(fp, "%d\t\t%s\t\t%s\t\t%s\t\t%.2f\t\t%s\n",list[i].id,list[i].name,list[i].education, list[i].major, list[i].points,list[i].state);
}
}
fprintf(fp,"\nThe Assigned Applicants are:\n");
//fprintf(fp, "ID\t\tName\t\tEducation\t\tMajor\t\tPoints\t\tState\n");
for (int i = 0; i < NUM_OF_APPLICANTS; i++) {
if (strcmp(list[i].state, "Assigned") == 0){
fprintf(fp, "%d\t\t%s\t\t%s\t\t%s\t\t%.2f\t\t%s\n", list[i].id, list[i].name,list[i].education, list[i].major, list[i].points, list[i].state);

 } 
}
fclose(fp);
}

void printList (){
printf("THE APPLICANTS LIST : \n");
printf("ID\t\tName\t\tEducation\t\tExperience\t\tMajor\t\tGPA\t\tState\n");
for (int i = 0; i < NUM_OF_APPLICANTS; i++) {
printf("%d\t\t%s\t\t%s\t\t%d\t\t%s\t\t%.2f\t\t%s\n",list[i].id,list[i].name,list[i].education,list[i].experience,list[i].major,list[i].GPA, list[i].state);
}
printf( "\nThe Candidates List is:\n");
printf( "ID\t\tName\t\tEducation\t\tMajor\t\tPoints\t\tState\n");
for (int i = 0; i < NUM_OF_APPLICANTS; i++) {
if (strcmp(list[i].state, "Candidate") == 0) { // here i mean if the state in equal to candidate
printf("%d\t\t%s\t\t%s\t\t%s\t\t%.2f\t\t%s\n",list[i].id,list[i].name,list[i].education, list[i].major, list[i].points,list[i].state);
}}
printf("\nThe Assigned Applicants are:\n");
//printf( "ID\t\tName\t\tEducation\t\tMajor\t\tPoints\t\tState\n");
for (int i = 0; i < NUM_OF_APPLICANTS; i++) {
if (strcmp(list[i].state, "Assigned") == 0){
printf( "%d\t\t%s\t\t%s\t\t%s\t\t%.2f\t\t%s\n", list[i].id, list[i].name,list[i].education, list[i].major, list[i].points, list[i].state);
}}

}

int main() {
    addApplicant();
    calculatePoints();
    char* MajorList[] = {"CSC", "SWE", "InS","CEN", NULL};
    setApplicantState(MajorList);
    writeAssignedApplicants();
    printList ();
    
    free(list);
    return 0;
}