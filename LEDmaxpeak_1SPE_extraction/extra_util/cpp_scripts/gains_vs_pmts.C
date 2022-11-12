#include <iostream>
#include <fstream>
#include "TTree.h"
#include "TBranch.h"
#include "TChain.h"
#include "TFile.h"
#include "TBranch.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <vector>
#include "TGraph.h"


using namespace std;

int main(){
ifstream infile_db ("pmt_gains_db.txt");
ifstream infile ("pmt_gains.txt");

double pmt, gain;
vector <double> pmts_db, pmts;
vector <double> gains_db, gains;


//number of pmts 
//vector <int> tot_num_pmts;
//for(int i=332; i< 464; i++)
//{
//tot_num_pmts.push_back(i);
//cout<< "pmt " << i << endl;
//}
//
//for(int i=0; i<gains.size();  i++)
//{
//cout<< "gains " << i << endl;
//}


while (infile_db >> pmt >> gain)
	{
	pmts_db.push_back(pmt);
	gains_db.push_back(gain);
	}

pmt = gain = 0;

while (infile >> pmt >> gain)
	{
	pmts.push_back(pmt);
	gains.push_back(gain);
	}


	{
            string cName = Form("gainsvspmts");
            TCanvas cgains( cName.c_str(), cName.c_str(), 1280, 800 );                                    

   		//TGraph* graph_new_gains = new TGraph(pmts.size(),&pmts[0], &gains[0]);
   		TGraph* graph_gains_db = new TGraph(pmts_db.size(),&pmts_db[0], &gains_db[0]);
		graph_gains_db->SetNameTitle("Gains");
		graph_gains_db->GetXaxis()->SetTitle("PMT");
		graph_gains_db->GetYaxis()->SetTitle("Gain");
		graph_gains_db->SetMarkerColor(4);
		graph_gains_db->SetMarkerStyle(20);
		graph_gains_db->Draw("AL*");

   		//cgains.SetLogy();
   		//cgains.SetLogx();

       	        cgains.SaveAs(Form("%s.pdf", cName.c_str()) );                                                              
	}	

}


