//*************************************************************
//*       Code for Fast neutron induced fission fragments     *
//*                                                           *
//*      Abhijit Bhattacharyya  :: NPD :: BARC                *
//*     Jan 22, 2019                                          *
//*    \file fissPhysicsList.hh                                *
//*************************************************************

//  $Id: fissPhysicsList.hh Jan 22, 2019    12:02:15Z   vega $

#ifndef fissPhysicsList_h
#define fissPhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

#include "G4EmStandardPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4EmParameters.hh"
#include "G4DecayPhysics.hh"
#include "G4NuclideTable.hh"
#include "G4RadioactiveDecayPhysics.hh"

#include "G4HadronElasticPhysicsHP.hh"
#include "G4HadronPhysicsFTFP_BERT_HP.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"
#include "G4HadronInelasticQBBC.hh"
#include "G4HadronPhysicsINCLXX.hh"
#include "G4IonElasticPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4IonINCLXXPhysics.hh"

// particles
#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BosonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4ShortLivedConstructor.hh"

#include "globals.hh"

class fissPhysicsList : public G4VModularPhysicsList {
public:
  fissPhysicsList();
  ~fissPhysicsList();

public:
  virtual void ConstructParticle();
  virtual void SetCuts();
};
#endif
