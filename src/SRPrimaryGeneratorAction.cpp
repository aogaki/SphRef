#include <TFile.h>

#include <G4SystemOfUnits.hh>
#include <G4AutoLock.hh>
#include <G4ParticleTable.hh>
#include <G4ChargedGeantino.hh>
#include <G4IonTable.hh>
#include <Randomize.hh>
#include <g4root.hh>

#include "SRPrimaryGeneratorAction.hpp"

static G4int nEveInPGA = 0;
G4Mutex mutexInPGA = G4MUTEX_INITIALIZER;


SRPrimaryGeneratorAction::SRPrimaryGeneratorAction()
   : G4VUserPrimaryGeneratorAction(),
     fParticleGun(nullptr)
{
   fParticleGun = new G4ParticleGun(1);

   auto particleTable = G4ParticleTable::GetParticleTable();
   auto particle = particleTable->FindParticle("gamma");
   fParticleGun->SetParticleDefinition(particle);
   fParticleGun->SetParticlePosition(G4ThreeVector(0., 100.*mm, 0.));
   fParticleGun->SetParticleEnergy(511.*keV);
   fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., -1., 0.));
}

SRPrimaryGeneratorAction::~SRPrimaryGeneratorAction()
{
   delete fParticleGun;
}

void SRPrimaryGeneratorAction::GeneratePrimaries(G4Event *event)
{
   fParticleGun->GeneratePrimaryVertex(event);

   G4AutoLock lock(&mutexInPGA);
   if (nEveInPGA++ % 10000 == 0)
      G4cout << nEveInPGA - 1 << " events done" << G4endl;
}
