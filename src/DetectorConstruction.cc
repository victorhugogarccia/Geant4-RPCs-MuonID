#include "DetectorConstruction.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "Randomize.hh"
#include "G4Torus.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PhysicalConstants.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include <cmath>
#include <math.h>

#include "G4VSensitiveDetector.hh"
#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"

DetectorConstruction::DetectorConstruction()
{}

DetectorConstruction::~DetectorConstruction()
{}

G4VPhysicalVolume *DetectorConstruction::Construct()
{
////////////////////////////////////////////////////////////
//Intro de materiales
	G4NistManager *nist = G4NistManager::Instance();
	G4Material *steel = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");//PARA CREAR EL ACERO
	G4Material *hierro = nist->FindOrBuildMaterial("G4_Fe");//hierro
	G4Material *glass = nist->FindOrBuildMaterial("G4_GLASS_PLATE");//Para el vidrio
	G4Material *grafito = nist->FindOrBuildMaterial("G4_GRAPHITE");
	G4Material *cobre = nist->FindOrBuildMaterial("G4_Cu");
	//Mezcla para freon
	G4Element* elC = nist->FindOrBuildElement("C");
	G4Element* elCl = nist->FindOrBuildElement("Cl");
	G4Element* elF = nist->FindOrBuildElement("F");
	G4Element* elH = nist->FindOrBuildElement("H");
	G4Element* elO = nist->FindOrBuildElement("O");
	//Definir las fracciones de masa para cada componente
    	G4double C_fraction = 1;   // Número de átomos de carbono en el Freón-12
	G4double Cl_fraction = 2;  // Número de átomos de cloro en el Freón-12
	G4double F_fraction = 2;   // Número de átomos de flúor en el Freón-12
	//Calcular la fracción molar normalizada para cada componente
	G4double total_fraction = C_fraction + Cl_fraction + F_fraction;
	G4double C_molar_fraction = C_fraction / total_fraction;
	G4double Cl_molar_fraction = Cl_fraction / total_fraction;
	G4double F_molar_fraction = F_fraction / total_fraction;
	// Definir las densidades para cada componente
	G4double C_density = 2.26 * g/cm3;  // Densidad del carbono en el Freón-12
	G4double Cl_density = 1.56 * g/cm3; // Densidad del cloro en el Freón-12
	G4double F_density = 1.55 * g/cm3;  // Densidad del flúor en el Freón-12
	// Calcular la densidad ponderada de la mezcla de Freón
	G4double mixture_density = (C_density * C_fraction + Cl_density * Cl_fraction + F_density * F_fraction) / total_fraction;
	// Crear el material de la mezcla de Freón
	G4Material* freonMixture = new G4Material("FreonMixture", mixture_density, 3);
	freonMixture->AddElement(elC, C_molar_fraction);
	freonMixture->AddElement(elCl, Cl_molar_fraction);
	freonMixture->AddElement(elF, F_molar_fraction);
	//Para crear el material acrilico 
	G4double density = 1.19*g/cm3;
	G4String materialName = "acrylic";
	G4Material* acrylic = new G4Material("acrylic", density, 3);
	acrylic->AddElement(elC, 5);
	acrylic->AddElement(elH, 8);
	acrylic->AddElement(elO, 2);	
	//Aqui defino las dimensiones de la placa de acero
	G4double plateLength = 1.0 * m;
	G4double plateWidth = 1.0 * m;
   	G4double plateDepth = 10.0 * cm;
	G4double energy[2]={1.239841939*eV/0.9, 1.239841939*eV/0.2};
	G4double rindexAerogel[2] = {1.1, 1.1};
	G4double rindexWorld[2]={1.0, 1.0};
	//Material del volumen madre
	G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
	G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
	mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);
	worldMat->SetMaterialPropertiesTable(mptWorld);
////////////////////////////////////////////////////////////////////
	//Contruccion del volumen mundo 
	G4Box *solidWorld = new G4Box("solidWorld", 20.0*m, 20.0*m, 20.0*m);	
	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
	G4VisAttributes* invis = new G4VisAttributes();
	invis->SetVisibility(false);
	logicWorld->SetVisAttributes(invis);
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);	
/////////////Constantes//////////////////////
	double anchstr = 0.17*m; //ancho de strip
	double sepstrip = 0.005*m; //separacion entre strips
	double separacion = anchstr+sepstrip ;//Separacion entre las strips de los primeros RPCs.Estos tienen un ancho de 5 cm y una separacion de 5mm
	double ns = 5 ;//numero de strips
	double astr1 = 2.76*m;//Distancia del centro a las primeras strips
	double aacrR1 = 2.76055*m;//Distancia del primer acrilico
	double apinR1 = 2.7611*m;//Distancia de la primer placa de pintura
	double avid1R1 = 2.76215*m;//Distancia del centro del anillo al primer vidrio
	double agap1R1 = 2.76365*m;//Distancia del centro del anillo al primer gap
	double avid2R1 = 2.76515*m;//Distancia del centro del anillo al segundo vidrio
	double agap2R1 = 2.76665*m;//Distancia del segundo gap
	double avid3R1 = 2.76815*m;//Distancia del tercer vidrio
	double apin2R1 = 2.7692*m;//Distancia de la primer pintura
	double aacr2R1 = 2.76975*m;//Distancia del segundo acrilico
	double separaciony = anchstr+sepstrip ;//Separacion entre las strips de los segundos RPCs.Estos tienen un ancho de 5 cm y una separacion de 5mm
	double astr2 = 2.87*m;//Distancia del centro a las primeras strips
	double aacrR2 = 2.87055*m;//Distancia del primer acrilico 2do layer
	double apinR2 = 2.8711*m;//Distancia de la primer pintura 2do l
	double avid1R2 = 2.87215*m;//Distancia del primer vidrio 2do l
	double agap1R2 = 2.87365*m;//Distancia del primer gap 2do l
	double avid2R2 = 2.87515*m;//Distancia del segundo vidrio 2do l
	double agap2R2 = 2.87665*m;//Distancia del segundo gap 2do l
	double avid3R2 = 2.87815*m;//Distancia del tercer vidrio 2do l
	double apin2R2 = 2.8792*m;//Distancia de la primer pintura 2do l
	double aacr2R2 = 2.87975*m;//Distancia del segundo acrilico 2do l
	double aacr3R2 = 2.88175*m;//Distancia del segundo acrilico 2do l
	
	
