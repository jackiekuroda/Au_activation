#include "StackingAction.hh"
#include "G4Track.hh"
#include "G4Event.hh"
#include "G4Gamma.hh"
#include "G4Neutron.hh"
#include "G4EventManager.hh"
#include "G4SystemOfUnits.hh"

StackingAction::StackingAction() : G4UserStackingAction() {}
StackingAction::~StackingAction() {}

G4ClassificationOfNewTrack StackingAction::ClassifyNewTrack(const G4Track* track)
{
   const G4ParticleDefinition* particleType = track->GetDefinition();

   if (particleType == G4Gamma::Gamma())
   {
	G4double global_time = track->GetGlobalTime();
	if (global_time < 600*s){return fKill;}
	//if (global_time > 365 * 24.0 * 3600*s){return fKill;}
   }

   return fUrgent;
}

