#include <stdio.h>
#include <stdlib.h>
#define x(i,j) x[(i) * (n+1) + (j)]         //要素番号を一次元配列の要素番号に変換


int n=0;      //連立方程式の変数の数nはすべての関数で使い回すため、グローバル変数とする

//int FileInsertMode(double *x);
double *KeyboardInsert();
//void FOutput(double ans[], int n);

int main() {
    int i,j,d,Iselect,Oselect,retry;
    double *x,*y,*xtemp,a,b,temp,check;

    printf("ようこそ連立方程式計算機へ！\n");

    do{
        printf("入力モードを選択してください。\n1:ファイルから入力\n2:キーボード入力\n3:終了\n-->");
        scanf("%d",&Iselect);
        printf("\n");

        switch (Iselect) {
            case 1:
               /* n=FileInsertMode(x);
                    */
                break;

            case 2:
               x=KeyboardInsert();
               break;

            case 3:
                printf("終了します・・・\n");
                free(x);
                free(y);
                exit(0);

            default:
                printf("不正な入力です。\n");
                retry=1;
                break;

        }
        if(n==0)
            retry=1;
        else
            retry=0;
    } while (retry==1);


    printf("=======calculating=======\n");
    for(i=0;i<=n-1;i++){
        for(j=0;j<=n;j++){
            printf("%f\t",x(i,j));
        }
        printf("\n");
    }

    //検算用に第一式の係数をxtempに保存
    xtemp= (double *) malloc(sizeof(double) * n);
    for(j=0;j<=n;j++){
        xtemp[j]=x(0,j);
        printf("%f\n",xtemp[j]);
    }


    //ピボット選択
    for (i=0; i<=n-1; i++) {
        if(x(i,i)==0){                         //対角成分が0かどうかを判定
            for (d=1; d<=n-1-i; d++) {          //1つ下の行の同じ列の成分が0かどうかを判定
                if(x(i+d,i)!=0){
                    for (j=0; j<=n; j++) {
                        temp=x(i,j);           //対角成分が0の行の成分を一時的に保存
                        x(i,j)=x(i+d,j);      //d行下の行の成分を0の行にコピー
                        x(i+d,j)=temp;         //0の行の成分をd行下にコピー
                    }
                    break;
                }
            }
        }
    }


    printf("↓ピボッティング\n"); //表示
    for(i=0;i<=n-1;i++){
        for(j=0;j<=n;j++){
            printf("%f\t",x(i,j));
            if(j==n)
                printf("\n");
        }
    }



    printf("↓上三角行列化\n");
    //ガウスの消去法
    for(i=0;i<=n-1;i++){
        if (i==n-1) {
            x(i,i+1)=x(i,i+1)/x(i,i);
            x(i,i)=1;
        }
        else{
            a=x(i,i);
            for(d=0;d<=n-1-i;d++){
                b=x(i+d,i);
                for(j=i;j<=n;j++){
                    if(d==0)
                        x(i,j)=x(i,j)/a;
                    else
                        x(i+d,j)=x(i+d,j)-x(i,j)*b;
                }
            }
        }
    }


    for(i=0;i<=n-1;i++){
        for(j=0;j<=n;j++){
            printf("%f\t",x(i,j));
        }
        printf("\n");
    }

    //解の計算
    y = (double *) malloc(sizeof(double) * n);
    temp=0;
    y[n-1]=x(n-1,n);
    for (i=n-2; i>=0; i--) {
        for (j=i+1; j<=n-1; j++) {
            temp=temp+x(i,j)*y[j];
        }
        y[i]=x(i,n)-temp;
        temp=0;
    }


    printf("==========done==========\n");
    printf("n=%d\n",n);//チェック用
    printf("[ANSWER]\n");
    for (i=0; i<=n-1; i++) {
        printf("ans[%d]=%f\n",i+1,y[i]);      //答えの表示
    }


    /*検算
    temp=0;
    for (i=0; i<=n-1; i++) {
        temp=temp + xtemp[i]*y[i];
    }
    printf("%f\n%f\n",temp,xtemp[n]);
    check=(temp - xtemp[n] )/ xtemp[n] * 100;
    printf("誤差=%.2fパーセント\n\n",check);

     */

    printf("続けてファイル出力しますか？\n1:ファイル出力\n2:終了\n-->");
    do{
        scanf("%d",&Oselect);
        printf("\n");
        switch (Oselect) {
            case 1: //ファイル出力
               // FOutput(y,n);
                retry=0;
                break;

            case 2:
                retry=0;
                break;

            default:
                printf("不正な入力です。\n-->");
                retry=1;
                break;
        }

    }while(retry==1);

    free(x);
    free(y);
    free(xtemp);

    return 0;
}

