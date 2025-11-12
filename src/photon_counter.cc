#include "photon_counter.hh"

// define the thread-local static storage
G4ThreadLocal G4long PhotonCounter::photonCount = 0;