// ********************************************************************
// nOnScintillator simulation
// ********************************************************************
/// \file nOnScintillatorTrackerHit.hh
/// \brief Definition of the nOnScintillatorTrackerHit class

#ifndef nOnScintillatorTrackerHit_h
#define nOnScintillatorTrackerHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"


class nOnScintillatorTrackerHit : public G4VHit
{
public:
    nOnScintillatorTrackerHit();
    nOnScintillatorTrackerHit(const nOnScintillatorTrackerHit&);
    virtual ~nOnScintillatorTrackerHit();
    
    // operators
    const nOnScintillatorTrackerHit& operator=(const nOnScintillatorTrackerHit&);
    G4int operator==(const nOnScintillatorTrackerHit&) const;
    
    inline void* operator new(size_t);
    inline void  operator delete(void*);
    
    // methods from base class
    virtual void Draw();
    virtual void Print();
    
    // Set methods
    void SetTrackID         (G4int track)       { fTrackID = track; };
    void SetChamberNb       (G4int chamb)       { fChamberNb = chamb; };
    void SetEdep            (G4double de)       { fEdep = de; };
    void SetPos             (G4ThreeVector xyz) { fPos = xyz; };
    void SetTotalEnergy     (G4double e_tot)    { fTotalEnergy = e_tot; };
    void SetParticleCode    (G4int p_code)      { fParticleCode = p_code; };
    void SetParticleName    (G4String p_name)   { fParticleName = p_name; };
    void SetKineticEnergy   (G4int e_kin)       { fKineticEnergy = e_kin; };
    void SetMomentum        (G4double p_momen)  { fMomentum = p_momen; };
    void SetTheta           (G4double p_theta)  { fTheta = p_theta; };
    void SetHitTime         (G4double hit_time) { fHitTime = hit_time; };
    
    // Get methods
    G4int GetTrackID()          const { return fTrackID; };
    G4int GetChamberNb()        const { return fChamberNb; };
    G4double GetEdep()          const { return fEdep; };
    G4ThreeVector GetPos()      const { return fPos; };
    G4double GetTotalEnergy()   const { return fTotalEnergy; };
    G4double GetKineticEnergy() const { return fKineticEnergy; };
    G4double GetMomentum()      const { return fMomentum; };
    G4double GetTheta()         const { return fTheta; };
    G4double GetX()             const { return fPos.x(); };
    G4double GetY()             const { return fPos.y(); };
    G4double GetZ()             const { return fPos.z(); };
    G4String GetParticleName()  const { return fParticleName; };
    G4int GetParticleCode()     const { return fParticleCode; };
    G4double GetHitTime()       const { return fHitTime; };
    
private:
    
    G4int         fTrackID;
    G4double      fEdep;
    G4ThreeVector fPos;
    G4double      fTotalEnergy;
    G4double      fKineticEnergy;
    G4double      fMomentum;
    G4int         fParticleCode;
    G4String      fParticleName;
    G4int         fChamberNb;
    G4double      fTheta;
    G4double      fX;
    G4double      fY;
    G4double      fZ;
    G4double      fHitTime;
    };

    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    
    typedef G4THitsCollection<nOnScintillatorTrackerHit> nOnScintillatorTrackerHitsCollection;
    
    extern G4ThreadLocal G4Allocator<nOnScintillatorTrackerHit>* nOnScintillatorTrackerHitAllocator;
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    
    inline void* nOnScintillatorTrackerHit::operator new(size_t)
    {
        if(!nOnScintillatorTrackerHitAllocator)
            nOnScintillatorTrackerHitAllocator = new G4Allocator<nOnScintillatorTrackerHit>;
        return (void *) nOnScintillatorTrackerHitAllocator->MallocSingle();
    }
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    
    inline void nOnScintillatorTrackerHit::operator delete(void *hit)
    {
        nOnScintillatorTrackerHitAllocator->FreeSingle((nOnScintillatorTrackerHit*) hit);
    }
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    
#endif