/////////////////////////////////////////////////////////////////////////////////////
//////////////////////Medidas para las rpc en los extremos del absorber//////////////
/////////////////////////////////////////////////////////////////////////////////////
	double astr1x = 2.61*m;//Distancia del centro a las primeras strips de los extremos del absorber
	double aacrR1x = 2.61055*m;//Distancia del primer acrilico
	double apinR1x = 2.6111*m;//Distancia de la primer placa de pintura
	double avid1R1x = 2.61215*m;//Distancia del centro del anillo al primer vidrio
	double agap1R1x = 2.61365*m;//Distancia del centro del anillo al primer gap
	double avid2R1x = 2.61515*m;//Distancia del centro del anillo al segundo vidrio
	double agap2R1x = 2.61665*m;//Distancia del segundo gap
	double avid3R1x = 2.61815*m;//Distancia del tercer vidrio
	double apin2R1x = 2.6192*m;//Distancia de la primer pintura
	double aacr2R1x = 2.61975*m;//Distancia del segundo acrilico
	//double separaciony = anchstr+sepstrip ;//Separacion entre las strips de los segundos RPCs.Estos tienen un ancho de 5 cm y una separacion de 5mm
	double astr2x = 2.72*m;//Distancia del centro a las primeras strips
	double aacrR2x = 2.72055*m;//Distancia del primer acrilico 2do layer
	double apinR2x = 2.7211*m;//Distancia de la primer pintura 2do l
	double avid1R2x = 2.72215*m;//Distancia del primer vidrio 2do l
	double agap1R2x = 2.72365*m;//Distancia del primer gap 2do l
	double avid2R2x = 2.72515*m;//Distancia del segundo vidrio 2do l
	double agap2R2x = 2.72665*m;//Distancia del segundo gap 2do l
	double avid3R2x = 2.72815*m;//Distancia del tercer vidrio 2do l
	double apin2R2x = 2.7292*m;//Distancia de la primer pintura 2do l
	double aacr2R2x = 2.72975*m;//Distancia del segundo acrilico 2do l
	double aacr3R2x = 2.72175*m;//Distancia del segundo acrilico 2do l
///////////////////////////////Parametros para las strips horizontales//////////////////////////////
	//G4double a = 2.9262*m;//no es el apotema, es el lado del triangulo que va del centro al centro de la RPC, es decir la hipotenusa
	double angintradian = 22.5 * M_PI / 180.0; //angulo interno del 16-agono en radianes
	G4double a = astr2/std::cos(angintradian/2); // hipotenusa del triangulo formado con la aultura del rpc y base la distancia del centro del MID al rpc
	G4double ax = astr2x/std::cos(angintradian/2); //es lo mismo pero para los extremos del absorber 
	double diferencia = (astr2*std::tan(angintradian/2))-(0.5*m); //Diferencia de alturas formada por el triangulo usando la altura del rpc y la altura del triangulo de base la distancia del centro al rpc y altura formada por el angulo de 11.25
	G4double diferenciax = (astr2x*std::tan(angintradian/2))-(0.5*m); //lo mismo pero para los extemos del absorber 
/////////////////Muon Absorber///////////////////////////
	G4Tubs* cil = new G4Tubs("cil", 2.05*m, 2.75*m, 3*m, 0.0, 360.0*degree);
	
	G4LogicalVolume *logiccil = new G4LogicalVolume(cil, steel, "logiccil");
	//fScoringVolume = logiccil; 
	G4RotationMatrix* rotationc = new G4RotationMatrix();
	rotationc->rotateY(90 * degree);	
	G4VisAttributes *vis = new G4VisAttributes(G4Colour(0.2, 0.2, 0.2));
	vis->SetVisibility(true);
	logiccil->SetVisAttributes(vis);
	G4VPhysicalVolume *physcil = new G4PVPlacement(rotationc, G4ThreeVector(0., 0., 0.), logiccil, "physcil", logicWorld, false, 0, true);
	
	
	G4Tubs* cil2 = new G4Tubs("cil2", 2.05*m, 2.6*m, 1*m, 0.0, 360.0*degree);
	G4LogicalVolume *logiccil2 = new G4LogicalVolume(cil2, steel, "logiccil2");
	G4RotationMatrix* rotationc2 = new G4RotationMatrix();
	rotationc2->rotateY(90 * degree);	
	G4VisAttributes *vis2 = new G4VisAttributes(G4Colour(0.2, 0.2, 0.2));
	vis2->SetVisibility(true);
	logiccil2->SetVisAttributes(vis2);
	G4VPhysicalVolume *physcil2 = new G4PVPlacement(rotationc2, G4ThreeVector(4.00001*m, 0., 0.), logiccil2, "physcil2", logicWorld, false, 0, true);
	
	G4Tubs* cil3 = new G4Tubs("cil3", 2.05*m, 2.6*m, 1*m, 0.0, 360.0*degree);
	G4LogicalVolume *logiccil3 = new G4LogicalVolume(cil3, steel, "logiccil3"); 
	G4RotationMatrix* rotationc3 = new G4RotationMatrix();
	rotationc3->rotateY(90 * degree);	
	G4VisAttributes *vis3 = new G4VisAttributes(G4Colour(0.2, 0.2, 0.2));
	vis3->SetVisibility(true);
	logiccil3->SetVisAttributes(vis3);
	G4VPhysicalVolume *physcil3 = new G4PVPlacement(rotationc3, G4ThreeVector(-4.00001*m, 0., 0.), logiccil3, "physcil3", logicWorld, false, 0, true);
