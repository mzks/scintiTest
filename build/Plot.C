void Plot()
{
  // Open file
  TFile *pfile=new TFile("PP1Tree.root");

  // Get Tree 
  TTree* pTree = (TTree*)pfile->Get("PP1Tree");
  //  pTree->StartViewer();
  
  TCanvas *c1 = new TCanvas("c1","My Canvas",10,10,400,400);
  pTree->Draw("E","code==22");
  TCanvas *c2 = new TCanvas("c2","My Canvas",10,10,400,400);
  pTree->Draw("Px:Py","code==22");
}
