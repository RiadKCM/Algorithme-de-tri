#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>



void benchmark(char *nom, int taille, int min, int max)
{
    int i, val, j;
    FILE *fp;
    fp = fopen(nom, "w"); // creation du fichier
    //fprintf(fp, "%d\n\n", taille); // enregistrement de la taille des tableaux

    // tableau croissant
    for (i = 0; i < taille; i++) fprintf(fp ,"%d ",i); // Ligne modifiée
    fprintf(fp, "\n");

    // tableau decroissant
    for (i = 0; i < taille; i++) fprintf(fp ,"%d ",taille -i -1); // Ligne modifiée
    fprintf(fp, "\n");

    // tableau constant
    val = rand() % (max - min) + min;
    for (i = 0; i < taille; i++) fprintf(fp ,"%d ",val); // Ligne modifiée
    fprintf(fp, "");

    // tableaux aléatoires
    for (i = 0; i < 96; i++) // on génère 500 tableaux
    {
        fprintf(fp, "\n");
        for (j = 0; j < taille; j++) fprintf(fp ,"%d ",rand () %( max - min ) +min ); // Ligne modifiée
    }
    fprintf(fp,"\n");

    // tableaux aléatoires pair
    for (int i = 0; i < taille; i++) {
        fprintf(fp,"%d ", (rand() % 51) * 2);
    }

    printf("\n");




    fclose(fp);
}


void is_sorted(int tab[],int taille){
    for(int i=0;i<=taille;i++){
        if(tab[i]>tab[i+1]){
            printf("desc");
        }
        printf("ascII");
    }
}

int *creation_tableau(int taille){
    int *tab = (int *)malloc(taille * sizeof (int));
    if(tab == NULL){
        printf("Erreur lors de l'allocation");
    }
    return tab;
}

void affichage_tableau(char tab[][60], int taille) {
    printf("\n");
    for (int i = 0; i < taille; i++) {
        printf("%s ", tab[i]);
    }
    printf("\n");
}


void initialisation_aleatoire(int *tab, int taille, int min, int max){
    for (int i = 0; i < taille; i++) printf("%d ",rand () %( max - min ) +min );
}

void copie_tableau(int * source, int * destination, int taille){
    if(sizeof(source) != sizeof(destination)){
        printf("Erreur !!!");
    }else{
        for(int i=0;i<taille;i++){
            destination[i] = source[i];
        }
    }
}

// Tri à bulle
void bubble_sort(int *tab, int taille) {
    int var;
    for (int i = 0; i < taille - 1; i++) {
        for (int j = 0; j < taille - i - 1; j++) {
            if (tab[j] > tab[j + 1]) {
                var = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = var;
            }
        }
    }
}

//Tri par insertion
void insertion_sort(int *tab, int taille){
    for(int i=0;i<taille;i++){
        int k = tab[i];
        int j = i-1;

        while (j>=0 && tab[j]>k){
            tab[j+1] = tab[j];
            j--;
        }
        tab[j+1] = k;
    }
}

//Tri par comptage
void counting_sort(int *tab , int taille){
    if (taille <= 1) {
        return;
    }

    int max = tab[0];
    for (int i = 1; i < taille; i++) {
        if (tab[i] > max) {
            max = tab[i];
        }
    }

    int *count = (int *)malloc(sizeof(int) * (max + 1));
    for (int i = 0; i <= max; i++) {
        count[i] = 0;
    }

    for (int i = 0; i < taille; i++) {
        count[tab[i]]++;
    }

    int index = 0;
    for (int i = 0; i <= max; i++) {
        while (count[i] > 0) {
            tab[index] = i;
            index++;
            count[i]--;
        }
    }
    free(count);
}

//Tri par selection
void selection_sort(int* tab, int taille){
    for (int i = 0; i < taille - 1; i++) {
        int min_index = i;

        for (int j = i + 1; j < taille; j++) {
            if (tab[j] < tab[min_index]) {
                min_index = j;
            }
        }

        int temp = tab[i];
        tab[i] = tab[min_index];
        tab[min_index] = temp;
    }
}

//Tri par fusion
void merge(int *arr, int left[], int right[], int left_size, int right_size) {
    int i = 0, j = 0, k = 0;

    while (i < left_size && j < right_size) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < left_size) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < right_size) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void merge_sort(int *tab, int taille) {
    if (taille <= 1) {
        return; 
    }

    int mid = taille / 2;
    int left_size = mid;
    int right_size = taille - mid;

    int *left = (int *)malloc(sizeof(int) * left_size);
    int *right = (int *)malloc(sizeof(int) * right_size);

    for (int i = 0; i < left_size; i++) {
        left[i] = tab[i];
    }
    for (int i = 0; i < right_size; i++) {
        right[i] = tab[mid + i];
    }

    merge_sort(left, left_size);
    merge_sort(right, right_size);
    merge(tab, left, right, left_size, right_size);

    free(left);
    free(right);
    
}

