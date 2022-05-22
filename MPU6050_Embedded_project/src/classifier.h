#include <stdlib.h>
#include <stdio.h>



int predict(float *x) {
                        uint8_t votes[4] = { 0 };
                        // tree #1
                        if (x[17] <= 9.0) {
                            votes[0] += 1;
                        }

                        else {
                            if (x[21] <= 3.0173362493515015) {
                                votes[1] += 1;
                            }

                            else {
                                if (x[40] <= -3.5) {
                                    votes[2] += 1;
                                }

                                else {
                                    if (x[22] <= 23.5) {
                                        votes[3] += 1;
                                    }

                                    else {
                                        votes[2] += 1;
                                    }
                                }
                            }
                        }

                        // tree #2
                        if (x[21] <= 3.0173362493515015) {
                            if (x[47] <= 34.0) {
                                votes[1] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        else {
                            if (x[0] <= -4.5) {
                                if (x[5] <= 2.3038597106933594) {
                                    votes[3] += 1;
                                }

                                else {
                                    votes[2] += 1;
                                }
                            }

                            else {
                                votes[3] += 1;
                            }
                        }

                        // tree #3
                        if (x[45] <= 0.5707090198993683) {
                            votes[0] += 1;
                        }

                        else {
                            if (x[21] <= 3.0173362493515015) {
                                votes[1] += 1;
                            }

                            else {
                                if (x[40] <= -3.5) {
                                    votes[2] += 1;
                                }

                                else {
                                    if (x[35] <= 3.5) {
                                        votes[3] += 1;
                                    }

                                    else {
                                        votes[2] += 1;
                                    }
                                }
                            }
                        }

                        // tree #4
                        if (x[16] <= -5.5) {
                            votes[2] += 1;
                        }

                        else {
                            if (x[47] <= 32.5) {
                                if (x[19] <= 16.0) {
                                    votes[1] += 1;
                                }

                                else {
                                    votes[3] += 1;
                                }
                            }

                            else {
                                if (x[9] <= 3.5) {
                                    votes[0] += 1;
                                }

                                else {
                                    votes[3] += 1;
                                }
                            }
                        }

                        // tree #5
                        if (x[6] <= 21.5) {
                            if (x[8] <= -6.0) {
                                votes[3] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        else {
                            if (x[1] <= 3.5) {
                                if (x[13] <= 3.629316568374634) {
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

                        // tree #6
                        if (x[19] <= 9.0) {
                            votes[0] += 1;
                        }

                        else {
                            if (x[23] <= 21.5) {
                                if (x[7] <= 19.5) {
                                    votes[2] += 1;
                                }

                                else {
                                    votes[3] += 1;
                                }
                            }

                            else {
                                if (x[6] <= 19.5) {
                                    votes[3] += 1;
                                }

                                else {
                                    votes[1] += 1;
                                }
                            }
                        }

                        // tree #7
                        if (x[35] <= 3.5) {
                            if (x[0] <= -7.0) {
                                votes[1] += 1;
                            }

                            else {
                                if (x[19] <= 10.0) {
                                    votes[0] += 1;
                                }

                                else {
                                    votes[3] += 1;
                                }
                            }
                        }

                        else {
                            votes[2] += 1;
                        }

                        // tree #8
                        if (x[40] <= -1.0) {
                            if (x[21] <= 3.0512475967407227) {
                                votes[1] += 1;
                            }

                            else {
                                if (x[6] <= 22.0) {
                                    votes[3] += 1;
                                }

                                else {
                                    if (x[21] <= 5.1657350063323975) {
                                        if (x[0] <= -4.5) {
                                            votes[2] += 1;
                                        }

                                        else {
                                            votes[3] += 1;
                                        }
                                    }

                                    else {
                                        votes[2] += 1;
                                    }
                                }
                            }
                        }

                        else {
                            votes[0] += 1;
                        }

                        // tree #9
                        if (x[8] <= -5.0) {
                            if (x[35] <= 1.5) {
                                votes[1] += 1;
                            }

                            else {
                                if (x[46] <= 8.0) {
                                    votes[3] += 1;
                                }

                                else {
                                    if (x[16] <= -5.0) {
                                        votes[2] += 1;
                                    }

                                    else {
                                        votes[3] += 1;
                                    }
                                }
                            }
                        }

                        else {
                            votes[0] += 1;
                        }

                        // tree #10
                        if (x[24] <= -0.5) {
                            if (x[39] <= 37.0) {
                                if (x[35] <= 3.5) {
                                    if (x[32] <= -1.5) {
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

const char idxToLabel(uint8_t classIdx) {
                        switch (classIdx) {
                            case 0:
                            return 'S';
                            case 1:
                            return 'L';
                            case 2:
                            return 'T';
                            case 3:
                            return 'R';
                            default:
                            return 'X';
                        }
                    }

/**
* Predict readable class name
*/
const char predictLabel(float *x) {
    return idxToLabel(predict(x));
}
