#include <stdlib.h>
#include <stdio.h>

extern const uint16_t features_count;
extern float features[48];
extern uint16_t head;
extern float queue[312];

int predict(float *x) {
                        uint8_t votes[4] = { 0 };
                        // tree #1
                        if (x[20] <= 6.412200927734375) {
                            if (x[47] <= 22.0) {
                                votes[3] += 1;
                            }

                            else {
                                if (x[40] <= -1.1541815102100372) {
                                    votes[1] += 1;
                                }

                                else {
                                    votes[0] += 1;
                                }
                            }
                        }

                        else {
                            votes[2] += 1;
                        }

                        // tree #2
                        if (x[0] <= -2.983176052570343) {
                            if (x[1] <= 8.261192321777344) {
                                votes[3] += 1;
                            }

                            else {
                                if (x[33] <= 1.1345300078392029) {
                                    votes[3] += 1;
                                }

                                else {
                                    votes[2] += 1;
                                }
                            }
                        }

                        else {
                            if (x[5] <= 1.312942624092102) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        // tree #3
                        if (x[45] <= 0.5174195915460587) {
                            votes[0] += 1;
                        }

                        else {
                            if (x[35] <= 1.9395795464515686) {
                                if (x[22] <= 22.0) {
                                    votes[3] += 1;
                                }

                                else {
                                    votes[1] += 1;
                                }
                            }

                            else {
                                votes[2] += 1;
                            }
                        }

                        // tree #4
                        if (x[16] <= 3.2884355783462524) {
                            if (x[43] <= 3.3018020391464233) {
                                if (x[10] <= 0.04309549927711487) {
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
                        if (x[15] <= 21.0) {
                            if (x[8] <= -7.059304237365723) {
                                votes[2] += 1;
                            }

                            else {
                                votes[3] += 1;
                            }
                        }

                        else {
                            if (x[41] <= 1.528161495923996) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        // tree #6
                        if (x[19] <= 10.590750694274902) {
                            votes[0] += 1;
                        }

                        else {
                            if (x[10] <= 0.045490000396966934) {
                                votes[1] += 1;
                            }

                            else {
                                if (x[22] <= 22.5) {
                                    votes[3] += 1;
                                }

                                else {
                                    votes[2] += 1;
                                }
                            }
                        }

                        // tree #7
                        if (x[10] <= 0.039503999054431915) {
                            if (x[45] <= 0.7663439065217972) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        else {
                            if (x[32] <= -2.1295005083084106) {
                                if (x[18] <= 3.2884355783462524) {
                                    votes[2] += 1;
                                }

                                else {
                                    votes[0] += 1;
                                }
                            }

                            else {
                                votes[3] += 1;
                            }
                        }

                        // tree #8
                        if (x[40] <= -1.0198845267295837) {
                            if (x[20] <= 6.400483131408691) {
                                if (x[14] <= 28.5) {
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

                        // tree #9
                        if (x[12] <= 1.429337978363037) {
                            if (x[4] <= 0.8079274594783783) {
                                if (x[46] <= 30.0) {
                                    votes[0] += 1;
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
                            votes[3] += 1;
                        }

                        // tree #10
                        if (x[12] <= 1.4466268420219421) {
                            if (x[40] <= -3.2467775344848633) {
                                votes[2] += 1;
                            }

                            else {
                                if (x[34] <= 0.011057500261813402) {
                                    votes[0] += 1;
                                }

                                else {
                                    votes[1] += 1;
                                }
                            }
                        }

                        else {
                            votes[3] += 1;
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
        return "line";
        case 3:
        return "nike";
        default:
        return "Sir, we have a problem";
    }
}
/**
* Predict readable class name
*/
const char* predictLabel(float *x) {
    return idxToLabel(predict(x));
}
