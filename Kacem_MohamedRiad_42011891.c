#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>


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


void gnome_sort(int *tab, int taille) {
    int index = 0;

    while (index < taille) {
        if (index == 0)
            index++;
        if (tab[index] >= tab[index - 1])
            index++;
        else {
            int temp = tab[index];
            tab[index] = tab[index - 1];
            tab[index - 1] = temp;
            index--;
        }
    }
}


void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void odd_even_sort(int *tab, int taille) {
    bool isSorted = false;

    while (!isSorted) {
        isSorted = true;

        for (int i = 0; i < taille - 1; i += 2) {
            if (tab[i] > tab[i + 1]) {
                swap(&tab[i], &tab[i + 1]);
                isSorted = false;
            }
        }

        for (int i = 1; i < taille - 1; i += 2) {
            if (tab[i] > tab[i + 1]) {
                swap(&tab[i], &tab[i + 1]);
                isSorted = false;
            }
        }
    }
}


void merge(int *tab, int debut, int milieu, int fin) {
    int taille1 = milieu - debut + 1;
    int taille2 = fin - milieu;

    int *gauche = (int *)malloc(taille1 * sizeof(int));
    int *droite = (int *)malloc(taille2 * sizeof(int));

    for (int i = 0; i < taille1; i++) {
        gauche[i] = tab[debut + i];
    }

    for (int j = 0; j < taille2; j++) {
        droite[j] = tab[milieu + 1 + j];
    }

    int i = 0, j = 0, k = debut;

    while (i < taille1 && j < taille2) {
        if (gauche[i] <= droite[j]) {
            tab[k] = gauche[i];
            i++;
        } else {
            tab[k] = droite[j];
            j++;
        }
        k++;
    }

    while (i < taille1) {
        tab[k] = gauche[i];
        i++;
        k++;
    }

    while (j < taille2) {
        tab[k] = droite[j];
        j++;
        k++;
    }

    free(gauche);
    free(droite);
}

void merge_sort(int *tab, int debut, int fin) {
    if (debut < fin) {
        int milieu = debut + (fin - debut) / 2;

        merge_sort(tab, debut, milieu);
        merge_sort(tab, milieu + 1, fin);

        merge(tab, debut, milieu, fin);
    }
}


int partitionner(int *tab, int debut, int fin) {
    int pivot = tab[fin];
    int i = debut - 1;

    for (int j = debut; j < fin; j++) {
        if (tab[j] <= pivot) {
            i++;
            swap(&tab[i], &tab[j]);
        }
    }

    swap(&tab[i + 1], &tab[fin]);
    return i + 1;
}

void quicksort(int *tab, int debut, int fin) {
    if (debut < fin) {
        int pivotIndex = partitionner(tab, debut, fin);

        quicksort(tab, debut, pivotIndex - 1);
        quicksort(tab, pivotIndex + 1, fin);
    }
}

void cocktail_sort(int *tab, int taille) {
    int debut = 0;
    int fin = taille - 1;
    int echange = 1;

    while (echange) {
        echange = 0;
        for (int i = debut; i < fin; i++) {
            if (tab[i] > tab[i + 1]) {
                swap(&tab[i], &tab[i + 1]);
                echange = 1;
            }
        }

        if (!echange) break;

        fin--;

        echange = 0;
        for (int i = fin - 1; i >= debut; i--) {
            if (tab[i] > tab[i + 1]) {
                swap(&tab[i], &tab[i + 1]);
                echange = 1;
            }
        }

        debut++;
    }
}


