//
//
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "PP1DetectorConstruction.hh"
#include "PP1DetectorMessenger.hh"
#include "PP1SensorSD.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4UniformMagField.hh"
#include "G4SDManager.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4SubtractionSolid.hh"
//#include "G4NistManager.hh"

////////////////////////////////////////////////////////////

PP1DetectorConstruction::PP1DetectorConstruction()
 :pTargetMaterial(0),vTargetThickness(0.),vTargetSize(0.),
  defaultMaterial(0),
  solidWorld(0),logicWorld(0),physWorld(0),
  solidTarget(0),logicTarget(0),physTarget(0),
  solidSensor(0),
  logicSensor(0),physSensor(0),
   magField(0)
{
  // World Size
  WorldSizeYZ =  100.0 *cm;
  WorldSizeX  =  100.0 *cm;

  // default parameter values of Target
  vTargetThickness =  0.15 *mm;
  vTargetSize      = 1.*cm;
  
  
  // materials
  DefineMaterials();
  SetTargetMaterial("Scintillator");
  
  // create commands for interactive definition of the calorimeter
  detectorMessenger = new PP1DetectorMessenger(this);
}

/////////////////////////////////////////////////////////

PP1DetectorConstruction::~PP1DetectorConstruction()
{ 
  delete detectorMessenger;
}

////////////////////////////////////////////////////////

