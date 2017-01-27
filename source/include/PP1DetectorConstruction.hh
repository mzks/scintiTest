//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// 

#ifndef PP1DetectorConstruction_h
#define PP1DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4UniformMagField;
class G4SubtractionSolid;
class PP1DetectorMessenger;



class PP1DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
  
    PP1DetectorConstruction();
   ~PP1DetectorConstruction();

  public:
     
     void SetTargetMaterial (G4String);     
     void SetTargetThickness(G4double);     
     void SetTargetSize(G4double);     

     void SetMagField(G4double);
     
     G4VPhysicalVolume* Construct();

     void UpdateGeometry();

  public:
  
     G4double GetWorldSizeX()  const    {return WorldSizeX;}; 
     G4double GetWorldSizeYZ() const    {return WorldSizeYZ;};
     
     const G4Material* GetTargetMaterial()  const {return pTargetMaterial;};
     G4double    GetTargetThickness() const {return vTargetThickness;};      
     G4double    GetTargetSize()      const {return vTargetSize;};      
     G4double    GetFieldValue()      const {return fieldValue;};      
     
     const G4VPhysicalVolume* GetphysiWorld() const {return physWorld;};           
     const G4VPhysicalVolume* GetTarget()     const {return physTarget;};
     const G4VPhysicalVolume* GetSensor()     const {return physSensor;};
                 
  private:
     
     G4Material*        pTargetMaterial;
     G4double           vTargetThickness;
     G4double           vTargetSize;
     
     G4Material*        defaultMaterial;
     G4double           WorldSizeYZ;
     G4double           WorldSizeX;
            
     G4Box*             solidWorld;       //pointer to the solid World 
     G4LogicalVolume*   logicWorld;       //pointer to the logical World
     G4VPhysicalVolume* physWorld;        //pointer to the physical World

     G4Box*             solidTarget;      //pointer to the solid Target
     G4LogicalVolume*   logicTarget;      //pointer to the logical Target
     G4VPhysicalVolume* physTarget;       //pointer to the physical Target
     
	 G4Box*             solidSensor;      //pointer to the solid Sensor
     //G4SubtractionSolid*             solidSensor;      //pointer to the solid Sensor
     G4LogicalVolume*   logicSensor;      //pointer to the logical Sensor
     G4VPhysicalVolume* physSensor;       //pointer to the physical Sensor
 
     //G4Box*             solidGun;      //pointer to the solid Gun
     //G4LogicalVolume*   logicGun;      //pointer to the logical Gun
     //G4VPhysicalVolume* physGun;       //pointer to the physical Gun
     
     G4UniformMagField* magField;      //pointer to the magnetic field
     G4double           fieldValue;

     PP1DetectorMessenger* detectorMessenger;  //pointer to the Messenger
      
  private:
    
     void DefineMaterials();
};

#endif

