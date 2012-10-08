#include "BinModel.h"
#include "Option.h"
#include "AsianOption.h"
#include "LbOption.h"
#include "EuroOption.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <bitset>
using namespace std;

int main()
{
	BinModel MyModel;  //¸ÄÎªÁË
	int Steps;int type; int con;

	/*
	cout <<"Please Choose Option type (1¡¢European Option; 2¡¢Asion Option)";cin>>con; cout<<endl;
	while (con==1 || con==2)
	{
		if(con==1) //European Future Options 
		{
			cout << "Enter Steps N = "; cin >>Steps; cout<<endl;
			cout << "Enter Option type (1,Call;2,Put): "; cin>>type;cout<<endl;
			MyModel.GetInputData(Steps);
			if(type==1){
				EuroCall MyOption0;
				MyOption0.GetInputData(Steps);
				 cout<< "European Call Future Option price by Monte Carlo = "<<MyOption0.PriceByMC(MyModel)<<endl; 
				 cout<< "European Call Future Option price by Black Model = "<<MyOption0.PriceByBlack(MyModel)<<endl; 
				 //cout<< "European Call Future Option price by CRR Model= " <<MyOption0.PriceByCRR(MyModel)<<endl;
			}
			else if(type==2)
			{
				EuroPut MyOption01;
				MyOption01.GetInputData(Steps);
				cout << "European Put Future Option price by Monte Carlo = " <<MyOption01.PriceByMC(MyModel)<<endl;
				cout << "European Put Future Option price by Black Model = " <<MyOption01.PriceByBlack(MyModel)<<endl;
				//cout << "European Put Future Option price by CRR Model = "	<<MyOption01.PriceByCRR(MyModel)<<endl;
			}
		}
		else if(con==2) //Asion Future Options
		{
			cout << "Enter Steps N = "; cin >>Steps; cout<<endl;
			cout << "Enter Option type (1,Call;2,Put): "; cin>>type;cout<<endl;
			MyModel.GetInputData(Steps);
			if(type==1){
				AsianCall MyOption11;
				MyOption11.GetInputData(Steps);
				cout << "Asian Call Future Option price by CRR = " <<MyOption11.PriceByCRR(MyModel)<<endl;
				cout << "Asian Call Future Option price by Monte Carlo = " <<MyOption11.PriceByMC(MyModel)<<endl;
			}
			else if(type==2)
			{
				AsianPut MyOption12;
				MyOption12.GetInputData(Steps);
				cout << "Asian Put Future Option price by CRR = " <<MyOption12.PriceByCRR(MyModel)<<endl;
				cout << "Asian Put Future Option price by Monte Carlo = " <<MyOption12.PriceByMC(MyModel)<<endl;
			}
		}
	}  */

	cout << "Enter Steps N = "; cin >>Steps; cout<<endl;
	MyModel.GetInputData(Steps);
	AsianCusCall ACOption0;
	ACOption0.GetInputData(Steps);
	
	//cout << "European Call Future Option price by Monte Carlo = " <<ACOption0.PriceByMC(MyModel)<<endl;
	//cout << "European Put Future Option price by CRR Model = "	<<ACOption0.PriceByCRR(MyModel)<<endl;

	for(int i=1;i<=100;i++)
	{
		cout << ACOption0.PriceByMC(MyModel) <<endl;
	}



	char x;
	cin >>x;

	return 0;

}