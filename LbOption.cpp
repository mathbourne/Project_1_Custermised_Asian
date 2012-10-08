#include "Option.h"
#include "LbOption.h"
#include "BinModel.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <bitset>
#include <ctime>
#include <fstream>

using namespace std;

int LbCall::GetInputData()
{
    cout << "Enter Lookback call option data:" <<endl;
	int N;
	cout << "Enter steps to expiry N: "; cin >> N; SetN(N);
	cout << endl;

	cout << "N = " << N << endl;
	cout << endl;

	return 0;
}

double LbCall::Payoff(BinModel Model, vector<int> Path)
{
    double news=Model.S(0,Path);
	double t;
	for(int i=0;i<=N;i++)
	{
		t=Model.S(i,Path);
		if(t<news) news=t;
	}

	return t-news;
}

double LbOption::PriceByCRR(BinModel Model)
{
	//timing
		//clock_t sta,edt;
		//sta=clock();  
	
	double Price=0;
	vector<int> Path;
	for (int n=0;n<pow(2.0,N);n++)
	{
	  Model.GetSPath(n,N,Path);
	  Price=Price+Model.GetPathProb(N,Path)
		  *Payoff(Model,Path)/pow(Model.GetR(),N);
	}

	Path.clear();

    //timing
		//edt=clock();
		//cout << "The time cost is: " << edt-sta << endl;           

	return Price;

}

double LbOption::PriceByMC(BinModel Model)
{
		//output file for testing
		//ofstream outFile;
		//outFile.open("recordLb1.txt",ios::out|ios::app);
	
	int M;
	cout << "Enter the number of random paths M: ";cin>> M; cout << endl;
	cout << "M = " << M << endl <<endl;
		//cout << endl;
		//for (int M=11000;M<=20000;M=M+1000){


	double Price=0;
	vector<int> Path;
	double rs;
		//double a[30001],hbar=0,sdv=0; //for store payoff of random paths

		//timing for test
		//clock_t st,ed;
		//st=clock();

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
			//a[i]=Payoff(Model,Path); //for store payoff of random paths,for test
		Price=Price+Payoff(Model,Path)/M/pow(Model.GetR(),N);
	}


		//timing for test
		//ed=clock();

		//for test, analyse the accuraacy by calculating the standard error
		/*
			for(int i=1;i<=M;i++)
				hbar=hbar+a[i];
			hbar=hbar/M;
			for(int i=1;i<=M;i++)
				sdv=sdv+(a[i]-hbar)*(a[i]-hbar);
			sdv=sqrt(sdv/(M-1));
			sdv=(sdv/sqrt((double)M))/pow(Model.GetR(),N); */
		//end of analysis of accuracy

		//record the data into file,for test
		//outFile <<M << "," <<Price << "," << ed-st <<"," << sdv <<endl;

		//}


	return Price;
}

int LbPut::GetInputData()
{
    cout << "Enter Lookback put option data:" <<endl;
	int N;
	cout << "Enter steps to expiry N: "; cin >> N; SetN(N);
	cout << endl;

	cout << "N = " << N << endl;
	cout << endl;

	return 0;
}


double LbPut::Payoff(BinModel Model, vector<int> Path)
{
    double news=Model.S(0,Path);
	double t;
	for(int i=0;i<=N;i++)
	{
		t=Model.S(i,Path);
		if(t<news) news=t;
	}

	return t-news;
}