G4VPhysicalVolume* PP1DetectorConstruction::Construct()
{
 // Clean old geometry, if any
  //
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();

  //     
  // World
  //
  solidWorld = new G4Box("World",				//its name
                   WorldSizeX/2,WorldSizeYZ/2,WorldSizeYZ/2);	//its size
                         
  logicWorld = new G4LogicalVolume(solidWorld,		//its solid
                                   defaultMaterial,	//its material
                                   "World");		//its name
                                   
  physWorld = new G4PVPlacement(0,			//no rotation
  				 G4ThreeVector(),	//at (0,0,0)
                                 logicWorld,		//its logical volume	 
                                 "World",		//its name
                                 0,			//its mother  volume
                                 false,			//no boolean operation
                                 0);			//copy number
  
  //                               
  //  
  //solidTarget = new G4Box("Target",		//its name
			  //vTargetThickness/2,vTargetSize/2,vTargetSize/2);//size
  

 
  //                                 
  // Sensor
  //
  //G4double   vSensorThickness = 1.0 *cm;

    //solidSensor = new G4Box("Sensor",
  		       //vSensorThickness/2,vSensorThickness/2,vSensorThickness/2);

//  G4VSolid* blank = new G4Box("Blank",
		  //0.1 *cm/2.0 ,
		  //1.0 *cm/2.0 ,
		  //1.0 *cm/2.0 );

	G4Tubs* solidEnvSensor = new G4Tubs(
			"solidEnvSensor",
			0,
			8.0/2.0 * mm,
			0.3/ 2.0 * mm,
			0,
			CLHEP::twopi);

	G4Tubs* blank  = new G4Tubs(
			"blank ",
			0,
			8.0/2.0 * mm,
			0.15/ 2.0 * mm,
			0,
			CLHEP::twopi);

	auto envSensor = new G4LogicalVolume(solidEnvSensor,
			defaultMaterial,
			"envSensor");

   auto logicTarget = new G4LogicalVolume(blank,	//its solid
				    pTargetMaterial,	//its material
				    "logicTarget");       	//its name

   auto logicSensor = new G4LogicalVolume(blank,
				    defaultMaterial,
				    "logicSensor");
    				       
  new G4PVPlacement(0,			//no rotation
				 G4ThreeVector(0 , 0 , -0.15/2*mm),	//at (0,0,0)
				 logicTarget,   	//its logical volume
				 "Target",	        //its name
				 envSensor,    	//its mother  volume
				 false,  		//no boolean operation
				 0);	        	//copy number

  new G4PVPlacement(0,			//no rotation
				 G4ThreeVector(0 , 0 , +0.15/2*mm),	//at (0,0,0)
				 logicSensor,   	//its logical volume
				 "Sensor",	        //its name
				 envSensor,    	//its mother  volume
				 false,  		//no boolean operation
				 0);	        	//copy number

	//Set source case to world
	G4RotationMatrix mat_source  = G4RotationMatrix();
	mat_source.rotateY(90 * deg);

	G4double source_length = 100.0 * mm;

	G4double source_offset = 2.5* mm;


  new G4PVPlacement(
		  //0,                      //no rotation
		  //G4ThreeVector(10.0 * cm,0.,0.), 
		  G4Transform3D(mat_source,G4ThreeVector(source_length + source_offset,0,0)),
		  envSensor,         
		  "physEnvSensor",
		  logicWorld,
		  false,                 
		  0);                    

  G4String symbol;             //a=mass of a mole;
  G4double a, z, density;      //z=mean number of protons;  
  G4int iz, n;                 //iz=number of protons  in an isotope; 
  // n=number of nucleons in an isotope;
  
  G4int ncomponents, natoms;
  G4double abundance, fractionmass;

  G4Element* H  = new G4Element("Hydrogen",symbol="H" , z= 1., a= 1.01*g/mole);
  G4Element* C  = new G4Element("Carbon"  ,symbol="C" , z= 6., a= 12.01*g/mole);

  G4Material* Sci = 
    new G4Material("Scintillator", density= 1.032*g/cm3, ncomponents=2);
  Sci->AddElement(C, natoms=9);
  Sci->AddElement(H, natoms=10);
  G4Material* Vacuum =
    new G4Material("Galactic", z=1., a=1.01*g/mole,density= universe_mean_density,
		   kStateGas, 2.73*kelvin, 3.e-18*pascal);
  G4Material* Al = new G4Material("Aluminum", z=13., a=26.98*g/mole, density=2.700*g/cm3);

  //Source Case
	//Parameters
	G4Tubs* env22NaCase = new G4Tubs(
			"env22NaCase",
			0,
			25.0/2.0 * mm,
			5.0 / 2.0 * mm,
			0,
			CLHEP::twopi);

	G4Tubs* solid22NaCase = new G4Tubs(
			"solid22NaCase",
			8.0 /2.0 * mm,
			25.0/2.0 * mm,
			5.0 / 2.0 * mm,
			0.0,
			CLHEP::twopi);

	G4Tubs* solid22NaCaseBottom = new G4Tubs(
			"solid22NaCaseBottom",
			0,
			8.0/2.0 * mm,
			2.0 / 2.0 * mm,
			0.0,
			CLHEP::twopi);

	G4Tubs* solid22NaCaseWindow = new G4Tubs(
			"solid22NaCaseWindow",
			0,
			8.0/2.0 * mm,
			0.1 / 2.0 * mm,
			0.0,
			CLHEP::twopi);
	
	G4LogicalVolume* logenv22NaCase = new G4LogicalVolume(
			env22NaCase,
			Vacuum,
			"logenv22NaCase",
			0,0,0,true);
	G4LogicalVolume* logSide22NaCase = new G4LogicalVolume(
			solid22NaCase,
			Sci,
			"logSide22NaCase",
			0,0,0,true);
	G4LogicalVolume* logBottom22NaCase = new G4LogicalVolume(
			solid22NaCaseBottom,
			Sci,
			"logBottom22NaCase",
			0,0,0,true);
	G4LogicalVolume* logWindow22NaCase = new G4LogicalVolume(
			solid22NaCaseWindow,
			Al,
			"logWindow22NaCase",
			0,0,0,true);

	new G4PVPlacement( 
			G4Transform3D(), //rotation and vector
			logSide22NaCase,	//logical volume
			"physEnv22NaCaseSide",//name
			logenv22NaCase, //mother logicall volume
			false,				//set to false
			9001,			//copy number
			true);			// check
	
	new G4PVPlacement( 
			G4Transform3D(G4RotationMatrix(),G4ThreeVector(0,0,-1.5*mm)), //rotation and vector
			logBottom22NaCase,	//logical volume
			"physEnv22NaCaseBottom",//name
			logenv22NaCase, //mother logicall volume
			false,				//set to false
			9002,			//copy number
			true);			// check

	new G4PVPlacement( 
			G4Transform3D(G4RotationMatrix(),G4ThreeVector(0,0,2.0*mm)), //rotation and vector
			logWindow22NaCase,	//logical volume
			"physEnv22NaCaseWindow",//name
			logenv22NaCase, //mother logicall volume
			false,				//set to false
			9003,			//copy number
			true);			// check



	new G4PVPlacement(
			G4Transform3D(mat_source,G4ThreeVector(0.0 *cm,0,0)),
			//G4Transform3D(mat_source,G4ThreeVector(-2.5 *mm,0,0)),
			"sourceCase",
			logenv22NaCase,
		   	physWorld, 
			false,
			9004,
			true);
  
  

  //                                 
  // Gun
  //
  //  G4double   vGunSize = 1.0 *cm;
  //G4double   vGunSize = 0.1 *cm;
  //solidGun = new G4Box("Gun",
  //  	       vGunSize/2,vGunSize/2,vGunSize/2);
  //  			   
  //logicGun = new G4LogicalVolume(solidGun,
  //  			 defaultMaterial,
  //  			 "Gun");
  //    				     
  //physGun = new G4PVPlacement(0,                      //no rotation
  //  		       G4ThreeVector((-0.4)*WorldSizeX+vGunSize,0.,0.), 
  //  		       logicGun,         
  //  		       "Gun",
  //  		       logicWorld,
  //  		       false,                 
  //  		       0);                    
  //
  //------------------------------------------------ 
  // Sensitive detectors
  //------------------------------------------------ 
  
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  PP1SensorSD* aSensorSD = (PP1SensorSD*)SDman->FindSensitiveDetector( "PP1/SensorSD");
  if ( aSensorSD == 0){
    aSensorSD = new PP1SensorSD(  "PP1/SensorSD" );
    SDman->AddNewDetector( aSensorSD );
  }
  logicSensor->SetSensitiveDetector( aSensorSD );
   

  //                                        
  // Visualization attributes
  //
  logicWorld->SetVisAttributes (G4VisAttributes::Invisible);
  //logicSensor->SetVisAttributes (G4VisAttributes::Invisible);
  //logicGun->SetVisAttributes (G4VisAttributes::Invisible);

  logicWorld->SetVisAttributes (G4VisAttributes(true,G4Colour(0.0,0.0,1.0))); // blue
  logicSensor->SetVisAttributes (G4VisAttributes(true,G4Colour(0.0,1.0,0.0))); //green
  //logicGun->SetVisAttributes (G4VisAttributes(true,G4Colour(1.0,0.0,0.0))); //red

  G4VisAttributes* simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,0.0,0.0));
  simpleBoxVisAtt->SetVisibility(true);
  logicTarget->SetVisAttributes(simpleBoxVisAtt);

  //
  //always return the physical World
  //
  //
  SetMagField(0.1 * tesla);

  return physWorld;
}

