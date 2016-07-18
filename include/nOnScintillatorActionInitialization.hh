// ********************************************************************
// nOnScintillator simulation
// ********************************************************************
/// \file nOnScintillatorActionInitialization.hh
/// \brief Definition of the nOnScintillatorActionInitialization class

#ifndef nOnScintillatorActionInitialization_h
#define nOnScintillatorActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class B4DetectorConstruction;

/// Action initialization class.
///

class nOnScintillatorActionInitialization : public G4VUserActionInitialization
{
  public:
    nOnScintillatorActionInitialization();
    virtual ~nOnScintillatorActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif

    
