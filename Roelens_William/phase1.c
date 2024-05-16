#include "projet.h"

InfosLigneSet lireSub(char* path) {
    FILE *fp;

    InfosLigneSet infosLigneSet;

    fp = fopen(path, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error reading file lireSub\n");
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
            
            infosLigneSet.tabVAcc[row-2] = sqrt(pow(infosLigneSub.userAccelerationX,2) + pow(infosLigneSub.userAccelerationY,2) + pow(infosLigneSub.userAccelerationY,2));
        }
        while(row < 601){
            infosLigneSet.tabVAcc[row-1] = 0; 
            row++;
        }

        fclose(fp);
    }
    return infosLigneSet;
}

void ecrireSet(char* path, InfosLigneSet infosLigneSet){
    FILE* fp;

    fp = fopen(path, "a");
    if (fp == NULL) {
        fprintf(stderr, "Error reading file ecritureSet\n");
    }
    else{
        // impression pour chaque ligne
        fprintf_s(fp, "%d,%d,%d", infosLigneSet.mouvement, infosLigneSet.genre, infosLigneSet.index);

        for (int i = 0; i < 600; i++) {
            if (infosLigneSet.tabVAcc[i] == 0){
                break;
            } 
            else{
                fprintf_s(fp,",%lf", infosLigneSet.tabVAcc[i]);
            }
        }
        fprintf_s(fp, "\n");
        
        fclose(fp);
    }
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

void getTabGenders(int tabGenders[24]){
    FILE* fp;

    fopen_s(&fp, "data_subjects_info.csv", "r");
    if (fp == NULL) {
        fprintf(stderr, "Error reading file tabGenders\n");
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
        fclose(fp); 
    }
}

void main(void){
    int tabGenders[24];
    getTabGenders(tabGenders);
    initialisationSet("trainSet.csv");
    initialisationSet("testSet.csv");    

    char path[100] = "A_DeviceMotion_data/A_DeviceMotion_data/";
    char sub[10];

    int index = 1;
    int iFichier;
    int iDossier = 0;
    int iii = 0;
    while (iDossier < 15){
        iFichier = 1;
        

        while (iFichier <= 24){
            strcat(path, paths[iDossier]);
            sprintf_s(sub, sizeof(char)*11,"sub_%d.csv", iFichier);
            strcat(path, sub);
            // printf("%s\n", path);

            InfosLigneSet infosLigneSet = lireSub(path);

            infosLigneSet.genre = tabGenders[iFichier-1];
            infosLigneSet.index = index;
            switch(iDossier){
                case 0 :
                case 1 :
                case 2 :
                    infosLigneSet.mouvement = 1; 
                
                break;
                case 3 :
                case 4 :
                    infosLigneSet.mouvement = 2;
                
                break;
                case 5 :
                case 6 :
                    infosLigneSet.mouvement = 3;
                
                break;
                case 7 :
                case 8 :
                    infosLigneSet.mouvement = 4;
                
                break;
                case 9:
                case 10: 
                case 11:
                    infosLigneSet.mouvement = 5;
                
                break;
                case 12: 
                case 13:
                case 14:
                    infosLigneSet.mouvement = 6;
                break;
             };

        if((iDossier == 0 && (iFichier == 7 || iFichier == 8 || iFichier == 9))
        || (iDossier == 1 && (iFichier == 8 || iFichier == 10))
        || (iDossier == 2 && (iFichier == 9 || iFichier == 10 || iFichier == 20))
        || (iDossier == 3 && (iFichier == 3 || iFichier == 4 || iFichier == 5))
        || (iDossier == 4 && (iFichier == 1 || iFichier == 10 || iFichier == 20))
        || (iDossier == 5 && (iFichier == 3 || iFichier == 5 || iFichier == 10))
        || (iDossier == 6 && (iFichier == 5 || iFichier == 7))
        || (iDossier == 7 && (iFichier == 10 || iFichier == 20))
        || (iDossier == 8 && (iFichier == 10 || iFichier == 20))
        || (iDossier == 9 && (iFichier == 3 || iFichier == 5))
        || (iDossier == 10 && (iFichier == 10 || iFichier == 20))
        || (iDossier == 11 && (iFichier == 10 || iFichier == 20))
        || (iDossier == 12 && (iFichier == 12 || iFichier == 13 || iFichier == 14))
        || (iDossier == 13 && (iFichier == 21 || iFichier == 1))
        || (iDossier == 14 && (iFichier == 1 || iFichier == 2))){
                iii++;
                printf("\t%d %s %s\n", iii, paths[iDossier], sub);
                ecrireSet("testSet.csv", infosLigneSet); 
            }
            else{
                ecrireSet("trainSet.csv", infosLigneSet);
            }

            index++;
            iFichier++;
            strcpy(path,"A_DeviceMotion_data/A_DeviceMotion_data/");
            strcpy(sub,"");
        }
        iDossier++;
    }
}