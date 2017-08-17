#ifndef SRDetectorConstruction_h
#define SRDetectorConstruction_h 1

#include <vector>

#include <G4VUserDetectorConstruction.hh>
#include <G4VPhysicalVolume.hh>
#include <G4Material.hh>
#include <G4VisAttributes.hh>
#include <G4GenericMessenger.hh>


class SRDetectorConstruction : public G4VUserDetectorConstruction
{
public:
   SRDetectorConstruction();
   virtual ~SRDetectorConstruction();

   virtual G4VPhysicalVolume *Construct();
   virtual void ConstructSDandField();

private:
   G4bool fCheckOverlap;
   
   // Materials
   void DefineMaterials();
   G4Material *fVacuumMat;
   
   std::vector<G4VisAttributes *> fVisAttributes;

};

#endif
