void Plot()
{
  // Open file
  //TFile *pfile=new TFile("PP1Tree.root");
  TFile *pfile=new TFile("./M10Ev5cm.root");

  // Get Tree 
  TTree* pTree = (TTree*)pfile->Get("PP1Tree");
    //pTree->StartViewer();
	
  // Make histgram
  TH1D* positronE = new TH1D("positronE","positron energy",100,0,1);
  TH1D* gammaE = new TH1D("gammaE","gamma energy",100,0,2);
  
  TCanvas *c1 = new TCanvas("c1","My Canvas",10,10,600,400);
  pTree->Draw("E >> positronE","code==-11");
  //TCanvas *c2 = new TCanvas("c2","My Canvas",10,10,400,800);
  //pTree->Draw("Px:Py","code==-11");
  //TCanvas *c3 = new TCanvas("c3","My Canvas",10,10,400,800);
  //pTree->Draw("Px:Pz","code==-11");
  TCanvas *c4 = new TCanvas("c4","My Canvas",10,10,600,400);
  pTree->Draw("E >> gammaE","code==22");

  positronE->SetTitle(";Energy (MeV);Entries");
  gammaE->SetTitle(";Energy (MeV);Entries");


}
