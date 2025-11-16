#include "ActionInitialization.hh"
#include "SteppingAction.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4Region.hh"
#include "G4RegionStore.hh"

ActionInitialization::ActionInitialization(DetectorConstruction* detector, G4double targetthic) : fDetector(detector), ftargetthic(targetthic) {}

ActionInitialization::~ActionInitialization() {}

void ActionInitialization::BuildForMaster() const
{
  RunAction* runAction = new RunAction(fDetector, nullptr);
  SetUserAction(runAction);
}


void ActionInitialization::Build() const
{
  PrimaryGeneratorAction* generator = new PrimaryGeneratorAction();
  SetUserAction(generator);

  RunAction* runAction = new RunAction(fDetector, generator);
  SetUserAction(runAction);

  SteppingAction* stepAction = new SteppingAction();
  SetUserAction(stepAction);

}
