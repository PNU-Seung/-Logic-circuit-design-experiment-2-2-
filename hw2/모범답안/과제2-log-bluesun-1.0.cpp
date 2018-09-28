#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int Bssearch(int x, int y[], int K) // binary search for s
{
    int high = K;
    int low = 0;
    int mid = 0;
    while(low <= high)
    {
        mid = (high + low)/2;
        if(y[mid] == x)
        {
            return mid;
        }

        else
        {
            if(y[mid] > x)
            {
                high = mid;
                if (high == low)
                    return mid;
            }
            else
            {
                low = mid +1;
                if (high == low)
                    return high;
            }
        }
    }
    return mid;
}



int Besearch(int x, int y[], int K)         //binary search for e
{
    int high = K;
    int low = 0;
    int mid = 0;
    while(low <= high)
    {
        mid = (high + low)/2;
        if(y[mid] == x)
        {
            return mid ;
        }
        if ( high - 1 == low)
        {
            return mid;
        }
        else
        {
            if(y[mid] > x)
            {
                high = mid ;
                if (high == low)
                    return mid;
            }
            else
            {
                low = mid;
                if (high == low)
                    return mid+1;
            }
        }
    }
    return mid;
}

int main()
{
    FILE *fp1;
    FILE *fp2;
    FILE *fp3;
    char line[256],*result;


    int k = 3, ds = 0, ts = 0, de = 0, te = 0, count = 0;
    int K = 3, Ds = 0, De = 0, T = 0;

    fp1 = fopen("syslog.txt","r");
    fp2 = fopen("log.inp","r");
    fp3 = fopen("log.out","w");
    fscanf(fp1,"%d",&K);
    fscanf(fp2,"%d",&k);
    int tcount = 0,scount = 0;
    int time[K];
    int day[K];
    fpos_t pos[K];

    for (int i = 0; i< K; i++)      // read syslog.txt
    {
        if( T == 0)
        {
            fscanf(fp1,"%d",&T);
            day[i] = T;
            fgetpos(fp1,&pos[i]);
        }
        while( T != 0)
        {
            fscanf(fp1,"%d",&T);
            if (T == 0)
                break;
            tcount++;
        }
        time[i] = tcount;
    }

    time[K] = 0;
    day[K] = 0;

    rewind(fp1);

    for (int i =0; i <k; i++)                       // search real data;
    {
        fscanf(fp2,"%d%d%d%d",&ds,&ts,&de,&te);
        Ds = Bssearch(ds,day,K);
        De = Besearch(de,day,K);
                                // count real visit
        count = time[De] - time[Ds-1];
        if( ds == day[Ds])
        {
            fsetpos(fp1,&pos[Ds]);
          //  fscanf(fp1,"%d",&T);
            while(1)
            {
                fscanf(fp1,"%d",&T);
                if( T == 0)
                {
                    break;
                }
                if(T < ts)
                    scount++;
                if( T == 0)
                {
                    break;
                }
            }
            count = count - scount;
            scount = 0;
            rewind(fp1);
        }

        if( de == day[De])
        {
            fsetpos(fp1,&pos[De]);
         //   fscanf(fp1,"%d",&T);
            while(1)
            {
                fscanf(fp1,"%d",&T);
                if( T == 0)
                {
                    break;
                }
                if(T > te)
                    scount++;
            }

            count = count - scount;
            scount = 0;
            rewind(fp1);
        }

        fprintf(fp3,"%d\n",count);
        count = 0;
    }
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);

    return 0;
}