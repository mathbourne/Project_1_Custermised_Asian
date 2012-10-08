#include "BinModel.h"
#include <iostream>
#include <cmath>
#include <bitset>

using namespace std;

double BinModel::RiskNeuProb()
{
	double prob=(R1-D)/(U-D);
	return prob;  //改为了1-D/U-D，这是Futures Option的Risk-Neutrual Prob
}

int BinModel::GetInputData(int N)
{
	//Enter market data
	cout << endl;
	cout << "Please enter some market information."<<endl<<endl;
	cout << "Enter initial future price S0:  "; cin>>S0;
	cout << "Enter expiry  time         T:  "; cin>>T;
	cout << "Enter interest rate        r:  "; cin>>rf;
	cout << "Enter the volatiliy    simga:  "; cin>>sigma;
	cout << "Enter the dividend rate	q:	"; cin>>q;
	cout << endl;

	//Display entered date
	cout << "S0 = " <<S0<<endl;
	cout << "T = " <<T<<endl;
	cout << "r = " <<rf<<endl;
	cout << "sigma = " <<sigma<<endl;
	cout << "q = "<<q<<endl;

	//Cal U,D,R
	double dT=T/N;
	U=exp(sigma*sqrt(dT));
	D=1/U;
	R=exp(rf*sqrt(dT));
	R1=exp((rf-q)*sqrt(dT));

	//Display
	cout << "U = " <<U<<endl;
	cout << "D = " <<D<<endl;
	cout << "R = " <<R<<endl;
	cout << "R1 = " <<R1<<endl;
	cout << "P= " << (R1-D)/(U-D)<<endl;
	

	/*
	//Entering data
	cout << "Enter S0: "; cin>>S0;
	cout << "Enter U:  "; cin>>U;
	cout << "Enter D:  "; cin>>D;
	cout << "Enter R:  "; cin>>R;
	cout << endl;

	//displaying entered data
	cout << "S0 = " << S0 << endl;
	cout << "U  = " << U  << endl;
	cout << "D  = " << D  << endl;
	cout << "R  = " << R  << endl;
	cout << endl;
	
	
	//making sure the data range is OK
   if (S0<=0 || U<=0 || D<=0 || U<=D || R<=0)
   {
      cout << "Illegal data ranges" << endl;
      cout << "Terminating program" << endl;
      return 1;
   } 

   //checking for arbitrage
   if (R>=U || R<=D)
   {
      cout << "Arbitrage exists" << endl;
      cout << "Terminating program" << endl;
      return 1;
   }

   cout << "Input data checked" << endl;
   cout << "There is no arbitrage" << endl << endl;  */

   return 0;

}

double BinModel::GetR()
{
  return R;
}

double BinModel::S(int t, vector<int> UDPath)
{
  int i;
  int up = 0;
  for(i=0;i<t;i++)
	  if(UDPath[i]==1) up++;

  return S0*pow(U,up)*pow(D,t-up);
}

double BinModel::GetPathProb(int N,vector<int> UDPath)
{
  int i;
  int up = 0;
  for (i=0;i<N;i++)
	  if(UDPath[i]==1) up++;

  return pow(RiskNeuProb(),up)*pow(1-RiskNeuProb(),N-up);
}

int BinModel::GetSPath(int n, int N,vector<int> &UDPath)
{
	UDPath.clear();
	
	bitset<100> b;
	b=n;

	for (int i=N-1; i>=0; i--)
		UDPath.push_back(b[i]);

	return 0;
}

double BinModel::NormDist(double x)
{
	double pi=3.14159265;
	double e=2.7182818284;
	
	double a1=0.319381530;
	double a2=-0.356563782;
	double a3=1.7814779937;
	double a4=-1.821255978;
	double a5=1.330274429;
	double gama=0.2316419;

	double n=pow(e,(x*x)*(-0.5))/sqrt(2*pi);

	if (x>0 || x==0){
		double k=1/(1+gama*x);
		double n=pow(e,(x*x)*(-0.5))/sqrt(2*pi);
	    double kright=a1*k+a2*pow(k,2)+a3*pow(k,3)+a4*pow(k,4)+a5*pow(k,5);
		return 1-n*kright;}
	else{
		x=-x;
		double k=1/(1+gama*x);
		double n=pow(e,(x*x)*(-0.5))/sqrt(2*pi);
	    double kright=a1*k+a2*pow(k,2)+a3*pow(k,3)+a4*pow(k,4)+a5*pow(k,5);
		return n*kright;}
}