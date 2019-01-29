#include <string.h>
#include "TSystem.h"
#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
#include "TClass.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TStyle.h"
#include "TGaxis.h"
#include "Riostream.h"

void plotHisto(){
   gROOT->Reset();
   int NumDir = 0;
   TLatex* tlx;

   TFile *tf = TFile::Open("indFiss.root");
   NumDir = (tf->GetListOfKeys())->GetSize();
   TDirectory *dirsav = gDirectory;

   cout << "File Name : " << dirsav->GetName() << " having "
        << NumDir << " subdirectories." << endl;
   
   TDirectory *subdir[NumDir];
   TIter next(tf->GetListOfKeys());
   TKey *key;
   int jDirCnt = 0;
   while ((key = (TKey*)next())) {
      if (key->IsFolder()) {
	TString dirName = (key->GetName());
	cout << " subdir:  " << dirName << endl;
	tf->cd(dirName);
        subdir[jDirCnt] = gDirectory;				
        dirsav->cd();
	jDirCnt++;
        continue;
      }
   }


   // Introduce some useful variables for limiting histogram
   double pid, energy, time, weight;
   const int TimeCnt = 20;
   Float_t fTimebin[TimeCnt];
   fTimebin[0] = 0.0;
   fTimebin[1] = 0.5;
   for (int i = 2; i < TimeCnt; i++) fTimebin[i] = fTimebin[i-1] * 10.0;
   
   // Loading histograms
   TH1D*  H10 = (TH1D*) subdir[0]->Get("H10");  // energy deposit in MeV in Target
   TH1D*  H11 = (TH1D*) subdir[0]->Get("H11");  // energy deposit in MeV in Detector
   TH1D*  H12 = (TH1D*) subdir[0]->Get("H12");  // Total energy deposit in MeV in Target and Detector
   TH1D*  H13 = (TH1D*) subdir[0]->Get("H13");  // Coinc spectrum (MeV) between Target and Detector
   TH1D*  H14 = (TH1D*) subdir[0]->Get("H14");  // Anti-Coinc spectrum (MeV) in Target
   TH1D*  H15 = (TH1D*) subdir[0]->Get("H15");  // Anti-Coinc spectrum (MeV) in Detector
   TH1D*  H16 = (TH1D*) subdir[0]->Get("H16");  // Decay emission spectrum (0-10 MeV)
   TH1D*  H17 = (TH1D*) subdir[0]->Get("H17");  // Decay emission spectrum (0-1 MeV)
   TH1D*  H18 = (TH1D*) subdir[0]->Get("H18");  // Decay emission spectrum (0-0.1 MeV)

   // Declaring Tuples from TREE
   TTreeReader t1Tree("T1", subdir[1]);
   Long64_t t1Len = t1Tree.GetEntries(1);
   TTreeReaderValue<Double_t> pidT1(t1Tree, "PID");
   TTreeReaderValue<Double_t> energyT1(t1Tree, "Energy");
   TTreeReaderValue<Double_t> timeT1(t1Tree, "Time");
   TTreeReaderValue<Double_t> weightT1(t1Tree, "Weight");
   
   TTreeReader t2Tree("T2", subdir[1]);
   Long64_t t2Len = t2Tree.GetEntries(1);
   TTreeReaderValue<Float_t>pidT2(t2Tree, "PID");
   TTreeReaderValue<Float_t>timeT2(t2Tree, "Time");
   TTreeReaderValue<Float_t>weightT2(t2Tree, "Weight");
   
   TTreeReader t3Tree("T3", subdir[1]);
   Long64_t t3Len = t3Tree.GetEntries(1);   
   TTreeReaderValue<Float_t>energyT3(t3Tree, "Energy");
   TTreeReaderValue<Float_t>timeT3(t3Tree, "Time");
   TTreeReaderValue<Float_t>weightT3(t3Tree, "Weight");

   TTreeReader rdTree("RDecayProducts", subdir[1]);
   Long64_t rdLen = rdTree.GetEntries(1);   
   TTreeReaderValue<Float_t>pidRD(rdTree, "PID");
   TTreeReaderValue<Float_t>ZRD(rdTree, "Z");
   TTreeReaderValue<Float_t>ARD(rdTree, "A");
   TTreeReaderValue<Float_t>energyRD(rdTree, "Energy");
   TTreeReaderValue<Float_t>timeRD(rdTree, "Time");
   TTreeReaderValue<Float_t>weightRD(rdTree, "Weight");


   // Declare new histograms from tuples
   TH2F* t1PIDEnergy = new TH2F("PidEnergyT1", " PID vs Energy", 100, 1, 30, 200, 0, 10.0);
   TH2F* t1TimeEnergy = new TH2F("TimeEnergyT1", " Time vs Energy", 100, 0, 40, 200, 0, 10.0);
   TH1F* t1PID = new TH1F("T1PID", "T1 PID ", 100, 1, 40);
   TH1F* t1Energy = new TH1F("T1Energy", "T1 Energy ", 100, 0, 3.0);

   TH2F* rdMassEnergy = new TH2F("MassEnergyRD", " Mass vs Energy", 100, 0, 110, 200, 0, 10.0);

   // Getting data from Tuples
   while (t1Tree.Next()){              // T1
     t1PID->Fill(*pidT1);
     t1Energy->Fill(*energyT1);
     t1TimeEnergy->Fill(*timeT1, *energyT1);
     t1PIDEnergy->Fill(*pidT1, *energyT1);
   }

   while (rdTree.Next()){              // RD
     rdMassEnergy->Fill(*ARD, *energyRD);
   }

   
   
   
   
   // Plotting Routine for histograms

   // H10 edep_Target
   TCanvas* c10 = new TCanvas("H10", "Energy deposit (MeV) in Target", 900, 700);
   
   gStyle->SetHistLineWidth(3);
   gStyle->SetTitleX(0.2);
   gPad->SetLogy();
   gPad->SetLogx();
   H10->Draw();
   c10->Print("Edep_in_Target.png");
   c10->Close();

   // H11 edep_Detector
   TCanvas* c11 = new TCanvas("H11", "Energy deposit (MeV) in Detector", 900, 700);
   gStyle->SetHistLineWidth(3);
   gStyle->SetTitleX(0.2);
   gPad->SetLogy();
   gPad->SetLogx();
   H11->Draw();
   c11->Print("Edep_in_Detector.png");
   c11->Close();

   // H12 tot_edep_Target_detector
   TCanvas* c12 = new TCanvas("H12", "Total Energy deposit (MeV) in Target and Detector", 900, 700);
   gStyle->SetHistLineWidth(3);
   gStyle->SetTitleX(0.2);
   gPad->SetLogy();
   gPad->SetLogx();
   H12->Draw();
   c12->Print("Edep_in_Targ_Det.png");
   c12->Close();

   // H13 Coinc_Spec_between_Target_Detector
   TCanvas* c13 = new TCanvas("H13", "", 900, 700);
   gStyle->SetHistLineWidth(3);
   //gStyle->SetTitleX(0.2);
   gPad->SetLogy();
   gPad->SetLogx();
   gStyle->SetTitleX(0.05);
   H13->SetTitle("");
   //H13->SetTitle("Coincidence spectrum between Target and Detector");
   tlx = new TLatex(0.12, 0.93, "Coincidence spectrum between Target and Detector");
   tlx->SetTextSize(0.04);
   tlx->SetNDC(kTRUE);
   tlx->Draw();
   H13->GetXaxis()->SetTitle("log10(Energy / MeV)");
   H13->Draw();
   tlx->Draw();
   c13->Print("Coin_Spec_in_Target_Detector.png");
   c13->Close();

   // H14 Anti-Coincidence_in Target
   TCanvas* c14 = new TCanvas("H14", "Anti-Coincidence in Target", 900, 700);
   gStyle->SetHistLineWidth(3);
   gStyle->SetTitleX(0.2);
   gPad->SetLogy();
   gPad->SetLogx();
   H14->Draw();
   c14->Print("Anti_Coinc_in_Target.png");
   c14->Close();


   // H15 Anti-Coincidence_in Detector
   TCanvas* c15 = new TCanvas("H15", "Anti-Coincidence in Detector", 900, 700);
   gStyle->SetHistLineWidth(3);
   gStyle->SetTitleX(0.2);
   gPad->SetLogy();
   gPad->SetLogx();
   H15->Draw();
   c15->Print("Anti_Coinc_in_Detector.png");
   c15->Close();

   // H16 Decay Emission spectrum (0 - 10 MeV)
   TCanvas* c16 = new TCanvas("H16", "Decay Emission Spectrum (0 - 10 MeV)", 900, 700);
   gStyle->SetHistLineWidth(3);
   gStyle->SetTitleX(0.2);
   gPad->SetLogy();
   gPad->SetLogx();
   H16->Draw();
   c16->Print("Decay_Emission_Spec_0_10_MeV.png");
   c16->Close();

   // H17 Decay Emission spectrum (0 - 1 MeV)
   TCanvas* c17 = new TCanvas("H17", "Decay Emission Spectrum (0 - 1 MeV)", 900, 700);
   gStyle->SetHistLineWidth(3);
   gStyle->SetTitleX(0.2);
   gPad->SetLogy();
   gPad->SetLogx();
   H17->Draw();
   c17->Print("Decay_Emission_Spec_0_1_MeV.png");
   c17->Close();

   // H18 Decay Emission spectrum (0 - 0.1 MeV)
   TCanvas* c18 = new TCanvas("H18", "Decay Emission Spectrum (0 - 0.1 MeV)", 900, 700);
   gStyle->SetHistLineWidth(3);
   gStyle->SetTitleX(0.2);
   gPad->SetLogy();
   gPad->SetLogx();
   H18->Draw();
   c18->Print("Decay_Emission_Spec_0_0MeV1.png");
   c18->Close();
   

   //H21
   TCanvas* ct1pid = new TCanvas("H21", "", 900, 700);
   ct1pid->Divide(2,2);
   ct1pid->cd(1);
   gStyle->SetHistLineWidth(3);
   gStyle->SetTitleX(0.2);
   gPad->SetLogy();
   gPad->SetLogx();
   t1PIDEnergy->SetMarkerStyle(kFullCircle);
   t1PIDEnergy->SetMarkerSize(0.6);
   t1PIDEnergy->SetMarkerColor(kBlue);
   t1PIDEnergy->SetStats(kFALSE);
   t1PIDEnergy->GetXaxis()->SetTitle("PID");
   t1PIDEnergy->GetYaxis()->SetTitle("Energy/MeV");
   t1PIDEnergy->Draw("SAME P");
   ct1pid->cd(2);
   t1PID->Draw("SAME");
   ct1pid->cd(3);
   t1Energy->Draw("SAME");
   ct1pid->cd(4);
   t1TimeEnergy->SetMarkerStyle(kFullCircle);
   t1TimeEnergy->SetMarkerSize(0.6);
   t1TimeEnergy->SetMarkerColor(kBlue);
   t1TimeEnergy->SetStats(kFALSE);   
   t1TimeEnergy->GetXaxis()->SetTitle("Time");
   t1TimeEnergy->GetXaxis()->SetTitleSize(0.06);
   t1TimeEnergy->GetXaxis()->SetTitleOffset(1.2);
   t1TimeEnergy->GetYaxis()->SetTitle("Energy");
   t1TimeEnergy->GetYaxis()->SetTitleOffset(1.2);
   t1TimeEnergy->Draw("SAME P");
   ct1pid->Print("PID_vs_Energy.png");
   ct1pid->Close();


    //H22
   TCanvas* crdmassen = new TCanvas("H22", "", 900, 700);
   gStyle->SetHistLineWidth(3);
   gStyle->SetTitleX(0.2);
   gPad->SetLogy();
   // gPad->SetLogx();
   rdMassEnergy->SetMarkerStyle(kFullCircle);
   rdMassEnergy->SetMarkerSize(0.6);
   rdMassEnergy->SetMarkerColor(kBlue);
   rdMassEnergy->SetStats(kFALSE);
   rdMassEnergy->GetXaxis()->SetTitle("PID");
   rdMassEnergy->GetYaxis()->SetTitle("Energy/MeV");
   rdMassEnergy->Draw("SAME P");

   crdmassen->Print("Mass_vs_Energy_RD.png");
   crdmassen->Close();

   
   
   //    subdir[0]->ls();
   // subdir[1]->ls();

   // Closing the file
   tf->Close();
   
}
