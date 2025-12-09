#include "SteppingAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Neutron.hh"
#include "G4Proton.hh"
#include "G4Gamma.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Event.hh"

SteppingAction::SteppingAction(){}
SteppingAction::~SteppingAction(){}


void SteppingAction::UserSteppingAction(const G4Step* step)
{
        G4Track *track = step->GetTrack();
        if (!track) return;


        if (track->GetDefinition() == G4Gamma::GammaDefinition() && track->GetCurrentStepNumber() == 1)
        {
           G4String pname = track->GetDefinition()->GetParticleName();
           G4String process = "unknown";
           if (track->GetCreatorProcess())
               process = track->GetCreatorProcess()->GetProcessName();


//		if( //process == "nCapture" ||
		    //process == "NeutronCapture" ||
		    //process == "nInelastic" ||
//		    process == "RadioactiveDecay")
		{
         		G4cout  << "[Gamma created]"
               			<< " | created by: " << process
               			<< " | KE: " << track->GetKineticEnergy() / MeV << " MeV"
               			<< G4endl;

		}
        }

}
