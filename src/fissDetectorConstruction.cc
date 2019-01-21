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

  ftargetLength = 0.2*cm;
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
  G4double isotopeAtMass, AtMass, fractionMass;

  fTargetMaterial = new G4Material("U238", z=92, a=238, 238.051*g/mole);

  G4Isotope* isoGe70 = new G4Isotope("Ge70", isotopeAtNum=32, isotopeAtMass = 70, AtMass=69.9242*g/mole);
  G4Isotope* isoGe72 = new G4Isotope("Ge72", isotopeAtNum=32, isotopeAtMass = 72, AtMass=71.922*g/mole);
  G4Isotope* isoGe73 = new G4Isotope("Ge73", isotopeAtNum=32, isotopeAtMass = 73, AtMass=72.9235*g/mole);
  G4Isotope* isoGe74 = new G4Isotope("Ge74", isotopeAtNum=32, isotopeAtMass = 74, AtMass=73.9212*g/mole);

  G4Element* N = new G4Element("Nitrogen", "N", 7, 14.01*g/mole);
  G4Element* O = new G4Element("Oxygen", "O", 8, 16.00*g/mole);
  G4Element* Bi = new G4Element("Bismuth", "Bi", z=83, a=209, 208.980*g/mole );
  G4Element* Ge = new G4Element("Germanium", "Ge", ncomponents=4);
  Ge->AddIsotope(isoGe70, abundance=20.52*perCent);
  Ge->AddIsotope(isoGe72, abundance=27.45*perCent);
  Ge->AddIsotope(isoGe73, abundance=7.76*perCent);
  Ge->AddIsotope(isoGe74, abundance=36.52*perCent);

  G4Material* BGO = new G4Material("BGO", 7.13*g/cm3, ncomponents=3, kStateSolid);
  BGO->AddElement(Bi, nAtoms=4);
  BGO->AddElement(Ge, nAtoms = 3);
  BGO->AddElement(O, nAtoms=12);
  fDetectorMaterial = BGO;

  G4Material* Air20 = new G4Material("Air", 1.205*mg/cm3, ncomponents=2, kStateGas, 293.0*kelvin, 1.0*atmosphere);
  Air20->AddElement(N, fractionMass=0.7);
  Air20->AddElement(O, fractionMass=0.3);
  fWorldMaterial = Air20;

}
