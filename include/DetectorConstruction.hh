#ifndef DETECTOR_CONSTRUCTION_HH
#define DETECTOR_CONSTRUCTION_HH

#include <iostream>
#include <string>

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "DetectorConstruction.hh"

#include "SensitiveDetector.hh"

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
	DetectorConstruction();
	~DetectorConstruction();
	
	G4LogicalVolume *GetScoringVolume() const { return fScoringVolume; }
	
	
	virtual G4VPhysicalVolume *Construct();
private: 
	G4LogicalVolume *logicStripR1;
	//G4LogicalVolume *logicStripR2;
	//G4LogicalVolume *logiccil;
	//G4LogicalVolume *logiccild;
	G4LogicalVolume *logicgap1R1;
	virtual void ConstructSDandField();
	
	G4LogicalVolume *fScoringVolume;
};

#endif
