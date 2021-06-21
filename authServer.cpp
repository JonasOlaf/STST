#include "authServer.h"
#include "palisade.h"
#include <iostream>

using namespace std;
using namespace lbcrypto;

// C e xx
void decryptAll(Ciphertext<Poly> (&encDB)[256], int (&distances)[512], CryptoContext<Poly> &cc, LPKeyPair<Poly> &keys) {
	Plaintext result;
	int count = 0;
	for(int i = 0; i < C; i++) {  // Every cipher
		cc->Decrypt(keys.secretKey, encDB[i], &result);
		for(int j = 0; j < N; j++) {  // Every template per cipher
			for(int k = 0; k < n; k++) {  // Every feature per template
				if (real(result->GetCoefPackedValue()[j*n+k]) == 1) {
					count = count + 1;
				}
			}
			distances[i*N+j] = count;
			count = 0;
		}
	}
}