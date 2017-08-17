#ifndef SRSD_h
#define SRSD_h 1

#include <G4VSensitiveDetector.hh>
#include <G4ThreeVector.hh>
#include <G4LogicalVolume.hh>

#include "SRHit.hpp"


class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class SRSD: public G4VSensitiveDetector
{
public:
   SRSD(const G4String &name,
            const G4String &hitsCollectionName);
   virtual ~SRSD();

   virtual void Initialize(G4HCofThisEvent *hce);
   virtual G4bool ProcessHits(G4Step *step, G4TouchableHistory *history);

private:
   SRHitsCollection *fHitsCollection;
};

#endif
