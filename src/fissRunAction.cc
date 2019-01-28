//*************************************************************
//*       Code for Fast neutron induced fission fragments     *
//*                                                           *
//*      Abhijit Bhattacharyya  :: NPD :: BARC                *
//*     Jan 23, 2019                                          *
//*    \file fissRunAction.cc                                *
//*************************************************************

//  $Id: fissRunAction.cc Jan 23, 2019    11:10:45Z   vega $

#include "fissRunAction.hh"

fissRunAction::fissRunAction(fissDetectorConstruction* det, fissPrimaryGeneratorAction* fprim)
  : G4UserRunAction(), fDetector(det), fPrimary(fprim), fHistoManager(0){
    fHistoManager = new fissHistoManager();
}

fissRunAction::~fissRunAction() {
  delete fHistoManager;
}

G4Run* fissRunAction::GenerateRun(){
  fRun = new fissRun(fDetector);
  return fRun;
}

void fissRunAction::BeginOfRunAction(const G4Run*) {
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  if (isMaster) G4Random::showEngineStatus();

  if (fPrimary){
    G4ParticleDefinition* particle = fPrimary->GetParticleGun()->GetParticleDefinition();
    G4double energy = fPrimary->GetParticleGun()->GetParticleEnergy();
    fRun->SetPrimary(particle, energy);
  }

  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  if (analysisManager->IsActive()) analysisManager->OpenFile();
}

void fissRunAction::EndOfRunAction(const G4Run*){
  if (isMaster) fRun->EndOfRun();
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  if (analysisManager-> IsActive()){
    analysisManager->Write();
    analysisManager->CloseFile();
  }
  if (isMaster) G4Random::showEngineStatus();
}