////////////////////////////////////Strips de primer capa de RPCs//////////////////////
G4Box* solidStripR1 = new G4Box("solidStripR1", anchstr/2, 0.5*m, 0.00005*m);
      	logicStripR1 = new G4LogicalVolume(solidStripR1, cobre, "logicStripR1");
      	fScoringVolume = logicStripR1;
	for(double x1=-4.5; x1 <= 4.5; x1++) {
		for (int k = 0; k < 16; k++) {
   			double angulogrados = 0+k*22.5;//para crear el anillo de volumenes, de ahi los 22.5 grados
			double anguloradian = angulogrados * M_PI / 180.0;//se pasan de radianes a grados
			// l es para las strips que seran 20
			for (int l = 0; l < ns; l++) {
				G4double xPos = x1*1*m+(0.5*m-(anchstr/2))-l*separacion;  //Separación de 2 veces el tamaño del volumen en el eje x
 				G4RotationMatrix* rotation = new G4RotationMatrix();//Se crea una matriz de rotación para colocar ls strips en el anillo
 				G4VisAttributes *vis1 = new G4VisAttributes(G4Colour(0.9, 0.8, 0.0));
				vis1->SetVisibility(true);
				logicStripR1->SetVisAttributes(vis1);
				rotation->rotateX(angulogrados * degree);
				if (-2.5 <= x1 && x1 < 3.5)
       			G4VPhysicalVolume *physStripR1 = new G4PVPlacement(rotation, G4ThreeVector(xPos, astr1*std::sin(anguloradian) , astr1*std::cos(anguloradian)), logicStripR1, "physStripR1", logicWorld, false, 1+l+k*ns+(ns*16)*x1, true);//la constante de k se ajusta para contar las strips al igual que la constante de x1
       			else 
       			G4VPhysicalVolume *physStripR1 = new G4PVPlacement(rotation, G4ThreeVector(xPos, astr1x*std::sin(anguloradian) , astr1x*std::cos(anguloradian)), logicStripR1, "physStripR1", logicWorld, false, 1+l+k*ns+(ns*16)*x1, true);//la constante de k se ajusta para contar las strips al igual que la constante de x1
						}
					}
				}
///////////////////////Acrilicos para primera capa de RPC///////////////////////////////////////						
  G4Box *solidacrilR1 = new G4Box("solidacrilR1", 0.5*m, 0.5*m, 0.0005*m); 
        G4LogicalVolume *logicacrilR1 = new G4LogicalVolume(solidacrilR1, acrylic, "logicalacrilR1");
		for (int p2 = 0; p2 < 16; p2++) {
			double angulogrados = 0+p2*22.5; //22.5 porque es el resultado de 360/16
			double anguloradian = angulogrados * M_PI / 180.0;
			for(double x1=-4.5; x1 <= 4.5 ; x1++) { 
				G4RotationMatrix* rotation = new G4RotationMatrix();
				rotation->rotateX(angulogrados * degree);
				G4VisAttributes *vis2 = new G4VisAttributes(G4Colour(0.6, 0.0, 0.0));
				vis2->SetVisibility(true);
				logicacrilR1->SetVisAttributes(vis2);
				if (-2.5 <= x1 && x1 < 3.5)
				G4VPhysicalVolume *physacrilR1 = new G4PVPlacement(rotation, G4ThreeVector(x1*m, aacrR1*std::sin(anguloradian) , aacrR1*std::cos(anguloradian)), logicacrilR1, "physacrilR1", logicWorld, false, 0, true);
				else 
				G4VPhysicalVolume *physacrilR1 = new G4PVPlacement(rotation, G4ThreeVector(x1*m, aacrR1x*std::sin(anguloradian) , aacrR1x*std::cos(anguloradian)), logicacrilR1, "physacrilR1", logicWorld, false, 0, true);
							}
			
						}
