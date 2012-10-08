#ifndef Option_h
#define Option_h

#include "BinModel.h"

class Option
{
protected:
	int N;
	
public:
	//setting time step N
	void SetN(int N_){N=N_;}
	//settting the payoff function virtually 
	virtual double Payoff(BinModel Model,vector<int> Path)=0;
	int GetN(){return N;}

};

#endif