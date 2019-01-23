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
  fissPrimaryGeneratorAction* primary = new fissPrimaryGeneratorAction();
  SetUserAction(primary);

  fissRunAction* runAction = new fissRunAction(fDetector, primary);
  SetUserAction(runAction);
}
