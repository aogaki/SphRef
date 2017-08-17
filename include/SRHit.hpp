#ifndef SRHit_h
#define SRHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4Types.hh"
#include "G4ThreeVector.hh"


class SRHit : public G4VHit
{
public:
   SRHit();
   virtual ~SRHit();
   SRHit(const SRHit &right);
   const SRHit &operator=(const SRHit &right);
   int operator==(const SRHit &right) const;

   inline void *operator new(size_t);
   inline void  operator delete(void *);

   // add setter/getter methods

private:

};

typedef G4THitsCollection<SRHit> SRHitsCollection;

extern G4ThreadLocal G4Allocator<SRHit> *SRHitAllocator;

inline void *SRHit::operator new(size_t)
{
   if (!SRHitAllocator)
      SRHitAllocator = new G4Allocator<SRHit>;
   return (void *)SRHitAllocator->MallocSingle();
}

inline void SRHit::operator delete(void *hit)
{
   SRHitAllocator->FreeSingle((SRHit *) hit);
}

#endif