///////////////////Pintura primer capa de RPC//////////////////
	G4Box *solidpinturaR1 = new G4Box("solidpinturaR1", 0.5*m, 0.5*m, 0.00005*m);
	G4LogicalVolume *logicpinturaR1 = new G4LogicalVolume(solidpinturaR1, grafito, "logicalpinturaR1");
		for (int p3 = 0; p3 < 16; p3++) {
			double angulogrados = 0+p3*22.5;
			double anguloradian = angulogrados * M_PI / 180.0;
			for(double x1=-4.5; x1 <= 4.5; x1++) {
				G4RotationMatrix* rotation = new G4RotationMatrix();
				rotation->rotateX(angulogrados * degree);
				G4VisAttributes *vis3 = new G4VisAttributes(G4Colour(0.0, 0.0, 0.0));
				vis3->SetVisibility(true);
				logicpinturaR1->SetVisAttributes(vis3);
				if (-2.5 <= x1 && x1 < 3.5)
				G4VPhysicalVolume *physacrilR1 = new G4PVPlacement(rotation, G4ThreeVector(x1*m, apinR1*std::sin(anguloradian) , apinR1*std::cos(anguloradian)), logicpinturaR1, "physpinturaR1", logicWorld, false, 0, true);
				else 
				G4VPhysicalVolume *physacrilR1 = new G4PVPlacement(rotation, G4ThreeVector(x1*m, apinR1x*std::sin(anguloradian) , apinR1x*std::cos(anguloradian)), logicpinturaR1, "physpinturaR1", logicWorld, false, 0, true);
							}
						}			

///////////////////Vidrio primer capa de RPC//////////////////
	G4Box *solidvid1R1 = new G4Box("solidvid1R1", 0.5*m, 0.5*m, 0.001*m);
	G4LogicalVolume *logicvid1R1 = new G4LogicalVolume(solidvid1R1, glass, "logicalvid1R1");
		for (int p4 = 0; p4 < 16; p4++) {
			double angulogrados = 0+p4*22.5;
			double anguloradian = angulogrados * M_PI / 180.0;
			for(double x1=-4.5; x1 <= 4.5; x1++) {
				G4RotationMatrix* rotation = new G4RotationMatrix();
				rotation->rotateX(angulogrados * degree);
				G4VisAttributes *vis4 = new G4VisAttributes(G4Colour(0.8, 0.8, 1.0));
				vis4->SetVisibility(true);
				logicvid1R1->SetVisAttributes(vis4);
				if (-2.5 <= x1 && x1 < 3.5)
				G4VPhysicalVolume *physvid1R1 = new G4PVPlacement(rotation, G4ThreeVector(x1*1*m, avid1R1*std::sin(anguloradian) , avid1R1*std::cos(anguloradian)), logicvid1R1, "physvid1R1", logicWorld, false, 0, true);
				else 
				G4VPhysicalVolume *physvid1R1 = new G4PVPlacement(rotation, G4ThreeVector(x1*1*m, avid1R1x*std::sin(anguloradian) , avid1R1x*std::cos(anguloradian)), logicvid1R1, "physvid1R1", logicWorld, false, 0, true);
							}
						}
/////////////Gaps para primer capa de RPCs///////////////////
	G4Box *solidgap1R1 = new G4Box("solidgap1R1", 0.5*m, 0.5*m, 0.0005*m);
	//logicgap1R1 = new G4LogicalVolume(solidgap1R1, freonMixture, "logicalgap1R1");
	fScoringVolume = logicgap1R1;
	for(int n = 0; n < 4; n++) {
		for (int p5 = 0; p5 < 16; p5++) {
			double angulogrados = 0+p5*22.5;
			double anguloradian = angulogrados * M_PI / 180.0;
			for(double x1=-4.5; x1 <= 4.5; x1++) {
    				G4RotationMatrix* rotation = new G4RotationMatrix();
    				G4VisAttributes *vis5 = new G4VisAttributes(G4Colour(0.9, 0.9, 0.8));
				vis5->SetVisibility(true);
				logicgap1R1->SetVisAttributes(vis5);
				rotation->rotateX(angulogrados * degree);
				if (n<2)
					if (-2.5 <= x1 && x1 < 3.5)
					G4VPhysicalVolume *physgap1R1 = new G4PVPlacement(rotation, G4ThreeVector(x1*1*m, (agap1R1+n*0.003*m)*std::sin(anguloradian) , (agap1R1+n*0.003*m)*std::cos(anguloradian)), logicgap1R1, "physgap1R1", logicWorld, false, 0, true);
					else 
					G4VPhysicalVolume *physgap1R1 = new G4PVPlacement(rotation, G4ThreeVector(x1*1*m, (agap1R1x+n*0.003*m)*std::sin(anguloradian) , (agap1R1x+n*0.003*m)*std::cos(anguloradian)), logicgap1R1, "physgap1R1", logicWorld, false, 0, true);
					
				else
					if (-2.5 <= x1 && x1 < 3.5)
					G4VPhysicalVolume *physgap1R1 = new G4PVPlacement(rotation, G4ThreeVector(x1*1*m, (agap1R2+(n-2)*0.003*m)*std::sin(anguloradian) , (agap1R2+(n-2)*0.003*m)*std::cos(anguloradian)), logicgap1R1, "physgap1R1", logicWorld, false, 0, true);
					else 
					G4VPhysicalVolume *physgap1R1 = new G4PVPlacement(rotation, G4ThreeVector(x1*1*m, (agap1R2x+(n-2)*0.003*m)*std::sin(anguloradian) , (agap1R2x+(n-2)*0.003*m)*std::cos(anguloradian)), logicgap1R1, "physgap1R1", logicWorld, false, 0, true);
									}
								}
						}
