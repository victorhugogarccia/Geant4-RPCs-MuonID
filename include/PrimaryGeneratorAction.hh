#ifndef PRIMARY_GENERATOR_ACTION_HH
#define PRIMARY_GENERATOR_ACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4VisAttributes.hh"

class PrimaryGeneratorAction: public G4VUserPrimaryGeneratorAction
{
public:
	PrimaryGeneratorAction();
	~PrimaryGeneratorAction();
	
	virtual void GeneratePrimaries(G4Event*);
	
private:
	G4ParticleGun *fParticleGun;
};

#endif
