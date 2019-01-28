//*************************************************************
//*       Code for Fast neutron induced fission fragments     *
//*                                                           *
//*      Abhijit Bhattacharyya  :: NPD :: BARC                *
//*     Jan 23, 2019                                          *
//*    \file fissSteppingAction.cc                                *
//*************************************************************

//  $Id: fissSteppingAction.cc Jan 26, 2019    00:53:45Z   vega $

#include "fissSteppingAction.hh"

fissSteppingAction::fissSteppingAction(fissDetectorConstruction* det, fissEventAction* event)
: G4UserSteppingAction(), fDetector(det), fEventAction(event) {

}

fissSteppingAction::~fissSteppingAction() {

}

void fissSteppingAction::UserSteppingAction(const G4Step* aStep){
  fissRun* run = static_cast<fissRun*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // which volume ?
  G4LogicalVolume* lVolume = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
  G4int iVol = 0;
  if (lVolume == fDetector->GetLogicTarget())    iVol = 1;
  if (lVolume == fDetector->GetLogicDetector())  iVol = 2;

  // count processes
  const G4StepPoint* endPoint = aStep->GetPostStepPoint();
  const G4VProcess* process = endPoint->GetProcessDefinedStep();
  run->CountProcesses(process, iVol);

  //energy deposit
  G4double edepStep = aStep->GetTotalEnergyDeposit();
  if (edepStep <= 0.0) return;
  G4double time = aStep->GetPreStepPoint()->GetGlobalTime();
  G4double weight = aStep->GetPreStepPoint()->GetWeight();
  fEventAction->AddEdep(iVol, edepStep, time, weight);

  // fill ntuple id = 2
  G4int id = 2;
  if (analysisManager->IsActive()) {
    analysisManager->FillNtupleDColumn(id, 0, edepStep);
    analysisManager->FillNtupleDColumn(id, 1, time/s);
    analysisManager->FillNtupleDColumn(id, 2, weight);
    analysisManager->AddNtupleRow(id);
  }
}
