#include <iostream>
#include <fstream>
#include <string>

//#define F_DEBUG 1

using namespace std;

#define MAX_TRK 100

void FillTree()
{
  
  TFile *f=new TFile("PP2Tree.root","recreate");

  // for each event, you want up to MAX_TRK candidates
  Int_t    n;
  Int_t    code[MAX_TRK];
  Float_t  charge[MAX_TRK];
  Double_t E[MAX_TRK];
  Float_t  Px[MAX_TRK];
  Float_t  Py[MAX_TRK];
  Float_t  Pz[MAX_TRK];

  TTree* pPP2Tree= new TTree("PP2Tree","An example of a tree");
  pPP2Tree->Branch("n",&n,"n/I");
  pPP2Tree->Branch("code",&code,"code[n]/I");
  pPP2Tree->Branch("charge",&charge,"charge[n]/F");
  pPP2Tree->Branch("E",&E,"E[n]/D");
  pPP2Tree->Branch("Px",&Px,"Px[n]/F");
  pPP2Tree->Branch("Py",&Py,"Py[n]/F");
  pPP2Tree->Branch("Pz",&Pz,"Pz[n]/F");

  //--- open file -----
  std::ifstream inFile;
  inFile.open("pp1.out");
  
  Int_t  n_evt=0;
  while( !inFile.eof() ){
    n_evt += 1;
    if (n_evt%100 ==0) {
      std::cout <<".";
      if (n_evt%2500 ==0) {
	std::cout <<std::endl;
	if (n_evt%10000 ==0) {
	  std::cout << n_evt << std::endl;
	}
      }
    }

    inFile >> n;
    for (size_t itrk=0; itrk<n ; ++itrk){
      if (itrk>=MAX_TRK) {
        // skip  
	Int_t dummy1,dummy2;
        Float_t dummy3,dummy4,dummy5,dummy6,dummy7;
        inFile >> dummy1 >> dummy2 >> dummy3
               >> dummy4 >> dummy5 >> dummy6 >>dummy7;
        continue;
      }
 	
      Int_t id;
      inFile >> id  
	     >> code[itrk] 
	     >> charge[itrk] 
	     >> E[itrk] 
	     >> Px[itrk] 
	     >> Py[itrk] 
	     >> Pz[itrk];  
      
#ifdef F_DEBUG
      std::cout << "TrackID: " << itrk << std::endl; 
      std::cout << "PDG code: "<< code[itrk] << "  "
		<< "charge: " << charge[itrk] << std::endl;
      std::cout << "enregy: " << E[itrk]  << std::endl;
      std::cout << "momentum: "
		<< Px[itrk] << " "
		<< Py[itrk] << " "
		<< Pz[itrk] << std::endl;
#endif
    }
    if (n>0) pPP2Tree->Fill();

  }
  
  pPP2Tree->Write();
  f->Close();
  delete f;
}
