//*************************************************************
//*       Code for Fast neutron induced fission fragments     *
//*                                                           *
//*      Abhijit Bhattacharyya  :: NPD :: BARC                *
//*     Jan 24, 2019                                          *
//*    \file fissHistoManager.hh                                *
//*************************************************************

//  $Id: fissHistoManager.hh Jan 24, 2019    15:02:15Z   vega $

#ifndef fissHistoManager_h
#define fissHistoManager_h 1

#include "globals.hh"
#include "g4root.hh"
//#include "g4xml.hh"
#include "G4UnitsTable.hh"

class fissHistoManager{
public:
  fissHistoManager();
  ~fissHistoManager();
private:
  void Book();
  G4String fFileName;// = "inducedFiss";
};
#endif
