#include "Run.hh"
#include "Randomize.hh"

RunAction::RunAction()
{

	G4AnalysisManager *man = G4AnalysisManager::Instance();

	//man->CreateNtuple("Hits","Hits");
	//man->CreateNtupleIColumn("fEvent");
	//man->CreateNtupleDColumn("Posx");
	//man->CreateNtupleDColumn("Posy");
	//man->CreateNtupleDColumn("Posz");
	//man->FinishNtuple(0);
	
	man->CreateNtuple("Scoring","Scoring");
	man->CreateNtupleDColumn("fEdep");//para saber cuantos muones tocaron el volumen cambiar la D por I
	man->FinishNtuple(0);
}

RunAction::~RunAction()
{}

void RunAction::BeginOfRunAction(const G4Run* run)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	G4int runID = run->GetRunID();
	
	std::stringstream strRunID;
	strRunID << runID;
	
	//man->OpenFile("output.root");
	man->OpenFile("output"+strRunID.str()+".root");
//G4AnalysisManager *man = G4AnalysisManager::Instance();

	//man->CreateNtuple("Hits","Hits");
	//man->CreateNtupleIColumn("fEvent");
	//man->CreateNtupleDColumn("Posx");
	//man->CreateNtupleDColumn("Posy");
	//man->CreateNtupleDColumn("Posz");
	//man->FinishNtuple(0);
	

	
	
	
}

void RunAction::EndOfRunAction(const G4Run*)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	man->Write();
	man->CloseFile();
}
