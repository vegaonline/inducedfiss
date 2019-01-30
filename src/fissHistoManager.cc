//*************************************************************
//*       Code for Fast neutron induced fission fragments     *
//*                                                           *
//*      Abhijit Bhattacharyya  :: NPD :: BARC                *
//*     Jan 24, 2019                                          *
//*    \file fissHistoManager.cc                                *
//*************************************************************

//  $Id: fissHistoManager.cc Jan 24, 2019    14:00:45Z   vega $

#include "fissHistoManager.hh"

fissHistoManager::fissHistoManager() : fFileName("inducedFiss"){
  Book();
}

fissHistoManager::~fissHistoManager(){
  delete G4AnalysisManager::Instance();
}

void fissHistoManager::Book() {
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetNtupleMerging(true, 0, false); // row-wise saving mode
  analysisManager->SetVerboseLevel(0);
  analysisManager->SetFileName(fFileName);
  analysisManager->SetActivation(true); // enable inactivation of histos, nTuples

  G4int nbins = 100;
  G4double vmin = 0.0;
  G4double vmax = 100.0;

  analysisManager->SetHistoDirectoryName("Histo");
  //analysisManager->SetFirstHistoId(1);
  //analysisManager->CreateH1("H10", "Energy deposit (MeV) in the target", nbins, vmin, vmax);
  G4int id = analysisManager->CreateH1("H10", "Energy deposit (MeV) in the target", nbins, vmin, vmax);
  analysisManager->SetH1Activation(id, false);

  //analysisManager->CreateH1("H11", "Energy deposit (MeV) in the detector", nbins, vmin, vmax);
  id = analysisManager->CreateH1("H11", "Energy deposit (MeV) in the detector", nbins, vmin, vmax);
  analysisManager->SetH1Activation(id, false);

  //analysisManager->CreateH1("H12","Total energy (MeV) in target and detector", nbins, vmin, vmax);
  id = analysisManager->CreateH1("H12","Total energy (MeV) in target and detector", nbins, vmin, vmax);
  analysisManager->SetH1Activation(id, false);

  //analysisManager->CreateH1("H13","Coincidence spectrum (MeV) between the target and detector", nbins, vmin, vmax);
  id = analysisManager->CreateH1("H13","Coincidence spectrum (MeV) between the target and detector", nbins, vmin, vmax);
  analysisManager->SetH1Activation(id, false);

  //analysisManager->CreateH1("H14","Anti-coincidence spectrum (MeV) in the traget", nbins, vmin, vmax);
  id = analysisManager->CreateH1("H14","Anti-coincidence spectrum (MeV) in the traget", nbins, vmin, vmax);
  analysisManager->SetH1Activation(id, false);

  //analysisManager->CreateH1("H15","Anti-coincidence spectrum (MeV) in the detector", nbins, vmin, vmax);
  id = analysisManager->CreateH1("H15","Anti-coincidence spectrum (MeV) in the detector", nbins, vmin, vmax);
  analysisManager->SetH1Activation(id, false);

  //analysisManager->CreateH1("H16","Decay emission spectrum (0 - 10 MeV)", nbins, vmin, vmax);
  id = analysisManager->CreateH1("H16","Decay emission spectrum (0 - 10 MeV)", nbins, vmin, vmax);
  analysisManager->SetH1Activation(id, false);

  //analysisManager->CreateH1("H17","Decay emission spectrum (0 - 1 MeV)", nbins, vmin, vmax);
  id = analysisManager->CreateH1("H17","Decay emission spectrum (0 - 1 MeV)", nbins, vmin, vmax);
  analysisManager->SetH1Activation(id, false);

  //analysisManager->CreateH1("H18","Decay emission spectrum (0 - 0.1 MeV)", nbins, vmin, vmax);
  id = analysisManager->CreateH1("H18","Decay emission spectrum (0 - 0.1 MeV)", nbins, vmin, vmax);
  analysisManager->SetH1Activation(id, false);

  // nTuples
  //
  analysisManager->SetNtupleDirectoryName("nTuple");
  //analysisManager->SetFirstNtupleId(1);
  analysisManager->CreateNtuple("T1", "Emitted Particles");
  analysisManager->CreateNtupleDColumn("PID");       //column 0
  analysisManager->CreateNtupleDColumn("Energy");    //column 1
  analysisManager->CreateNtupleDColumn("Time");      //column 2
  analysisManager->CreateNtupleDColumn("Weight");    //column 3
  analysisManager->FinishNtuple();

  analysisManager->CreateNtuple("T2", "RadioIsotopes");
  analysisManager->CreateNtupleDColumn("PID");       //column 0
  analysisManager->CreateNtupleDColumn("Time");      //column 1
  analysisManager->CreateNtupleDColumn("Weight");    //column 2
  analysisManager->FinishNtuple();

  analysisManager->CreateNtuple("T3", "Energy depositions");
  analysisManager->CreateNtupleDColumn("Energy");    //column 0
  analysisManager->CreateNtupleDColumn("Time");      //column 1
  analysisManager->CreateNtupleDColumn("Weight");    //column 2
  analysisManager->FinishNtuple();

  analysisManager->CreateNtuple("RDecayProducts", "All Products of RDecay");
  analysisManager->CreateNtupleDColumn("PID");       //column 0
  analysisManager->CreateNtupleDColumn("Z");         //column 1
  analysisManager->CreateNtupleDColumn("A");         //column 2
  analysisManager->CreateNtupleDColumn("Energy");    //column 3
  analysisManager->CreateNtupleDColumn("Time");      //column 4
  analysisManager->CreateNtupleDColumn("Weight");    //column 5
  analysisManager->FinishNtuple();

  analysisManager->SetNtupleActivation(false);

}
