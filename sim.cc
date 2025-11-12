#include <iostream>

#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "construction.hh"
#include "physics.hh"
#include "action.hh"
int main(int argc, char** argv)
{
    // Create run manager first
    // #ifdef G4MULTITHREADED
    //     G4MTRunManager *runManager = new G4MTRunManager;
    // #else
    G4RunManager *runManager = new G4RunManager;
    // #endif
    
    // 
    DetectorConstruction* detectorConstruction = new DetectorConstruction();
    // Choose material: 0=LXe, 1=NaI_pure, 2=NaI(Tl), 3=CsI_pure, 4=CsI(Tl), 
    // 5=PbWO4, 6=BGO, 7=CeBr3, 8=LYSO, 9=MyMade
    detectorConstruction->SetMaterial(9); 
    detectorConstruction->SetCrystalZ(20.0*mm);


    runManager->SetUserInitialization(detectorConstruction);
    // Set physics list
    runManager->SetUserInitialization(new Physics());
    // Set action initialization
    runManager->SetUserInitialization(new ActionInitialization());
    // Initialize the run manager
    runManager->Initialize();

    // User Interface
    G4UIExecutive *ui = new G4UIExecutive(argc,argv);
    // Visualization manager
    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();
    // Ui manager
    G4UImanager *UImanager = G4UImanager::GetUIpointer();

    // Initialize visualization with proper sequence
    UImanager->ApplyCommand("/vis/open OGL");  // Open OpenGL viewer first
    UImanager->ApplyCommand("/vis/viewer/set/autoRefresh false");
    UImanager->ApplyCommand("/vis/drawVolume");
    UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 1 1");
    UImanager->ApplyCommand("/vis/viewer/set/lightsVector 1 1 1");
    UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
    UImanager->ApplyCommand("/vis/scene/add/axes 0 0 0 50 mm");  // Add XYZ axes at origin with 50mm length
    UImanager->ApplyCommand("/vis/modeling/trajectories/create/drawByParticleID");
    UImanager->ApplyCommand("/vis/modeling/trajectories/drawByParticleID-0/set gamma green");
    UImanager->ApplyCommand("/vis/modeling/trajectories/drawByParticleID-0/set e- red");
    UImanager->ApplyCommand("/vis/modeling/trajectories/drawByParticleID-0/set e+ blue");
    UImanager->ApplyCommand("/vis/modeling/trajectories/drawByParticleID-0/set opticalphoton yellow");
    UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");
    UImanager->ApplyCommand("/tracking/storeTrajectory 1");
    UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");
    UImanager->ApplyCommand("/tracking/verbose 1");

    // Fire one event so geometry is visible
    // UImanager->ApplyCommand("/run/beamOn 1");
    
    ui->SessionStart();
    
    return 0;
}