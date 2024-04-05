/*
c++ -o fitRLC fitRLC.cpp `root-config --cflags --glibs`
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
  myGraph->SetTitle("|H_{R}(#omega)|");
  myGraph->GetXaxis()->SetTitle("#omega [seconds^{-1}]");
  myGraph->GetYaxis()->SetTitle("V_{R}/V_{g} [Volt]");
  
  TF1* myFun = new TF1 ("myFun","[2]/sqrt(([2]+39)^2+(x*[1]-1/([0]*x))^2)");
  myFun->SetParName(1,"L [H]");
  myC->SetLogx();
  myFun->SetParName(0,"C [F]");
  myFun->SetParName(2,"R [#Omega]");
  myFun->SetParameter(1,0.08);
  myFun->SetParameter(0,0.000002);
  myFun->SetParameter(2,33);

  myC->cd();
  myGraph->Draw("AP");
  myGraph->Fit("myFun");   
  myC->Modified();
  myC->Update();

  cout << "\nThe result of the fit with the model I(p1,p2) = p1*(exp(p2)-1) is:" << endl;
  cout << "A = " << myFun->GetParameter(0) << " +/- " << myFun->GetParError(0) << endl;
  cout << "B = " << myFun->GetParameter(1) << " +/- " << myFun->GetParError(1) << endl;
    
  myApp->Run();
  return 0;
}
