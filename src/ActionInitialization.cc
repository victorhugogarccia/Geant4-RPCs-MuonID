#include "ActionInitialization.hh"

ActionInitialization::ActionInitialization()
{}

ActionInitialization::~ActionInitialization()
{}

void ActionInitialization::Build() const {

	PrimaryGeneratorAction *generator = new PrimaryGeneratorAction();
	SetUserAction(generator);
	
	RunAction *runAction = new RunAction();
	SetUserAction(runAction);
	
	MyEventAction *eventAction = new MyEventAction(runAction);
	SetUserAction(eventAction);
	
	MySteppingAction *steppingAction = new MySteppingAction(eventAction);
	SetUserAction(steppingAction);
}
