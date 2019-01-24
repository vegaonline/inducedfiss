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
  G4AnalysisManger* analysis = G4AnalysisManager::Instance();
  analysis->SetFileName(fFileName);
  analysis->SetVerboseLevel(1);
  analysis->SetActivation(true); // enable inactivation of histos, nTuples

  G4int nbins = 100;
  G4double vmin = 0.0;
  G4double vmax = 100.0;

  analysis->SetHistoDirectoryName("Histo");
  analysis->SetFirstHistoId(1);
  G4int id = analysis->CreateH1("H10", "Energy deposit (MeV) in the target", nbins, vmin, vmax);
  analysis->SetH1Activation(id, false);

  id = analysis->CreateH1("H11", "Energy deposit (MeV) in the detector", nbins, vmin, vmax);
  analysis->SetH1Activation(id, false);

  id = analysis->CreateH1("H12","Total energy (MeV) in target and detector", nbins, vmin, vmax);
  analysis->SetH1Activation(id, false);

  id = analysis->CreateH1("H13","Coincidence spectrum (MeV) between the target and detector", nbins, vmin, vmax);
  analysis->SetH1Activation(id, false);

  id = analysis->CreateH1("H14","Anti-coincidence spectrum (MeV) in the traget", nbins, vmin, vmax);
  analysis->SetH1Activation(id, false);

   id = analysis->CreateH1("H15","Anti-coincidence spectrum (MeV) in the detector", nbins, vmin, vmax);
  analysis->SetH1Activation(id, false);

  id = analysis->CreateH1("H16","Decay emission spectrum (0 - 10 MeV)", nbins, vmin, vmax);
  analysis->SetH1Activation(id, false);

  id = analysis->CreateH1("H17","Decay emission spectrum (0 - 1 MeV)", nbins, vmin, vmax);
  analysis->SetH1Activation(id, false);

  id = analysis->CreateH1("H18","Decay emission spectrum (0 - 0.1 MeV)", nbins, vmin, vmax);
  analysis->SetH1Activation(id, false);

  // nTuples
  //
  analysis->SetNtupleDirectoryName("nTuple");
  analysis->SetFirstNtupleId(1);
  analysis->CreateNtuple("T1", "Emitted Particles");
  analysis->CreateNtupleDColumn("PID");       //column 0
  analysis->CreateNtupleDColumn("Energy");    //column 1
  analysis->CreateNtupleDColumn("Time");      //column 2
  analysis->CreateNtupleDColumn("Weight");    //column 3
  analysis->FinishNtuple();

  analysis->CreateNtuple("T2", "RadioIsotopes");
  analysis->CreateNtupleDColumn("PID");       //column 0
  analysis->CreateNtupleDColumn("Time");      //column 1
  analysis->CreateNtupleDColumn("Weight");    //column 2
  analysis->FinishNtuple();

  analysis->CreateNtuple("T3", "Energy depositions");
  analysis->CreateNtupleDColumn("Energy");    //column 0
  analysis->CreateNtupleDColumn("Time");      //column 1
  analysis->CreateNtupleDColumn("Weight");    //column 2
  analysis->FinishNtuple();

  analysis->CreateNtuple("RDecayProducts", "All Products of RDecay");
  analysis->CreateNtupleDColumn("PID");       //column 0
  analysis->CreateNtupleDColumn("Z");         //column 1
  analysis->CreateNtupleDColumn("A");         //column 2
  analysis->CreateNtupleDColumn("Energy");    //column 3
  analysis->CreateNtupleDColumn("Time");      //column 4
  analysis->CreateNtupleDColumn("Weight");    //column 5
  analysis->FinishNtuple();

  analysis->SetNtupleActivation(false);

}
