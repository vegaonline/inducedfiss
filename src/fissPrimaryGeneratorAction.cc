//*************************************************************
//*       Code for Fast neutron induced fission fragments     *
//*                                                           *
//*      Abhijit Bhattacharyya  :: NPD :: BARC                *
//*     Jan 22, 2019                                          *
//*    \file fissPrimaryGeneratorAction.cc                                *
//*************************************************************

//  $Id: fissPrimaryGeneratorAction.cc Jan 22, 2019    12:06:45Z   vega $

#include "fissPrimaryGeneratorAction.hh"

fissPrimaryGeneratorAction::fissPrimaryGeneratorAction (): G4VUserPrimaryGeneratorAction(), fParticleGun(0), fEnergy(0*MeV)  {
  G4int n_particle = 1;
  fParticleGun = new G4ParticleGun(n_particle);

  G4ParticleDefinition* particleDefinition = G4ParticleTable::GetParticleTable()->FindParticle("neutron");

  fParticleGun->SetParticleDefinition(particleDefinition);
  fParticleGun->SetParticleEnergy(3.0*MeV);
  fParticleGun->SetParticlePosition(G4ThreeVector(0.0*cm, 0.0*cm, -1.0*cm));
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.0, 0.0, 1.0));
}

fissPrimaryGeneratorAction::~fissPrimaryGeneratorAction(){
  delete fParticleGun;
}

void fissPrimaryGeneratorAction::GeneratePrimaries( G4Event* anEvent) {
  G4double tmp = fParticleGun->GetParticleEnergy();
  fParticleGun->GeneratePrimaryVertex(anEvent);
  if (!GetEnergy()) SetEnergy(tmp);
}
