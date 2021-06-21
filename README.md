# STST

The encrypted identification was implemented using [Palisade](https://gitlab.com/palisade/palisade-release) in C++. The security level is 128 bits. The shown implementation uses features of 1024 bits and ciphertexts of 2048, but can easily be modified to other configurations.

The main.cpp file initialises the crypto context, handles timings, and calls the HE operations. Additionally it makes the decision of identity.

The comparison.cpp loads the biometric data, handles encryption and HE operations.

The authServer.cpp decrypts the ciphertexts into scores.
