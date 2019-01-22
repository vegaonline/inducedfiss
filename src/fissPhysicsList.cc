//*************************************************************
//*       Code for Fast neutron induced fission fragments     *
//*                                                           *
//*      Abhijit Bhattacharyya  :: NPD :: BARC                *
//*     Jan 22, 2019                                          *
//*    \file fissPhysicsList.cc                                *
//*************************************************************

//  $Id: fissPhysicsList.cc Jan 22, 2019    12:06:45Z   vega $

#include "fissPhysicsList.hh"

fissPhysicsList::fissPhysicsList() : G4VModularPhysicsList() {
  G4int verb = 1;
  SetVerboseLevel(verb);

  // Adding new units for radioactive decay
  new G4UnitDefinition("millielectronVolt", "meV", "Energy", 1.0e-3*eV);
  const G4double minute = 60.0 * second;
  const G4double hour     = 60.0 * minute;
  const G4double day       = 24.0 * hour;
  const G4double year     = 365.0 * day;
  new G4UnitDefinition("minute", "min", "Time", minute);
  new G4UnitDefinition("hour",     "hr",    "Time", hour);
  new G4UnitDefinition("day",       "d",     "Time", day);
  new G4UnitDefinition("year",      "y",     "Time", year);

  // Mandatory for the nuclide table
  G4NuclideTable::GetInstance()->SetThresholdOfHalfLife(0.1 * picosecond);
  G4NuclideTable::GetInstance()->SetLevelTolerance(1.0 * eV);

  //EM Physics
  RegisterPhysics(new G4EmStandardPhysics());
  G4EmParameters* param = G4EmParameters::Instance();
  param->SetAugerCascade(true);
  param->SetStepFunction(1.0, 1*CLHEP::mm);

  //Decay
  RegisterPhysics(new G4DecayPhysics());

  //RadioActive Decay
  RegisterPhysics(new G4RadioactiveDecayPhysics());

  //Hadron Elastic Scattering
  RegisterPhysics(new G4HadronElasticPhysicsHP(verb));

  //Hadron Inelastic Physics
  // RegisterPhysics(new G4HadronPhysicsFTFP_BERT_HP(verb));
  RegisterPhysics(new G4HadronPhysicsQGSP_BIC_HP(verb));
  //RegisterPhysics(new G4HadronInelasticQBBC(verb));
  // RegisterPhysics(new G4HadronPhysicsINCLXX(verb));

  //Ion Elastic Scattering
  RegisterPhysics(new G4IonElasticPhysics(verb));

  // Ion Inelastic Physics
  RegisterPhysics(new G4IonPhysics(verb));
  // RegisterPhysics(new G4IonINCLXXPhysics(verb));

  //Gamma Nuclear Physics
  G4EmExtraPhysics* gnuc = new G4EmExtraPhysics(verb);
  gnuc->ElectroNuclear(false);
  gnuc->MuonNuclear(false);
  RegisterPhysics(gnuc);
}

fissPhysicsList::~fissPhysicsList(){

}

void fissPhysicsList::ConstructParticle() {
  G4BosonConstructor pBosonConstructor;
  pBosonConstructor.ConstructParticle();

  G4LeptonConstructor pLeptonConstructor;
  pLeptonConstructor.ConstructParticle();

  G4MesonConstructor pMesonConstructor;
  pMesonConstructor.ConstructParticle();

  G4BaryonConstructor pBaryonConstructor;
  pBaryonConstructor.ConstructParticle();

  G4IonConstructor pIonConstructor;
  pIonConstructor.ConstructParticle();

  G4ShortLivedConstructor pShortLivedConstructor;
  pShortLivedConstructor.ConstructParticle();
}

void fissPhysicsList::SetCuts() {
  SetCutValue(0.0*mm, "proton");
  SetCutValue(10.0*km, "e-");
  SetCutValue(10.0*km, "e+");
  SetCutValue(10.0*km, "gamma");
}
