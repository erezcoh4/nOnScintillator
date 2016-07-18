// ********************************************************************
// nOnScintillator simulation
// ********************************************************************
/// \file nOnScintillatorDetectorMessenger.hh
/// \brief Definition of the nOnScintillatorDetectorMessenger class

#ifndef nOnScintillatorDetectorMessenger_h
#define nOnScintillatorDetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class nOnScintillatorDetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/// Messenger class that defines commands for nOnScintillatorDetectorConstruction.
///
/// It implements commands:
/// - /nOnScintillator/det/setTargetMaterial name
/// - /nOnScintillator/det/setChamberMaterial name
/// - /nOnScintillator/det/stepMax value unit

class nOnScintillatorDetectorMessenger: public G4UImessenger
{
  public:
    nOnScintillatorDetectorMessenger(nOnScintillatorDetectorConstruction* );
    virtual ~nOnScintillatorDetectorMessenger();
    
    virtual void SetNewValue(G4UIcommand*, G4String);
    
  private:
    nOnScintillatorDetectorConstruction*  fDetectorConstruction;

    G4UIdirectory*           fnOnScintillatorDirectory;
    G4UIdirectory*           fDetDirectory;

    G4UIcmdWithAString*      fTargMatCmd;
    G4UIcmdWithAString*      fChamMatCmd;

    G4UIcmdWithADoubleAndUnit* fStepMaxCmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
