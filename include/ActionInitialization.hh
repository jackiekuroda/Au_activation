#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "DetectorConstruction.hh"
#include "SteppingAction.hh"

class ActionInitialization : public G4VUserActionInitialization

{
public:
    ActionInitialization(DetectorConstruction* detector, G4double beamEnergy, G4double detectorAngle, G4double targetthic);
    ~ActionInitialization();


    virtual void BuildForMaster() const;
    virtual void Build() const;

private:
    DetectorConstruction* fDetector;
    G4double fBeamEnergy;
    G4double fdetectorAngle;
    G4double ftargetthic;
};
#endif
