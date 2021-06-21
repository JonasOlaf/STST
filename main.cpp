#include <iostream>
#include "palisade.h"
#include "comparison.h"
#include "authServer.h"
#include <fstream>
#include <chrono>
#include <vector>

using namespace std;
using namespace lbcrypto;

// C x
Ciphertext<Poly> encDB[256] = {};
Ciphertext<Poly> encProbe = {};
int n = 1024;
int N = 2;
int C = 256;
int e = 512;
int s = 2048;


int main(){
	auto start = std::chrono::steady_clock::now();
	// Use StSt1 for s=1024, and use StSt3 for s=2048
	CryptoContext<Poly> cc = CryptoContextHelper::getNewContext("StSt3");
	cc->Enable(ENCRYPTION);
	cc->Enable(SHE);
	
	LPKeyPair<Poly> keys = cc->KeyGen();
	
	setupEncDB(encDB, cc, keys);
	
	auto initDone = std::chrono::steady_clock::now();
	setupEncProbe(encProbe, cc, keys);
	
	compareAll(encDB, encProbe, cc, keys);
	
	// e xx
	int distances[512] = {};
	decryptAll(encDB, distances, cc, keys);
	
	/*cout << distances[0] << endl;
	cout << distances[417] << endl;
	cout << distances[418] << endl;
	cout << distances[419] << endl;*/
	
	
	auto identificationDone = std::chrono::steady_clock::now();
	auto initTime = std::chrono::duration_cast<std::chrono::milliseconds>(initDone - start);
	auto identificationTime = std::chrono::duration_cast<std::chrono::milliseconds>(identificationDone - initDone);
	cout << "Initialisation:\t" << initTime.count() << " ms" << endl;
	cout << "Identification:\t" << identificationTime.count() << " ms"  << endl;
	return 0;
}