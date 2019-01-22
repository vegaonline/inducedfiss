//*************************************************************
//*       Code for Fast neutron induced fission fragments     *
//*                                                           *
//*      Abhijit Bhattacharyya  :: NPD :: BARC                *
//*     Jan 22, 2019                                          *
//*    \file fissActtionInitialization.hh                                *
//*************************************************************

//  $Id: fissActionInitialization.hh Jan 22, 2019    12:02:15Z   vega $

#ifndef fissActionInitialization_h
#define fissActionInitialization_h 1

#include "G4VUserActionInitialization.hh"
#include "fissDetectorConstruction.hh"

class fissDetectorConstruction;

class fissActionInitialization : public G4VUserActionInitialization {
public:
  fissActionInitialization(fissDetectorConstruction* detector);
  virtual ~fissActionInitialization();

  virtual void BuildForMaster() const;
  virtual void Build() const;

private:
  fissDetectorConstruction* fDetector;
};

#endif
