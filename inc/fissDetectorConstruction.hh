//*************************************************************
//*       Code for Fast neutron induced fission fragments     *
//*                                                           *
//*      Abhijit Bhattacharyya  :: NPD :: BARC                *
//*     Jan 21, 2019                                          *
//*    \file fissDetectorConstruction.hh                                *
//*************************************************************

//  $Id: fissDetectorConstruction.hh Jan 21, 2019    21:53:15Z   vega $

#ifndef fissDetectorConstruction_h
#define fissDetectorConstruction_h 1

#incllude "G4VUserDetectorConstruction.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4RunManager.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4UnitsTable.hh"
#include "globals.hh"

class fissDetectorConstruction : public G4VUserDetectorConstruction {
public:
  fissDetectorConstruction();
  ~fissDetectorConstruction();

public:
  virtual G4VPhysicalVolume* Construct();
  void SetTargetLength(G4double value);
  void SetTargetRadius (G4double value);
  void SetTargetMaterial(G4String);

  void SetDetectorLength(G4double value);
  void SetDetectorRadius(G4double value);
  void SetDetectorMaterial(G4String);

  void PrintParameters();

  G4double GetTargetLength();                      // Target
  G4double GetTargetRadius();
  G4Material* GetTargetMaterial();
  G4LogicalVolume* GetLogicTarget();

  G4double GetDetectorLength();               // Detector
  G4double GetDetectorRadius();
  G4Material* GetDetectorMaterial();
  G4LogicalVolume* GetLogicDetector();

private:
  G4double     fTargetLength;                                // Target
  G4double     fTargetRadius;
  G4Material* fTargetMaterial;
  G4LogicalVolume* fLogicTarget;

  G4double     fDetectorLength;                     // Detector
  G4double     fDetectorRadius;
  G4Material* fDetectorMaterial;
  G4LogicalVolume* fLogicDetector;

  G4double fWorldLength;
  G4double fWorldRadius;
  G4Material* fWorldMaterial;
  G4PhysicalVolume* fPhysiWorld;

  void DefineMaterials();
  G4VPhysicalVolume* ConstructVolumes();
};

#endif
