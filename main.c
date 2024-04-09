#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LGPATH 8

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
    int nbLignesSet;
};
    
char paths[15][LGPATH] = {"dws_1/", "dws_2/", "dws_11/", "jog_9/", "jog_16/", "sit_5/", "sit_13/", "std_6/", "std_14/", "ups_3/", "ups_4/", "ups_12/", "wlk_7/", "wlk_8/", "wlk_15/"};

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

/*
----------------------------------------------------------------------
    PHASE 2
----------------------------------------------------------------------
*/

void initialisationPattern(char* path){
    FILE* fp;
    fopen_s(&fp, path, "w");

    // initialisation fichier
    fprintf_s(fp, "Mouvement");
    for (int i = 0; i < 600; i++){
        fprintf_s(fp,",Vacc");
    }
    fprintf_s(fp, "\n");

    fclose(fp);
}

void lireTrainSet(char* path, InfosLigneSet* tabInfosLigneSet){
    FILE *fp;

    InfosLigneSet infosLigneSet;

    fp = fopen(path, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error reading file lireSet\n");
    }
     else {
        // Here we have taken size of
        // array 1024 you can modify it
        char buffer[100000];

        int row = 0;
        int column = 0;
        double info;
        int mouvement = 1;
        tabInfosLigneSet[0].mouvement = 1; 
        int tabNbMouvements[6] = {0,};
 
        while (fgets(buffer,
                     100000, fp)) {
            column = 0;
            row++;
            tabInfosLigneSet[0].nbLignesSet = row;
 
            // To avoid printing of column
            // names in file can be changed
            // according to need    
           
            if (row == 1) continue;
 
            // Splitting the data
            char* value = strtok(buffer, ", ");
 
            while (value) {
                switch(column){
                    case 0:
                        if (atoi(value) != mouvement){
                            mouvement++;
                            tabInfosLigneSet[mouvement-1].mouvement = mouvement;
                        }
                        tabNbMouvements[mouvement-1]++;   
                    break;
                    case 1:
                        infosLigneSet.genre = atoi(value);
                    break;
                    case 2:
                        infosLigneSet.index = atoi(value);
                    break;
                    default:
                            info = strtod(value,NULL);                            
                            tabInfosLigneSet[mouvement-1].tabVAcc[column-3] += info;
                };
                value = strtok(NULL, ", ");
                column++;
            }
        } 
        for (mouvement = 0; mouvement < 6; mouvement++){
            for (int iVacc = 0; iVacc < 600; iVacc++){
                tabInfosLigneSet[mouvement].tabVAcc[iVacc] /= tabNbMouvements[mouvement];
            }
        }
        fclose(fp);
    }
}

void ecrirePatterns(char* path, InfosLigneSet infosLigneSet){
    FILE* fp;

    fp = fopen(path, "a");
    if (fp == NULL) {
        fprintf(stderr, "Error reading file ecriturePatterns\n");
    }
    else{
        // impression pour chaque ligne
        fprintf_s(fp, "%d", infosLigneSet.mouvement);

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

/*
-----------------------------------------------------------------------
 changer la ", " en "; " dans getTabGenders (2 fois) si problème avec tabGenders
-----------------------------------------------------------------------
*/

/*
----------------------------------------------------------------------
    PHASE 3
----------------------------------------------------------------------
*/

typedef struct infoLignePattern InfoLignePattern;
struct infoLignePattern{
    int mouvement;
    double vAcc[600];
};

void lirePattern(FILE* fp, InfoLignePattern* patterns){

    int column;
    char buffer[10000];
    double info;
    int row = 0;

    while (fgets(buffer,
                    100000, fp)) {
        column = 0;
        row++;

        // To avoid printing of column
        // names in file can be changed
        // according to need    
        
        if (row == 1) continue;

        // Splitting the data
        char* value = strtok(buffer, ", ");
        
        while (value) {
            switch(column){
                case 0:
                    patterns[row-2].mouvement = atoi(value);

                break;
                default:
                    patterns[row-2].vAcc[column-1] = strtod(value, NULL);

                break;
            };
            value = strtok(NULL, ", ");
            column++;
        }
    }
}

void lireTestSet(FILE* fp, InfosLigneSet* tabInfosLigneSet){
    char buffer[100000];

    int row = 0;
    int column = 0;
    double info;


    while (fgets(buffer,
                    100000, fp)) {
        column = 0;
        row++;

        // To avoid printing of column
        // names in file can be changed
        // according to need    
        
        if (row == 1) continue;

        // Splitting the data
        char* value = strtok(buffer, ", ");

        while (value) {
            switch(column){
                case 0:
                    tabInfosLigneSet[row-2].mouvement = atoi(value);
                break;
                case 1:
                    tabInfosLigneSet[row-2].genre = atoi(value);
                break;
                case 2:
                    tabInfosLigneSet[row-2].index = atoi(value);
                break;
                default:
                        info = strtod(value,NULL);                            
                        tabInfosLigneSet[row-2].tabVAcc[column-3] = info;
            };
            value = strtok(NULL, ", ");
            column++;
        }
    } 
}

void displayResultForEachClass(int* realClasses, int* estimatedClasses, int nbTests){
    printf("REAL CLASSES\tESTIMATED CLASSES");
    for (int i = 0; i < nbTests; i++){
        printf("\n%d\t\t%d", realClasses[i], estimatedClasses[i]);
    }
}

/*
----------------------------------------------------------------------
    Main
----------------------------------------------------------------------
*/

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
    while (iDossier < 15){
        iFichier = 1;

        while (iFichier <= 24){
            strcat(path, paths[iDossier]);
            sprintf_s(sub, sizeof(char)*11,"sub_%d.csv", iFichier);
            strcat(path, sub);
            printf("%s\n", path);

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

            if(iFichier % 10 == 0 || (iFichier == 3  && fmod(iDossier,3) == 0) || (iFichier == 1 && iDossier == 1)){
                printf("\t%s %s\n", paths[iDossier], sub);
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
    /*------------------------
            PHASE 2
    ------------------------*/
    initialisationPattern("pattern.csv");
    InfosLigneSet tabTrainSet[6];
    for (int iMouvement = 0; iMouvement < 6; iMouvement++){
        for (int iVacc = 0; iVacc < 600; iVacc++){
            tabTrainSet[iMouvement].tabVAcc[iVacc] = 0;
        }
    }
    lireTrainSet("trainSet.csv", tabTrainSet);
    for (int iLigne = 0; iLigne < 6; iLigne++){
        ecrirePatterns("pattern.csv", tabTrainSet[iLigne]);
    }

    /*------------------------
            PHASE 3
    ------------------------*/

    
    FILE* fiTest = fopen("testSet.csv", "r");
    FILE* fiPattern = fopen("pattern.csv", "r");
    if (fiTest && fiPattern){
        
        InfoLignePattern models[6];
        lirePattern(fiPattern, models);
        
        InfosLigneSet testSet[36];
        lireTestSet(fiTest, testSet);

        int realClasses[36];
        for (int i = 0; i < 36; i++){
            realClasses[i] = testSet[i].mouvement;
        }

        int estimatedClasses[36] = {0,};

        // for (int iLigne = 0; iLigne < 36; iLigne++){
        //     for (int iVacc = 0; iVacc < 600; iVacc++){
        //         estimatedClasses[iLigne] += pow((testSet[iLigne].tabVAcc[iVacc] - models[]),2)
        //     }
        // }

        displayResultForEachClass(realClasses,estimatedClasses,36);



    }
    else{
        fprintf(stderr, "erreur dans l'ouverture de fiTest ou fiPattern\n");
    }
}
