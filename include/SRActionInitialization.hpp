#ifndef SRActionInitialization_h
#define SRActionInitialization_h 1

#include <G4VUserActionInitialization.hh>
#include <globals.hh>


class SRActionInitialization : public G4VUserActionInitialization
{
public:
   SRActionInitialization();
   virtual ~SRActionInitialization();

   virtual void BuildForMaster() const;
   virtual void Build() const;

private:
      
};

#endif