/////////////////Segundo vidrio primer capa de RPCs///////////////
	G4Box *solidvid2R1 = new G4Box("solidvid2R1", 0.5*m, 0.5*m, 0.001*m);
	G4LogicalVolume *logicvid2R1 = new G4LogicalVolume(solidvid2R1, glass, "logicalvid2R1");
		for (int p6 = 0; p6 < 16; p6++) {
			double angulogrados = 0+p6*22.5;
			double anguloradian = angulogrados * M_PI / 180.0;
			for(double x1= -4.5; x1 <= 4.5; x1++) {
				G4RotationMatrix* rotation = new G4RotationMatrix();
				rotation->rotateX(angulogrados * degree);
				G4VisAttributes *vis6 = new G4VisAttributes(G4Colour(0.8, 0.8, 1.0));
				vis6->SetVisibility(true);
				logicvid2R1->SetVisAttributes(vis6);
				if (-2.5 <= x1 && x1 < 3.5)
				G4VPhysicalVolume *physvid2R1 = new G4PVPlacement(rotation, G4ThreeVector(x1*1*m, avid2R1*std::sin(anguloradian) , avid2R1*std::cos(anguloradian)), logicvid2R1, "physvid2R1", logicWorld, false, 0, true);
				else 
				G4VPhysicalVolume *physvid2R1 = new G4PVPlacement(rotation, G4ThreeVector(x1*1*m, avid2R1x*std::sin(anguloradian) , avid2R1x*std::cos(anguloradian)), logicvid2R1, "physvid2R1", logicWorld, false, 0, true);
							}
						}

/////Tercer vidrio primer capa de RPCs /////////////////////
	G4Box *solidvid3R1 = new G4Box("solidvid3R1", 0.5*m, 0.5*m, 0.001*m);
	G4LogicalVolume *logicvid3R1 = new G4LogicalVolume(solidvid3R1, glass, "logicalvid3R1");
		for (int p8 = 0; p8 < 16; p8++) {
			double angulogrados = 0+p8*22.5;
			double anguloradian = angulogrados * M_PI / 180.0;
			for(double x1= -4.5; x1 <= 4.5; x1++) {
				G4RotationMatrix* rotation = new G4RotationMatrix();
				rotation->rotateX(angulogrados * degree);
				G4VisAttributes *vis8 = new G4VisAttributes(G4Colour(0.8, 0.8, 1.0));
				vis8->SetVisibility(true);
				logicvid3R1->SetVisAttributes(vis8);
				if (-2.5 <= x1 && x1 < 3.5)
				G4VPhysicalVolume *physvid3R1 = new G4PVPlacement(rotation, G4ThreeVector(x1*1*m, avid3R1*std::sin(anguloradian) , avid3R1*std::cos(anguloradian)), logicvid3R1, "physvid3R1", logicWorld, false, 0, true);
				else
				G4VPhysicalVolume *physvid3R1 = new G4PVPlacement(rotation, G4ThreeVector(x1*1*m, avid3R1x*std::sin(anguloradian) , avid3R1x*std::cos(anguloradian)), logicvid3R1, "physvid3R1", logicWorld, false, 0, true);
						}
					}
///////Segunda capa de pintura para primer capa de RPCs////////////////////////////////
	G4Box *solidpintura2R1 = new G4Box("solidpintura2R1", 0.5*m, 0.5*m, 0.00005*m);
	G4LogicalVolume *logicpintura2R1 = new G4LogicalVolume(solidpintura2R1, grafito, "logicalpintura2R1");
		for (int p9 = 0; p9 < 16; p9++) {
			double angulogrados = 0+p9*22.5;
    			double anguloradian = angulogrados * M_PI / 180.0;
			for(double x1=-4.5 ; x1 <= 4.5; x1++) {           
    				G4RotationMatrix* rotation = new G4RotationMatrix();
				rotation->rotateX(angulogrados * degree);
				G4VisAttributes *vis9 = new G4VisAttributes(G4Colour(0.0, 0.0, 0.0));
				vis9->SetVisibility(true);
				logicpintura2R1->SetVisAttributes(vis9);
				if (-2.5 <= x1 && x1 < 3.5)
       			G4VPhysicalVolume *physpintura2R1 = new G4PVPlacement(rotation, G4ThreeVector(x1*1*m, apin2R1*std::sin(anguloradian) , apin2R1*std::cos(anguloradian)), logicpintura2R1, "physpintura2R1", logicWorld, false, 0, true);
       			else
       			G4VPhysicalVolume *physpintura2R1 = new G4PVPlacement(rotation, G4ThreeVector(x1*1*m, apin2R1x*std::sin(anguloradian) , apin2R1x*std::cos(anguloradian)), logicpintura2R1, "physpintura2R1", logicWorld, false, 0, true);
    								}
						}
////////Segundo acrilico para primer capa de RPCs//////////////////////////////////
	G4Box *solidacril2R1 = new G4Box("solidacril2R1", 0.5*m, 0.5*m, 0.0005*m);
	G4LogicalVolume *logicacril2R1 = new G4LogicalVolume(solidacril2R1, acrylic, "logicalacril2R1");
		for (int p10 = 0; p10 < 16; p10++) {
				double angulogrados = 0+p10*22.5;
				double anguloradian = angulogrados * M_PI / 180.0;
				for(double x1= -4.5; x1 <= 4.5; x1++) {  
					G4RotationMatrix* rotation = new G4RotationMatrix();
					rotation->rotateX(angulogrados * degree);
					G4VisAttributes *vis10 = new G4VisAttributes(G4Colour(0.6, 0.0, 0.0));
					vis10->SetVisibility(true);
					logicacril2R1->SetVisAttributes(vis10);
					if (-2.5 <= x1 && x1 < 3.5)
					G4VPhysicalVolume *physacril2R1 = new G4PVPlacement(rotation, G4ThreeVector(x1*1*m, aacr2R1*std::sin(anguloradian) , aacr2R1*std::cos(anguloradian)), logicacril2R1, "physacril2R1", logicWorld, false, 0, true);
					else 
					G4VPhysicalVolume *physacril2R1 = new G4PVPlacement(rotation, G4ThreeVector(x1*1*m, aacr2R1x*std::sin(anguloradian) , aacr2R1x*std::cos(anguloradian)), logicacril2R1, "physacril2R1", logicWorld, false, 0, true);
								}
						}
