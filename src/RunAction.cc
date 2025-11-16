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
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    analysisManager->CreateH1("Edep", "Neutron", 8192, 0., 3.5 * MeV);

    analysisManager->CreateNtuple("Photons", "Photons");
    analysisManager->CreateNtupleIColumn("iEvent");
    analysisManager->CreateNtupleDColumn("fX");
    analysisManager->CreateNtupleDColumn("fY");
    analysisManager->CreateNtupleDColumn("fZ");
    analysisManager->CreateNtupleDColumn("fGlobalTime");
    analysisManager->CreateNtupleDColumn("fWlen");

    analysisManager->FinishNtuple(0);
}

RunAction::~RunAction()
{
}

void RunAction::BeginOfRunAction(const G4Run *run)
{
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    G4int runID = run->GetRunID();

    std::stringstream strRunID;
    strRunID << runID;

    G4double energyMeV = fPrimary->GetBeamEnergy() / MeV;
    G4double angleDeg = fDetector->GetdetAngle() / deg;
    G4double targetthic = fDetector ->Gettargetthic() / um;

    std::ostringstream energyStream;
    energyStream << std::fixed << std::setprecision(1) << energyMeV;
    std::string ene = energyStream.str();
    std::replace(ene.begin(), ene.end(), '.', '_');

    std::ostringstream angleStream;
    angleStream << static_cast<int>(std::round(angleDeg));
    std::string angle = angleStream.str();

    std::ostringstream thickStream;
    thickStream << static_cast<int>(std::round(targetthic));
    std::string thic = thickStream.str();

    std::string filename = ene + "MeV" + angle + "deg" + thic + "um.root";
    analysisManager->OpenFile(filename);
}

void RunAction::EndOfRunAction(const G4Run *run)
{
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
    G4int runID = run->GetRunID();
    G4cout << "Finishing run " << runID << G4endl;
    G4cout << "Total neutrons produced " << SteppingAction::fTotalNeutronproduced << G4endl;
    G4cout << "Total neutrons detected " << SteppingAction::fTotalNeutroncount << G4endl;
    SteppingAction::fTotalNeutroncount = 0;
}

