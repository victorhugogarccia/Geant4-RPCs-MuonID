#include "event.hh"

MyEventAction::MyEventAction(RunAction*)
{
	fEdep = 0.;
	//counter = 0;
}

MyEventAction::~MyEventAction()
{}

void MyEventAction::BeginOfEventAction(const G4Event*)
{
	fEdep = 0.;
	//counter = 0;
	counter++;

}

void MyEventAction::EndOfEventAction(const G4Event*)
{
	//G4cout << "Energy deposition: " << fEdep << G4endl;
	
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	//man->FillNtupleDColumn(0, 0, fEdep); este es el original 
	//man->FillNtupleDColumn(0, fEdep);
	//man->AddNtupleRow(0);
	
///////////////////////////////////////////////////////////////////////////////////////////////////	
	//Para obtener el numero de muones incidentes se usa esto
		
	if (fEdep > 0){
	man->FillNtupleIColumn(0, fEdep);
	
	man->AddNtupleRow(0);
	in++;
	}
	if (counter == 100000){
	G4cout << "La eficiencia es del %" << 100*in/counter << G4endl;
	counter = 0;
	in = 0;
	}
	
	
}
