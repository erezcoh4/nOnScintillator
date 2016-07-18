// ********************************************************************
// nOnScintillator simulation
// ********************************************************************
// $Id: nOnScintillatorDetectorMessenger.cc 69706 2013-05-13 09:12:40Z gcosmo $
// 
/// \file nOnScintillatorDetectorMessenger.cc
/// \brief Implementation of the nOnScintillatorDetectorMessenger class

#include "nOnScintillatorDetectorMessenger.hh"
#include "nOnScintillatorDetectorConstruction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nOnScintillatorDetectorMessenger::nOnScintillatorDetectorMessenger(nOnScintillatorDetectorConstruction* Det)
 : G4UImessenger(),
   fDetectorConstruction(Det)
{
  fnOnScintillatorDirectory = new G4UIdirectory("/nOnScintillator/");
  fnOnScintillatorDirectory->SetGuidance("UI commands specific to this example.");

  fDetDirectory = new G4UIdirectory("/nOnScintillator/det/");
  fDetDirectory->SetGuidance("Detector construction control");

  fTargMatCmd = new G4UIcmdWithAString("/nOnScintillator/det/setTargetMaterial",this);
  fTargMatCmd->SetGuidance("Select Material of the Target.");
  fTargMatCmd->SetParameterName("choice",false);
  fTargMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fChamMatCmd = new G4UIcmdWithAString("/nOnScintillator/det/setChamberMaterial",this);
  fChamMatCmd->SetGuidance("Select Material of the Chamber.");
  fChamMatCmd->SetParameterName("choice",false);
  fChamMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fStepMaxCmd = new G4UIcmdWithADoubleAndUnit("/nOnScintillator/det/stepMax",this);
  fStepMaxCmd->SetGuidance("Define a step max");
  fStepMaxCmd->SetParameterName("stepMax",false);
  fStepMaxCmd->SetUnitCategory("Length");
  fStepMaxCmd->AvailableForStates(G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nOnScintillatorDetectorMessenger::~nOnScintillatorDetectorMessenger()
{
  delete fTargMatCmd;
  delete fChamMatCmd;
  delete fStepMaxCmd;
  delete fnOnScintillatorDirectory;
  delete fDetDirectory;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nOnScintillatorDetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
  if( command == fTargMatCmd )
   { fDetectorConstruction->SetTargetMaterial(newValue);}

  if( command == fChamMatCmd )
   { fDetectorConstruction->SetChamberMaterial(newValue);}

  if( command == fStepMaxCmd ) {
    fDetectorConstruction
      ->SetMaxStep(fStepMaxCmd->GetNewDoubleValue(newValue));
  }   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