//Tri par combinaison
void comb_sort(int *tab, int taille) {
    int intervalle = taille;
    bool swapped = true;

    while (intervalle > 1 || swapped) {
        if (intervalle > 1) {
            intervalle = (intervalle * 10) / 13;
        }

        swapped = false;

        for (int i = 0; i < taille - intervalle; i++) {
            if (tab[i] > tab[i + intervalle]) {
                int temp = tab[i];
                tab[i] = tab[i + intervalle];
                tab[i + intervalle] = temp;
                swapped = true;
            }
        }
    }
}

//Tri par arboresance
struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *insert(struct TreeNode *root, int key) {
    if (root == NULL) {
        struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
        newNode->data = key;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (key < root->data) {
        root->left = insert(root->left, key);
    } else if (key >= root->data) {
        root->right = insert(root->right, key);
    }
    return root;
}

void inOrder(struct TreeNode *root, int *arr, int *index) {
    if (root != NULL) {
        inOrder(root->left, arr, index);
        arr[(*index)++] = root->data;
        inOrder(root->right, arr, index);
    }
}

void tree_sort(int *tab, int taille) {
    struct TreeNode *root = NULL;
    for (int i = 0; i < taille; i++) {
        root = insert(root, tab[i]);
    }

    int index = 0;
    inOrder(root, tab, &index);
}

double calculer_moyenne(double *temps_exec, int nb_tableaux) {
    double somme = 0.0;

    for (int i = 0; i < nb_tableaux; i++) {
        somme += temps_exec[i];
    }

    double moyenne = somme / nb_tableaux;
    return moyenne;
}

int main(void){
    benchmark("C.txt",60,0,20);
    int *tab=creation_tableau(20);
    FILE *fichier = fopen("C.txt", "r");
    
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return 1;
    }
    
    int ligneActuelle = 0;

    char lignes[1000][600]; 
    
    
    while (fgets(lignes[ligneActuelle], sizeof(lignes[ligneActuelle]), fichier)) {
        if (lignes[ligneActuelle][strlen(lignes[ligneActuelle]) - 1] == '\n') {
            lignes[ligneActuelle][strlen(lignes[ligneActuelle]) - 1] = '\0';
        }
        ligneActuelle++;
        
        if (ligneActuelle >= 1000) {
            printf("Limite de lignes atteinte. Arrêt de la lecture.\n");
            break;
        }
    }
    
    // Imprimer les lignes stockées dans le tableau
    // for (int i = 0; i < ligneActuelle; i++) {
    //     printf("Ligne %d : %s\n", i + 1, lignes[i]);
    // }

    fclose(fichier);

    double temps_execution[1000];
    int nb_mesures = 0;

    for (int i = 0; i < ligneActuelle; i++) {
        int tab[60]; // Tableau pour stocker les entiers

        char *token = strtok(lignes[i], " ");
        int j = 0;
        while (token != NULL) {
            tab[j++] = atoi(token);
            token = strtok(NULL, " ");
        }


        clock_t start = clock();
        
        tree_sort(tab, j);

        clock_t end = clock();
        double temps_ecoule = (double)(end - start) / CLOCKS_PER_SEC;

        temps_execution[nb_mesures] = temps_ecoule;
        nb_mesures++;

        // bubble_sort(tab, j);
        // insertion_sort(tab,j);
        // counting_sort(tab,j);
        // selection_sort(tab,j);
        // merge_sort(tab,j);
        // comb_sort(tab,j);
        // tree_sort(tab,j);



        // Réécriture du tableau trié dans le fichier ou affichage
        // printf("Tableau trie %d: ", i + 1);
        // for (int k = 0; k < j; k++) {
        //     printf("%d ", tab[k]);
        // }
        // printf("\n");
        // printf("\n");
    }

    double somme_temps_execution = 0.0;
    for (int i = 0; i < nb_mesures; i++) {
        somme_temps_execution += temps_execution[i];
    }

    double moyenne_temps_execution = calculer_moyenne(temps_execution, ligneActuelle);
    printf("Moyenne du temps d'execution : %f secondes\n", moyenne_temps_execution);

    return 0;

    

}
