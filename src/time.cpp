#include "time.h"

float calculateSpawningTime(float realTime){
        //realTime is the time we want the note to be perfectly hit on

        float d = 1000; //Choix arbitraire de la durée passée sur l'écran (en ms)
        float spawning_time = realTime - d;

        return spawning_time;

}
