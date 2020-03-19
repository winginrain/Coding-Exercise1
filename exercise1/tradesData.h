
#pragma once
#include <string>
#include <vector>
using namespace std;
//暂存TradesData相关信息
struct TradesData
{
	//暂存最新更新的时间戳，用于计算TimeGap
    long timeStamp;
    long maxTimeGap;
    int volume;
    long weightedAveragePrice;
	long maxPrice;
    void setTradeData (vector<string> fields)    
    {
        long TimeStamp = stol(fields[0]);
  		string Symbol = fields[1]; 
  		int Quantity = stol(fields[2]); 
  		long Price = stoi(fields[3]);
  		
  		this->maxTimeGap = (long)0;
  		this->maxPrice = Price;
  		this->weightedAveragePrice = Price;
  		this->volume = Quantity;
  		this->timeStamp = TimeStamp;
    }
};

