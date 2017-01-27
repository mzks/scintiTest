//
//
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"


#include "PP1PrimaryGeneratorAction.hh"

#include "PP1DetectorConstruction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"


PP1PrimaryGeneratorAction::PP1PrimaryGeneratorAction(
                           const PP1DetectorConstruction* PP1DC)
  :PP1Detector(PP1DC)
{
  G4int n_particle = 1;
  particleGun  = new G4ParticleGun(n_particle);
  
  // default particle kinematic

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
                    = particleTable->FindParticle(particleName="gamma");
  particleGun->SetParticleDefinition(particle);
  particleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
  particleGun->SetParticleEnergy(10.*MeV);
  G4double position = -0.4*(PP1Detector->GetWorldSizeX());
  particleGun->SetParticlePosition(G4ThreeVector(position,0.*cm,0.*cm));

}



PP1PrimaryGeneratorAction::~PP1PrimaryGeneratorAction()
{
  delete particleGun;
}



void PP1PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called at the begining of event
  // 
  //G4double x0 = -0.4*(PP1Detector->GetWorldSizeX());
 //G4double x0 = 0.0 *cm; 
 G4double x0 = -0.0 *cm; 
  G4double y0 = 0.*cm, z0 = 0.*cm;
  particleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));

  particleGun->GeneratePrimaryVertex(anEvent);
}



