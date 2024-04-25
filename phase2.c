#include "projet.h"

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

void main(void){
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
}