//////////////////////////Segundo RPC///////////////////////////////
/////////////////Strips horizontales para segunda capa de RPCs///////////////
	
	G4Box* solidStripR2 = new G4Box("solidStripR2", 0.5*m, (anchstr/2), 0.00005*m);
	G4LogicalVolume *logicStripR2 = new G4LogicalVolume(solidStripR2, cobre, "logicStripR2");
	//fScoringVolume = logicStripR2;
		//fScoringVolume = logicStripR2; //para saber cuantos muones 
		for(double x1=-4.5; x1 <= 4.5; x1++){//x1 es para ciclar los strips a lo largo del MUONID
			for (int s2 = 0; s2 < 16; s2++) {
				double angulogrados = s2*22.5;
    				double anguloradian = angulogrados * M_PI / 180.0;
    				double angulogamarad = 78.75 * M_PI / 180.0;
    				for (int n = 0; n < ns; n++) {//Vamos a usar ley de cosenos
    	 				//G4double a = 2.9262*m;//no es el apotema, es el lado del triangulo que va del centro al centro de la RPC
    	 				if (-2.5 <= x1 && x1 < 3.5){
    	 				double b = (diferencia+(anchstr/2))+separaciony*n;//esta es la distancia del primer strip al lado que va al centro del rpc 
    	 				double cosg = std::cos(angulogamarad);//es el coseno del angulo interno del triangulo 
    	 				double l = sqrt((a*a)+(b*b)-2*a*b*cosg);//ley de cosenos
    	 				double beta = acos((a*a+l*l-b*b)/(2*a*l));
    	 				double alpha = (11.25+s2*22.5)* M_PI / 180.0-beta;
        				double yPos = l*std::sin(alpha); 
       				double zPos = l*std::cos(alpha); 
    					G4RotationMatrix* rotationy = new G4RotationMatrix();
    					rotationy->rotateX(angulogrados * degree);
    					G4VisAttributes *vis11 = new G4VisAttributes(G4Colour(0.9, 0.8, 0.0));
					vis11->SetVisibility(true);
					logicStripR2->SetVisAttributes(vis11);
       				G4VPhysicalVolume *physStripR2 = new G4PVPlacement(rotationy, G4ThreeVector(x1*1*m, yPos , zPos), logicStripR2, "physStripR2", logicWorld, false, 1+n+s2*ns+x1*(ns*16), true);}
       				
       				else {
       				double b = (diferenciax+(anchstr/2))+separaciony*n;//esta es la distancia del primer strip al lado que va al centro del rpc 
    	 				double cosg = std::cos(angulogamarad);//es el coseno del angulo interno del triangulo 
    	 				double l = sqrt(ax*ax+b*b-2*ax*b*cosg);//ley de cosenos
    	 				double beta = acos((ax*ax+l*l-b*b)/(2*ax*l));
    	 				double alpha = (11.25+s2*22.5)* M_PI / 180.0-beta;
        				double yPos = l*std::sin(alpha); 
       				double zPos = l*std::cos(alpha); 
    					G4RotationMatrix* rotationy = new G4RotationMatrix();
    					rotationy->rotateX(angulogrados * degree);
    					G4VisAttributes *vis11 = new G4VisAttributes(G4Colour(0.9, 0.8, 0.0));
					vis11->SetVisibility(true);
					logicStripR2->SetVisAttributes(vis11);
       				G4VPhysicalVolume *physStripR2 = new G4PVPlacement(rotationy, G4ThreeVector(x1*1*m, yPos , zPos), logicStripR2, "physStripR2", logicWorld, false, 1+n+s2*ns+x1*(ns*16), true);
       				}
								}
    							}
   						}
	
	
	
	
//////////////////Primer acrilico segunda capa de RPCs/////////////
	G4Box *solidacrilR2 = new G4Box("solidacrilR2", 0.5*m, 0.5*m, 0.0005*m);
    	G4LogicalVolume *logicacrilR2 = new G4LogicalVolume(solidacrilR2, acrylic, "logicalacrilR2");
		for (int a2 = 0; a2 < 16; a2++) {
 			double angulogrados = 0+a2*22.5;
			double anguloradian = angulogrados * M_PI / 180.0;
			for(double  x1=-4.5; x1 <= 4.5; x1++) {
				G4RotationMatrix* rotation = new G4RotationMatrix();
				rotation->rotateX(angulogrados * degree);
				G4VisAttributes *vis12 = new G4VisAttributes(G4Colour(0.6, 0.0, 0.0));
				vis12->SetVisibility(true);
				logicacrilR2->SetVisAttributes(vis12);
				if (-2.5 <= x1 && x1 < 3.5)
				G4VPhysicalVolume *physacrilR2 = new G4PVPlacement(rotation, G4ThreeVector(x1*1*m, aacrR2*std::sin(anguloradian) , aacrR2*std::cos(anguloradian)), logicacrilR2, "physacrilR2", logicWorld, false, 0, true);
				else 
				G4VPhysicalVolume *physacrilR2 = new G4PVPlacement(rotation, G4ThreeVector(x1*1*m, aacrR2x*std::sin(anguloradian) , aacrR2x*std::cos(anguloradian)), logicacrilR2, "physacrilR2", logicWorld, false, 0, true);
						}
					}
