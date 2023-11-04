#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int RC4(unsigned char * data, unsigned char * key, int data_len, int key_len){
    unsigned char S[256];
    unsigned char T[256];
    unsigned char keystream[sizeof(data)];
    int i;
    int j;
    int y;
    unsigned char temp = 0;

    // Initialize S and T vectors
    for(i=0; i<256; i++){
        S[i] = i;
        T[i] = key[i % key_len];
    }

    // KSA -> Permutation
    j = 0;
    for(i=0; i<256; i++){
        j = (j + S[i] + T[i]) % 256;
        //swap
        temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }

    // PRGA -> Generates a Keystream
    i = 0;
    j = 0;
    for(y=0; y<data_len; y++){
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;

        // swap
        temp = 0;
        temp = S[i];
        S[i] = S[j];
        S[j] = temp;

        temp = (S[i] + S[j]) % 256;
        keystream[y] =  S[temp];
    }

    // XOR -> Data with PRGA Keystream
    for(i=0; i<data_len; i++){
        data[i] = data[i] ^ keystream[i];
    }
    return 0;
}

int main(void) {

    int i;
    unsigned char data[] = {0xb7, 0x9a, 0x54, 0x6f, 0x6c, 0x53, 0xd1, 0x8e, 0x0d, 0x3d, 0xca, 0x11, 0x5d, 0x6b, 0xdf, 0x03, 0xad, 0x60};
    unsigned char key[] = {0x70, 0x61, 0x73, 0x73, 0x77, 0x6f, 0x72, 0x64};
    
    printf("RC4 algorithm:\n\n");

    printf("[!] Encrypted Data\n");
    for(i=0; i<sizeof(data); i++){
        printf("%c", data[i]);
    }

    
    RC4(data, key, sizeof(data), sizeof(key));
    printf("\n\n[!] Decrypted Data\n");
    for(i=0; i<sizeof(data); i++){
        printf("%c", data[i]);
    }

}