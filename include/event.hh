#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"

#include "G4AnalysisManager.hh"

#include "Run.hh"

class MyEventAction : public G4UserEventAction
{
public:
	MyEventAction(RunAction*);
	~MyEventAction();
	
	virtual void BeginOfEventAction(const G4Event*);
	virtual void EndOfEventAction(const G4Event*);
	
	void AddEdep(G4double edep) { fEdep += edep; }
	
private:
	G4double fEdep;
	G4double counter;
	G4double in;
};

#endif