////////////////////Primer pintura segunda capa de RPCs//////////////////
 	G4Box *solidpinturaR2 = new G4Box("solidpinturaR2", 0.5*m, 0.5*m, 0.00005*m);
     	G4LogicalVolume *logicpinturaR2 = new G4LogicalVolume(solidpinturaR2, grafito, "logicalpinturaR2");
    		for (int a3 = 0; a3 < 16; a3++) {
   			double angulogrados = 0+a3*22.5;
   			double anguloradian = angulogrados * M_PI / 180.0;
    			for(double x1=-4.5; x1 <= 4.5; x1++) {
    				G4RotationMatrix* rotation = new G4RotationMatrix();
    				rotation->rotateX(angulogrados * degree);
    				G4VisAttributes *vis13 = new G4VisAttributes(G4Colour(0.0, 0.0, 0.0));
				vis13->SetVisibility(true);
				logicpinturaR2->SetVisAttributes(vis13);
				if (-2.5 <= x1 && x1 < 3.5)
     				G4VPhysicalVolume *physpinturaR2 = new G4PVPlacement(rotation, G4ThreeVector(x1*1*m, apinR2*std::sin(anguloradian) , apinR2*std::cos(anguloradian)), logicpinturaR2, "physpinturaR2", logicWorld, false, 0, true);
     				else 
     				G4VPhysicalVolume *physpinturaR2 = new G4PVPlacement(rotation, G4ThreeVector(x1*1*m, apinR2x*std::sin(anguloradian) , apinR2x*std::cos(anguloradian)), logicpinturaR2, "physpinturaR2", logicWorld, false, 0, true);
						}
					}
////////////////////////Primer vidrio segunda capa de RPCs/////////////
	G4Box *solidvid1R2 = new G4Box("solidvid1R2", 0.5*m, 0.5*m, 0.001*m);
      	G4LogicalVolume *logicvid1R2 = new G4LogicalVolume(solidvid1R2, glass, "logicalvid1R2"); 
    		for (int a4 = 0; a4 < 16; a4++) {
    			double angulogrados = 0+a4*22.5;
    			double anguloradian = angulogrados * M_PI / 180.0;
   			for(double x1=-4.5; x1 <= 4.5; x1++) {
    				G4RotationMatrix* rotation = new G4RotationMatrix();
    				rotation->rotateX(angulogrados * degree);
    				G4VisAttributes *vis14 = new G4VisAttributes(G4Colour(0.8, 0.8, 1.0));
				vis14->SetVisibility(true);
				logicvid1R2->SetVisAttributes(vis14);
				if (-2.5 <= x1 && x1 < 3.5)
       			G4VPhysicalVolume *physvid1R2 = new G4PVPlacement(rotation, G4ThreeVector(x1*1*m, avid1R2*std::sin(anguloradian) , avid1R2*std::cos(anguloradian)), logicvid1R2, "physvid1R2", logicWorld, false, 0, true);
       			else 
       			G4VPhysicalVolume *physvid1R2 = new G4PVPlacement(rotation, G4ThreeVector(x1*1*m, avid1R2x*std::sin(anguloradian) , avid1R2x*std::cos(anguloradian)), logicvid1R2, "physvid1R2", logicWorld, false, 0, true);
    							}
						}

////////Segudo vidrio segunda capa de RPCs///////////////
     	G4Box *solidvid2R2 = new G4Box("solidvid2R2", 0.5*m, 0.5*m, 0.001*m);
	G4LogicalVolume *logicvid2R2 = new G4LogicalVolume(solidvid2R2, glass, "logicalvid2R2");
   		for (int a6 = 0; a6 < 16; a6++) {
  			double angulogrados = 0+a6*22.5;
   			double anguloradian = angulogrados * M_PI / 180.0;
   			for(double x1=-4.5; x1 <= 4.5; x1++) {
    				G4RotationMatrix* rotation = new G4RotationMatrix();
    				rotation->rotateX(angulogrados * degree);
    				G4VisAttributes *vis16 = new G4VisAttributes(G4Colour(0.8, 0.8, 1.0));
				vis16->SetVisibility(true);
				logicvid2R1->SetVisAttributes(vis16);
				if (-2.5 <= x1 && x1 < 3.5)
       			G4VPhysicalVolume *physvid2R2 = new G4PVPlacement(rotation, G4ThreeVector(x1*1*m, avid2R2*std::sin(anguloradian) , avid2R2*std::cos(anguloradian)), logicvid2R2, "physvid2R2", logicWorld, false, 0, true);
       			else 
       			G4VPhysicalVolume *physvid2R2 = new G4PVPlacement(rotation, G4ThreeVector(x1*1*m, avid2R2x*std::sin(anguloradian) , avid2R2x*std::cos(anguloradian)), logicvid2R2, "physvid2R2", logicWorld, false, 0, true);
   							}
						}

