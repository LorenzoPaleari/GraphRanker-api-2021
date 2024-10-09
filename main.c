/**
 * @file main.c
 * @brief Implementation of a Red-Black Tree and Dijkstra's algorithm.
 *
 * This file contains the implementation of a Red-Black Tree and Dijkstra's algorithm
 * for finding the shortest paths in a graph. The program reads input from the standard
 * input, processes the data, and performs various operations including insertion into
 * the Red-Black Tree, rotations, and heap operations.
 *
 * @details
 * The program defines several structures and functions to manage the Red-Black Tree and
 * perform Dijkstra's algorithm. The main components include:
 * - Red-Black Tree node structure and related functions (insertion, rotations, fixing violations).
 * - Heap operations for managing nodes during Dijkstra's algorithm.
 * - Functions for reading and processing input data.
 * - Main function to control the flow of the program.
 *
 * @note
 * The program uses several global variables to manage the state of the tree and heap.
 * The input is read using `getchar_unlocked` for faster I/O operations.
 *
 * @author
 * Lorenzo Paleari
 * 
 * @date
 * 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int K;
int Nnodes;
int ContrStmp = 0;
int HeapSize = 0;

typedef enum{FALSE, TRUE} boolean;
typedef enum{RED, BLACK} Colour;

struct node {
    struct node* p;
    struct node* r;
    struct node* l;
    int Key;
    Colour color;
    int index;
};

typedef struct{
    int dist;
    int index;
}Node;

struct node* root = NULL;


/**
 * @brief Inserts a node into a red-black tree.
 *
 * This function takes a red-black tree (RBT) and a node, and inserts the node into the RBT
 * while maintaining the RBT properties.
 *
 * @param T A pointer to the root of the red-black tree.
 * @param X A pointer to the node to be inserted into the red-black tree.
 * @return A pointer to the root of the red-black tree after the insertion.
 */
struct node* insert(struct node* T, struct node* X){
    struct node* Curr;
    struct node* Pre;

    if (T == NULL)
        return X;

    Pre = NULL;

    Curr = T;
    while (Curr != NULL){
        Pre = Curr;
        if (X -> Key < Curr -> Key)
            Curr = Curr -> l;
        else
            Curr = Curr -> r;
    }

    X -> p = Pre;
    if (X -> Key < Pre -> Key)
        Pre -> l = X;
    else
        Pre -> r = X;

    return T;
}

/**
 * @brief Performs a left rotation on the given node.
 *
 * This function takes a pointer to a node and performs a left rotation
 * to balance the tree structure. It is typically used in self-balancing
 * binary search trees such as AVL trees or Red-Black trees.
 *
 * @param X A pointer to the node to be rotated.
 */
void LeftRotate(struct node* X){
    struct node* Dx = X -> r;

    X -> r = Dx -> l;

    if (Dx -> l != NULL)
        Dx -> l -> p = X;
    Dx -> p = X -> p;

    if (X -> p == NULL){
        root = Dx;
    }
    else if (X == X -> p -> l) {
        X -> p -> l = Dx;
    }
    else {
        X -> p -> r = Dx;
    }

    Dx -> l = X;
    X -> p = Dx;
}

/**
 * @brief Performs a right rotation on the given node.
 *
 * This function takes a pointer to a node and performs a right rotation,
 * which is a common operation in balanced binary search trees such as AVL trees.
 *
 * @param X A pointer to the node to be rotated.
 */
void RightRotate(struct node* X){
    struct node* Sx = X -> l;

    X -> l = Sx -> r;

    if (Sx -> r != NULL)
        Sx -> r -> p = X;
    Sx -> p = X -> p;

    if (X -> p == NULL){
        root = Sx;
    }
    else if (X == X -> p -> r) {
        X -> p -> r = Sx;
    }
    else {
        X -> p -> l = Sx;
    }

    Sx -> r = X;
    X -> p = Sx;
}

/**
 * @brief Repairs the Red-Black Tree after insertion.
 *
 * This function is responsible for fixing any violations of the Red-Black Tree
 * properties that may occur after a new node is inserted into the tree.
 *
 * @param root A pointer to the root node of the Red-Black Tree.
 * @param New A pointer to the newly inserted node that may cause violations.
 */
