//*************************************************************
//*       Code for Fast neutron induced fission fragments     *
//*                                                           *
//*      Abhijit Bhattacharyya  :: NPD :: BARC                *
//*     Jan 23, 2019                                          *
//*    \file fissRun.cc                                *
//*************************************************************

//  $Id: fissRun.cc Jan 23, 2019    14:00:45Z   vega $

#include "fissRun.hh"

fissRun::fissRun(fissDetectorConstruction* det) : G4Run(), fDetector(det), fParticle(0), fEkin(0.0) {
  fEdepTarget1 = fEdepTarget2 = 0.0;
  fEdepDetect1 = fEdepDetect2 = 0.0;
}

fissRun::~fissRun(){

}

void fissRun::SetPrimary(G4ParticleDefinition* particle, G4double energy) {
  fParticle = particle;
  fEkin = energy;
}

void fissRun::CountProcesses(const G4VProcess* process, G4int iVol) {
  G4String procName = process->GetProcessName();
  if (iVol == 1) {
    std::map>G4String, G4int>::iterator itr1 = fProcCounter1.find(procName);
    if (itr1 ==fProcCounter1.end()) {
      fProcCounter1[procName] = 1;
    } else {
      fProcCounter1[procName++];
    }
  }
  if (iVol == 2) {
    std::map<G4String, G4int>::iterator itr2 = fProcCounter2.find(procName);
    if (it2 == fProcCounter2.end()) {
      fProcCounter2[procName] = 1;
    } else {
      fProcCounter2[procName]++;
    }
  }
}

void fissRun::ParticleCount(G4String name, G4double Ekin, G4int iVol) {
  if (iVol == 1) {
   std::map<G4String, ParticleData>::iterator itr1 = fParticleDataMap1.find(name);
   if ( itr1 == fParticleDataMap1.end()) {
     fParticleDataMap1[name] = ParticleData(1, Ekin, Ekin, Ekin);
   }
   else {
     ParticleData& data = itr1->second;
     data.fCount++;
     data.fEmean += Ekin;
     //update min max
     G4double emin = data.fEmin;
     if (Ekin < emin) data.fEmin = Ekin;
     G4double emax = data.fEmax;
     if (Ekin > emax) data.fEmax = Ekin;
   }
  }

  if (iVol == 2) {
   std::map<G4String, ParticleData>::iterator itr2 = fParticleDataMap2.find(name);
   if ( itr2 == fParticleDataMap2.end()) {
     fParticleDataMap2[name] = ParticleData(1, Ekin, Ekin, Ekin);
   }
   else {
     ParticleData& data = itr2->second;
     data.fCount++;
     data.fEmean += Ekin;
     //update min max
     G4double emin = data.fEmin;
     if (Ekin < emin) data.fEmin = Ekin;
     G4double emax = data.fEmax;
     if (Ekin > emax) data.fEmax = Ekin;
   }
  }
}

void fissRun::AddEdep(G4double edep1, G4double edep2) {
  fEdepTarget1 += edep1;
  fEdepDetect2 += edep1 * edep1;
  fEdepDetect1 += edep2;
  fEdepDetect2 += edep2 * edep2;
}

