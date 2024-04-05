/*
c++ -o fitRC fitRC.cpp `root-config --cflags --glibs`
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
  myGraph->SetTitle("|H_{C}(#omega)|");
  myGraph->GetXaxis()->SetTitle("#omega [seconds^{-1}]");
  myGraph->GetYaxis()->SetTitle("V_{C}/V_{g}");
  
  TF1* myFun = new TF1 ("myFun","1/sqrt(1+(2*3.14*x*[0]*[1])^2)");
  //1/(2*3.14*x*[1])/sqrt(([2]/(1+(2*3.14*x*[0]*[2])^2))^2+(1/(2*3.14*x*[1])-(2*3.14*x*[0]*[2]^2)/(1+(2*3.14*x)^2*[0]^2*[2]^2))^2)
  myFun->SetParName(1,"C [F]");
  //myFun->SetParName(0,"C_{sonda} [F]");
  myC->SetLogx();
  myC->SetLogy();
  myFun->SetParName(0,"R [Ohm]");
  //myFun->SetParameter(0,0.00000001);
  myFun->SetParameter(1,0.000000098);
  myFun->FixParameter(0,99);

  myC->cd();
  myGraph->Draw("AP");
  myGraph->Fit("myFun");   
  myC->Modified();
  myC->Update();

  cout << "\nThe result of the fit with the model I(p1,p2) = p1*(exp(p2)-1) is:" << endl;
  cout << "A = " << myFun->GetParameter(0) << " +/- " << myFun->GetParError(0) << endl;
  //cout << "B = " << myFun->GetParameter(1) << " +/- " << myFun->GetParError(1) << endl;
    
  myApp->Run();
  return 0;
}