void RBinsert_and_repair(struct node* root, struct node* New){
    while ((New != root) && (New -> color != BLACK) && (New -> p -> color == RED)){
        if (New -> p == New -> p -> p -> l){
            struct node* Y = New -> p -> p -> r;

            if ((Y != NULL) && (Y -> color == RED)){
                New -> p -> color = BLACK;
                New -> p -> p -> color = RED;
                Y -> color = BLACK;
                New = New -> p -> p;
            }
            else {
                if (New == New -> p -> r) {
                    New = New -> p;
                    LeftRotate(New);
                }

                Colour app = New -> p -> color;
                New -> p -> color = New -> p -> p -> color;
                New -> p -> p -> color = app;
                RightRotate(New -> p -> p);
            }
        } else {
            struct node* Y = New -> p -> p -> l;

            if ((Y != NULL) && (Y -> color == RED))
            {
                New -> p -> color = BLACK;
                New -> p -> p -> color = RED;
                Y -> color = BLACK;
                New = New -> p -> p;
            }
            else {
                if (New == New -> p -> l) {
                    New = New -> p;
                    RightRotate(New);
                }

                Colour app = New -> p -> color;
                New -> p -> color = New -> p -> p -> color;
                New -> p -> p -> color = app;
                LeftRotate(New -> p -> p);
            }
        }
    }

    root -> color = BLACK;
}

/**
 * @brief Prints the contents of the binary tree.
 *
 * This function traverses the binary tree pointed to by T and prints its contents.
 *
 * @param T Pointer to the root node of the binary tree.
 */
void output_print(struct node *T){
    if (T == NULL)
        return;
    output_print(T->l);
    if (ContrStmp == 0){
        int Somma = T->index;
        int array[10] = {0,0,0,0,0,0,0,0,0,0};
        if (Somma == 0){
            putchar_unlocked('0');
        } else {
            int i = 0;
            while (Somma > 0) {
                array[i] = Somma % 10;
                i++;
                Somma = Somma / 10;
            }
            i--;
            while (i >= 0) {
                putchar_unlocked(array[i] + '0');
                i--;
            }
        }
        ContrStmp++;
    } else if (ContrStmp < K) {
        putchar_unlocked(' ');
        int Somma = T->index;
        int array[10] = {0,0,0,0,0,0,0,0,0,0};
        int i = 0;
        if (Somma == 0){
            putchar_unlocked('0');
        } else {
            while (Somma > 0) {
                array[i] = Somma % 10;
                i++;
                Somma = Somma / 10;
            }
            i--;
            while (i >= 0) {
                putchar_unlocked(array[i] + '0');
                i--;
            }
            ContrStmp++;
        }
    }
    output_print(T->r);
}

/**
 * @brief Finds the minimum node in the binary tree.
 *
 * This function traverses the binary tree to find the node with the minimum key value.
 *
 * @param T Pointer to the root node of the binary tree.
 * @return Pointer to the node with the minimum key value.
 */
struct node* min_val(struct node *T){
    struct node* Curr;
    Curr = T;
    while (Curr -> l != NULL){
        Curr = Curr -> l;
    }
    return Curr;
}

/**
 * @brief Finds the successor of a given node in the binary tree.
 *
 * This function finds the successor of a given node in the binary tree.
 *
 * @param minimo Pointer to the node whose successor is to be found.
 * @param Contatore Counter to keep track of the number of nodes visited.
 * @return Key value of the successor node.
 */
int successor(struct node* minimo, int Contatore){
    int CIAO;
    if (Contatore == K){
        CIAO = minimo -> Key;
        return CIAO;
    }

    struct node * y;
    if (minimo -> r != NULL) {
        Contatore++;
        y = min_val(minimo->r);
        CIAO = successor(y, Contatore);
        return CIAO;
    }
    else {
        y = minimo->p;
        while (y != NULL && y -> r == minimo){
            minimo = y;
            y = y -> p;
        }
        Contatore++;

        CIAO = successor(y, Contatore);
        return CIAO;
    }
}

/**
 * @brief Inserts a node into a max heap.
 *
 * This function inserts a node into a max heap and maintains the heap property.
 *
 * @param A Array representing the heap.
 * @param a Node to be inserted into the heap.
 */
void InsertMAX(Node A[], Node a){
    int i;
    Node c;

    HeapSize++;
    A[HeapSize].dist = a.dist;
    A[HeapSize].index = a.index;
    i = HeapSize;

    while ((i>1) && (A[i/2].dist > A[i].dist)){
        c = A[i/2];
        A[i/2] = A[i];
        A[i] = c;
        i = i/2;
    }
}