void fissRun::Merge(const G4Run* thisRun){
  const fissRun* localRun = static_cast<const fissRun*> (thisRun);

  fParticle = localRun->fParticle;   // *** primary particle info ***//
  fEkin = localRun->fEkin;

  fEdepTarget1 += localRun->fEdepTarget1;  // *** accumulate sums *** //
  fEdepTarget2 += localRun->fEdepTarget2;
  fEdepDetect1 += localRun->fEdepDetect1;
  fEdepDetect2 += localRun->fEdepDetect2;

  std::map<G4String, G4int>::const_iterator itp1;    // ***** map process count in target *** //
  for(itp1 = localRun->fProcCoounter1.begin(); itp1 != localRun->fProcCounter1.end(); ++itp1) {
    G4String procName = itp1->first;
    G4int localCount = itp1->second;
    if (fProcCounter1.find(procName) == fProcCounter1.end()){
      fProcCounter1[procName] = localCount;
    } else {
      fProcCounter1[procName] += localCount;
    }
  }

  std::map<G4String, G4int>::const_iterator itp2;    // ***** map process count in detector *** //
  for(itp2 = localRun->fProcCoounter2.begin(); itp2 != localRun->fProcCounter2.end(); ++itp2) {
    G4String procName = itp2->first;
    G4int localCount = itp2->second;
    if (fProcCounter2.find(procName) == fProcCounter2.end()){
      fProcCounter2[procName] = localCount;
    } else {
      fProcCounter2[procName] += localCount;
    }
  }

  std::map<G4String, ParticleData>::const_iterator itc;  // ** map created by particles in target *** //
  for (itc = localRun->fParticleDataMap1.begin(); itc != localRun->fParticleDataMap1.end(); ++itc) {
    G4String name = itc->first;
    const ParticleData& localData = itc->second;
    if ( fParticleDataMap1.find(name) == fParticleDataMap1.end()) {
      fParticleDataMap1[name] = ParticleData(localData.fCount, localData.fEmean, localData.fEmin, localData.fEmax);
    }
    else {
      ParticleData& data = fParticleDataMap1[name];
      data.fCount += localData.fCount;
      data.fEmean += localData.fEmean;
      G4double emin = localData.fEmin;
      if (emin < data.fEmin) data.fEmin = emin;
      G4double emax = localData.fEmax;
      if (emax > data.fEmax) data.fEmax = emax;
    }
  }

  std::map<G4String, ParticleData>::const_iterator itd;  // ** map created by particles in detector *** //
  for (itd = localRun->fParticleDataMap2.begin(); itd != localRun->fParticleDataMap2.end(); ++itd) {
    G4String name = itd->first;
    const ParticleData& localData = itd->second;
    if ( fParticleDataMap2.find(name) == fParticleDataMap2.end()) {
      fParticleDataMap2[name] = ParticleData(localData.fCount, localData.fEmean, localData.fEmin, localData.fEmax);
    }
    else {
      ParticleData& data = fParticleDataMap2[name];
      data.fCount += localData.fCount;
      data.fEmean += localData.fEmean;
      G4double emin = localData.fEmin;
      if (emin < data.fEmin) data.fEmin = emin;
      G4double emax = localData.fEmax;
      if (emax > data.fEmax) data.fEmax = emax;
    }
  }

  G4Run::Merge(fissRun);
}

void fissRun::EndOfRun() {
  G4int prec = 5, wid = prec + 2;
  G4int dfprec = G4cout.precision(prec);

  // run condition
  G4String particle = fParticle->GetParticleName();
  G4ccout << "\n The RUN is " << numberOfEvent << " " << Particle << " of "
          << G4BestUnit(fEkin, "Energy") << " through : ";

  G4cout << "\n Target : Length = "
         << G4BestUnit(fDetector->GetTargetLength(), "Length")
         << " Radius = "
         << G4BestUnit(fDetector->GetTargetRadius(), "Length")
         << " Material = "
         << fDetector->GetTargetMaterial()->GetName();
  G4cout << "\n Detector : Length = "
         << G4BestUnit(fDetector->GetDetectorLength(),"Length")
         << " Thickness = "
         << G4BestUnit(fDetector->GetDetectorThickness(),"Length")
         << " Material = "
         << fDetector->GetDetectorMaterial()->GetName() << G4endl;

  if (numberOfEvent == 0) { G4cout.precision(dfprec);   return;}

 // compute mean Energy deposited and rms in target
  //
  G4int TotNumberOFevents = numberOfEvent;
  fEdepTarget1 /= TotNumberOFevents; fEdepTarget2 /= TotNumberOFevents;
  G4double rmsEdep = fEdepTarget2 - fEdepTarget*fEdepTarget;
  if (rmsEdep>0.) rmsEdep = std::sqrt(rmsEdep);
  else            rmsEdep = 0.;

  G4cout << "\n Mean energy deposit in target,   in time window = "
         << G4BestUnit(fEdepTarget,"Energy") << ";  rms = "
         << G4BestUnit(rmsEdep,    "Energy")
         << G4endl;

  // compute mean Energy deposited and rms in detector
  //
  fEdepDetect /= TotNbofEvents; fEdepDetect2 /= TotNbofEvents;
  rmsEdep = fEdepDetect2 - fEdepDetect*fEdepDetect;
  if (rmsEdep>0.) rmsEdep = std::sqrt(rmsEdep);
  else            rmsEdep = 0.;

  G4cout << " Mean energy deposit in detector, in time window = "
         << G4BestUnit(fEdepDetect,"Energy") << ";  rms = "
         << G4BestUnit(rmsEdep,    "Energy")
         << G4endl;



}
