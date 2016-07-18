// ********************************************************************
// nOnScintillator simulation
// ********************************************************************
/// \file nOnScintillatorEventAction.hh
/// \brief Definition of the nOnScintillatorEventAction class

#ifndef nOnScintillatorEventAction_h
#define nOnScintillatorEventAction_h 1

#include "G4UserEventAction.hh"
#include "TRandom2.h"

#include "globals.hh"

/// Event action class

class nOnScintillatorEventAction : public G4UserEventAction
{
  public:
    TRandom2 * rand2;
    nOnScintillatorEventAction();
    virtual ~nOnScintillatorEventAction();

    virtual void  BeginOfEventAction(const G4Event* );
    virtual void    EndOfEventAction(const G4Event* );
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
