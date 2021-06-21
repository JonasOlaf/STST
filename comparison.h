#include "palisade.h"
using namespace lbcrypto;

extern int n;
extern int N;
extern int C;
extern int e;
extern int s;

void readTemplate(int subjectID, int (&tempArr)[1024]);
void setupEncProbe(Ciphertext<Poly> (&encProbe), CryptoContext<Poly> &cc, LPKeyPair<Poly> keys);
// C xx
void setupEncDB(Ciphertext<Poly> (&encDB)[256], CryptoContext<Poly> &cc, LPKeyPair<Poly> &keyPair);



void compareOne(Ciphertext<Poly> (&encTemplate), Ciphertext<Poly> (&encProbe), CryptoContext<Poly> &cc, LPKeyPair<Poly> & keys);
// C xx
void compareAll(Ciphertext<Poly> (&encDB)[256], Ciphertext<Poly> (&encProbe), CryptoContext<Poly> &cc, LPKeyPair<Poly> & keys);