/**
 * @brief Maintains the min-heap property.
 *
 * This function maintains the min-heap property by ensuring that the parent node
 * is smaller than its child nodes.
 *
 * @param A Array representing the heap.
 * @param key Index of the node to be heapified.
 */
void Min_Heapify(Node A[], int key) {
    int posmin;
    Node appoggio;

    int l = 2*key;
    int r = 2*key + 1;

    if ((l <= HeapSize)&&(A[l].dist<A[key].dist))
        posmin = l;
    else
        posmin = key;

    if ((r <= HeapSize)&&(A[r].dist<A[posmin].dist))
        posmin = r;

    if (posmin != key){
        appoggio = A[posmin];
        A[posmin] = A[key];
        A[key] = appoggio;

        Min_Heapify(A, posmin);
    }

}

/**
 * @brief Deletes the minimum node from the heap.
 *
 * This function deletes the minimum node from the heap and returns it.
 *
 * @param A Array representing the heap.
 * @return The minimum node from the heap.
 */
Node Cancella_Min(Node A[]){
    Node max;
    if (HeapSize < 1) {
        max.dist = -1;
        max.index = -1;
        return max;
    }
    max.dist = A[1].dist;
    max.index = A[1].index;
    A[1] = A[HeapSize];
    HeapSize = HeapSize - 1;
    Min_Heapify(A, 1);
    return max;
}

/**
 * @brief Maintains the min-heap property after insertion.
 *
 * This function maintains the min-heap property by ensuring that the parent node
 * is smaller than its child nodes after a new node is inserted.
 *
 * @param A Array representing the heap.
 * @param key Index of the node to be heapified.
 */
void Min_Heapify2(Node A[], int key){
    Node appogg;

    while ((key > 1)&&(A[key/2].dist>A[key].dist)){
        appogg = A[key/2];
        A[key/2] = A[key];
        A[key] = appogg;

        key = key/2;
    }
}

/**
 * @brief Modifies the heap with a new distance value.
 *
 * This function modifies the heap by updating the distance value of a node
 * and maintaining the heap property.
 *
 * @param A Array representing the heap.
 * @param distance New distance value.
 * @param Index Index of the node to be modified.
 */
void ModificaHeap(Node A[], int distance, int Index){
    boolean Flag = FALSE;
    int i = 1;
    while  ((i <= HeapSize) && (Flag != TRUE)){
        if (A[i].index == Index) {
            A[i].dist = distance;
            Flag = TRUE;
            i++;
        } else {
            i++;
        }
    }
    i--;
    Min_Heapify2(A, i);
}

/**
 * @brief Performs Dijkstra's algorithm to find the shortest paths.
 *
 * This function performs Dijkstra's algorithm to find the shortest paths
 * from a source node to all other nodes in the graph.
 *
 * @param Visited Array indicating whether a node has been visited.
 * @param Table 2D array representing the adjacency matrix of the graph.
 * @param Distances Array representing the shortest distances from the source node.
 * @param A Array representing the heap.
 * @return The sum of the shortest distances.
 */
int Djikstra(boolean Visited[], int Table[][Nnodes], int Distances[], Node A[]){
    int sum = 0;
    Node New;
    Node u = Cancella_Min(A);
    while (u.dist != -1){
        Visited[u.index] = TRUE;
        sum = sum + u.dist;

        for (int i = 1; i < Nnodes; i++){
            if ((Visited[i] != TRUE) && (Distances[i] != 0) && (Table[u.index][i] != 0) && (Distances[i] > u.dist + Table[u.index][i])){
                Distances[i] = u.dist + Table[u.index][i];
                ModificaHeap(A, Distances[i], i);
            } else if ((Distances[i] == 0) && (Table[u.index][i] != 0) && (Visited[i] != TRUE)){
                New.index = i;
                New.dist = u.dist + Table[u.index][i];
                Distances[i] = New.dist;
                InsertMAX(A, New);
            }
        }

        u = Cancella_Min(A);
    }

    return sum;
}

/**
 * @brief Fills the adjacency matrix with input data.
 *
 * This function reads input data and fills the adjacency matrix representing the graph.
 *
 * @param Table 2D array representing the adjacency matrix of the graph.
 */
