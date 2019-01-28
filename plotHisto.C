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
   int pid;
   double energy, time, weight;
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

   // Loading Tuples
   TNtuple* t1 = (TNtuple*) subdir[1]->Get("t1"); // Emitted Particles Data
   TNtuple* t2 = (TNtuple*) subdir[1]->Get("t2"); // RadioIsotope Data
   TNtuple* t3 = (TNtuple*) subdir[1]->Get("t3"); // Energy depositions Data

   // Declare new histograms from tuples
   TH1F* t1EnergyTime = new TH1F("T1EnergyTime", "T1 Energy vs Time ", (TimeCnt - 1), fTimebin);



   // Getting data from Tuples
   
   for (int irow = 0; irow < t1->GetEntries(); ++irow) {
     t1->SetBranchAddress("PID",    &pid);    t1->GetEntry(irow);
     t1->SetBranchAddress("Energy", &energy); t1->GetEntry(irow);
     t1->SetBranchAddress("Time",   &time);   t1->GetEntry(irow);
     t1->SetBranchAddress("Weight", &weight); t1->GetEntry(irow);

     t1EnergyTime->Fill(time, energy);
     TAxis* xAxist1 = t1EnergyTime->GetXaxis();
     Int_t binXt1   = xAxist1->FindBin(time);
     
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
   TCanvas* c21 = new TCanvas("H21", "", 900, 700);
   gStyle->SetHistLineWidth(3);
   gStyle->SetTitleX(0.2);
   gPad->SetLogy();
   gPad->SetLogx();
   t1EnergyTime->Draw("SAME");
   c21->Print("t1 Time vs Energy.png");
   c21->Close();


   
   
   subdir[0]->ls();
   subdir[1]->ls();

   // Closing the file
   tf->Close();
   
}
