//
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "PP1SteppingAction.hh"
#include "G4SteppingManager.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4TrackStatus.hh"
#include "G4TrackVector.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4ios.hh"
#include <iomanip>
#include <fstream>

PP1SteppingAction::PP1SteppingAction()
{
 //--- open file -----
  G4String fileName = "pi.out";  
  outFile.open(fileName, std::ios::out);
}

PP1SteppingAction::~PP1SteppingAction()
{
  outFile.close();
}

void PP1SteppingAction::UserSteppingAction(const G4Step* theStep)
{
  static G4int previousID = -1;
  G4Track * theTrack = theStep->GetTrack();

  // check if it is alive
  //if(theTrack->GetTrackStatus()==fAlive) { return; }
  if (theTrack->GetTrackID() == previousID) return;
  previousID= theTrack->GetTrackID(); 
  if ( (theTrack->GetDefinition() != G4PionPlus::PionPlus()) &&
       (theTrack->GetDefinition() != G4NeutrinoMu::NeutrinoMu()) )  return;
  outFile.setf( std::ios:: scientific, std::ios::floatfield );
  outFile << std::setprecision(8);
  outFile << 1 << G4endl;
  outFile << theTrack->GetTrackID() <<" " 
	  << theTrack->GetDefinition()->GetPDGEncoding() << " "
	  << theTrack->GetDefinition()->GetPDGCharge()/eplus <<" " 
	  << theTrack->GetKineticEnergy()/MeV  <<" " 
	  << theTrack->GetMomentum().x()/MeV  <<" " 
	  << theTrack->GetMomentum().y()/MeV  <<" "
	  << theTrack->GetMomentum().z()/MeV  <<" "
	  << G4endl;

  //G4cout << "      "
  //       << std::setw( 9)
  //	   << theTrack->GetMomentumDirection().x() << " "
  //	   << std::setw( 9)
  //	   << theTrack->GetMomentumDirection().y() << " "
  //	   << std::setw( 9)
  //	   << theTrack->GetMomentumDirection().z() << " "
  //	   << std::setw( 9)
  //	   << theTrack->GetKineticEnergy() / MeV 
  //	   << G4endl;
  
  return;
}

