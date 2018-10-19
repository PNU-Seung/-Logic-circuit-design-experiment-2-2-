#include <stdio.h>

int main() {
    FILE *fp;
    fp = fopen("nanobot.inp","r");

    int n, m, X, Y, K;
    int a=2, b=1, x=1, y=1, k=1;
    int num, posX, posY, searched = 0;

    fscanf(fp, "%d %d %d %d %d", &n, &m, &X, &Y, &K);
    fclose(fp);

    while(1){

        while(y < m){ //y가 m보다 작을때에는
            if(x == X && y == Y){ //좌표가 (X, Y)인지 검사
                num = k;
                searched++;
            }
            if(k == K){ //번호가 K인지 검사
                posX = x; posY = y;
                searched++;
            }
            y++; //위로 좌표 이동
            k++; //하나씩 번호 증가
        }
        m--; //나선회로 한 칸 감소
        if(searched == 2) break; //다 찾으면 while문 break

        while(x < n){  //오른쪽으로 이동 --->
            if(x == X && y == Y){
                num = k;
                searched++;
            }
            if(k == K){
                posX = x; posY = y;
                searched++;
            }
            x++;
            k++;
        }
        n--;
        if(searched == 2) break;

        while(y > b){ //아래쪽으로 이동
            if(x == X && y == Y){
                num = k;
                searched++;
            }
            if(k == K){
                posX = x; posY = y;
                searched++;
            }
            y--;
            k++;
        }
        b++;
        if(searched == 2) break;

        while(x > a){ //왼 쪽으로 이동 <---
            if(x == X && y == Y){
                num = k;
                searched++;
            }
            if(k == K){
                posX = x; posY = y;
                searched++;
            }
            x--;
            k++;
        }
        a++;
        if(searched == 2) break;

    } //while(1)

    fp = fopen("nanobot.out", "w");
    fprintf(fp, "%d\n", num);
    fprintf(fp, "%d %d", posX, posY);
    fclose(fp);

    return 0;
}
