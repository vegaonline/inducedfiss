//*************************************************************
//*       Code for Fast neutron induced fission fragments     *
//*                                                           *
//*      Abhijit Bhattacharyya  :: NPD :: BARC                *
//*     Jan 23, 2019                                          *
//*    \file fissTrackingAction.cc                                *
//*************************************************************

//  $Id: fissTrackingAction.cc Jan 26, 2019    11:53:45Z   vega $

#include "fissTrackingAction.hh"

fissTrackingAction::fissTrackingAction(fissDetectorConstruction* det)
  : G4UserTrackingAction(), fDetector(det) {

}

fissTrackingAction::~fissTrackingAction(){

}


void fissTrackingAction::PreUserTrackingAction(const G4Track* track) {
  fissRun* run =  static_cast<fissRun*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // which volume ?
  G4LogicalVolume* lVolume = track->GetVolume()->GetLogicalVolume();
  G4int iVol = 0;
  if (lVolume == fDetector->GetLogicTarget())   iVol = 1;
  if (lVolume == fDetector->GetLogicDetector()) iVol = 2;

  if (track->GetTrackID() == 1) return;   // secondary particles only

  const G4ParticleDefinition* particle = track->GetParticleDefinition();
  G4String name   = particle->GetParticleName();
  G4int pid       = particle->GetPDGEncoding();
  G4int Z         = particle->GetAtomicNumber();
  G4int A         = particle->GetAtomicMass();
  G4double charge = particle->GetPDGCharge();
  G4double energy = track->GetKineticEnergy();
  G4double time   = track->GetGlobalTime();
  G4double weight = track->GetWeight();

  run->ParticleCount(name, energy, iVol);

  G4int id = 0;
  // RadioActive decay products
  G4int processType = track->GetCreatorProcess()->GetProcessSubType();
  if (processType == fRadioactiveDecay) {
    // fill ntuple id = 3
    if (analysisManager->IsActive()) {
      id = 3;
      analysisManager->FillNtupleDColumn(id, 0, double(pid));
      analysisManager->FillNtupleDColumn(id, 1, double(Z));
      analysisManager->FillNtupleDColumn(id, 2, double(A));
      analysisManager->FillNtupleDColumn(id, 3, energy);
      analysisManager->FillNtupleDColumn(id, 4, time/s);
      analysisManager->FillNtupleDColumn(id, 5, weight);
      analysisManager->AddNtupleRow(id);

      if (charge < 3.0) {
        // fill ntuple id = 0
        id = 0;
        analysisManager->FillNtupleDColumn(id, 0, double(pid));
        analysisManager->FillNtupleDColumn(id, 1, energy);
        analysisManager->FillNtupleDColumn(id, 2, time/s);
        analysisManager->FillNtupleDColumn(id, 3, weight);
        analysisManager->AddNtupleRow(id);

        analysisManager->FillH1(6, energy, weight);
        analysisManager->FillH1(7, energy, weight);
        analysisManager->FillH1(8, energy, weight);
      }
    }
  }

  // all unstable ions produced in target
  G4bool unstableIon = ((charge > 2.0) && ( !(particle->GetPDGStable())));
  if ((unstableIon) && (iVol == 1)) {
    // fill nTuple ID = 1
    if (analysisManager->IsActive()) {
      id = 1;
      analysisManager->FillNtupleDColumn(id, 0, double(pid));
      analysisManager->FillNtupleDColumn(id, 1, time/s);
      analysisManager->FillNtupleDColumn(id, 2, weight);
      analysisManager->AddNtupleRow(id);
    }
  }
}


void fissTrackingAction::PostUserTrackingAction(const G4Track*) {

}