///////////////////////////////////////////////////////

void PP1DetectorConstruction::DefineMaterials()
{ 
  //This function illustrates the possible ways to define materials
  
  G4String symbol;             //a=mass of a mole;
  G4double a, z, density;      //z=mean number of protons;  
  G4int iz, n;                 //iz=number of protons  in an isotope; 
  // n=number of nucleons in an isotope;
  
  G4int ncomponents, natoms;
  G4double abundance, fractionmass;
  
	// Get pointer to 'Material Manager'
	//G4NistManager* materi_Man = G4NistManager::Instance();
  //
  // define Elements
  //
  
  G4Element* H  = new G4Element("Hydrogen",symbol="H" , z= 1., a= 1.01*g/mole);
  G4Element* C  = new G4Element("Carbon"  ,symbol="C" , z= 6., a= 12.01*g/mole);
  G4Element* N  = new G4Element("Nitrogen",symbol="N" , z= 7., a= 14.01*g/mole);
  G4Element* O  = new G4Element("Oxygen"  ,symbol="O" , z= 8., a= 16.00*g/mole);
  G4Element* Si = new G4Element("Silicon",symbol="Si" , z= 14., a= 28.09*g/mole);
	//G4Material* Al = new G4Material("Aluminum", z=13., a=26.98*g/mole, density=2.700*g/cm3);
	//G4Material* Sci = new G4Material("Scintillator", density= 1.032*g/cm3, ncomponents=2);
	//Sci->AddElement(C, natoms=9);
	//Sci->AddElement(H, natoms=10);

	//G4Material* vac    = materi_Man->FindOrBuildMaterial("G4_Galactic");
  
  //
  // define an Element from isotopes, by relative abundance 
  //
  
  G4Isotope* U5 = new G4Isotope("U235", iz=92, n=235, a=235.01*g/mole);
  G4Isotope* U8 = new G4Isotope("U238", iz=92, n=238, a=238.03*g/mole);
  
  G4Element* U  = new G4Element("enriched Uranium",symbol="U",ncomponents=2);
  U->AddIsotope(U5, abundance= 90.*perCent);
  U->AddIsotope(U8, abundance= 10.*perCent);
  
  //
  // define simple materials
  //
  
  //new G4Material("Aluminium", z=13., a=26.98*g/mole, density=2.700*g/cm3);
  new G4Material("liquidArgon", z=18., a= 39.95*g/mole, density= 1.390*g/cm3);
  new G4Material("Lead"     , z=82., a= 207.19*g/mole, density= 11.35*g/cm3);
  new G4Material("Tungsten" , z=74., a= 183.84*g/mole, density= 19.25*g/cm3);
  new G4Material("Iron" , z=26., a= 55.845*g/mole, density= 7.874*g/cm3);
  
  //
  // define a material from elements.   case 1: chemical molecule
  //
  
  G4Material* H2O = 
    new G4Material("Water", density= 1.000*g/cm3, ncomponents=2);
  H2O->AddElement(H, natoms=2);
  H2O->AddElement(O, natoms=1);
  // overwrite computed meanExcitationEnergy with ICRU recommended value 
  H2O->GetIonisation()->SetMeanExcitationEnergy(75.0*eV);
  
//  G4Material* Sci = 
//    new G4Material("Scintillator", density= 1.032*g/cm3, ncomponents=2);
//  Sci->AddElement(C, natoms=9);
//  Sci->AddElement(H, natoms=10);
  
  G4Material* Myl = 
    new G4Material("Mylar", density= 1.397*g/cm3, ncomponents=3);
  Myl->AddElement(C, natoms=10);
  Myl->AddElement(H, natoms= 8);
  Myl->AddElement(O, natoms= 4);
  
  G4Material* SiO2 = 
    new G4Material("quartz",density= 2.200*g/cm3, ncomponents=2);
  SiO2->AddElement(Si, natoms=1);
  SiO2->AddElement(O , natoms=2);
  
  //
  // define a material from elements.   case 2: mixture by fractional mass
  //
  
  G4Material* Air = 
    new G4Material("Air"  , density= 1.290*mg/cm3, ncomponents=2);
  Air->AddElement(N, fractionmass=0.7);
  Air->AddElement(O, fractionmass=0.3);
  
  //
  // define a material from elements and/or others materials (mixture of mixtures)
  //
  
  G4Material* Aerog = 
    new G4Material("Aerogel", density= 0.200*g/cm3, ncomponents=3);
  Aerog->AddMaterial(SiO2, fractionmass=62.5*perCent);
  Aerog->AddMaterial(H2O , fractionmass=37.4*perCent);
  Aerog->AddElement (C   , fractionmass= 0.1*perCent);
  
  //
  // examples of gas in non STP conditions
  //

  G4Material* CO2 = 
    new G4Material("CarbonicGas", density= 27.*mg/cm3, ncomponents=2,
                              kStateGas, 325.*kelvin, 50.*atmosphere);
  CO2->AddElement(C, natoms=1);
  CO2->AddElement(O, natoms=2);
  
  G4Material* steam = 
    new G4Material("WaterSteam", density= 0.3*mg/cm3, ncomponents=1,
		   kStateGas, 500.*kelvin, 2.*atmosphere);
  steam->AddMaterial(H2O, fractionmass=1.);
  
  //
  // examples of vacuum
  //
  
//  G4Material* Vacuum =
//    new G4Material("Galactic", z=1., a=1.01*g/mole,density= universe_mean_density,
//		   kStateGas, 2.73*kelvin, 3.e-18*pascal);
  
  G4Material* beam = 
    new G4Material("Beam", density= 1.e-5*g/cm3, ncomponents=1,
		   kStateGas, STP_Temperature, 2.e-2*bar);
  beam->AddMaterial(Air, fractionmass=1.);

  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
  
  //default materials of the World
  //defaultMaterial  = Vacuum;
  defaultMaterial  = Air;
}

