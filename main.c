#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LGPATH 6

typedef struct infosLigneSub InfosLigneSub;
struct infosLigneSub{
    int numLigne;
    double attitudeRoll;
    double attitudePitch;
    double attitudeYaw;
    double gravityX;
    double gravityY;
    double gravityZ;
    double rotationRateX;
    double rotationRateY;
    double rotationRateZ;
    double userAccelerationX;
    double userAccelerationY;
    double userAccelerationZ;
};

typedef struct infosLigneSet InfosLigneSet;
struct infosLigneSet{
    int mouvement;
    int genre;
    int index;
    double tabVAcc[600];
};

char paths[15][LGPATH] = {"dws_1", "dws_2", "dws_11", "jog_9", "jog_16", "sit_5", "sit_13", "std_6", "std_14", "ups_3", "ups_4", "ups_12", "wlk_7", "wlk_8", "wlk_15"};

InfosLigneSet lireFichier(char* path) {
    FILE *fp;

    InfosLigneSet infosLigneSet;

    fp = fopen(path, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error reading file\n");
    }
     else {
        // Here we have taken size of
        // array 1024 you can modify it
        char buffer[1024];
 
        int row = 0;
        int column = 0;
        InfosLigneSub infosLigneSub;
        double info;
 
        while (fgets(buffer,
                     1024, fp) && row < 601) {
            column = 0;
            row++;
 
            // To avoid printing of column
            // names in file can be changed
            // according to need    
           
            if (row == 1) continue;
 
            // Splitting the data
            char* value = strtok(buffer, ", ");
 
            while (value) {
                if (column == 0){
                    infosLigneSub.numLigne = atoi(value);
                }
                else{
                    info = strtod(value,NULL);
                    switch (column)
                    {
                    case 1:
                        infosLigneSub.attitudeRoll = info;

                    break;
                    case 2:
                        infosLigneSub.attitudePitch = info;

                    break;
                    case 3:
                        infosLigneSub.attitudeYaw = info;

                    break;
                    case 4:
                        infosLigneSub.gravityX = info;

                    break;
                    case 5:
                        infosLigneSub.gravityY = info;

                    break;
                    case 6:
                        infosLigneSub.gravityZ = info;

                    break;
                    case 7:
                        infosLigneSub.rotationRateX = info;

                    break;
                    case 8:
                        infosLigneSub.rotationRateY = info;

                    break;
                    case 9:
                        infosLigneSub.rotationRateZ = info;

                    break;
                    case 10:
                        infosLigneSub.userAccelerationX = info;

                    break;
                    case 11:
                        infosLigneSub.userAccelerationY = info;

                    break;
                    case 12:
                        infosLigneSub.userAccelerationZ = info;

                    break;
                    }
                }

                

                value = strtok(NULL, ", ");
                column++;

            }
            
            infosLigneSet.tabVAcc[row-1] = sqrt(pow(infosLigneSub.userAccelerationX,2) + pow(infosLigneSub.userAccelerationY,2) + pow(infosLigneSub.userAccelerationY,2));
        }
    }
    fclose(fp);
    return infosLigneSet;
}

void ecrireSet(char* path, InfosLigneSet infosLigneSet){
    FILE* fp;

    fopen_s(&fp, path, "a");

    // impression pour chaque ligne
    fprintf_s(fp, ",,");

    int i = 0;
    while (i < 600){
        fprintf_s(fp,",%.2lf", infosLigneSet.tabVAcc[i]);
        i++;
    }
    fprintf_s(fp, "\n");

    fclose(fp);
}

void initialisationSet(char* path){
    FILE* fp;
    fopen_s(&fp, path, "w");

    // initialisation fichier
    fprintf_s(fp, "Mouvement,Genre,Index");
    int i = 0;
    while (i < 600){
        fprintf_s(fp,",Vacc");
        i++;
    }
    fprintf_s(fp, "\n");

    fclose(fp);
}

void getTabGenders(int* tabGenders){
    FILE* fp;

    fopen_s(&fp, "data_subjects_info.csv", "r");
    if (fp == NULL) {
        fprintf(stderr, "Error reading file\n");
    }
     else {
        // Here we have taken size of
        // array 1024 you can modify it
        char buffer[1024];
 
        int row = 0;
        int column = 0;
        double info;
 
        while (fgets(buffer,
                     1024, fp)) {
            column = 0;
            row++;
 
            // To avoid printing of column
            // names in file can be changed
            // according to need    
           
            if (row == 1) continue;
 
            // Splitting the data
            char* value = strtok(buffer, "; ");
 
            while (value) {
                if (column == 4){
                    tabGenders[row-2] = atoi(value);
                }
                value = strtok(NULL, "; ");
                column++;

            } 
        }
    }
}

void main(void){
    int tabGenders[24];
    getTabGenders(tabGenders);
    InfosLigneSet infosLigneSet = lireFichier("A_DeviceMotion_data/A_DeviceMotion_data/dws_1/sub_1.csv");
    initialisationSet("testSet.csv");
    initialisationSet("dataSet.csv");
    ecrireSet("testSet.csv", infosLigneSet);
}
