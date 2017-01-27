//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Dec 25 17:28:03 2016 by ROOT version 6.06/04
// from TTree PP1Tree/An example of a tree
// found on file: PP1Tree.root
//////////////////////////////////////////////////////////

#ifndef PP1Tree_h
#define PP1Tree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class PP1Tree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           n;
   Int_t           code[14];   //[n]
   Float_t         charge[14];   //[n]
   Double_t        E[14];   //[n]
   Float_t         Px[14];   //[n]
   Float_t         Py[14];   //[n]
   Float_t         Pz[14];   //[n]

   // List of branches
   TBranch        *b_n;   //!
   TBranch        *b_code;   //!
   TBranch        *b_charge;   //!
   TBranch        *b_E;   //!
   TBranch        *b_Px;   //!
   TBranch        *b_Py;   //!
   TBranch        *b_Pz;   //!

   PP1Tree(TTree *tree=0);
   virtual ~PP1Tree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef PP1Tree_cxx
PP1Tree::PP1Tree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("PP1Tree.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("PP1Tree.root");
      }
      f->GetObject("PP1Tree",tree);

   }
   Init(tree);
}

PP1Tree::~PP1Tree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t PP1Tree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t PP1Tree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void PP1Tree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("n", &n, &b_n);
   fChain->SetBranchAddress("code", code, &b_code);
   fChain->SetBranchAddress("charge", charge, &b_charge);
   fChain->SetBranchAddress("E", E, &b_E);
   fChain->SetBranchAddress("Px", Px, &b_Px);
   fChain->SetBranchAddress("Py", Py, &b_Py);
   fChain->SetBranchAddress("Pz", Pz, &b_Pz);
   Notify();
}

Bool_t PP1Tree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void PP1Tree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t PP1Tree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef PP1Tree_cxx