/////////////////////////Tercer vidrio segunda capa de RPCs/////////////////////
     	G4Box *solidvid3R2 = new G4Box("solidvid3R2", 0.5*m, 0.5*m, 0.001*m);
     	G4LogicalVolume *logicvid3R2 = new G4LogicalVolume(solidvid3R2, glass, "logicalvid3R2");
  		for (int a8 = 0; a8 < 16; a8++) {
  			double angulogrados = 0+a8*22.5;
   			double anguloradian = angulogrados * M_PI / 180.0;
   			for(double x1=-4.5; x1 <= 4.5; x1++) {
   				G4RotationMatrix* rotation = new G4RotationMatrix();
   				rotation->rotateX(angulogrados * degree);
   				G4VisAttributes *vis18 = new G4VisAttributes(G4Colour(0.8, 0.8, 1.0));
				vis18->SetVisibility(true);
				logicvid3R2->SetVisAttributes(vis18);
				if (-2.5 <= x1 && x1 < 3.5)
     				G4VPhysicalVolume *physvid3R2 = new G4PVPlacement(rotation, G4ThreeVector(x1*1.0*m, avid3R2*std::sin(anguloradian) , avid3R2*std::cos(anguloradian)), logicvid3R2, "physvid3R2", logicWorld, false, 0, true);
     				else
     				G4VPhysicalVolume *physvid3R2 = new G4PVPlacement(rotation, G4ThreeVector(x1*1.0*m, avid3R2x*std::sin(anguloradian) , avid3R2x*std::cos(anguloradian)), logicvid3R2, "physvid3R2", logicWorld, false, 0, true);
   							}
						}
///////Segunda pintura segunda capa de RPCs////////////////////////////////
      	G4Box *solidpintura2R2 = new G4Box("solidpintura2R2", 0.5*m, 0.5*m, 0.00005*m);
     	G4LogicalVolume *logicpintura2R2 = new G4LogicalVolume(solidpintura2R2, grafito, "logicalpintura2R2");
  	//fScoringVolume = logicgap2R2;
  		for (int a9 = 0; a9 < 16; a9++) {
  			double angulogrados = 0+a9*22.5;
  			double anguloradian = angulogrados * M_PI / 180.0;
  			for(double x1=-4.5; x1 <= 4.5; x1++) {
   				G4RotationMatrix* rotation = new G4RotationMatrix();
  				rotation->rotateX(angulogrados * degree);
  				G4VisAttributes *vis19 = new G4VisAttributes(G4Colour(0.0, 0.0, 0.0));
				vis19->SetVisibility(true);
				logicpintura2R2->SetVisAttributes(vis19);
				if (-2.5 <= x1 && x1 < 3.5)
       			G4VPhysicalVolume *physpintura2R2 = new G4PVPlacement(rotation, G4ThreeVector(x1*1*m, apin2R2*std::sin(anguloradian) , apin2R2*std::cos(anguloradian)), logicpintura2R2, "physpintura2R2", logicWorld, false, 0, true);
       			else 
       			G4VPhysicalVolume *physpintura2R2 = new G4PVPlacement(rotation, G4ThreeVector(x1*1*m, apin2R2x*std::sin(anguloradian) , apin2R2x*std::cos(anguloradian)), logicpintura2R2, "physpintura2R2", logicWorld, false, 0, true);
   							}
						}
////////////////////// Segundo acrilico segunda capa de RPCs//////////////////////////////////
      	G4Box *solidacril2R2 = new G4Box("solidacril2R2", 0.5*m, 0.5*m, 0.0005*m);
      	G4LogicalVolume *logicacril2R2 = new G4LogicalVolume(solidacril2R2, acrylic, "logicalacril2R2");
      	//fScoringVolume = logicacril2R2;
  		for (int a10 = 0; a10 < 16; a10++) {
    			double angulogrados = 0+a10*22.5;
    			double anguloradian = angulogrados * M_PI / 180.0;
    			for(double x1=-4.5; x1 <= 4.5; x1++) {
   				G4RotationMatrix* rotation = new G4RotationMatrix();
    				rotation->rotateX(angulogrados * degree);
    				G4VisAttributes *vis20 = new G4VisAttributes(G4Colour(0.6, 0.0, 0.0));
				vis20->SetVisibility(true);
				logicacril2R2->SetVisAttributes(vis20);
				if (-2.5 <= x1 && x1 < 3.5)
       			G4VPhysicalVolume *physacril2R2 = new G4PVPlacement(rotation, G4ThreeVector(x1*1*m, aacr2R2*std::sin(anguloradian) , aacr2R2*std::cos(anguloradian)), logicacril2R2, "physacril2R2", logicWorld, false, 0, true);
       			else 
       			G4VPhysicalVolume *physacril2R2 = new G4PVPlacement(rotation, G4ThreeVector(x1*1*m, aacr2R2x*std::sin(anguloradian) , aacr2R2x*std::cos(anguloradian)), logicacril2R2, "physacril2R2", logicWorld, false, 0, true);
    							}
						}


	return physWorld;
}

void DetectorConstruction::ConstructSDandField()
{
	//SensitiveDetector2 *sensDet2 = new SensitiveDetector2("SensitiveDetector2");
	
	//logicStripR2->SetSensitiveDetector(sensDet2);
	
	
	SensitiveDetector *sensDet = new SensitiveDetector("SensitiveDetector");
	
	logicgap1R1->SetSensitiveDetector(sensDet);

	
	//SensitiveDetector3 *sensDet3 = new SensitiveDetector3("SensitiveDetector3");
	
	//logiccil->SetSensitiveDetector(sensDet3);
}
