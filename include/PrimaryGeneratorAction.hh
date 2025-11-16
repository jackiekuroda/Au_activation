#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4Event.hh"

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction(G4double energy);
    ~PrimaryGeneratorAction() override;
    G4double GetBeamEnergy() const;

 public:
    void GeneratePrimaries(G4Event* event) override;

  private:
    G4ParticleGun* fParticleGun;
    G4double fBeamEnergy;
};


#endif
