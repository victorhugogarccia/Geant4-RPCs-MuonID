#include "SensitiveDetector.hh"
#include "stepping.hh"
SensitiveDetector::SensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

SensitiveDetector::~SensitiveDetector()
{}


SensitiveDetector2::SensitiveDetector2(G4String name2) : G4VSensitiveDetector(name2)
{}

SensitiveDetector2::~SensitiveDetector2()
{}

SensitiveDetector3::SensitiveDetector3(G4String name3) : G4VSensitiveDetector(name3)
{}

SensitiveDetector3::~SensitiveDetector3()
{}

G4bool SensitiveDetector2::ProcessHits(G4Step *bStep, G4TouchableHistory *R0hist)
{
	G4Track *track2 = bStep->GetTrack();

	//track2->SetTrackStatus(fStopAndKill);
	
	G4StepPoint *preStepPoint = bStep->GetPreStepPoint();
	G4StepPoint *postStepPoint = bStep->GetPostStepPoint();//duda sobre particulas cargadas pues menciona que varia de acuerdo a la particula si tiene o no carga 
	
	G4ThreeVector preposAbs = preStepPoint->GetPosition();
	//G4ThreeVector aftposPhoton = postStepPoint->GetPosition();
	//G4cout << "Muon position in second layer" << preposAbs << G4endl; //Este comando me dice la posicion en la que el foton interactuo con el detector
	
	const G4VTouchable *touchable = bStep->GetPreStepPoint()->GetTouchable();
	
	G4int copyNo = touchable->GetCopyNumber();
	
	//G4cout << "Copy number: " << copyNo << G4endl; //Este sirve para saber el numero del volumen logico del detector en el que se encuentra el  foton
	
	//G4VPhysicalVolume *physVol = touchable->GetVolume();
	//G4ThreeVector posDetector = physVol->GetTranslation(); //Este ultimo sirve para saber la posicion del detector que fue atravesado por un foton
	
	//G4cout << "Detector position: " << posDetector << G4endl;
	
	//G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
	
	//G4AnalysisManager *man = G4AnalysisManager::Instance();
	//man->FillNtupleIColumn(0,evt);
	//man->FillNtupleDColumn(1, preposAbs[0]);
	//man->FillNtupleDColumn(2, preposAbs[1]);
	//man->FillNtupleDColumn(3, preposAbs[2]);
	//man->AddNtupleRow(0);
	
}
G4bool SensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *R0hist)
{
	G4Track *track = aStep->GetTrack();

	//track->SetTrackStatus(fStopAndKill);
	
	G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
	G4StepPoint *postStepPoint = aStep->GetPostStepPoint();
	
	G4ThreeVector posMuon1 = preStepPoint->GetPosition();
	
	//G4cout << "Muon position in first layer: " << posMuon1 << G4endl; //Este comando me dice la posicion en la que el foton interactuo con el detector
	
	
	const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
	
	G4int copyNo = touchable->GetCopyNumber();
	
	//G4cout << "Copy number: " << copyNo << G4endl;// Este sirve para saber el numero del volumen logico del detector en el que se encuentra el  foton
	
	G4VPhysicalVolume *physVol = touchable->GetVolume();
	G4ThreeVector posDetector = physVol->GetTranslation(); //Este ultimo sirve para saber la posicion del detector que fue atravesado por un foton
	
	//G4cout << "Detector position: " << posDetector << G4endl;
	
	//G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
	
	//G4AnalysisManager *man = G4AnalysisManager::Instance();
	//man->FillNtupleIColumn(0,evt);
	//man->FillNtupleDColumn(1, posMuon1[0]);
	//man->FillNtupleDColumn(2, posMuon1[1]);
	//man->FillNtupleDColumn(3, posMuon1[2]);
	//man->AddNtupleRow(0);
	
}



G4bool SensitiveDetector3::ProcessHits(G4Step *cStep, G4TouchableHistory *R0hist)
{
	G4Track *track = cStep->GetTrack();

	//track->SetTrackStatus(fStopAndKill);
	
	G4StepPoint *preStepPoint = cStep->GetPreStepPoint();
	G4StepPoint *postStepPoint = cStep->GetPostStepPoint();//duda sobre particulas cargadas pues menciona que varia de acuerdo a la particula si tiene o no carga 
	G4ThreeVector preposMuon2 = preStepPoint->GetPosition();
	//G4ThreeVector aftposPhoton = postStepPoint->GetPosition();
	//G4cout << "Muon position in absorber" << preposMuon2 << G4endl; //Este comando me dice la posicion en la que el foton interactuo con el detector
	
	const G4VTouchable *touchable = cStep->GetPreStepPoint()->GetTouchable();
	
	//G4int copyNo = touchable->GetCopyNumber();
	
	//G4cout << "Copy number: " << copyNo << G4endl; //Este sirve para saber el numero del volumen logico del detector en el que se encuentra el  foton
	
	G4VPhysicalVolume *physVol = touchable->GetVolume();
	G4ThreeVector posDetector = physVol->GetTranslation(); //Este ultimo sirve para saber la posicion del detector que fue atravesado por un foton
	
	//G4cout << "Detector position: " << posDetector << G4endl;
	
	//G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
	
	//G4AnalysisManager *man = G4AnalysisManager::Instance();
	//man->FillNtupleIColumn(0,evt);
	//man->FillNtupleDColumn(1, preposMuon2[0]);
	//man->FillNtupleDColumn(2, preposMuon2[1]);
	//man->FillNtupleDColumn(3, preposMuon2[2]);
	//man->AddNtupleRow(0);
	
}

