    #include <stdio.h>
    #include <stdbool.h>
    #include <stdlib.h>
    #define N 10

    typedef struct {
        int node;       
        int jarak;      
        int* jalur;       
        int panjangJalur;  
        bool dikunjungi[N]; 
    } jarakNode;

    void dfs(int graph[N][N], int awal, int akhir, jarakNode* jalurMungkin, int* banyakJalurMungkin) {
        jarakNode stack[100];
        int ukuranStack = 0;
        int jarakTerdekat = -1;

        bool awalDikunjungi[N] = {false};
        awalDikunjungi[awal] = true;
        stack[ukuranStack++] = (jarakNode){awal, 0, NULL, 0, {false}};

        while (ukuranStack > 0) {
            jarakNode sekarang = stack[--ukuranStack];

            if (sekarang.node == akhir) {
                if (jarakTerdekat == -1 || sekarang.jarak <= jarakTerdekat) {
                    jarakTerdekat = sekarang.jarak;

                    jalurMungkin[*banyakJalurMungkin] = (jarakNode){
                        .node = sekarang.node,
                        .jarak = sekarang.jarak,
                        .jalur = (int*)malloc(sekarang.panjangJalur * sizeof(int)),
                        .panjangJalur = sekarang.panjangJalur
                    };
                    for (int i = 0; i < sekarang.panjangJalur; i++) {
                        jalurMungkin[*banyakJalurMungkin].jalur[i] = sekarang.jalur[i];
                    }
                    (*banyakJalurMungkin)++;
                }
                continue;
            }

            for (int i = 0; i < N; i++) {
                if (graph[sekarang.node][i] && !sekarang.dikunjungi[i]) {
        
                    int* jalurBaru = (int*)malloc((sekarang.panjangJalur + 1) * sizeof(int));

                    for (int j = 0; j < sekarang.panjangJalur; j++) {
                        jalurBaru[j] = sekarang.jalur[j];
                    }
                    jalurBaru[sekarang.panjangJalur] = sekarang.node;

                    bool dikunjungiBaru[N];
                    for (int j = 0; j < N; j++) {
                        dikunjungiBaru[j] = sekarang.dikunjungi[j];
                    }
                    dikunjungiBaru[i] = true;
        
                    stack[ukuranStack++] = (jarakNode){i, sekarang.jarak + 1, jalurBaru, sekarang.panjangJalur + 1, {false}};
                    for (int j = 0; j < N; j++) {
                        stack[ukuranStack-1].dikunjungi[j] = dikunjungiBaru[j];
                    }
                }
            }

            free(sekarang.jalur); 
        }
    }

    void printJalurTerpendek(jarakNode* jalurMungkin, int banyakJalurMungkin, int awal, int akhir) {
        int jarakTerdekat = -1;

        for (int i = 0; i < banyakJalurMungkin; i++) {
            if (jarakTerdekat == -1 || jalurMungkin[i].jarak < jarakTerdekat) {
                jarakTerdekat = jalurMungkin[i].jarak;
            }
        }

        for (int i = 0; i < banyakJalurMungkin; i++) {
            if (jalurMungkin[i].jarak == jarakTerdekat) {
                printf("Jalur terpendek dari simpul %d ke simpul %d: ", awal, akhir);
                for (int j = 0; j < jalurMungkin[i].panjangJalur; j++) {
                    printf("%d ", jalurMungkin[i].jalur[j]);
                }
                printf("%d\n", akhir);
            }
        }
    }

    int main() {
        int graph[N][N] = {
            {0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
            {1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
            {1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 1, 0, 0, 1, 0, 1, 0, 0, 0},
            {0, 0, 1, 1, 0, 1, 0, 1, 1, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
            {0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 1, 0, 1, 0, 0, 1},
            {0, 0, 0, 0, 1, 1, 0, 0, 0, 1},
            {0, 0, 0, 0, 0, 0, 0, 1, 1, 0}
        };

        jarakNode jalurMungkin[100]; 
        int banyakJalurMungkin = 0;       

        dfs(graph, 0, 9, jalurMungkin, &banyakJalurMungkin);

        printJalurTerpendek(jalurMungkin, banyakJalurMungkin, 0, 9); 

        for (int i = 0; i < banyakJalurMungkin; i++) {
            free(jalurMungkin[i].jalur);
        }

        return 0;
    }
