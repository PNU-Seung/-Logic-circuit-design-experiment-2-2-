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

        while(y < m){ //y�� m���� ����������
            if(x == X && y == Y){ //��ǥ�� (X, Y)���� �˻�
                num = k;
                searched++;
            }
            if(k == K){ //��ȣ�� K���� �˻�
                posX = x; posY = y;
                searched++;
            }
            y++; //���� ��ǥ �̵�
            k++; //�ϳ��� ��ȣ ����
        }
        m--; //����ȸ�� �� ĭ ����
        if(searched == 2) break; //�� ã���� while�� break

        while(x < n){  //���������� �̵� --->
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

        while(y > b){ //�Ʒ������� �̵�
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

        while(x > a){ //�� ������ �̵� <---
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
