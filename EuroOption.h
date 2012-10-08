#ifndef EuroOption_h
#define EuroOption_h

#include "Option.h"

class EuroOption:public virtual Option
{
private:
public:
	double PriceByCRR(BinModel Model);
	double PriceByMC(BinModel Model);
};

class EuroCall: public EuroOption
{
private:
	int K;
public:
	double Payoff(BinModel MyModel, vector<int> SPath);
	int GetInputData(int N);
	double PriceByBlack(BinModel MyModel);
};

class EuroPut:public EuroOption
{
private:
	int K;
public:
	void SetK(int K_){K=K_;}
	double Payoff(BinModel Model,vector<int> SPath);
	int GetInputData(int N);
	double PriceByBlack(BinModel sMyModel);
};

#endif