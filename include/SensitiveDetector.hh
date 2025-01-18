#ifndef SENSITIVE_DETECTOR_HH
#define SENSITIVE_DETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"

#include "G4AnalysisManager.hh"

class SensitiveDetector : public G4VSensitiveDetector
{
public:
	SensitiveDetector(G4String);
	~SensitiveDetector();
	
private:
	virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
};
class SensitiveDetector2 : public G4VSensitiveDetector
{
public:
	SensitiveDetector2(G4String);
	~SensitiveDetector2();
	
private:
	virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
};
class SensitiveDetector3 : public G4VSensitiveDetector
{
public:
	SensitiveDetector3(G4String);
	~SensitiveDetector3();
	
private:
	virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
};

#endif
