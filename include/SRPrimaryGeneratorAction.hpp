#ifndef SRPrimaryGeneratorAction_h
#define SRPrimaryGeneratorAction_h 1

#include <TH2.h>

#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4ParticleGun.hh>
#include <G4ThreeVector.hh>
#include <G4Threading.hh>
#include <G4Event.hh>
#include <G4GenericMessenger.hh>


class SRPrimaryGeneratorAction: public G4VUserPrimaryGeneratorAction
{
public:
   SRPrimaryGeneratorAction();
   virtual ~SRPrimaryGeneratorAction();

   virtual void GeneratePrimaries(G4Event *);

private:
   G4ParticleGun *fParticleGun;

};

#endif
