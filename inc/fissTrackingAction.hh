//*************************************************************
//*       Code for Fast neutron induced fission fragments     *
//*                                                           *
//*      Abhijit Bhattacharyya  :: NPD :: BARC                *
//*     Jan 26, 2019                                          *
//*    \file fissTrackingAction.hh                                *
//*************************************************************

//  $Id: fissTrackingAction.hh Jan 26, 2019    11:13:15Z   vega $

#ifndef fissTrackingAction_h
#define fissTrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "fissDetectorConstruction.hh"
#include "fissRun.hh"
#include "fissHistoManager.hh"
#include "G4RunManager.hh"
#include "G4Track.hh"
#include "G4HadronicProcessType.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"

class fissDetectorConstruction;

class fissTrackingAction : public G4UserTrackingAction {
public:
  fissTrackingAction(fissDetectorConstruction*);
  ~fissTrackingAction();

  virtual void PreUserTrackingAction(const G4Track*);
  virtual void PostUserTrackingAction(const G4Track*);

private:
  fissDetectorConstruction* fDetector;
};
#endif
