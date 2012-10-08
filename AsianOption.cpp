#include "Option.h"
#include "AsianOption.h"
#include "BinModel.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <bitset>
#include <ctime>
#include <fstream>

using namespace std;

int AsianCusCall::GetInputData(int N)
{
	cout << "Enter Asian custermised call option data:" <<endl;
	//int N;
	//cout << "Enter steps to expiry N: "; cin >> N; SetN(N);
	cout << "Enter parameter K:       "; cin >> K; SetN(N);
	cout << "Enter parameter F:       "; cin >> F;
	cout << endl;

	cout << "N = " << N << endl;
	cout << "K = " << K << endl;
	cout << "F = " << F << endl;
	cout << endl;

	return 0;
}

int AsianCusPut::GetInputData(int N)
{
	cout << "Enter Asian custermised put option data:" <<endl;
	//int N;
	//cout << "Enter steps to expiry N: "; cin >> N; SetN(N);
	cout << "Enter parameter K:       "; cin >> K; SetN(N);
	cout << "Enter parameter F:       "; cin >> F;
	cout << endl;

	cout << "N = " << N << endl;
	cout << "K = " << K << endl;
	cout << "F = " << F << endl;
	cout << endl;

	return 0;
}

int AsianCall::GetInputData(int N)
{
	cout << "Enter Asian call option data:" <<endl;
	//int N;
	//cout << "Enter steps to expiry N: "; cin >> N; SetN(N);
	cout << "Enter parameter K:       "; cin >> K; SetN(N);
	cout << endl;

	cout << "N = " << N << endl;
	cout << "K = " << K << endl;
	cout << endl;

	return 0;
}



int AsianPut::GetInputData(int N)
{
	cout << "Enter Asian put option data:" <<endl;
	//int N;
	//cout << "Enter steps to expiry N: "; cin >> N; SetN(N);
	cout << "Enter parameter K:       "; cin >> K;SetN(N);
	cout << endl;

	cout << "N = " << N << endl;
	cout << "K = " << K << endl;
	cout << endl;

	return 0;
}


double AsianOption::PriceByCRR(BinModel Model)
{
			//timing	
			//clock_t sta,edt;
			//sta=clock(); 

	
	//pricing
	double Price=0;
	vector<int> Path;
	for (int n=0;n<pow(2.0,N);n++)
	{
	  Model.GetSPath(n,N,Path);
	  Price=Price+Model.GetPathProb(N,Path)
		  *Payoff(Model,Path);
	}
	Price=Price*exp(-1*Model.GetRf()*Model.GetT());

	Path.clear();

			//timing
			//edt=clock();
			//cout <<endl << " The time cost is: " << edt-sta <<endl;

	return Price;
  
}

double AsianOption::PriceByMC(BinModel Model)
{
			//output file for recording the test data
			//fstream outFile;
			//outFile.open("recordAsianF.txt",ios::out | ios::app);

	int M;
	cout << "Enter the number of random paths M: ";cin>> M; cout << endl;
	cout << "M = " << M << endl <<endl; 
			
			//for testing efficient and accuarcy for different sample numbers M
			//int M;
			//for(M=2500;M<=10000;M=M+500) {


	double Price=0;
	vector<int> Path;
	double rs;
			//double a[30001],hbar=0,sdv=0; //for store payoff of random paths

			//initialise time variables
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
			//a[i]=Payoff(Model,Path); //for store payoff of random paths
		Price=Price+Payoff(Model,Path)/M;
	}
	Price=Price*exp(-1*Model.GetRf()*Model.GetT());

	//path clear and calculate the fair price
	Path.clear();
	
			//timimg
			//ed=clock(); 

			//for store payoff of random paths to analyse the accuraacy
			/*
			for(int i=1;i<=M;i++)
				hbar=hbar+a[i];
			hbar=hbar/M;
			for(int i=1;i<=M;i++)
				sdv=sdv+(a[i]-hbar)*(a[i]-hbar);
			sdv=sqrt(sdv/(M-1));
			sdv=(sdv/sqrt((double)M))/pow(Model.GetR(),N); */
			//end of analysis of accuracy


			//record the data into file
			//outFile <<M << "," <<Price << "," << ed-st <<"," << sdv <<endl;


			//}   //for testing effiency and accuracy

	return Price;
}



double AsianCall::Payoff(BinModel MyModel,vector<int> SPath)
{
	double sum=0;
	for(int i=1;i<=N;i++)
		sum=sum+MyModel.S(i,SPath)/N;

	if(sum>K) return sum-K;
	else return 0;

}

		// used for checking the Pricing function is right

		//double AsianCall::Payoff(BinModel MyModel,vector<int> Path)
		//{
		//	if(MyModel.S(N,Path)>K) return MyModel.S(N,Path)-K;
		//	else return 0;
		//}


double AsianCusCall::Payoff(BinModel MyModel,vector<int> SPath)
{
	double sum=0;
	int step=N/F;
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=F;j++)
		{
			if(i==j*step) sum=sum+MyModel.S(i,SPath);
		}
	}

	sum=sum/F;
	if(sum>K) return sum-K;
	else return 0;
}

double AsianCusPut::Payoff(BinModel MyModel,vector<int> SPath)
{
	double sum=0;
	int step=N/F;
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=F;j++)
		{
			if(i==j*step) sum=sum+MyModel.S(i,SPath);
		}
	}
	sum=sum/F;
	if(K>sum) return K-sum;
	else return 0;
}

double AsianPut::Payoff(BinModel MyModel,vector<int> SPath)
{
	double sum=0;
	for(int i=1;i<=N;i++)
		sum=sum+MyModel.S(i,SPath)/N;

	if(K>sum) return K-sum;
	else return 0;

} 