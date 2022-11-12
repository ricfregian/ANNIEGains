
#include "iostream"
#include "TTree.h"
#include "TBranch.h"
#include "TChain.h"
#include "TFile.h"
#include "TBranch.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <vector>
#include <TKey.h>
#include "TLegend.h"

using namespace std;


int main()

{
TFile *f = new TFile("/Users/giancaceresvera/Desktop/ANNIE/calibration/gains_data/LED_2runs/LEDRun3134_3158_S0ALLLEDS_allPMTs_Run-1.root");
TFile *f_th = new TFile("/Users/giancaceresvera/Desktop/ANNIE/calibration/gains_data/LED_5runs/LEDRun_5Runs_S0_threshold_nversion_Run-1.root");

vector <int> ETEL_list = {350,351,353,354,355,356,357,358,359,360,361,362,363,364,365,366,367,368,369,370,371,372,373,374,375};

for(int i: ETEL_list){
//int i = 350;
TH1F * h1 = (TH1F*)f->Get(Form("hist_charge_%i",i));
TH1F * h1_th = (TH1F*)f_th->Get(Form("hist_charge_%i",i));
            //cout<< " list   " << h1_th->GetListOfFunctions()/*->FindObject("functionName")*/<< endl;                                                                                           
            //string cName = Form( "%s",h1->GetName());          
            TCanvas cSIS("SIS" ,"SIS" , 1280, 800 );                                    

	    delete h1->GetListOfFunctions()->FindObject("total");
            int h1_e = h1->GetEntries();
	    //h1->Scale(1/h1_e,"width");
	    h1->SetLineWidth(4);
            h1->GetXaxis()->SetRangeUser(0, 0.01);
	    //h1->Scale(1,"width");
	    //h1->GetListOfFunctions()->Print();
	    //h1->GetFunction("total");

	    h1->Draw();
	    
	    delete h1_th->GetListOfFunctions()->FindObject("total");
            int h1_th_e = h1_th->GetEntries();
            h1_th->GetXaxis()->SetRangeUser(0, 0.01);
	    //h1_th->Scale(1/h1_th_e,"width");
	    h1_th->SetLineWidth(4);
	    h1_th->SetLineColor(2);
	    //h1_th->Scale(1,"width");
	    //h1_th->Scale(1/h1_th_e);
	    h1_th->Draw("same");
	    //h1_th->Draw();
	    
     	    //auto legend = new TLegend(0.44,0.8,0.76,0.9);
	    //legend->AddEntry((TObject*)0, Form(" %.1f percent events captured", frac_events*100 ), "");
	    //legend->Draw();
            cSIS.SetLogy();
            cSIS.SaveAs(Form("hist_charge_%i.png",i));                                                              
                                                                                               
}
}

//TH1D* h_tof =(TH1D*)fin->Get("h_tot_ncapt_tof");
  //double entries = h_tof->GetEntries();

/*
  TList* list = fin->GetListOfKeys() ;
  if (!list) { printf("<E> No keys found in file\n") ; exit(1) ; }
  TIter next(list) ;
  TKey* key ;
  TObject* obj ;
      
  while ( key = (TKey*)next() ) {//warning about the parenthesis
    obj = key->ReadObj() ;
    if (    (strcmp(obj->IsA()->GetName(),"TProfile")!=0)
         && (!obj->InheritsFrom("TH2"))
	 && (!obj->InheritsFrom("TH1")) 
       ) {
      printf("<W> Object %s is not 1D or 2D histogram : "
             "will not be converted\n",obj->GetName()) ;
    }
    printf("Histo name:%s title:%s\n",obj->GetName(),obj->GetTitle());

    TH1F *hnew = (TH1F*)obj->Clone(obj->GetName()); 

        {                                                                                                
            string cName = Form( "%s",obj->GetName());          
            TCanvas cSIS( cName.c_str(), cName.c_str(), 1280, 800 );                                    
	    //gStyle->SetLineWidth(3);
	    //obj->SetLineWidth(7);
	    //obj->Draw();
	    //double entries = hnew->GetEntries();
	    //double frac_events = entries/10000;
	
	    hnew->SetLineWidth(2);
	    hnew->Draw();
	    
     	    //auto legend = new TLegend(0.44,0.8,0.76,0.9);

	    //legend->AddEntry((TObject*)0, Form(" %.1f percent events captured", frac_events*100 ), "");
	    //legend->Draw();
            cSIS.SetLogy();
            cSIS.SaveAs(Form("plots_2p5_10M_mediumvol/%s.pdf", cName.c_str()) );                                                              
        }                                                                                       


  }
*/

