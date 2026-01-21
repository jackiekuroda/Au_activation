#include "StackingAction.hh"
#include "G4Track.hh"
#include "G4Event.hh"
#include "G4Gamma.hh"
#include "G4Neutron.hh"
#include "G4EventManager.hh"
#include "G4SystemOfUnits.hh"

StackingAction::StackingAction() : G4UserStackingAction() {}
StackingAction::~StackingAction() {}

G4ClassifiactionOfNewTrack StackingAction::ClassifyNewTrack(const G4Track* track)
{

}

