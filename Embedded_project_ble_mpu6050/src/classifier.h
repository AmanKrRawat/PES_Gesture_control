#include <stdlib.h>
#include <stdio.h>

int predict(float *x) {
 uint8_t votes[4] = { 0 };
 // tree #1
 if (x[17] <= 17.764975547790527) {
     if (x[13] <= 1.9636380076408386) {
         if (x[38] <= 27.5) {
             votes[1] += 1;
         }

         else {
             votes[0] += 1;
         }
     }

     else {
         votes[3] += 1;
     }
 }

 else {
     votes[2] += 1;
 }

 // tree #2
 if (x[27] <= 2.0515599846839905) {
     if (x[1] <= 3.3375165462493896) {
         votes[0] += 1;
     }

     else {
         votes[1] += 1;
     }
 }

 else {
     if (x[33] <= 1.2268590033054352) {
         votes[3] += 1;
     }

     else {
         votes[2] += 1;
     }
 }

 // tree #3
 if (x[45] <= 0.42716532945632935) {
     votes[0] += 1;
 }

 else {
     if (x[19] <= 15.109806537628174) {
         votes[1] += 1;
     }

     else {
         votes[2] += 1;
     }
 }

 // tree #4
 if (x[16] <= 2.6623520851135254) {
     if (x[36] <= -0.09625046327710152) {
         if (x[19] <= 13.393163681030273) {
             votes[1] += 1;
         }

         else {
             votes[3] += 1;
         }
     }

     else {
         votes[2] += 1;
     }
 }

 else {
     votes[0] += 1;
 }

 // tree #5
 if (x[13] <= 1.3375637531280518) {
     votes[0] += 1;
 }

 else {
     if (x[23] <= 25.5) {
         if (x[41] <= 2.6922695636749268) {
             votes[1] += 1;
         }

         else {
             votes[3] += 1;
         }
     }

     else {
         votes[2] += 1;
     }
 }

 // tree #6
 if (x[19] <= 8.504203796386719) {
     votes[0] += 1;
 }

 else {
     if (x[8] <= -3.333926558494568) {
         if (x[22] <= 28.0) {
             votes[2] += 1;
         }

         else {
             votes[3] += 1;
         }
     }

     else {
         votes[1] += 1;
     }
 }

 // tree #7
 if (x[33] <= 1.5381540060043335) {
     if (x[39] <= 25.0) {
         if (x[19] <= 11.42752456665039) {
             votes[0] += 1;
         }

         else {
             votes[3] += 1;
         }
     }

     else {
         votes[1] += 1;
     }
 }

 else {
     votes[2] += 1;
 }

 // tree #8
 if (x[40] <= -1.0083599984645844) {
     if (x[43] <= 2.2642639875411987) {
         votes[1] += 1;
     }

     else {
         if (x[47] <= 32.5) {
             votes[2] += 1;
         }

         else {
             votes[3] += 1;
         }
     }
 }

 else {
     votes[0] += 1;
 }

 // tree #9
 if (x[31] <= 28.5) {
     if (x[4] <= 0.7493155598640442) {
         votes[0] += 1;
     }

     else {
         if (x[27] <= 2.67215096950531) {
             votes[1] += 1;
         }

         else {
             votes[3] += 1;
         }
     }
 }

 else {
     votes[2] += 1;
 }

 // tree #10
 if (x[24] <= -1.5206334590911865) {
     if (x[40] <= -1.8024845123291016) {
         if (x[19] <= 18.25698471069336) {
             votes[3] += 1;
         }

         else {
             votes[2] += 1;
         }
     }

     else {
         votes[1] += 1;
     }
 }

 else {
     votes[0] += 1;
 }

 // return argmax of votes
 uint8_t classIdx = 0;
 float maxVotes = votes[0];

 for (uint8_t i = 1; i < 4; i++) {
     if (votes[i] > maxVotes) {
         classIdx = i;
         maxVotes = votes[i];
     }
 }

 return classIdx;
 }
const char* idxToLabel(uint8_t classIdx) {
    switch (classIdx) {
        case 0:
        return "stationary";
        case 1:
        return "circle";
        case 2:
        return "square";
        case 3:
        return "triangle";
        default:
        return "Houston we have a problem";
    }
}
/**
* Predict readable class name
*/
const char* predictLabel(float *x) {
    return idxToLabel(predict(x));
}