void init_table(int Table[][Nnodes]) {
    int ritorno, Result;
    for (int i = 1; i < Nnodes; i++) {
        Result = 0;
        ritorno = getchar_unlocked();

        while(ritorno != ','){
            Result = 10*Result + ritorno - '0';
            ritorno = getchar_unlocked();
        }

        Table[i][0] = Result;

        int j = 1;
        ritorno = getchar_unlocked();
        while(ritorno != 10){
            Result = 0;

            while (ritorno != ',' && ritorno != 10) {
                Result = 10 * Result + ritorno - '0';
                ritorno = getchar_unlocked();
            }

            if (ritorno != 10) {
                ritorno = getchar_unlocked();
            }

            Table[i][j] = Result;
            j++;
        }
    }

}

/**
 * @brief Fills the distances array and heap with input data.
 *
 * This function reads input data and fills the distances array and heap
 * representing the initial distances from the source node.
 *
 * @param Distances Array representing the shortest distances from the source node.
 * @param A Array representing the heap.
 */
void init_heaps(int Distances[], Node A[]){
    Node a;
    int Result = 0;
    int ritorno;

    ritorno = getchar_unlocked();

    while(ritorno != ','){
        Result = 10*Result + ritorno - '0';
        ritorno = getchar_unlocked();
    }

    Distances[0] = Result;

    int y = 1;
    ritorno = getchar_unlocked();
    while (ritorno != 10){
        Result = 0;

        while (ritorno != ',' && ritorno != 10) {
            Result = 10 * Result + ritorno - '0';
            ritorno = getchar_unlocked();
        }

        Distances[y] = Result;
        if (Distances[y] != 0) {
            a.dist = Distances[y];
            a.index = y;
            InsertMAX(A, a);
        }

        if (ritorno != 10) {
            ritorno = getchar_unlocked();
        }

        y++;
    }
}

/**
 * @brief Main function to control the flow of the program.
 *
 * This function reads input data, processes it, and performs various operations
 * including insertion into the Red-Black Tree, rotations, and heap operations.
 *
 * @return Exit status of the program.
 */
int main() {
    int trash;
    int sum;
    int val_max = 1200000;
    int count = 0;

    trash = scanf("%d", &Nnodes);
    trash = scanf("%d", &K);
    trash = scanf("%d", &trash);

    boolean Visited[Nnodes];
    Visited[0] = TRUE;

    int Table[Nnodes][Nnodes];
    int Distances[Nnodes];
    Node A[Nnodes];

    struct node* min;

    for (int i = 0; i < Nnodes; i++) {
        Table[0][i] = 0;
    }

    char command[15];
    while (NULL != fgets(command, sizeof(command), stdin)){
        if (command[0] == 'T'){
            ContrStmp = 0;
            output_print(root);
            printf("\n");
        } else {
            HeapSize = 0;

            for (int i = 1; i < Nnodes; i++){
                Visited[i] = FALSE;
            }

            init_heaps(Distances, A);
            init_table(Table);

            sum = Djikstra(Visited, Table, Distances, A);

            if (K < 20000) {
                if (count < K) {
                    struct node *added = (struct node *) malloc(sizeof(struct node));
                    added -> r = NULL;
                    added -> l = NULL;
                    added -> p = NULL;
                    added -> Key = sum;
                    added -> index = count;
                    added -> color = RED;

                    root = insert(root, added);

                    RBinsert_and_repair(root, added);
                }

                if ((count >= K) && (sum < val_max)) {
                    struct node *added = (struct node *) malloc(sizeof(struct node));
                    added -> r = NULL;
                    added -> l = NULL;
                    added -> p = NULL;
                    added -> Key = sum;
                    added -> index = count;
                    added -> color = RED;

                    root = insert(root, added);

                    RBinsert_and_repair(root, added);

                    int contatore = 1;
                    min = min_val(root);
                    val_max = successor(min, contatore);
                }

                count++;
                if (count == K) {
                    int contatore = 1;
                    min = min_val(root);
                    val_max = successor(min, contatore);
                }
            } else {
                struct node *added = (struct node *) malloc(sizeof(struct node));
                added -> r = NULL;
                added -> l = NULL;
                added -> p = NULL;
                added -> Key = sum;
                added -> index = count;
                added -> color = RED;

                root = insert(root, added);

                RBinsert_and_repair(root, added);

                count++;
            }
        }
    }

    return 0;
}
