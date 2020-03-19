
#pragma once
#define SWAP(a, b) (a) ^= (b) ^= (a) ^= (b)
using namespace std;
//trade数据结构
struct TradesData
{
    unsigned short Length;
    char Type;
    char Symbol[6];
    unsigned short Size;
    long long Price;

//根据body获取数据
    void setTradeData(char body[])
    {
        SWAP(body[0], body[1]);
        Length = *((unsigned short *)body);
        Type = body[2];
        if (Type == 'T')
        {
            strncpy(Symbol, body + 3, 5);
            Symbol[5] = 0;
            SWAP(body[8], body[9]);
            Size = *((unsigned short *)(body + 8));
            for (int i = 0; i < 4; i++)
                SWAP(body[10 + i], body[17 - i]);
            Price = *((long long *)(body + 10));
        // }else{
            // strncpy(Symbol, body + 3, 5);
            // Symbol[5] = 0;
            // SWAP(body[8], body[9]);
            // Level = *((unsigned short *)(body + 8));
            // SWAP(body[10], body[11]);
            // Size = *((unsigned short *)(body + 10));
            // for (int i = 0; i < 4; i++)
            //     SWAP(body[12 + i], body[19 - i]);
            // Price = *((int *)(body + 12));
            // DLLength = Length - 20;
        }
    }
};
