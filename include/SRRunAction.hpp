#ifndef SRRunAction_h
#define SRRunAction_h 1

#include <G4UserRunAction.hh>
#include <G4Run.hh>


class SRRunAction: public G4UserRunAction
{
public:
   SRRunAction();
   virtual ~SRRunAction();

   virtual void BeginOfRunAction(const G4Run *);
   virtual void EndOfRunAction(const G4Run *);

private:

};

#endif
