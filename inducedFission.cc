//*************************************************************
//*       Code for Fast neutron induced fission fragments     *
//*                                                           *
//*      Abhijit Bhattacharyya  :: NPD :: BARC                *
//*     Jan 21, 2019                                          *
//*    \file inducedfission.cc                                *
//*************************************************************

//  $Id: inducedfission.cc Jan 21, 2019    21:53:15Z   vega $

#include "G4Types.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "Randomize.hh"

#include "fissDetectorConstruction.hh"

#include "fissActionInitialization.hh"


#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

int main( int argc, char** argv) {
  //detect interactive mode (if no arguments) and define UI session
  G4UIExecutive* ui = 0;
  if (argc == 1) ui = new G4UIExecutive(argc,argv);

  //choose the Random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);

  // Construct the default run manager
#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
  G4int nThreads = G4Threading::G4GetNumberOfCores();
  if (argc==3) nThreads = G4UIcommand::ConvertToInt(argv[2]);
  runManager->SetNumberOfThreads(nThreads);
#else
  //my Verbose output class
  //G4VSteppingVerbose::SetInstance(new SteppingVerbose);
  G4RunManager* runManager = new G4RunManager;
#endif

//set mandatory initialization classes
  fissDetectorConstruction* det= new fissDetectorConstruction;
  runManager->SetUserInitialization(det);

  //fissPhysicsList* phys = new fissPhysicsList;
  //runManager->SetUserInitialization(phys);

  runManager->SetUserInitialization(new fissActionInitialization(det));

 //initialize visualization
  G4VisManager* visManager = nullptr;

 // get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (ui)  {
    //interactive mode
    visManager = new G4VisExecutive;
    visManager->Initialize();
    ui->SessionStart();
    delete ui;
  } else  {
    //batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }

 //job termination
  delete visManager;
  delete runManager;
}
