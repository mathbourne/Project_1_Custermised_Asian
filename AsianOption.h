#ifndef AsianOption_h
#define AsianOption_h

#include "Option.h"

class AsianOption: public virtual Option    //defining the Asian option class
{
private:

public:
	
	double PriceByCRR(BinModel Model); //price by normal CRR method

	double PriceByMC(BinModel Model);  //price by Monte Carlo method
};

class AsianCall: public AsianOption  //defining the Asian call class
{
private:
	int K;

public:

	//setting the payoff fucntion
	double Payoff(BinModel MyModel,vector<int> SPath);

	//input the data for asian call option
	int GetInputData(int);
};


class AsianPut: public AsianOption  //defining the Asian put class
{
private:
	int K;

public:
	//setting up strike price K
	void SetK(int K_){K=K_;}

	//setting the payoff fucntion
	double Payoff(BinModel Model,vector<int> SPath);

	//input the data for asian put option
	int GetInputData(int);

};

class AsianCusCall:public AsianOption
{
private:
	int K;
	int F;
public:
	void SetK(int K_) {K=K_;}
	void SetF(int F_) {F=F_;}
	int GetInputData(int);
	double Payoff(BinModel Model,vector<int> SPath);
};

class AsianCusPut:public AsianOption
{
private:
	int K;
	int F;
public:
	void SetK(int K_) {K=K_;}
	void SetF(int F_) {F=F_;}
	int GetInputData(int);
	double Payoff(BinModel Model,vector<int> SPath);
};



#endif