//*************************************************************
//*       Code for Fast neutron induced fission fragments     *
//*                                                           *
//*      Abhijit Bhattacharyya  :: NPD :: BARC                *
//*     Jan 23, 2019                                          *
//*    \file fissRunAction.hh                                *
//*************************************************************

//  $Id: fissRunAction.hh Jan 23, 2019    11:02:15Z   vega $

#ifndef fissRunAction_h
#define fissRunAction_h 1

#include "G4UserRunAction.hh"
#include "fissDetectorConstruction.hh"
#include "fissPrimaryGeneratorAction.hh"
#include "fissRun.hh"
#include "fissHistoManager.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include <iomanip>
#include "globals.hh"

class fissDetectorConstruction;
class fissRun;
class fissPrimaryGeneratorAction;
class fissHistoManager;

class fissRunAction : public G4UserRunAction {
public:
  fissRunAction(fissDetectorConstruction*, fissPrimaryGeneratorAction*);
  ~fissRunAction();

public:
  virtual G4Run* GenerateRun();
  virtual void BeginOfRunAction(const G4Run*);
  virtual void EndOfRunAction(const G4Run*);

private:
  fissDetectorConstruction* fDetector;
  fissPrimaryGeneratorAction* fPrimary;
  fissRun* fRun;
  fissHistoManager* fHistoManager;
};

#endif