//========================================================

double *FileInsertMode(){
    int i,j,select,ret;
    double temp,*x;
    //   char adress;
    FILE *fi;
    printf("【ファイル入力モード】\n");

    /*
     printf("現在の設定は以下の通りです。\n");
     printf("ファイル名：gyouretsu.txt\n");
     printf("設定を変更しますか？\n1:はい\n2:いいえ\n3:キャンセル--→");
     scanf("%d",&select);
     printf("\n");

     printf("読み込むファイルを選択してください。\n1:既存のファイル\n2:新規作成\n--→");
     scanf("%d",&select);
     printf("\n");
     */

    if ((fi=fopen("in.txt","r" )) == NULL) {
        printf("読み込めませんでした。\n");
        exit(-1);
    }

    while ((temp = fgetc(fi)) != EOF) {
        // printf("%lf ",temp);
        if (temp == '\n') n++;
    }

    for(i=0;i<=n-1;i++){
        for(j=0;j<=n;j++) {
            fscanf(fi, "%lf", &temp);               //fgetc(fi);
            x(i, j) = temp;
            printf("%f ", x(i,j));
            /*
            if (x(i,j)==EOF) {
                printf("データの大きさが不正です。\n");
                return -2;
            }
            */
        }
    }
    printf("\n");

    fclose(fi);
    printf("読み込みが終了しました。\n");
}


double *KeyboardInsert() {
    int i, j, select;
    double temp,*x;

    do {
        printf("【キーボード入力モード】\n");
        printf("未知数の数は？\n-->");
        do {
            scanf("%d", &n);
            if (n <= 0) printf("自然数を入力してください\n-->");
        } while (n <= 0);

        x = (double *) malloc(sizeof(double) * n * (n + 1));

        printf("各変数の係数を%dx%dの行列に見立てて入力してください\n", n, n + 1);
        for (i = 0; i<=n-1; i++) {
            for (j = 0; j <=n; j++) {
                printf("%d行%d列：", i+1, j+1);
                scanf("%lf", &temp);
                x(i, j) = temp;        //2次元配列を1次元配列で表現する
            }
        }

        printf("\n現在保存されている%d次連立方程式の係数\n",n);

        for (i = 0; i <= n - 1; i++) {
            for (j = 0; j <= n; j++) {
                printf("%f ", x(i, j));
            }
            printf("\n");
        }

        printf("これでよろしいですか？\n1:はい 2:やり直す 3:入力方法選択に戻る\n-->");
        scanf("%d", &select);
        switch(select) {
            case 1:
                break;
            case 2:
                select = 0;
                free(x);
                break;
            case 3:
                n = 0;            //グローバル変数nを0にし、メイン関数でretry=trueにさせる。
                free(x);
            default:
                printf("不正な入力です。\n");
                select = 0;
                free(x);
                break;
        }
    } while (select == 0);
    printf("\n");
    return x;
}

/*
void FOutput(double ans[],int n){
    FILE *fo;
    int i;

    printf("【ファイル出力モード】\n");

    if ((fo=fopen("result.txt","w" )) == NULL) {
        printf("読み込めませんでした。\n");
    }

    for (i=0; i<=n-1; i++) {
        fprintf(fo,"ans%d=%f\n",i+1,ans[i]);
    }
    fclose(fo);
}
*/