//*************************************************************
//*       Code for Fast neutron induced fission fragments     *
//*                                                           *
//*      Abhijit Bhattacharyya  :: NPD :: BARC                *
//*     Jan 23, 2019                                          *
//*    \file fissRun.hh                                *
//*************************************************************

//  $Id: fissRun.hh Jan 23, 2019    14:46:15Z   vega $

#ifndef fissRun_h
#define fissRun_h 1

#include "fissDetectorConstruction.hh"
#include "fissPrimaryGeneratorAction.hh"
//#include "fissHistoManager.hh"

#include "G4VProcess.hh"
#include "G4ProcessTable.hh"
#include "G4RadioactiveDecay.hh"
#include "G4TwoVector.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Run.hh"
#include "globals.hh"
#include <fstream>
#include <map>

class fissDetectorConstruction;
class G4ParticleDefinition;

class fissRun : public G4Run {
public:
  fissRun(fissDetectorConstruction*);
  ~fissRun();

public:
  void SetPrimary(G4ParticleDefinition* particle, G4double energy);
  void CountProcesses(const G4VProcess* process, G4int iVol);
  void ParticleCount(G4String, G4double, G4int);
  void AddEdep(G4double, G4double);

  virtual void Merge(const G4Run*);
  void EndOfRun();
  void WriteActivity(G4int);

private:
  struct ParticleData{
    ParticleData() : fCount(0), fEmean(0.0), fEmin(0.0), fEmax(0.0) {}
    ParticleData(G4int count, G4double EKin, G4double EMin, G4double EMax)
        : fCount(count), fEmean(EKin), fEmin(EMin), fEmax(EMax) {}
        G4int fCount;
        G4double fEmean;
        G4double fEmin;
        G4double fEmax;
  };
private:
  fissDetectorConstruction* fDetector;
  G4ParticleDefinition* fParticle;
  G4double fEkin;
  G4double fEdepTarget1, fEdepTarget2;
  G4double fEdepDetect1, fEdepDetect2;

  std::map<G4String, G4int>   fProcCounter1;
  std::map<G4String, G4int>   fProcCounter2;
  std::map<G4String, ParticleData> fParticleDataMap1;
  std::map<G4String, ParticleData> fParticleDataMap2;
};

#endif
