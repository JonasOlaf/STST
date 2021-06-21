#include "palisade.h"
using namespace lbcrypto;

extern int n;
extern int N;
extern int C;
extern int e;
extern int s;

// C e  xx
void decryptAll(Ciphertext<Poly> (&encDB)[256], int (&distances)[512], CryptoContext<Poly> &cc, LPKeyPair<Poly> &keys);