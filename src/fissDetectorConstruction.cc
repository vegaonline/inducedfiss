//*************************************************************
//*       Code for Fast neutron induced fission fragments     *
//*                                                           *
//*      Abhijit Bhattacharyya  :: NPD :: BARC                *
//*     Jan 21, 2019                                          *
//*    \file fissDetectorConstruction.cc                                *
//*************************************************************

//  $Id: fissDetectorConstruction.cc Jan 21, 2019    22:46:45Z   vega $

#include "fissDetectorConstruction.hh"

fissDetectorConstruction::fissDetectorConstruction() : G4VUserDetectorConstruction(), fTargetMaterial(0), fLogicTarget(0),
    fDetectorMaterial(0), fLogicDetector(0), fWorldMaterial(0), fPhysiWorld(0) {

  fTargetLength = 0.2*cm;
  fTargetRadius = 1.1*cm;

  fDetectorLength = 15.2*cm;
  fDetectorRadius = 3.8*cm;

  fWorldLength = 1.4 * (fTargetLength + fDetectorLength);
  fWorldRadius = 1.4 * std::max(fTargetRadius, fDetectorRadius);

  DefineMaterials();
}


fissDetectorConstruction::~fissDetectorConstruction() {

}

G4VPhysicalVolume* fissDetectorConstruction::Construct() {
  return ConstructVolumes();
}

void fissDetectorConstruction::DefineMaterials() {
  G4int isotopeAtNum, ncomponents, nAtoms;
  G4double isotopeAtMass, AtMass, fractionMass, abundance;

  G4Isotope* isoGe70 = new G4Isotope("Ge70", isotopeAtNum = 32, isotopeAtMass = 70, AtMass = 69.9242*g/mole);
  G4Isotope* isoGe72 = new G4Isotope("Ge72", isotopeAtNum = 32, isotopeAtMass = 72, AtMass = 71.922*g/mole);
  G4Isotope* isoGe73 = new G4Isotope("Ge73", isotopeAtNum = 32, isotopeAtMass = 73, AtMass = 72.9235*g/mole);
  G4Isotope* isoGe74 = new G4Isotope("Ge74", isotopeAtNum = 32, isotopeAtMass = 74, AtMass = 73.9212*g/mole);

  G4Element* N = new G4Element("Nitrogen", "N", 7, 14.01*g/mole);
  G4Element* O = new G4Element("Oxygen", "O", 8, 16.00*g/mole);
  G4Element* Bi = new G4Element("Bismuth", "Bi", 83, 208.980*g/mole);
  G4Element* Ge = new G4Element("Germanium", "Ge", ncomponents = 4);

  Ge->AddIsotope(isoGe70, abundance=20.52*perCent);
  Ge->AddIsotope(isoGe72, abundance=27.45*perCent);
  Ge->AddIsotope(isoGe73, abundance=7.76*perCent);
  Ge->AddIsotope(isoGe74, abundance=36.52*perCent);

  G4Material* BGO = new G4Material("BGO", 7.13*g/cm3, ncomponents=3, kStateSolid);
  BGO->AddElement(Bi, nAtoms = 4);
  BGO->AddElement(Ge, nAtoms = 3);
  BGO->AddElement(O, nAtoms=12);
  fDetectorMaterial = BGO;

  G4Material* U238T = new G4Material("U238", 92, 238.051*g/mole, 18.95*g/cm3);
  fTargetMaterial = U238T;

  G4Material* Air20 = new G4Material("Air", 1.205*mg/cm3, ncomponents=2, kStateGas, 293.0*kelvin, 1.0*atmosphere);
  Air20->AddElement(N, fractionMass=0.7);
  Air20->AddElement(O, fractionMass=0.3);
  fWorldMaterial = Air20;
}


