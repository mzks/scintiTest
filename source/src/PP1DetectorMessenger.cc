//
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"


#include "PP1DetectorMessenger.hh"
#include "PP1DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"


PP1DetectorMessenger::PP1DetectorMessenger(
                                           PP1DetectorConstruction* PP1Det)
:PP1Detector(PP1Det)
{ 
  PP1Dir = new G4UIdirectory("/PP1/");
  PP1Dir->SetGuidance("UI commands of this example");
  detDir = new G4UIdirectory("/PP1/det/");
  detDir->SetGuidance("UI commands for detector setup");
  
  MaterialCmd = new G4UIcmdWithAString("/PP1/det/setMaterial",this);
  MaterialCmd->SetGuidance("Select Material of the target");
  MaterialCmd->SetParameterName("choice",false);
  MaterialCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  ThicknessCmd = new G4UIcmdWithADoubleAndUnit("/PP1/det/setThickness",this);
  ThicknessCmd->SetGuidance("Set Thickness of the target");
  ThicknessCmd->SetParameterName("Size",false);
  ThicknessCmd->SetRange("Size>=0.");
  ThicknessCmd->SetUnitCategory("Length");
  ThicknessCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  SizeYZCmd = new G4UIcmdWithADoubleAndUnit("/PP1/det/setSize",this);
  SizeYZCmd->SetGuidance("Set tranverse size of the target");
  SizeYZCmd->SetParameterName("Size",false);
  SizeYZCmd->SetRange("Size>0.");
  SizeYZCmd->SetUnitCategory("Length");    
  SizeYZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  MagFieldCmd = new G4UIcmdWithADoubleAndUnit("/PP1/det/setField",this);  
  MagFieldCmd->SetGuidance("Define magnetic field.");
  MagFieldCmd->SetGuidance("Magnetic field will be in Z direction.");
  MagFieldCmd->SetParameterName("Bz",false);
  MagFieldCmd->SetUnitCategory("Magnetic flux density");
  MagFieldCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  
}


PP1DetectorMessenger::~PP1DetectorMessenger()
{
  delete MaterialCmd;
  delete ThicknessCmd;
  delete SizeYZCmd;  
  delete MagFieldCmd;
  delete PP1Dir;  
}


void PP1DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == MaterialCmd ){
    PP1Detector->SetTargetMaterial(newValue);

  } else if( command == ThicknessCmd ){
    PP1Detector->SetTargetThickness(
		   ThicknessCmd->GetNewDoubleValue(newValue)
		  );
   
  } else if( command == SizeYZCmd ){
    PP1Detector->SetTargetSize(SizeYZCmd->GetNewDoubleValue(newValue));
    

  } else if( command == MagFieldCmd ){
    PP1Detector->SetMagField(MagFieldCmd->GetNewDoubleValue(newValue));

  }
}


G4String PP1DetectorMessenger::GetCurrentValue(G4UIcommand * command)
{
  G4String cv;
  
  if( command==MaterialCmd ){
    cv =  PP1Detector->GetTargetMaterial()->GetName();

  } else if( command==ThicknessCmd ){
    cv =  ThicknessCmd->ConvertToString( PP1Detector->GetTargetThickness()/mm,"mm");
  } else if( command==SizeYZCmd ){
    cv =  SizeYZCmd->ConvertToString( PP1Detector->GetTargetSize()/mm,"mm");

  } else if( command==MagFieldCmd ){
    cv =  MagFieldCmd->ConvertToString( PP1Detector->GetFieldValue()/tesla,"tesla");

  }
  
  return cv;
}

