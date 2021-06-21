#include "comparison.h"
#include <iostream>

using namespace std;

// n xx
void readTemplate(int subjectID, int (&tempArr)[1024]){

	// 64, 128 or 512 xx
    string s = "/Users/jonasolafsson/Documents/speciale/biometrics.nosync/small/feretbin512/" + to_string(subjectID) + ".txt";

    char * path = new char [s.size() + 1];
    strcpy(path, s.c_str());


    ifstream template1;
    template1.open(path);
    if (!template1) {
        cerr << "Unable to open file " + s;
        exit(1);
    }
	
    for(int i = 0;  i< n; i++){
        if(template1.get() == 48){
            tempArr[i] = 0;
        }
        else tempArr[i] = 1;
    }

    template1.close();
}

// C xx
void setupEncDB(Ciphertext<Poly> (&encDB)[256], CryptoContext<Poly> &cc, LPKeyPair<Poly> &keyPair) {
	vector<vector<int64_t>> plainDB(C, vector<int64_t> (2048, 0));
	int plain[1024] = {};  //[n]x
	
	for(int i = 0; i<C; i++) { // Each cipher
		for(int j = 0; j<N; j++) { // Each subject
			readTemplate(j+i*N, plain);
			for(int k = 0; k<n; k++) { // Each feature
				plainDB[i][j*n+k] = plain[k];
			}
		}
	}
	for(int i = 0; i<C; i++) {
		Plaintext tempP = cc->MakeCoefPackedPlaintext(plainDB[i]);
		encDB[i] = cc->Encrypt(keyPair.publicKey, tempP);
	}
}


void setupEncProbe(Ciphertext<Poly> (&encProbe), CryptoContext<Poly> &cc, LPKeyPair<Poly> keys) {
	// n xx
	int probe[1024] = {};
	readTemplate(999, probe);
	// s xx
	vector<int64_t> Probe(2048);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < N; j++) {
			Probe[j*n + i] = probe[i];
		}
		
	}
	Plaintext temp = cc->MakeCoefPackedPlaintext(Probe);
	encProbe = cc->Encrypt(keys.publicKey, temp);
}

void compareOne(Ciphertext<Poly> (&encTemplate), Ciphertext<Poly> (&encProbe), CryptoContext<Poly> &cc, LPKeyPair<Poly> & keys) {
	encTemplate = cc->EvalAdd(encTemplate, encProbe);
}

// C xx
void compareAll(Ciphertext<Poly> (&encDB)[256], Ciphertext<Poly> (&encProbe), CryptoContext<Poly> &cc, LPKeyPair<Poly> & keys) {
	for(int i = 0; i < C; i++) {
		compareOne(encDB[i], encProbe, cc, keys);
	}
}