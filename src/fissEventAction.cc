//*************************************************************
//*       Code for Fast neutron induced fission fragments     *
//*                                                           *
//*      Abhijit Bhattacharyya  :: NPD :: BARC                *
//*     Jan 24, 2019                                          *
//*    \file fissEventAction.cc                                *
//*************************************************************

//  $Id: fissEventAction.cc Jan 24, 2019    14:00:45Z   vega $

#include "fissEventAction.hh"

fissEventAction::fissEventAction(): G4UserEventAction(), fEdep1(0.0), fEdep2(0.0), fWeight1(0.0), fWeight2(0.0), fTime0(-1*s){

}

fissEventAction::~fissEventAction(){

}

void fissEventAction::BeginOfEventAction(const G4Event*){
  fEdep1 = fEdep2 = fWeight1 = fWeight2 = 0.0;
  fTime0 = -1.0*s;
}

void fissEventAction::AddEdep(G4int iVol, G4double edep, G4double time, G4double weight) {
  if (fTime0 < 0.0) fTime0 = time;

  const G4double TimeWindow (1.0*microsecond);     // out of time window ?
  if (std::fabs(time - fTime0) > TimeWindow) return;

  if (iVol == 1) { fEdep1 += edep; fWeight1 += edep * weight; }
  if (iVol == 2) { fEdep2 += edep; fWeight2 += edep * weight; }
}

void fissEventAction::EndOfEventAction(const G4Event*) {
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4double Etot = fEdep1 + fEdep2;
  G4double Wtot = (fWeight1 + fWeight2) / Etot;

  if (fEdep1 > 0.0) {   // Pulse Height in Target
      fWeight1 /= fEdep1;
      analysisManager->FillH1(0, fEdep1, fWeight1);
  }
  if (fEdep2 > 0.0) {   // Pulse Height in Detector
    fWeight2 /= fEdep2;
    analysisManager->FillH1(1, fEdep2, fWeight2);
  }

  analysisManager->FillH1(2, Etot, Wtot);   // Total
  const G4double  Threshold1(10*keV), Threshold2(10*keV); // Threshold for target & detector CHECK ?????

  // COINCIDENCE and anti-COINCIDENCE OK ?
  G4bool coincidence       = ((fEdep1 >= Threshold1) && (fEdep2 >= Threshold2));
  G4bool anti_coincidence1 = ((fEdep1 >= Threshold1) && (fEdep2 <  Threshold2));
  G4bool anti_coincidence2 = ((fEdep1 <  Threshold1) && (fEdep2 >=  Threshold2));
  if (coincidence)       analysisManager->FillH1(3, fEdep2, fWeight2);
  if (anti_coincidence1) analysisManager->FillH1(4, fEdep1, fWeight1);
  if (anti_coincidence2) analysisManager->FillH1(5, fEdep2, fWeight2);

  fissRun* fissrun = static_cast<fissRun*> (G4RunManager::GetRunManager()->GetNonConstCurrentRun());
  fissrun->AddEdep(fEdep1, fEdep2);
}
