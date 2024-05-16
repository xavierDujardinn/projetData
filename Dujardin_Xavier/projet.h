#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

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
