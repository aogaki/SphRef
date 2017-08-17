#include <iomanip>

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "SRHit.hpp"


G4ThreadLocal G4Allocator<SRHit> *SRHitAllocator = 0;


SRHit::SRHit()
   : G4VHit()
{}

SRHit::~SRHit()
{}

SRHit::SRHit(const SRHit & /*right*/)
   : G4VHit()
{}

const SRHit &
SRHit::operator=(const SRHit & /*right*/)
{
   return *this;
}

int SRHit::operator==(const SRHit & /*right*/) const
{
   return 0;
}
