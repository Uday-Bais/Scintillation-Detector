#include "action.hh"

ActionInitialization::ActionInitialization()
{}
ActionInitialization::~ActionInitialization()
{}
void ActionInitialization::Build() const
{
    PrimaryGenerator *generator = new PrimaryGenerator();
    SetUserAction(generator);
    RunAction *runAction = new RunAction();
    SetUserAction(runAction);
    EventAction *eventAction = new EventAction(runAction);
    SetUserAction(eventAction);
    SteppingAction *steppingAction = new SteppingAction(eventAction);
    SetUserAction(steppingAction);
}