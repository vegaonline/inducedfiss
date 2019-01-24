//*************************************************************
//*       Code for Fast neutron induced fission fragments     *
//*                                                           *
//*      Abhijit Bhattacharyya  :: NPD :: BARC                *
//*     Jan 24, 2019                                          *
//*    \file fissEventAction.hh                                *
//*************************************************************

//  $Id: fissEventAction.hh Jan 24, 2019    14:12:15Z   vega $

#ifndef fissEventAction_h
#define fissEventAction_h 1
#include "fissRun.hh"
#include "fissHistoManager.hh"
#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "globals.hh"

class fissEventAction : public G4UserEventAction {
public:
  fissEventAction();
  ~fissEventAction();

public:
  virtual void BeginOfEventAction(const G4Event*);
  virtual void EndOfEventAction(const G4Event*);
  void AddEdep(G4int, G4double, G4double, G4double);

private:
  G4double fEdep1, fEdep2;
  G4double fWeight1, fWeight2;
  G4double fTime0;

};
#endif
