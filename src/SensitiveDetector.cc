#include "SensitiveDetector.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4ParticleDefinition.hh"
#include "G4Neutron.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"
#include "G4ParticleTable.hh"


SensitiveDetector::SensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{
}

SensitiveDetector::~SensitiveDetector()
{
}

void SensitiveDetector::Initialize(G4HCofThisEvent *)
{
}

G4bool SensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
	G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
        G4Track *track =aStep->GetTrack();
        G4ParticleDefinition *particle = track->GetDefinition();
	G4double EnergyDeposited = track->GetKineticEnergy();
	fTotalEnergyDeposited = fTotalEnergyDeposited + EnergyDeposited;
        return true;
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent *)
{
    	G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
//    	analysisManager->FillH1(0,  fTotalEnergyDeposited);
}

