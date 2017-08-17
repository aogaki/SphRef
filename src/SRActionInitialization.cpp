#include "SRActionInitialization.hpp"
#include "SRPrimaryGeneratorAction.hpp"
#include "SRRunAction.hpp"
#include "SREventAction.hpp"


SRActionInitialization::SRActionInitialization()
   : G4VUserActionInitialization()
{}

SRActionInitialization::~SRActionInitialization()
{}

void SRActionInitialization::BuildForMaster() const
{
   SetUserAction(new SRRunAction());
}

void SRActionInitialization::Build() const
{
   SetUserAction(new SRPrimaryGeneratorAction());
   SetUserAction(new SRRunAction());
   SetUserAction(new SREventAction());
}
