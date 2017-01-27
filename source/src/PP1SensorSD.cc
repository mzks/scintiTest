//
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "PP1SensorSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

/////////////////////////////////////////////////////

PP1SensorSD::PP1SensorSD(G4String name)
:G4VSensitiveDetector(name)
{
  G4String HCname;
  collectionName.insert(HCname="sensorCollection");

  //--- open file -----
  G4String fileName = "pp1.out";  
  outFile.open(fileName, std::ios::out);
}

/////////////////////////////////////////////////////

PP1SensorSD::~PP1SensorSD()
{ 
  outFile.close();
}

/////////////////////////////////////////////////////

void PP1SensorSD::Initialize(G4HCofThisEvent* HCE)
{
  sensorCollection = new PP1SensorHitsCollection
                          (SensitiveDetectorName,collectionName[0]); 
  static G4int HCID = -1;
  if(HCID<0)
  { HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]); }
  HCE->AddHitsCollection( HCID, sensorCollection ); 
}

/////////////////////////////////////////////////////

G4bool PP1SensorSD::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{
  G4int NbHits = sensorCollection->entries();
  G4bool found = false;
  for (G4int i=0; (i<NbHits) && (!found) ;i++) {
    found = ( aStep->GetTrack()->GetTrackID() == (*sensorCollection)[i]->GetTrackID() );
  } 
  if (!found) {
    PP1SensorHit* newHit = new PP1SensorHit();
    newHit->Set(aStep->GetTrack());
    sensorCollection->insert( newHit );
    
    newHit->Print();
    newHit->Draw();
  }
  return true;
}

///////////////////////////////////////////////////////

void PP1SensorSD::EndOfEvent(G4HCofThisEvent*)
{
  G4int NbHits = sensorCollection->entries();
  if (verboseLevel>0) {
    G4cout << "\n-------->Hits Collection: in this event they are " 
	 << NbHits 
	 << " hits in the tracker chambers: " << G4endl;
  }
  outFile.setf( std::ios:: scientific, std::ios::floatfield );
  outFile << std::setprecision(8);
  outFile << NbHits << G4endl;
  
  for (G4int i=0;i<NbHits;i++){
    PP1SensorHit* hit = (*sensorCollection)[i];
    
    if (verboseLevel>0) {
      hit->Print();
    }    
    
    outFile << hit->GetTrackID() <<" " 
	    << hit->GetPDGcode() <<" " 
	    << hit->GetCharge()/eplus <<" " 
	    << hit->GetEnergy()/MeV  <<" " 
	    << hit->GetMomentum().x()/MeV  <<" " 
	    << hit->GetMomentum().y()/MeV  <<" "
	    << hit->GetMomentum().z()/MeV  <<" "
		//<< hit->GetTime()/ns <<" "
	    << G4endl;
  }
  
}



