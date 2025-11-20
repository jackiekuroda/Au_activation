#include "SteppingAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Neutron.hh"
#include "G4Proton.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Event.hh"

G4int SteppingAction::fTotalNeutroncount = 0;
G4int SteppingAction::fTotalNeutronproduced = 0;
SteppingAction::SteppingAction(){}
SteppingAction::~SteppingAction(){}


void SteppingAction::UserSteppingAction(const G4Step* step)
{
        G4Track *track = step->GetTrack();
        if (!track) return;


        if (track->GetParentID() > 0 && track->GetDefinition() == G4Neutron::NeutronDefinition() && track->GetCurrentStepNumber() == 1)
        {
           G4String pname = track->GetDefinition()->GetParticleName();
           G4String process = "unknown";
           if (track->GetCreatorProcess())
               process = track->GetCreatorProcess()->GetProcessName();

           fTotalNeutronproduced++;

         G4cout << "[Secondary] "
               << pname
               << " | created by: " << process
               << " | KE: " << track->GetKineticEnergy() / MeV << " MeV"
               << G4endl;

        }


    if (track->GetDefinition() != G4Neutron::Definition())
        return;


if (track->GetLogicalVolumeAtVertex() &&
    track->GetLogicalVolumeAtVertex()->GetName() == "logCrystal") // or whatever your detector's logical volume is named
{
    return; // neutron was created inside the detector, skip it
}


 if (!track->GetUserInformation())
    {
        track->SetUserInformation(new MyTrackInfo());
    }


        auto* info = static_cast<MyTrackInfo*>(track->GetUserInformation());
        if (!info) return;
        if (info->counted) return;

    const G4StepPoint* prePoint = step->GetPreStepPoint();
    const G4StepPoint* postPoint = step->GetPostStepPoint();
    if (!prePoint || !postPoint) return;

    G4VPhysicalVolume* preVol = prePoint->GetTouchableHandle()->GetVolume();
    G4VPhysicalVolume* postVol = postPoint->GetTouchableHandle()->GetVolume();
    if (!preVol || !postVol) return;

    G4String preName = preVol->GetName();
    G4String postName = postVol->GetName();

    // Count if neutron enters or leaves/stops in the detector
    bool entered = (preName != "physidetector" && postName == "physidetector");
    bool stoppedIn = (preName == "physidetector" && postName != "physidetector");

    if (entered || stoppedIn)
        {
           info->counted = true;

           G4double kineticEnergy = track->GetKineticEnergy();
           auto* analysisManager = G4AnalysisManager::Instance();
           analysisManager->FillH1(0, kineticEnergy);

           fTotalNeutroncount++;

        }



}
