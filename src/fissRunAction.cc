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
  : G4UserRunAction(), fDetector(det), fPrimary(fprim){

}

fissRunAction::~fissRunAction() {

}

G4Run* fissRunAction::GenerateRun(){
return 0;
}

void fissRunAction::BeginOfRunAction(const G4Run*) {
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  if (isMaster) G4Random::showEngineStatus();

  if (fPrimary){
    G4ParticleDefinition* particle = fPrimary->GetParticleGun()->GetParticleDefinition();
    G4double energy = fPrimary->GetParticleGun()->GetParticleEnergy();
  }
}

void fissRunAction::EndOfRunAction(const G4Run*){
  if (isMaster) G4Random::showEngineStatus();
}
