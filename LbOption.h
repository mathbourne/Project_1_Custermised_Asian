#ifndef LbOption_h
#define LbOption_h

#include "Option.h"

class LbOption: public virtual Option
{
public:
	
	double PriceByCRR(BinModel Model);

	double PriceByMC(BinModel Model);
};

class LbCall: public LbOption
{
public:
	//inputting data for Lookback call
	int GetInputData();

	double Payoff(BinModel Model,vector<int> Path); //calculating the payoff of lookback call

};

class LbPut: public LbOption
{
public:
	int GetInputData();

	double Payoff(BinModel Model,vector<int> Path);
};

#endif