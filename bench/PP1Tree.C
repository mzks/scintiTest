#define PP1Tree_cxx
#include "PP1Tree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void PP1Tree::Loop()
{

//   In a ROOT session, you can do:
//      root> .L PP1Tree.C
//      root> PP1Tree t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//
	TH1D* positronE = new TH1D("positronE","positronE",100,0,2);
	TH1D* gammaE = new TH1D("gammaE","gammaE",100,0,2);

   if (fChain == 0) return;
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {

      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;

	  if(code[ientry] == -11)positronE->Fill(E[ientry]);
	  if(code[ientry] == 22 )gammaE->Fill(E[ientry]);

      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
   TCanvas* c1 = new TCanvas();
   positronE->Draw();
   TCanvas* c2 = new TCanvas();
   gammaE->Draw();
}
