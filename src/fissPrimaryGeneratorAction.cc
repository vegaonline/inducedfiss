//*************************************************************
//*       Code for Fast neutron induced fission fragments     *
//*                                                           *
//*      Abhijit Bhattacharyya  :: NPD :: BARC                *
//*     Jan 22, 2019                                          *
//*    \file fissPrimaryGeneratorAction.cc                                *
//*************************************************************

//  $Id: fissPrimaryGeneratorAction.cc Jan 22, 2019    12:06:45Z   vega $

#include "fissPrimaryGeneratorAction.hh"

fissPrimaryGeneratorAction::fissPrimaryGeneratorAction (): G4VUserPrimaryGeneratorAction(), fGPS(0), fEnergy(0*MeV)  {
  fGPS = new G4GeneralParticleSource;
}

fissPrimaryGeneratorAction::~fissPrimaryGeneratorAction(){
  delete fGPS;
}

void fissPrimaryGeneratorAction::GeneratePrimaries( G4Event* anEvent) {
  G4double tmp = fGPS->GetParticleEnergy();
  fGPS->GeneratePrimaryVertex(anEvent);
  if (!GetEnergy()) SetEnergy(tmp);
}
