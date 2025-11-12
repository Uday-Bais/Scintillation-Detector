#ifndef PHOTONCOUNTER_HH
#define PHOTONCOUNTER_HH

#include "G4Types.hh"

class PhotonCounter {
public:
  static void Inc(G4int n = 1) { photonCount += n; }
  static G4long GetTotal() { return photonCount; }
  static void Reset() { photonCount = 0; }

private:
  static G4ThreadLocal G4long photonCount;
};

#endif