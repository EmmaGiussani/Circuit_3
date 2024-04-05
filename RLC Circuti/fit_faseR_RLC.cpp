/*
c++ -o fit_faseR_RLC fit_faseR_RLC.cpp `root-config --cflags --glibs`
*/

#include <iostream>

#include <TStyle.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <cmath>

using namespace std;

int main(int argc, char** argv)
{
  if (argc < 2)
    {
      cout << "Not enough parameters: ./fitretta filedati.txt" << endl;
      return 1;
    }
  
  gStyle->SetOptFit(1112);

  TApplication* myApp = new TApplication("myApp", NULL, NULL);
  TCanvas* myC = new TCanvas("myC","myC",0,0,700,500);
  TGraphErrors* myGraph = new TGraphErrors(argv[1]);
  myGraph->SetMarkerStyle(20);
  myGraph->SetTitle("#Phi_{R}(#omega)");
  myGraph->GetXaxis()->SetTitle("#omega [seconds^{-1}]");
  myGraph->GetYaxis()->SetTitle("#Delta#phi [rad]");
  
  TF1* myFun = new TF1 ("myFun","atan2((x*[1]-1/(x*[0])),([2]+39))");
  myFun->SetParName(1,"L [H]");
  //myC->SetLogx();
  myFun->SetParName(0,"C [F]");
  myFun->SetParName(2,"R [#Omega]");
  myFun->SetParameter(1,0.04);
  myFun->SetParameter(0,0.000002);
  myFun->SetParameter(2,33);

  myC->cd();
  myGraph->Draw("AP");
  myGraph->Fit("myFun");   
  myC->Modified();
  myC->Update();

  myApp->Run();
  return 0;
}
