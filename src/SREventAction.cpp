#include <G4Event.hh>
#include <G4SDManager.hh>
#include <g4root.hh>

#include "SREventAction.hpp"


SREventAction::SREventAction()
   : G4UserEventAction(),
     fHitsCollectionID(-1)
{}

SREventAction::~SREventAction()
{}

SRHitsCollection *SREventAction::GetHitsCollection(G4int hcID, const G4Event *event)
const
{
   SRHitsCollection *hitsCollection 
      = static_cast<SRHitsCollection *>(
         event->GetHCofThisEvent()->GetHC(hcID));
  
   if ( ! hitsCollection ) {
      G4ExceptionDescription msg;
      msg << "Cannot access hitsCollection ID " << hcID;
      // check how to use G4Exception
      G4Exception("SREventAction::GetHitsCollection()",
                  "SRCode0003", FatalException, msg);
   }         

   return hitsCollection;
}

void SREventAction::BeginOfEventAction(const G4Event *)
{}

void SREventAction::EndOfEventAction(const G4Event *event)
{
   if (fHitsCollectionID == -1)
      fHitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID("HC");
   
   SRHitsCollection *hc = GetHitsCollection(fHitsCollectionID, event);
   const G4int kHit = hc->entries();
   for (G4int iHit = 0; iHit < kHit; iHit++) {
      SRHit *newHit = (*hc)[iHit];
   }

}

