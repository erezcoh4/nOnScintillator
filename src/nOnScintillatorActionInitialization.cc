// ********************************************************************
// nOnScintillator simulation
// ********************************************************************
/// \file nOnScintillatorActionInitialization.cc
/// \brief Implementation of the nOnScintillatorActionInitialization class

#include "nOnScintillatorActionInitialization.hh"
#include "nOnScintillatorPrimaryGeneratorAction.hh"
#include "nOnScintillatorRunAction.hh"
#include "nOnScintillatorEventAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nOnScintillatorActionInitialization::nOnScintillatorActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nOnScintillatorActionInitialization::~nOnScintillatorActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nOnScintillatorActionInitialization::BuildForMaster() const
{
  SetUserAction(new nOnScintillatorRunAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nOnScintillatorActionInitialization::Build() const
{
  SetUserAction(new nOnScintillatorPrimaryGeneratorAction);
  SetUserAction(new nOnScintillatorRunAction);
  SetUserAction(new nOnScintillatorEventAction);
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
