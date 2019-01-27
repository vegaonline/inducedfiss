//*************************************************************
//*       Code for Fast neutron induced fission fragments     *
//*                                                           *
//*      Abhijit Bhattacharyya  :: NPD :: BARC                *
//*     Jan 22, 2019                                          *
//*    \file fissActionInitialization.cc                                *
//*************************************************************

//  $Id: fissActionInitialization.cc Jan 22, 2019    12:06:45Z   vega $

#include "fissActionInitialization.hh"

fissActionInitialization::fissActionInitialization(fissDetectorConstruction* detector)
 : G4VUserActionInitialization(), fDetector(detector){

}

fissActionInitialization::~fissActionInitialization() {

}

void fissActionInitialization::BuildForMaster() const {
  fissRunAction* runAction = new fissRunAction(fDetector, 0);
  SetUserAction(runAction);
}

void fissActionInitialization::Build() const {
  fissPrimaryGeneratorAction* fissprimary = new fissPrimaryGeneratorAction();
  SetUserAction(fissprimary);

  fissRunAction* fissrunaction = new fissRunAction(fDetector, fissprimary);
  SetUserAction(fissrunaction);

  fissEventAction* fissevent = new fissEventAction();
  SetUserAction(fissevent);

  fissTrackingAction*  fissTrack = new fissTrackingAction(fDetector);
  SetUserAction(fissTrack);

  fissSteppingAction* fisssteppingaction = new fissSteppingAction(fDetector, fissevent);
  SetUserAction(fisssteppingaction);
}
