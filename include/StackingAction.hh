#ifndef StackingAction_h
#define StackingAction_h 1

#include "G4UserStackingAction.hh"
#include "G4ClassificationOfNewTrack.hh"
#include "globals.hh"

class G4Track

class StackingAction : public G4UserStackingAction
{
   public:
	StackingAction(EventAction*);
	~StackingAction();

   private:

};

#endif
