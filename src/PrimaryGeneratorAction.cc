#include "PrimaryGeneratorAction.hh"

//includes to make the source
#include "G4Event.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleGun.hh"
#include "G4Proton.hh"
#include "G4Neutron.hh"
#include "G4IonTable.hh"
#include "G4ParticleTable.hh"

//creatig the particle source
PrimaryGeneratorAction::PrimaryGeneratorAction(G4double energy): fBeamEnergy(energy)
{
        //setsnumber of particles per event
        fParticleGun = new G4ParticleGun(1);
        //for testing
        fParticleGun->SetParticleDefinition(G4Proton::ProtonDefinition());
	fParticleGun->SetParticleEnergy(fBeamEnergy);
        fParticleGun->SetParticlePosition(G4ThreeVector(0,0,-1*cm));
        fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
}
//for the event creation
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
   //creating an event

   fParticleGun->GeneratePrimaryVertex(anEvent);
}

G4double PrimaryGeneratorAction::GetBeamEnergy() const
{
    return fBeamEnergy;
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fParticleGun;
}


