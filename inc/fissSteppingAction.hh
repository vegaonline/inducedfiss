//*       Code for Fast neutron induced fission fragments     *
//*                                                           *
//*      Abhijit Bhattacharyya  :: NPD :: BARC                *
//*     Jan 25, 2019                                          *
//*    \file fissSteppingAction.hh                                *
//*************************************************************

//  $Id: fissSteppingAction.hh Jan 25, 2019    15:02:15Z   vega $

#ifndef fissSteppingAction_h
#define fissSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "fissDetectorConstruction.hh"
#include "fissRun.hh"
#include "fissEventAction.hh"
#include "fissHistoManager.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "globals.hh"

class fissDetectorConstruction;
class fissEventAction;

class fissSteppingAction : public G4UserSteppingAction {
public:
  fissSteppingAction(fissDetectorConstruction*, fissEventAction*);
  ~fissSteppingAction();

  virtual void UserSteppingAction(const G4Step*);

private:
  fissDetectorConstruction* fDetector;
  fissEventAction* fEventAction;
};
#endif
