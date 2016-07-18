// ********************************************************************
// nOnScintillator simulation
// ********************************************************************
/// \file nOnScintillatorTrackerSD.hh
/// \brief Definition of the nOnScintillatorTrackerSD class

#ifndef nOnScintillatorTrackerSD_h
#define nOnScintillatorTrackerSD_h 1

#include "G4VSensitiveDetector.hh"

#include "nOnScintillatorTrackerHit.hh"

#include <vector>

class G4Step;
class G4HCofThisEvent;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/// nOnScintillatorTracker sensitive detector class
///
/// The hits are accounted in hits in ProcessHits() function which is called
/// by Geant4 kernel at each step. A hit is created with each step with non zero 
/// energy deposit.

class nOnScintillatorTrackerSD : public G4VSensitiveDetector
{
  public:
    nOnScintillatorTrackerSD(const G4String& name, 
                const G4String& hitsCollectionName);
    virtual ~nOnScintillatorTrackerSD();
  
    // methods from base class
    virtual void   Initialize(G4HCofThisEvent* hitCollection);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
    virtual void   EndOfEvent(G4HCofThisEvent* hitCollection);

  private:
    nOnScintillatorTrackerHitsCollection* fHitsCollection;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif