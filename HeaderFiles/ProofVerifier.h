#pragma once
#include "Constants.h"

class ProofVerifier 
{
private:
    string proofSteps[MAX_PROOF_STEPS];
    int stepCount;
    
public:
    ProofVerifier();
    void addProofStep(string step);
    bool verifyInductionProof(string baseCase, string inductiveStep);
    bool verifyLogicProof(string premises[], int premiseCount, string conclusion);
    void displayProof();
    void clearProof();
};