G4VPhysicalVolume* fissDetectorConstruction::ConstructVolumes() {
  // cleaning up old geometry
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();

  // Just checking with re-declaration for testing
  fWorldLength = 1.4 * (fTargetLength + fDetectorLength);
  fWorldRadius = 1.4 * std::max(fTargetRadius, fDetectorRadius);

  // The World
  sWorld = new G4Tubs("World", 0.0, fWorldRadius, 0.5 * fWorldLength, 0.0, twopi);
  lWorld = new G4LogicalVolume(sWorld, fWorldMaterial, "World");
  fPhysiWorld = new G4PVPlacement(0, G4ThreeVector(), lWorld, "World", 0, false, 0);

  // The TARGET
  sTarget = new G4Tubs("Target", 0.0, fTargetRadius, 0.5 * fTargetLength, 0.0, twopi);
  fLogicTarget = new G4LogicalVolume(sTarget, fTargetMaterial, "Target");
  new G4PVPlacement(0, G4ThreeVector(), fLogicTarget, "Target", lWorld, false, 0);

  // The Detector
  sDetector = new G4Tubs("Detector", 0.0, fDetectorRadius, 0.5 * fDetectorLength, 0.0, twopi);
  fLogicDetector = new G4LogicalVolume(sDetector, fDetectorMaterial, "Detector");
  new G4PVPlacement(0, G4ThreeVector(), fLogicDetector, "Detector", lWorld, false, 0);

  PrintParameters();
  return fPhysiWorld;
}

void fissDetectorConstruction::PrintParameters() {
  G4cout << "\n Target : Length = " << G4BestUnit(fTargetLength,"Length")
         << " Radius = " << G4BestUnit(fTargetRadius, "Length")
         << " Material = " << fTargetMaterial->GetName();
  G4cout << "\n Detector : Length = " << G4BestUnit(fDetectorLength,"Length")
         << " Radius = " << G4BestUnit(fDetectorRadius,"Length")
         << " Material = " << fDetectorMaterial->GetName() << G4endl;
  G4cout << "\n" << fTargetMaterial << "\n" << fDetectorMaterial << G4endl;
}

void fissDetectorConstruction::SetTargetMaterial(G4String matChoice){
  G4Material* MatPt = G4NistManager::Instance()->FindOrBuildMaterial(matChoice);

  if (MatPt) {
    fTargetMaterial = MatPt;
    if (fLogicTarget) fLogicTarget->SetMaterial(fTargetMaterial);
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();
  } else {
    G4cout << "\n--> Warning :: DetectorConstruction::SetTargetMaterial "
           << matChoice << " not found" << G4endl;
  }
}

void fissDetectorConstruction::SetDetectorMaterial(G4String matChoice) {
  G4Material* MatPt = G4NistManager::Instance()->FindOrBuildMaterial(matChoice);
  if (MatPt) {
    fDetectorMaterial = MatPt;
    if (fLogicDetector) fLogicDetector->SetMaterial(fDetectorMaterial);
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();
  } else {
    G4cout << "\n--> Warning :: DetectorConstruction::SetDetectorMaterial "
           << matChoice << " not found" << G4endl;
  }
}

void fissDetectorConstruction::SetTargetRadius (G4double value) {
  fTargetRadius = value;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

void fissDetectorConstruction::SetTargetLength(G4double value) {
  fTargetLength = value;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

void fissDetectorConstruction::SetDetectorRadius(G4double value) {
  fDetectorRadius = value;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

void fissDetectorConstruction::SetDetectorLength(G4double value) {
  fDetectorLength = value;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

G4double fissDetectorConstruction::GetTargetRadius() {
  return fTargetRadius;
}

G4double fissDetectorConstruction::GetTargetLength(){
  return fTargetLength;
}

G4Material* fissDetectorConstruction::GetTargetMaterial(){
  return fTargetMaterial;
}

G4LogicalVolume* fissDetectorConstruction::GetLogicTarget() {
  return fLogicTarget;
}

G4double fissDetectorConstruction::GetDetectorRadius(){
  return fDetectorRadius;
}

G4double fissDetectorConstruction::GetDetectorLength() {
  return fDetectorLength;
}

G4Material* fissDetectorConstruction::GetDetectorMaterial() {
  return fDetectorMaterial;
}

G4LogicalVolume* fissDetectorConstruction::GetLogicDetector() {
  return fLogicDetector;
}
