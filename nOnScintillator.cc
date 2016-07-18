// ********************************************************************
// Neutron Beam simulation
// ********************************************************************
/// \file nOnScintillator.cc
/// \brief Main program of the nOnScintillator

#include "nOnScintillatorDetectorConstruction.hh"
#include "nOnScintillatorActionInitialization.hh"
//#include "G4Scintillation.hh"
#include "G4MTRunManager.hh"


#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "FTFP_BERT.hh"
#include "QGSP_BIC_HP.hh"
#include "QGSP_BIC.hh"
#include "QGSP_BERT.hh"

#include "G4StepLimiterPhysics.hh"

#include "Randomize.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  // Choose the Random engine

  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  
  // Construct the default run manager


//    G4RunManager * runManager = new G4MTRunManager;
    G4MTRunManager * runManager = new G4MTRunManager;
    runManager->SetNumberOfThreads(8);

//    G4RunManager * runManager = new G4RunManager;

  // Set mandatory initialization classes

    runManager->SetUserInitialization(new nOnScintillatorDetectorConstruction());

//    G4VModularPhysicsList* physicsList = new FTFP_BERT;
//    G4VModularPhysicsList* physicsList = new QGSP_BIC_HP;
//    G4VModularPhysicsList* physicsList = new QGSP_BIC;
    G4VModularPhysicsList* physicsList = new QGSP_BERT;

    //ADD Scinitillation
    physicsList->RegisterPhysics(new G4StepLimiterPhysics());
    runManager->SetUserInitialization(physicsList);

    
    
    
  runManager->SetUserInitialization(new nOnScintillatorActionInitialization());
  
  // Initialize G4 kernel

  runManager->Initialize();
  
#ifdef G4VIS_USE
  // Initialize visualization
  G4VisManager* visManager = new G4VisExecutive("Quiet");
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();
#endif

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (argc!=1)   // batch mode
    {
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UImanager->ApplyCommand(command+fileName);
    }
  else
    {  // interactive mode : define UI session
#ifdef G4UI_USE
      G4UIExecutive* ui = new G4UIExecutive(argc, argv);
#ifdef G4VIS_USE
        UImanager->ApplyCommand("/control/execute init_vis.mac");
#else
        UImanager->ApplyCommand("/control/execute init.mac");
#endif
      if (ui->IsGUI())
         UImanager->ApplyCommand("/control/execute gui.mac");
      ui->SessionStart();
      delete ui;
#endif
    }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted
  // in the main() program !

#ifdef G4VIS_USE
  delete visManager;
#endif
  delete runManager;

  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
