#include "Option.h"
#include "EuroOption.h"
#include "BinModel.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <bitset>
#include <ctime>
#include <fstream>

using namespace std;

int EuroCall::GetInputData(int Steps)
{
	cout << "Enter European call future option data:" <<endl;
	//cout << "Enter steps to expiry N: "; cin >> N; SetN(N);
	cout << "Enter parameter K:       "; cin >> K; SetN(Steps);
	cout << endl;

	cout << "N = " << N << endl;
	cout << "K = " << K << endl;
	cout << endl;

	return 0;
}

int EuroPut::GetInputData(int Steps)
{
	cout << "Enter European put future option data:" <<endl;
	//cout << "Enter steps to expiry N: "; cin >> N; SetN(N);
	cout << "Enter parameter K:       "; cin >> K; SetN(Steps);
	cout << endl;
	

	cout << "N = " << N << endl;
	cout << "K = " << K << endl;
	cout << endl;

	return 0;
}

double EuroOption::PriceByCRR(BinModel Model)
{
	double Price=0;
	vector<int> Path;
	for (int n=0;n<pow(2.0,N);n++)
	{
		Model.GetSPath(n,N,Path);
		Price=Price+Model.GetPathProb(N,Path)*Payoff(Model,Path);
	}
	Price=Price*exp(-1*Model.GetRf()*Model.GetT());
	Path.clear();
	return Price;
}

double EuroOption::PriceByMC(BinModel Model)
{
	int M;
	cout << "Enter the number of random paths M: ";cin>> M; cout << endl;
	cout << "M = " << M << endl <<endl; 

	double Price=0;
	vector<int> Path;
	double rs;

	srand((unsigned)time(NULL));
	for(int i=1;i<=M;i++)
	{
		Path.clear();
   		for( int j=0;j<N;j++)
		{
			rs=(double)rand()/(RAND_MAX+1);
			if(rs<Model.RiskNeuProb()) Path.push_back(1);
			else Path.push_back(0);
		}
			//a[i]=Payoff(Model,Path); //for store payoff of random paths
		Price=Price+Payoff(Model,Path)/M;
	}

	Price=Price*exp(-1*Model.GetRf()*Model.GetT());
	Path.clear();
	return Price;
}


double EuroCall::Payoff(BinModel MyModel, vector<int> SPath)
{
	double Ft=MyModel.S(N,SPath);
	if(Ft>K) return Ft-K;
	else return 0;
}

double EuroPut::Payoff(BinModel MyModel, vector<int> SPath)
{
	double Ft=MyModel.S(N,SPath);
	if(Ft<K) return K-Ft;
	else return 0;
}

double EuroCall::PriceByBlack(BinModel MyModel)
{
	double F0=MyModel.GetF0();
	double r=MyModel.GetRf();
	double sigma=MyModel.GetSigma();
	double T=MyModel.GetT();
	
	double d1=(log(F0/K)+0.5*sigma*sigma*T)/(sigma*sqrt(T));
	double d2=(log(F0/K)-0.5*sigma*sigma*T)/(sigma*sqrt(T));

	return exp(-1*r*T)*(F0*MyModel.NormDist(d1)-K*MyModel.NormDist(d2));
}

double EuroPut::PriceByBlack(BinModel MyModel)
{
	double F0=MyModel.GetF0();
	double r=MyModel.GetRf();
	double sigma=MyModel.GetSigma();
	double T=MyModel.GetT();

	double d1=(log(F0/K)+0.5*sigma*sigma*T)/(sigma*sqrt(T));
	double d2=(log(F0/K)-0.5*sigma*sigma*T)/(sigma*sqrt(T));

	return exp(-1*r*T)*(K*MyModel.NormDist(-1*d2)-F0*MyModel.NormDist(-1*d1));
}