/////////////////////////////////////////////////////////////

void PP1DetectorConstruction::SetTargetMaterial(G4String materialChoice)
{
  // search the material by its name
  G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);
  if (pttoMaterial) {
    pTargetMaterial = pttoMaterial;
    G4cout << " PP1DetectorConstruction::SetTargetMaterial:  ";
    G4cout << "Target material is " << materialChoice << G4endl;
    UpdateGeometry();
 } else {
    G4cout << " PP1DetectorConstruction::SetTargetMaterial:  ";
    G4cout << materialChoice << " is not in the Material Table.";
    G4cout <<G4endl;
  }
}

//////////////////////////////////////////////////////////////

void PP1DetectorConstruction::SetTargetThickness(G4double val)
{
  if (val<WorldSizeYZ) {
    vTargetThickness = val;
    G4cout << " PP1DetectorConstruction::SetTargetThickness:  ";
    G4cout << "Target thickness is " << val/mm << "mm" << G4endl;
    UpdateGeometry();
 }
}

//////////////////////////////////////////////////////////////

void PP1DetectorConstruction::SetTargetSize(G4double val)
{
    //vTargetSize = val;
    UpdateGeometry();
}

///////////////////////////////////////////////////////////////////

#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"

void PP1DetectorConstruction::SetMagField(G4double value)
{
  //apply a global uniform magnetic field along Z axis
  G4FieldManager* fieldMgr
   = G4TransportationManager::GetTransportationManager()->GetFieldManager();

  if(magField) delete magField;		//delete the existing magn field

  if(value!=0.){			// create a new one if non nul
    fieldValue = value;
    magField = new G4UniformMagField(G4ThreeVector(fieldValue,0.,0.));
    fieldMgr->SetDetectorField(magField);
    fieldMgr->CreateChordFinder(magField);
  } else {
    magField = 0;
    fieldMgr->SetDetectorField(magField);
  }
}

#include "G4RunManager.hh"

void PP1DetectorConstruction::UpdateGeometry()
{
  G4RunManager::GetRunManager()->DefineWorldVolume(Construct());
}

