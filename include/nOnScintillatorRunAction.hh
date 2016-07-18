// ********************************************************************
// nOnScintillator simulation
// ********************************************************************
/// \file nOnScintillatorRunAction.hh
/// \brief Definition of the nOnScintillatorRunAction class

#ifndef nOnScintillatorRunAction_h
#define nOnScintillatorRunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Event.hh"
#include "globals.hh"
//#include <TFile.h>
//#include <TTree.h>
//#include <TLorentzVector.h>
//#include <TVector3.h>
//#include <vector>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Run;

/// Run action class

class nOnScintillatorRunAction : public G4UserRunAction
{
private:

public:
    
    nOnScintillatorRunAction();
    virtual ~nOnScintillatorRunAction();

    virtual void BeginOfRunAction(const G4Run* run);
    virtual void EndOfRunAction(const G4Run* run);

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
