#include "stepping.hh" 

MySteppingAction::MySteppingAction(MyEventAction *eventAction)
{
	fEventAction = eventAction;
}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step *step)
{
	G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
	 // step->GetPreStepPoint()... Obtienen el punto del paso presente y paso anterior (donde comienza el paso)
	 // ...GetTouchableHandle()->GetVolume()... Obtienen los volumenes fisicos(incluyen posicion y orientacion) donde ocurrio el prepaso
	 //...GetLogicalVolume(); De este volumen físico, obtenemos el volumen lógico, que representa las propiedades geométricas y de materiales 	del volumen, pero sin información sobre la posición en el espacio.
	
	const DetectorConstruction *detectorConstruction = static_cast<const DetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction()); // Se obtiene una instancia de la clase DetectorConstruction 
	//para acceder al volumen de puntuación (fScoringVolume), que es el volumen en el que estamos interesados en registrar la energía depositada.
	
	G4LogicalVolume *fScoringVolume = detectorConstruction->GetScoringVolume();
	//Se llama a un método de DetectorConstruction que devuelve el volumen lógico de puntuación (registro), que es el volumen específico donde estamos interesados en registrar la energía depositada.
	if(volume != fScoringVolume)
		return; //Se verifica si el volumen actual es el volumen de puntuación. Si no lo es, la función retorna y no hace nada más.

	G4double edep = step->GetTotalEnergyDeposit();//Si el volumen es el de puntuación, se obtiene la energía total depositada en este paso (step) y se agrega a fEventAction llamando al método AddEdep.
	fEventAction->AddEdep(edep);
}

