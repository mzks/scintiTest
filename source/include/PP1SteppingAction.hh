#ifndef PP1SteppingAction_H
#define PP1SteppingAction_H 1

#include "globals.hh"
#include "G4UserSteppingAction.hh"
#include <iomanip>
#include <fstream>

class PP1SteppingAction : public G4UserSteppingAction
{
  public:
    PP1SteppingAction();
    ~PP1SteppingAction();
    virtual void UserSteppingAction(const G4Step*);
  private:
  std::ofstream outFile;
};

#endif

