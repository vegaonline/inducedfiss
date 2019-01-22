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
#include "fissPhysicsList.hh"
#include "fissPrimaryGeneratorAction.hh"
#include "fissActionInitialization.hh"


#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

void PrintUsage() {
  G4cerr << G4endl;
  G4cerr << "Usage: inducedFission [-m macro] [-u UIsession] [-t nThreads] " << G4endl;
  G4cerr << "\t \t Here -t option is available for multithreaded mode only." << G4endl;
}

int main( int argc, char** argv) {
  G4String macro;
  G4String session;
  G4int nThreads;
  
  if (argc < 1 || argc > 7){
    PrintUsage();
    return -1;
  }

  //choose the Random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);

#ifdef G4MULTITHREADED
  nThreads = G4Threading::G4GetNumberOfCores();
#endif


  for (G4int i = 1; i < argc; i += 2) {
    G4String inArg = G4String (argv[i]);
    if (inArg == "-m") macro = argv[i + 1];
    if (inArg == "-u" ) session = argv[i + 1];
  // Construct the default run manager
#ifdef G4MULTITHREADED
    if (inArg == "-t") nThreads = (G4String(argv[i+1]) == "NMAX")
                                      ?  G4Threading::G4GetNumberOfCores()
                                      : G4UIcommand::ConvertToInt(argv[i + 1]);
#endif
    if (inArg != "-m" && inArg != "-u" && inArg != "-t"){
      PrintUsage();
      return -1;
    }
  }

#ifdef G4MULTITHREADED
  auto runManager = new G4MTRunManager;
  if (nThreads > 0) runManager->SetNumberOfThreads(nThreads);
#else
  //my Verbose output class
  //G4VSteppingVerbose::SetInstance(new SteppingVerbose);
  auto runManager = new G4RunManager;
#endif

//set mandatory initialization classes
  fissDetectorConstruction* det= new fissDetectorConstruction;
  runManager->SetUserInitialization(det);

  fissPhysicsList* phys = new fissPhysicsList;
  runManager->SetUserInitialization(phys);

  runManager->SetUserInitialization(new fissActionInitialization(det));

  runManager->Initialize();

 //initialize visualization
  auto visManager = new G4VisExecutive;
  visManager->Initialize();

 // get the pointer to the User Interface manager
  auto UImanager = G4UImanager::GetUIpointer();

  if (macro.size()){
    // batch mode
    G4String command = "/control/execute ";
    UImanager->ApplyCommand(command + macro);
  } else {
    UImanager->ApplyCommand("/control/execute vis.mac");
#ifdef G4UI_USE
    G4UIExecutive* ui = new G4UIExecutive(argc, argv, session);
#endif
    ui->SessionStart();
    delete ui;
  }

  G4GeometryManager::GetInstance()->OpenGeometry();
  //termination of job
#ifdef G4VIS_USE
  delete visManager;
  G4cout << "Vis manager deleted" << G4endl;
#endif
  //delete runManager;
  //G4cout << "run manager deleted" << G4endl;
  return 0;
}
