//*************************************************************
//*       Code for Fast neutron induced fission fragments     *
//*                                                           *
//*      Abhijit Bhattacharyya  :: NPD :: BARC                *
//*     Jan 22, 2019                                          *
//*    \file fissPrimaryGeneratorAction.hh                                *
//*************************************************************

//  $Id: fissPrimaryGeneratorAction.hh Jan 22, 2019    12:02:15Z   vega $

#ifndef fissPrimaryGeneratorAction_h
#define fissPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"
#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "globals.hh"

class G4Event;
class G4GeneralParticleSource;

class fissPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction{
public:
  fissPrimaryGeneratorAction();
  virtual ~fissPrimaryGeneratorAction();

public:
  virtual void GeneratePrimaries(G4Event*);
  G4GeneralParticleSource* GetParticleGun() { return fGPS; }
  G4double GetEnergy() { return fEnergy; }
  G4double GetMomentum() { return fMomentum; }

  void SetEnergy(G4double value)   { fEnergy = value; }
  void SetMomentum(G4double value) { fMomentum = value; }

private:
  G4GeneralParticleSource* fGPS;
  G4double fEnergy;
  G4double fMomentum;
};

#endif
