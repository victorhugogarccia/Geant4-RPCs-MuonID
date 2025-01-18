#ifndef ACTION_INITIALIZATION_HH
#define ACTION_INITIALIZATION_HH

#include "G4VUserActionInitialization.hh"

#include "PrimaryGeneratorAction.hh"
#include "Run.hh"
#include "event.hh"
#include "stepping.hh"
class DetectorConstruction;

class ActionInitialization: public G4VUserActionInitialization
{
public:
	ActionInitialization();
	~ActionInitialization();
	
	virtual void Build() const;
};

#endif
