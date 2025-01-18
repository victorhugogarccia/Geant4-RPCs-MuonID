#include "PrimaryGeneratorAction.hh"
#include "G4MuonMinus.hh" 
#include "G4VisAttributes.hh"
#include "G4ParticleGun.hh"
#include "G4Tubs.hh"
#include "Randomize.hh"
#include <cmath>
#include <math.h>
#include <cstdlib>
#include <random>
	
PrimaryGeneratorAction::PrimaryGeneratorAction()
{
	//G4double r = G4UniformRand() * 2;
	fParticleGun = new G4ParticleGun(1);
	G4ParticleDefinition* particle = G4MuonMinus::Definition();
	fParticleGun->SetParticleMomentum(3*GeV);
	fParticleGun->SetParticleDefinition(particle);


	
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
	delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
{

	CLHEP::HepRandom::setTheSeed((unsigned)clock());//genera numeros random en cada corrida tomando como base la hora en el CPU
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName = "muon";
	G4ParticleDefinition *particle = particleTable->FindParticle("mu-");
	

	//G4ParticleDefinition* particle = G4MuonMinus::Definition();
	
	G4ThreeVector pos(0., 0., 0.);
	G4double theta = G4UniformRand() *2* CLHEP::pi;
	G4double phi = G4UniformRand() *2 * CLHEP::pi;
	G4int n = std::round(m);
	G4double min = 0.695*CLHEP::pi;;
   	G4double max = CLHEP::pi;;
   	G4double min1 = 0;
   	G4double max1 = 3;
   	G4double min2 = 0.305*CLHEP::pi;;
   	G4double max2 = 0.695*CLHEP::pi;;
   	G4double min3 = 0.305*CLHEP::pi;;
   	G4double max3 = 0.695*CLHEP::pi;;
	//G4double dual = std::pow(-1,n);
	std::random_device rd;
    	std::mt19937 gen(rd());
    	std::uniform_real_distribution<double> distribucion(min, max);
    	std::uniform_int_distribution<int> distribucion1(min1, max1);
    	std::uniform_real_distribution<double> distribucion2(min2, max2);
    	std::uniform_real_distribution<double> distribucion3(min3, max3);
    	G4double random = distribucion(gen);
    	G4double random1 = distribucion1(gen);
    	G4double random2 = distribucion2(gen);
	G4double random3 = distribucion3(gen);
	if(random1 == 0){
	G4double theta = G4UniformRand() * 0.305*CLHEP::pi;
	G4double phi = G4UniformRand() * 2.0 * CLHEP::pi;
	G4ThreeVector mom(sin(theta)*cos(phi), sin(theta)*sin(phi), cos(theta));
	fParticleGun->SetParticleMomentumDirection(mom);
	}
	if(random1 == 1){
	G4double theta =  random;
	G4double phi = G4UniformRand() * 2.0 * CLHEP::pi;
	G4ThreeVector mom(sin(theta)*cos(phi), sin(theta)*sin(phi), cos(theta));
	fParticleGun->SetParticleMomentumDirection(mom);
	}
	if(random1 == 2){
	G4double theta =  random2;
	G4double phi = random3;
	G4ThreeVector mom(sin(theta)*cos(phi), sin(theta)*sin(phi), cos(theta));
	fParticleGun->SetParticleMomentumDirection(mom);
	}
	if(random1 == 3){
	G4double theta =  random2;
	G4double phi = -random3;
	G4ThreeVector mom(sin(theta)*cos(phi), sin(theta)*sin(phi), cos(theta));
	fParticleGun->SetParticleMomentumDirection(mom);
	}
	
	//////////////////////////////////////////////
	//Para eta = 0 descomentar y comentar los ifs anteriores
	//G4ThreeVector mom(0, sin(theta), cos(theta));
	//////////////////////////////////////////////////////
	
	//fParticleGun->SetParticleMomentumDirection(mom);

	
	
	fParticleGun->SetParticlePosition(pos);

	fParticleGun->GeneratePrimaryVertex(anEvent);
}
