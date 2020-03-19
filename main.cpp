#include "tradesData.h"
#include <map> 
#include <iostream>
#include <fstream> //定义读写已命名文件的类型
#include <vector>
#include <sstream> //多定义的类型则用于读写存储在内存中的string对象
#include <string>
using namespace std;
string& trim(string&);
void updateTradeData(vector<string> fields, TradesData *tradesData); 
int main()
{
	ifstream fin("input.csv");

 	string line; 
	//用于保存股票以及股票数据的函数
 	map<string, TradesData*> mapTrade;
 	while (getline(fin, line)) {
  		istringstream sin(line); 
  		vector<string> fields; 
  		string field;
		//分割数据
 		while (getline(sin, field, ',')) {
   			fields.push_back(field); 
  		}
		//获取股票代码
  		string Symbol = trim(fields[1]); 
		//判断股票代码是否存在于Map中
  		if(mapTrade.count(Symbol) == 0){
  			TradesData *tradesData = new TradesData;
  			tradesData->setTradeData(fields);
  			mapTrade.insert(pair<string, TradesData*>(Symbol, tradesData));
		}else{
		  	updateTradeData(fields, mapTrade[Symbol]);
		}
  		// cout << fields[0] << "\t" << fields[1] << "\t" << fields[2] << "\t" << fields[3] << endl;
 	}
	fin.close();
 	map<string, TradesData*>::iterator iter;
	ofstream fout("output.csv");
	if (!fout)
	{
		cout << "文件不能打开" <<endl;
	}
 	for(iter = mapTrade.begin(); iter != mapTrade.end(); iter++){
 		string key = iter -> first;
 		TradesData *value = iter -> second;
 		fout << key << "," << value->maxTimeGap << "," << value->volume << "," << value->weightedAveragePrice << "," << value->maxPrice << endl;
		// cout << key << "," << value->maxTimeGap << "," << value->volume << "," << value->weightedAveragePrice << "," << value->maxPrice << endl;
	}
 	fout.close();

	getchar();
	return 0;
}
//根据当前单子更新数据
void updateTradeData(vector<string> fields, TradesData *tradesData){
	
	long TimeStamp = stol(fields[0]);
  	string Symbol = fields[1]; 
  	int Quantity = stol(fields[2]); 
  	long Price = stoi(fields[3]);
  	
  	tradesData->maxTimeGap = max(tradesData->maxTimeGap, TimeStamp - tradesData->timeStamp);
  	tradesData->maxPrice = max(tradesData->maxPrice, Price);
  	tradesData->weightedAveragePrice = 
	  (tradesData->weightedAveragePrice * tradesData->volume + Price * Quantity) / (tradesData->volume + Quantity );
  	tradesData->volume += Quantity;
  	tradesData->timeStamp = TimeStamp;
}
string& trim(string &s)   
{  
    if (s.empty())   
    {  
        return s;  
    }  
  
    s.erase(0,s.find_first_not_of(" "));  
    s.erase(s.find_last_not_of(" ") + 1);  
    return s;  
}  

