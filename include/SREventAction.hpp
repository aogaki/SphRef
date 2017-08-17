#ifndef SREventAction_h
#define SREventAction_h 1

#include <G4UserEventAction.hh>

#include "SRHit.hpp"

class SREventAction : public G4UserEventAction
{
public:
   SREventAction();
   virtual ~SREventAction();

   virtual void BeginOfEventAction(const G4Event *);
   virtual void EndOfEventAction(const G4Event *);

private:
   SRHitsCollection *GetHitsCollection(G4int hcID, const G4Event *event) const;
   
   G4int fHitsCollectionID;
};

#endif
