#include <G4Tubs.hh>
#include <G4Box.hh>
#include <G4NistManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4SDManager.hh>
#include <G4LogicalVolumeStore.hh>
#include <G4PVReplica.hh>
#include <G4RunManager.hh>
#include <G4Element.hh>

#include "SRDetectorConstruction.hpp"
#include "SRSD.hpp"


SRDetectorConstruction::SRDetectorConstruction()
   : fVacuumMat(nullptr),
     fAirMat(nullptr),
     fScintiMat(nullptr)
{
   fCheckOverlap = true;
   DefineMaterials();
}

SRDetectorConstruction::~SRDetectorConstruction()
{}

void SRDetectorConstruction::DefineMaterials()
{
   G4NistManager *manager = G4NistManager::Instance();

   // NIST database materials
   fVacuumMat = manager->FindOrBuildMaterial("G4_Galactic");
   fAirMat = manager->FindOrBuildMaterial("G4_AIR");

   // Scintillator LYSO.  The amount of Ce or dope is very small.  I don't use
   auto eleO = manager->FindOrBuildElement("O");
   auto eleLu = manager->FindOrBuildElement("Lu");
   auto eleY = manager->FindOrBuildElement("Y");

   // L2 O3
   auto matL2O3 = new G4Material("LutetiumOxide", 9.41*g/cm3, 2);
   matL2O3->AddElement(eleLu, 2);	
   matL2O3->AddElement(eleO, 3);

   // Si O2
   auto matSiO2 = manager->FindOrBuildMaterial("G4_SILICON_DIOXIDE");

   // Y2 O3
   auto matY2O3 = new G4Material("YttriumOxide", 5.01*g/cm3, 2);
   matY2O3->AddElement(eleY, 2);	
   matY2O3->AddElement(eleO, 3);

   auto matLYSO = new G4Material("LYSO", 7.1*g/cm3, 3);
   matLYSO->AddMaterial(matL2O3, 81*perCent);
   matLYSO->AddMaterial(matSiO2, 14*perCent);
   matLYSO->AddMaterial(matY2O3, 5*perCent);

   fScintiMat = matLYSO;
}

G4VPhysicalVolume *SRDetectorConstruction::Construct()
{
   // world volume
   G4double worldX = 0.6*m;
   G4double worldY = 0.6*m;
   G4double worldZ = 0.6*m;
   
   G4Box *worldS = new G4Box("World", worldX / 2., worldY / 2., worldZ / 2.);
   G4LogicalVolume *worldLV = new G4LogicalVolume(worldS, fAirMat, "World");

   G4VisAttributes *visAttributes = new G4VisAttributes(G4Colour::White());
   visAttributes->SetVisibility(false);
   worldLV->SetVisAttributes(visAttributes);
   fVisAttributes.push_back(visAttributes);

   G4VPhysicalVolume *worldPV
      = new G4PVPlacement(nullptr, G4ThreeVector(), worldLV, "World", 0,
                          false, 0, fCheckOverlap);

   // Scintillator
   G4double scintiX = 0.01*m;
   G4double scintiY = 0.01*m;
   G4double scintiZ = 0.01*m;

   G4Box *scintiS = new G4Box("Scintillator", scintiX / 2., scintiY / 2., scintiZ / 2.);
   G4LogicalVolume *scintiLV = new G4LogicalVolume(scintiS, fScintiMat, "Scintillator");

   visAttributes = new G4VisAttributes(G4Colour::Cyan());
   scintiLV->SetVisAttributes(visAttributes);
   fVisAttributes.push_back(visAttributes);

   auto scintiPos = G4ThreeVector(0., 0., 0.);
   new G4PVPlacement(nullptr, scintiPos, scintiLV, "Scintillator", worldLV,
                     false, 0, fCheckOverlap);

   MakeMPTable();
   fScintiMat->SetMaterialPropertiesTable(fLYSOTable);
   fAirMat->SetMaterialPropertiesTable(fAirTable);

   return worldPV;
}

void SRDetectorConstruction::MakeMPTable()
{
   // This is copied from https://github.com/cacunas/ParG4_cluster/blob/master/LYSO/src/LYSOGeometry.cc
   const G4int num = 21;
   G4double ene[num]   =  {1.79*eV, 1.85*eV, 1.91*eV, 1.97*eV,
                           2.04*eV, 2.11*eV, 2.19*eV, 2.27*eV,
                           2.36*eV, 2.45*eV, 2.56*eV, 2.67*eV,
                           2.80*eV, 2.94*eV, 3.09*eV, 3.25*eV,
                           3.44*eV, 3.65*eV, 3.89*eV, 4.16*eV,
                           4.43*eV};

   G4double fast[num]  =  {0.01, 0.10, 0.20, 0.50,
                           0.90, 1.70, 2.90, 5.00,
                           8.30, 12.5, 17.0, 22.9,
                           26.4, 25.6, 16.8, 4.20,
                           0.30, 0.20, 0.10, 0.01,
                           0.00};

   G4double rLyso[num] =  {1.81, 1.81, 1.81, 1.81,
                           1.81, 1.81, 1.81, 1.81,
                           1.81, 1.81, 1.81, 1.81,
                           1.81, 1.81, 1.81, 1.81,
                           1.81, 1.81, 1.81, 1.81,
                           1.81};
   G4double rAir[num]  =  {1.00, 1.00, 1.00, 1.00,
                           1.00, 1.00, 1.00, 1.00,
                           1.00, 1.00, 1.00, 1.00,
                           1.00, 1.00, 1.00, 1.00,
                           1.00, 1.00, 1.00, 1.00,
                           1.00};

   G4double abs[num]   =  {50*cm, 50*cm, 50*cm, 50*cm,
                           50*cm, 50*cm, 50*cm, 50*cm,
                           50*cm, 50*cm, 50*cm, 50*cm,
                           50*cm, 50*cm, 50*cm, 50*cm,
                           50*cm, 50*cm, 50*cm, 50*cm,
                           50*cm};

   fLYSOTable = new G4MaterialPropertiesTable();
   fAirTable = new G4MaterialPropertiesTable();
   
   fLYSOTable->AddProperty("FASTCOMPONENT", ene, fast, num);
   fLYSOTable->AddProperty("RINDEX", ene, rLyso , num);
   fLYSOTable->AddProperty("ABSLENGTH", ene, abs, num);
   fLYSOTable->AddConstProperty("SCINTILLATIONYIELD",32./keV);
   fLYSOTable->AddConstProperty("RESOLUTIONSCALE", 1);
   fLYSOTable->AddConstProperty("FASTTIMECONSTANT",41*ns);

   fAirTable->AddProperty("RINDEX" , ene, rAir , num);
 
}

void SRDetectorConstruction::ConstructSDandField()
{
// Sensitive Detectors
   G4VSensitiveDetector *SD = new SRSD("SD", "HC");
   G4SDManager::GetSDMpointer()->AddNewDetector(SD);
   
   G4LogicalVolumeStore *lvStore = G4LogicalVolumeStore::GetInstance();
   for(auto &&lv: *lvStore){
      if(lv->GetName().contains("LGSORow") ||
         lv->GetName().contains("NaI"))
         SetSensitiveDetector(lv->GetName(), SD);
   }
}
