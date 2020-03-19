
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include "tradesData.h"
#define SWAP(a, b) (a) ^= (b) ^= (a) ^= (b)
FILE *fin, *fout;
int i, n, r, DL;
char head[4];
char body[20];
TradesData *tradesData;
unsigned short PacketLength;
unsigned short MarketUpdate;
char Dynamic_Data[65518];

int main()
{
    fin = fopen("input.dat", "rb");
    fout = fopen("output.dat", "w");
    if (fin == NULL)
    {
        printf("Can not open file data.bin!\n");
        return 0;
    }
    n = 0;
    while (1)
    {
        //获取头数据
        r = fread(head, 1, 4, fin);
        if (r < 4)
            break;
        SWAP(head[0], head[1]);
        PacketLength = *((unsigned short *)head);
        SWAP(head[2], head[3]);
        MarketUpdate = *((unsigned short *)head + 2);
        unsigned short count = 0;
        //获取body数据
        while (count < PacketLength)
        {
            r = fread(body, 1, 18, fin);
            tradesData = new TradesData;
            //设置body数据
            tradesData->setTradeData(body);
            count += tradesData->Length;
            //获取剩余数据量并跳过
            DL = tradesData->Length - 18;
            if (DL > 0)
            {
                r = fread(Dynamic_Data, 1, DL, fin);
                if (r < DL)
                    break;
            }
            //计数
            n++;
            if(tradesData->Type == 'T'){
                // printf("Pack %06d:PacketLength=%hd,MarketUpdate=%hd, Length=%hd,Type=%c,Symbol=%s,Size=%hd,Price=%lg,Dynamic Data Length=%d\n", n, PacketLength, MarketUpdate, Length, Type, Symbol, Size, Price, DL);
                // printf("%d %s @ %.2f\n", tradesData->Size, tradesData->Symbol, (double)tradesData->Price/10000);
                fprintf(fout,"%d %s @ %.2f\n", tradesData->Size, tradesData->Symbol, (double)tradesData->Price/10000);
            }
        }
    }
    fclose(fin);
    fclose(fout);

    return 0;
}
