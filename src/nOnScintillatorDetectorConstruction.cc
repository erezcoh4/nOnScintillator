// ********************************************************************
// nOnScintillator simulation
// ********************************************************************
/// \file nOnScintillatorDetectorConstruction.cc
/// \brief Implementation of the nOnScintillatorDetectorConstruction class

#include "nOnScintillatorDetectorConstruction.hh"
#include "nOnScintillatorDetectorMessenger.hh"
#include "nOnScintillatorTrackerSD.hh"

#include "G4Material.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4NistManager.hh"

#include "G4Sphere.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"

#include "G4UserLimits.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4UnitsTable.hh"

#include "G4SystemOfUnits.hh"



#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSDoseDeposit.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal
G4GlobalMagFieldMessenger* nOnScintillatorDetectorConstruction::fMagFieldMessenger = 0;

nOnScintillatorDetectorConstruction::nOnScintillatorDetectorConstruction()
:G4VUserDetectorConstruction(),
fNbOfChambers(0),
fLogicTarget(NULL), fLogicChamber(NULL),
fTargetMaterial(NULL), fChamberMaterial(NULL),
fStepLimit(NULL),
fCheckOverlaps(true){
    fMessenger = new nOnScintillatorDetectorMessenger(this);
    
    fNbOfChambers = 5;
    fLogicChamber = new G4LogicalVolume*[fNbOfChambers];
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
nOnScintillatorDetectorConstruction::~nOnScintillatorDetectorConstruction(){
    delete [] fLogicChamber;
    delete fStepLimit;
    delete fMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4VPhysicalVolume* nOnScintillatorDetectorConstruction::Construct(){
    // Define materials
    DefineMaterials();
    
    // Define volumes
    return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nOnScintillatorDetectorConstruction::DefineMaterials(){
    // Material definition
    
    G4NistManager* man = G4NistManager::Instance();
    
    
    // Define StainlessSteel not in NIST, following http://hypernews.slac.stanford.edu/HyperNews/geant4/get/geometry/915.html?inline=1
    G4Element* C  = man->FindOrBuildElement("C");
    G4Element* Si = man->FindOrBuildElement("Si");
    G4Element* Cr = man->FindOrBuildElement("Cr");
    G4Element* Mn = man->FindOrBuildElement("Mn");
    G4Element* Fe = man->FindOrBuildElement("Fe");
    G4Element* Ni = man->FindOrBuildElement("Ni");
    
    G4Material* StainlessSteel = new G4Material( "StainlessSteel", 8.06*g/cm3, 6 );
    StainlessSteel->AddElement(C, 0.001);
    StainlessSteel->AddElement(Si, 0.007);
    StainlessSteel->AddElement(Cr, 0.18);
    StainlessSteel->AddElement(Mn, 0.01);
    StainlessSteel->AddElement(Fe, 0.712);
    StainlessSteel->AddElement(Ni, 0.09);
    
    G4Material* Air = man->FindOrBuildMaterial("G4_AIR");
    G4Material* vacuum = new G4Material("Vacuum", 1.e-25*g/cm3, 1, kStateGas, 2.e-2*bar, CLHEP::STP_Temperature);
    vacuum -> AddMaterial(Air, 1.);
    
    
    
    // Print materials
    G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* nOnScintillatorDetectorConstruction::DefineVolumes(){
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* vacuum          = nist->FindOrBuildMaterial("Vacuum");
    G4Material* default_mat     = nist->FindOrBuildMaterial("G4_AIR");
    G4Material* SS_mat          = nist->FindOrBuildMaterial("StainlessSteel");
    G4Material* LeadWall_mat    = nist->FindOrBuildMaterial("G4_Pb");
    G4Material* BAND_mat        = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    
    bool DoTarget           = false;
    bool DoBandAsFullCircle = true;
    bool DoBandAsProposed   = !DoBandAsFullCircle;
    
    
    //--------- World --------------//
    G4double worldXYZ =  8000.*cm;
    G4Box* solidWorld = new G4Box("World", 0.5*worldXYZ, 0.5*worldXYZ, 0.5*worldXYZ );
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, vacuum, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld,  "World", 0,  false,  0, fCheckOverlaps);
    
    
    
   
    G4double RinDetector,  RoutDetector;
    G4double BANDThickness = 5.*cm;
    if (DoBandAsFullCircle){
        //--------- Full circle Detector for scattering angle --------------//
        RinDetector = 0.*cm;  RoutDetector = 2.*m;
    }
    if (DoBandAsProposed){
        //--------- BAND proposed Detector ---------------------------------//
        RinDetector = 612.*mm;  RoutDetector = 1292.;
    }
    G4Tubs* solidDetector = new G4Tubs("Detector", RinDetector , RoutDetector , BANDThickness/2. , 0., CLHEP::twopi);
    G4LogicalVolume* logicDetector = new G4LogicalVolume(solidDetector,BAND_mat,"DetectorLV");
    new G4PVPlacement(0,G4ThreeVector(0,0,3304*mm+BANDThickness/2.),logicDetector, "Detector",logicWorld, false,  0, fCheckOverlaps);
    G4Colour Detec_Color( 0.75 , 0.6 , 0.75 );
    G4VisAttributes* DetecVisAttributes = new G4VisAttributes( true , Detec_Color );
    logicDetector -> SetVisAttributes(DetecVisAttributes);
    
    
    
    // Always return the physical world
    return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nOnScintillatorDetectorConstruction::ConstructSDandField()
{
    
    
    
    // Neutron Scorrer
//    G4MultiFunctionalDetector* NeutonScorrer = new G4MultiFunctionalDetector("NeutonScorrer");
//    G4VPrimitiveScorer* primitiv1 = new G4PSEnergyDeposit("edep");
//    NeutonScorrer -> RegisterPrimitive(primitiv1);
//    SetSensitiveDetector("DetectorLV" , NeutonScorrer);
//    
    
    
    
    // Sensitive detectors
    G4String trackerChamberSDname = "Detector/TrackerChamberSD";
    nOnScintillatorTrackerSD* aTrackerSD = new nOnScintillatorTrackerSD(trackerChamberSDname,"TrackerHitsCollection");
    SetSensitiveDetector("DetectorLV" , aTrackerSD , true);

    
    
    
    G4ThreeVector fieldValue = G4ThreeVector();
    
    // Register the field messenger for deleting
    
    G4AutoDelete::Register(fMagFieldMessenger);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nOnScintillatorDetectorConstruction::SetTargetMaterial(G4String materialName)
{
    G4NistManager* nistManager = G4NistManager::Instance();
    
    G4Material* pttoMaterial =
    nistManager->FindOrBuildMaterial(materialName);
    
    if (fTargetMaterial != pttoMaterial) {
        if ( pttoMaterial ) {
            fTargetMaterial = pttoMaterial;
            if (fLogicTarget) fLogicTarget->SetMaterial(fTargetMaterial);
            //        G4cout << "\n----> The target is made of " << materialName << G4endl;
        } else {
            //        G4cout << "\n-->  WARNING from SetTargetMaterial : "
            //               << materialName << " not found" << G4endl;
        }
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nOnScintillatorDetectorConstruction::SetChamberMaterial(G4String materialName)
{
    G4NistManager* nistManager = G4NistManager::Instance();
    
    G4Material* pttoMaterial =
    nistManager->FindOrBuildMaterial(materialName);
    
    if (fChamberMaterial != pttoMaterial) {
        if ( pttoMaterial ) {
            fChamberMaterial = pttoMaterial;
            for (G4int copyNo=0; copyNo<fNbOfChambers; copyNo++) {
                if (fLogicChamber[copyNo]) fLogicChamber[copyNo]->
                    SetMaterial(fChamberMaterial);
            }
            //        G4cout << "\n----> The chambers are made of " << materialName << G4endl;
        } else {
            //        G4cout << "\n-->  WARNING from SetChamberMaterial : "
            //               << materialName << " not found" << G4endl;
        }
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nOnScintillatorDetectorConstruction::SetMaxStep(G4double maxStep)
{
    if ((fStepLimit)&&(maxStep>0.)) fStepLimit->SetMaxAllowedStep(maxStep);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nOnScintillatorDetectorConstruction::SetCheckOverlaps(G4bool checkOverlaps)
{
    fCheckOverlaps = checkOverlaps;
}  
