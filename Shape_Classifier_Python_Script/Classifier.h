#pragma once
#include <cstdarg>
namespace Eloquent {
    namespace ML {
        namespace Port {
            class Classifier {
                public:
                    /**
                    * Predict class for features vector
                    */
                    int predict(float *x) {
                        uint8_t votes[4] = { 0 };
                        // tree #1
                        if (x[28] <= 0.07692308072000742) {
                            if (x[13] <= 4.199864625930786) {
                                if (x[38] <= 2.5) {
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

                        // tree #2
                        if (x[16] <= -5.5) {
                            votes[2] += 1;
                        }

                        else {
                            if (x[47] <= 47.5) {
                                if (x[46] <= 14.5) {
                                    votes[3] += 1;
                                }

                                else {
                                    votes[1] += 1;
                                }
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        // tree #3
                        if (x[45] <= 0.6153846085071564) {
                            votes[0] += 1;
                        }

                        else {
                            if (x[21] <= 3.0631784200668335) {
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
                            if (x[5] <= 0.9405884742736816) {
                                votes[0] += 1;
                            }

                            else {
                                if (x[19] <= 15.5) {
                                    votes[1] += 1;
                                }

                                else {
                                    votes[3] += 1;
                                }
                            }
                        }

                        // tree #5
                        if (x[6] <= 26.5) {
                            if (x[8] <= -5.5) {
                                votes[3] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        else {
                            if (x[1] <= 4.5) {
                                if (x[21] <= 3.2330050468444824) {
                                    if (x[14] <= 10.5) {
                                        votes[0] += 1;
                                    }

                                    else {
                                        votes[1] += 1;
                                    }
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
                        if (x[19] <= 9.5) {
                            votes[0] += 1;
                        }

                        else {
                            if (x[43] <= 3.5) {
                                votes[3] += 1;
                            }

                            else {
                                if (x[11] <= 14.5) {
                                    votes[2] += 1;
                                }

                                else {
                                    votes[1] += 1;
                                }
                            }
                        }

                        // tree #7
                        if (x[46] <= 4.5) {
                            votes[0] += 1;
                        }

                        else {
                            if (x[0] <= -7.0) {
                                if (x[19] <= 17.0) {
                                    votes[1] += 1;
                                }

                                else {
                                    votes[2] += 1;
                                }
                            }

                            else {
                                votes[3] += 1;
                            }
                        }

                        // tree #8
                        if (x[40] <= -1.0) {
                            if (x[21] <= 3.2321637868881226) {
                                votes[1] += 1;
                            }

                            else {
                                if (x[47] <= 39.0) {
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
                        if (x[18] <= 0.5) {
                            if (x[35] <= 3.5) {
                                votes[3] += 1;
                            }

                            else {
                                votes[2] += 1;
                            }
                        }

                        else {
                            if (x[27] <= 1.5) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        // tree #10
                        if (x[18] <= 0.5) {
                            if (x[5] <= 2.6902445554733276) {
                                votes[3] += 1;
                            }

                            else {
                                votes[2] += 1;
                            }
                        }

                        else {
                            if (x[19] <= 9.5) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
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

                    /**
                    * Predict readable class name
                    */
                    const char* predictLabel(float *x) {
                        return idxToLabel(predict(x));
                    }

                    /**
                    * Convert class idx to readable name
                    */
                    const char* idxToLabel(uint8_t classIdx) {
                        switch (classIdx) {
                            case 0:
                            return "stationary";
                            case 1:
                            return "line";
                            case 2:
                            return "nike";
                            case 3:
                            return "square";
                            default:
                            return "Houston we have a problem";
                        }
                    }

                protected:
                };
            }
        }
    }