#include "HeaderFiles/ProofVerifier.h"

ProofVerifier::ProofVerifier() 
{
    stepCount = 0;
}

void ProofVerifier::addProofStep(string step) 
{
    proofSteps[stepCount] = step;
    stepCount++;
}

bool ProofVerifier::verifyInductionProof(string baseCase, string inductiveStep) 
{
    cout << "\n=== Verifying Induction Proof ===" << endl;
    cout << "Base Case: " << baseCase << endl;
    cout << "Inductive Step: " << inductiveStep << endl;
    cout << "Proof is valid if both steps are satisfied." << endl;
    return true;
}

bool ProofVerifier::verifyLogicProof(string premises[], int premiseCount, string conclusion) 
{
    cout << "\n=== Verifying Logic Proof ===" << endl;
    cout << "Premises:" << endl;
    for(int i = 0; i < premiseCount; i++)
    {
        cout << "  - " << premises[i] << endl;
    }
    cout << "Conclusion: " << conclusion << endl;
    return true;
}

void ProofVerifier::displayProof() 
{
    cout << "\n=== Proof Steps ===" << endl;
    for(int i = 0; i < stepCount; i++)
    {
        cout << "Step " << (i + 1) << ": " << proofSteps[i] << endl;
    }
}

void ProofVerifier::clearProof() 
{
    stepCount = 0;
}