//
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "PP1SensorHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

G4Allocator<PP1SensorHit> PP1SensorHitAllocator;


PP1SensorHit::PP1SensorHit():
              trackID(0),
	      codePDG(0),
	      charge(0.0),
	      energy(0.0),
	      momentum(0., 0., 0.),
	      pos(0., 0., 0.),
	      time(0.0)
{}


PP1SensorHit::~PP1SensorHit() 
{}



PP1SensorHit::PP1SensorHit(const PP1SensorHit& right)
  : G4VHit()
{
  trackID     = right.trackID;
  codePDG     = right.codePDG;
  charge      = right.charge;
  energy      = right.energy;
  momentum    = right.momentum;
  pos         = right.pos;
  time        = right.time;  
}


const PP1SensorHit& PP1SensorHit::operator=(const PP1SensorHit& right)
{
  if (this != &right) {
    trackID     = right.trackID;
    codePDG     = right.codePDG;
    charge      = right.charge;
    energy      = right.energy;
    momentum    = right.momentum;
    pos         = right.pos;
    time        = right.time;    
  }
  return *this;
}



G4int PP1SensorHit::operator==(const PP1SensorHit& right) const
{
  return (this==&right) ? 1 : 0;
}


void PP1SensorHit::Set(const G4Track* track)
{
  trackID  =  track->GetTrackID();
  codePDG  =  track->GetDefinition()->GetPDGEncoding();
  charge   =  track->GetDefinition()->GetPDGCharge();
  energy   =  track->GetKineticEnergy();
  momentum =  track->GetMomentum();
  pos      =  track->GetPosition();
  time     =  track->GetGlobalTime();
}

void PP1SensorHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager){
    G4Circle circle(pos);
    circle.SetScreenSize(2.);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.,0.,0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
}



void PP1SensorHit::Print()
{
//  G4cout << "TrackID: " << trackID << G4endl; 
//  G4cout << "PDG code: "<< codePDG << "  "
//         << "charge: " << charge/eplus << G4endl;
//  G4cout << "enregy: " << energy /MeV  << G4endl;
//  G4cout << "momentum: "<< momentum.x()/MeV << " "
//	 << momentum.y()/MeV << " "
//	 << momentum.z()/MeV << G4endl;
//  G4cout << "position: "<< pos.x()/mm << " "
//	 << pos.y()/mm << " "
//	 << pos.z()/mm << G4endl;
//  G4cout << "time: "<< time/ns << G4endl;
}



