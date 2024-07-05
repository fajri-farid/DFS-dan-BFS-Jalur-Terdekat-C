#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 

#define N 5

typedef struct {
    int node; 
    int jarak; 
    int* jalur;  
    int panjangJalur; 
    bool dikunjungi[N]; 
} jarakNode;

void bfs(int graph[N][N], int start, int target) {
    jarakNode* queue = NULL;
    int front = 0, rear = 0, banyakAntrian = 0;
    int jarakTerdekat = -1;

    queue = (jarakNode*)realloc(queue, (banyakAntrian + 1) * sizeof(jarakNode));

    jarakNode nodeAwal = {start, 0, NULL, 0, {false}};
    nodeAwal.dikunjungi[start] = true;
    queue[rear++] = nodeAwal;
    banyakAntrian++;

    while (front < rear) {
        jarakNode sekarang = queue[front++];

        // Jika menemukan target
        if (sekarang.node == target) {
            if (jarakTerdekat == -1) {
                jarakTerdekat = sekarang.jarak;
            }

            if (sekarang.jarak > jarakTerdekat) {
                break;
            }

            printf("Jalur terpendek dari simpul %d ke simpul %d: ", start, target);
            for (int i = 0; i < sekarang.panjangJalur; i++) {
                printf("%d ", sekarang.jalur[i]);
            }
            printf("%d\n", target);
        }

        // Memproses semua tetangga
        for (int i = 0; i < N; i++) {
            if (graph[sekarang.node][i] && !sekarang.dikunjungi[i]) {
             
                queue = (jarakNode*)realloc(queue, (banyakAntrian + 1) * sizeof(jarakNode));
                int* jalurBaru = (int*)malloc((sekarang.panjangJalur + 1) * sizeof(int));

                for (int j = 0; j < sekarang.panjangJalur; j++) {
                    jalurBaru[j] = sekarang.jalur[j];
                }
                jalurBaru[sekarang.panjangJalur] = sekarang.node;

                jarakNode nodeBaru = {i, sekarang.jarak + 1, jalurBaru, sekarang.panjangJalur + 1, {false}};
                for (int j = 0; j < N; j++) {
                    nodeBaru.dikunjungi[j] = sekarang.dikunjungi[j];
                }
                nodeBaru.dikunjungi[i] = true;

                queue[rear++] = nodeBaru;
                banyakAntrian++;
            }
        }

        free(sekarang.jalur); 
    }

    free(queue); 
}

int main() {
    int graph[N][N] = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 1, 0},
        {1, 1, 0, 1, 0},
        {0, 1, 1, 0, 1},
        {0, 0, 0, 1, 0}
    };
    
    bfs(graph, 0, 4); 
    
    return 0;
}
