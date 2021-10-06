#include <stdio.h>
#include <stdlib.h>
#define x(i,j) x[(i) * (n+1) + (j)]

int n=0;

int main(){
    int i,j,select,ret;
    double temp, *x;
    char a;
    //   char adress;
    FILE *fi;
    printf("【ファイル入力モード】\n");

    if ((fi=fopen("in.txt","r" )) == NULL) {
        printf("読み込めませんでした。\n");
        exit(1);
    }

    while ((temp = fgetc(fi)) != EOF) {
        // printf("%lf ",temp);
        if (temp == '\n') n++;
    }
    n++;

    printf("n=%d\n",n);
    rewind(fi);

    x= (double *) malloc(sizeof(double) * n * (n+1));

    for(i=0;i<=n-1;i++){
        for(j=0;j<=n;j++) {
            fscanf(fi, "%f", &temp);
            temp= fgetc(fi);

            x(i, j) = (double)a;
            printf("%f ", temp);

            //if (i!=n-1 && j!=n && temp==EOF) {
              //  printf("データの大きさが不正です。\n");
                //return -2;
           // }

        }
        printf("\n");
    }



    free(x);
    fclose(fi);
    printf("読み込みが終了しました。\n");
    return 0;
}