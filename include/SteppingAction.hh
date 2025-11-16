#ifndef SteppingAction_h
#define SteppingAction_h

#include "G4UserSteppingAction.hh"
#include "globals.hh"

#include "G4VUserTrackInformation.hh"

class MyTrackInfo : public G4VUserTrackInformation
{
public:
    MyTrackInfo() : counted(false) {}
    virtual ~MyTrackInfo() {}

    G4bool counted;
};

class G4ParticleDefinition;

class SteppingAction : public G4UserSteppingAction
{
  public:
   static G4int fTotalNeutroncount;
   static G4int fTotalNeutronproduced;
    SteppingAction();
    virtual ~SteppingAction();

    void UserSteppingAction(const G4Step*) override;

};

#endif
