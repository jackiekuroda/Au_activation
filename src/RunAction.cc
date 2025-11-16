#include "RunAction.hh"
#include "SensitiveDetector.hh"
#include "SteppingAction.hh"

#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "Randomize.hh"

#include <iomanip>

RunAction::RunAction(DetectorConstruction* detector, PrimaryGeneratorAction* primary)
  : fDetector(detector), fPrimary(primary)
{
}

RunAction::~RunAction()
{
}

void RunAction::BeginOfRunAction(const G4Run *run)
{
}

void RunAction::EndOfRunAction(const G4Run *run)
{
    G4int runID = run->GetRunID();
    G4cout << "Finishing run " << runID << G4endl;
    G4cout << "Total neutrons produced " << SteppingAction::fTotalNeutronproduced << G4endl;
    G4cout << "Total neutrons detected " << SteppingAction::fTotalNeutroncount << G4endl;
    SteppingAction::fTotalNeutroncount = 0;
}

