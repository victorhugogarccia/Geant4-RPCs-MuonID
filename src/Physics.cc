#include "Physics.hh"

PhysicsList::PhysicsList()
{
	RegisterPhysics (new G4EmStandardPhysics());
}

PhysicsList::~PhysicsList()
{}
