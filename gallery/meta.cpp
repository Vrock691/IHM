#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " </amuhome/q22011786/IHMPROJET/bleu.png>" << endl;
        return 1;
    }

    int width, height, actual_channels;
    
    unsigned char *pixels = stbi_load(argv[1], &width, &height, &actual_channels, 0);

    if (!pixels) {
        cerr << "Erreur : Impossible de lire l'image " << argv[1] << endl;
        return 1;
    }

    cout << "--- Informations sur l'image ---" << endl;
    cout << "Fichier    : " << argv[1] << endl;
    cout << "Largeur    : " << width << " px" << endl;
    cout << "Hauteur    : " << height << " px" << endl;
    cout << "Canaux     : " << actual_channels << endl;

    stbi_image_free(pixels);

    return 0;
}
