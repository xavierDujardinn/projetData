#include "projet.h"

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
        printf("\n%d : %d\t\t%d", i + 1 ,realClasses[i], estimatedClasses[i]);
    }
}

void displayAccuracy(int * realClasses, int* estimatedClasses, int nbTests){
    double accuracy = 0;
    for (int i = 0; i < nbTests; i++){
        if (realClasses[i] == estimatedClasses[i]){
            accuracy++;
        }
    }
    printf("\nAccuracy : %lf %.lf", (accuracy/nbTests)*100, accuracy);
}

void main(void){
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
        double temp;
        double dist;

        for (int iLigne = 0; iLigne < 36; iLigne++){
            dist = DBL_MAX;
            for (int iModel = 0; iModel < 6; iModel++){
                temp = 0;
                for (int iVacc = 0; iVacc < 600; iVacc++){
                    temp += pow((testSet[iLigne].tabVAcc[iVacc] - models[iModel].vAcc[iVacc]),2);
                }
                temp = sqrt(temp);

                if (temp <= dist) {
                    dist = temp;
                    estimatedClasses[iLigne] = iModel + 1;
                } 
            }
            //printf("%d : %.4lf\n", iLigne + 1, dist);
        }

        displayResultForEachClass(realClasses,estimatedClasses,36);
        displayAccuracy(realClasses,estimatedClasses,36);



    }
    else{
        fprintf(stderr, "erreur dans l'ouverture de fiTest ou fiPattern\n");
    }
}