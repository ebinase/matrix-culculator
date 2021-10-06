#include <stdio.h>
#include <stdlib.h>

#define x(i,j) x[(i) * (n+1) + (j)]


int main() {
    int *x;
    int i, j, n, temp;


    printf("【キーボード入力モード】\n");
    printf("未知数の数は？\n--→");
    scanf("%d", &n);

    x = (int *) malloc(sizeof(int) * n * (n + 1));

    for (i = 0; i <= n - 1; i++) {
        for (j = 0; j <= n; j++) {
            printf("%d行%d列：", i + 1, j + 1);
            scanf("%d", &temp);
            x(i, j) = temp;        //2次元配列を1次元配列で表現する
        }
    }


    for (i = 0; i <= n - 1; i++) {
        for (j = 0; j <= n; j++) {
            printf("%d ", x(i, j));
        }
        printf("\n");
    }

    printf("%d ", x(0 + 1, 2));

    free(x);

    return 0;
}