#ifndef BinModel_h
#define BinModel_h

#include <vector>
using namespace std;

class BinModel
{
private:
	double S0;
	double U;
	double R;
	double D;
	vector<int> UDPath;
	double T;
	double rf;
	double sigma;
	double R1;
	double q;

public:
	//computing risk neutural probability
	double RiskNeuProb();

	//get the path of node
	int GetSPath(int n, int N,vector<int>& UDPath);

	//get the price of any node
	double S(int t, vector<int> UDPath);

	//get the probability of node
	double GetPathProb(int N,vector<int> UDPath);

	//inputing data for the Binomial model
	int GetInputData(int N);

	double GetR();
	double GetT(){return T;}
	double GetRf(){return rf;}
	double GetSigma(){return sigma;}
	double GetF0(){return S0;}

	double NormDist(double x);
};


#endif