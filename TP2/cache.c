//
// Created by Antoine MAZURE on 07/03/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cache.h"

void init(ram* ram, cache* cache, int ram_size, int cache_size) {
    ram->size = ram_size;
    ram->data = (int) (int *) malloc(ram_size * sizeof(int));

    cache->size = cache_size;
    cache->data = (int) (int *) malloc(cache_size * sizeof(int));
}

void Gen_Input_File(int NB_cases_RAM) {
    FILE* fichier = fopen("input_file.txt", "w");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NB_cases_RAM; ++i) {
        int adresse = rand() % NB_cases_RAM;
        fprintf(fichier, "%d\n", adresse);
    }

    fclose(fichier);
}


int main() {
    int ram_size = 1024; // Taille de la RAM en mots
    int cache_size = 256; // Taille du cache en mots

    ram ram;
    cache cache;

    init(&ram, &cache, ram_size, cache_size);

    // Générer le fichier d'entrée
    Gen_Input_File(10000);

    // Simuler le cache
    // simulate_cache(&ram, &cache);

    // Calculer les métriques demandées (taux de succès, temps global d'accès, etc.)


    return 1;
}