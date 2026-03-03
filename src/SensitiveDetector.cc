#include "SensitiveDetector.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Neutron.hh"
#include "G4SystemOfUnits.hh"

SensitiveDetector::SensitiveDetector(G4String name)
: G4VSensitiveDetector(name), fTotalEnergyDeposited(0.)
{}

SensitiveDetector::~SensitiveDetector() {}

void SensitiveDetector::Initialize(G4HCofThisEvent *)
{
    fTotalEnergyDeposited = 0.0; // reset for each event
}

G4bool SensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *)
{

    G4double hitTime = aStep->GetPreStepPoint()->GetGlobalTime();
    //ignores neutrons used for activation
    if (hitTime < 550*s)
    {
        return true;
    }

    G4double edep = aStep->GetTotalEnergyDeposit();
    fTotalEnergyDeposited += edep;
    return true;
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent *)
{
    auto analysisManager = G4AnalysisManager::Instance();
    if (fTotalEnergyDeposited > 100 * keV)
    {
        analysisManager->FillH1(0, fTotalEnergyDeposited);
    }
}
