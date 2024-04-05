/*
c++ -o fitRL fitRL.cpp `root-config --cflags --glibs`
*/

#include <iostream>
#include <TMultiGraph.h>
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
  myGraph->SetTitle("|H_{L}(#omega)|");
  myGraph->GetXaxis()->SetTitle("#omega [seconds^{-1}]");
  myGraph->GetYaxis()->SetTitle("V_{L}/V_{g}");
  
  TF1* myFun = new TF1 ("myFun","1/sqrt((1+([0]/(2*3.14*x*[1]))^2))");
  //39/(39+[0])*sqrt(((1-4*3.14^2*x^2*[1]*[3]/39)^2+(2*3.14*x*(1+[0]/39)*[3]+[1]/39-[0]*[2]/39)^2)/((1+(2*3.14*x*[3])^2)*(1+(2*3.14*x*[1]/([0]+39))^2)))
  //1/sqrt((1+([0]/(2*3.14*x*[1]))^2))
  
  
  myFun->SetParName(0,"R [Ohm]");
  myFun->SetParName(1,"L [H]");
  //myFun->SetParName(2,"#tau_{zero} [seconds]");
  //myFun->SetParName(3,"#tau_{polo} [seconds]");
  
  myFun->FixParameter(0,2157);
  myFun->SetParameter(1,0.042);
  //myFun->SetParameter(2,0.0001);
  //myFun->SetParameter(3,0.00008);
  
  myC->SetLogx();
  //myC->SetLogy();

  myC->cd();
  myGraph->Draw("AP");
  myGraph->Fit("myFun");   
  myC->Modified();
  myC->Update();

  cout << "\nThe result of the fit with the model I(p1,p2) = p1*(exp(p2)-1) is:" << endl;
  cout << "A = " << myFun->GetParameter(0) << " +/- " << myFun->GetParError(0) << endl;
 
  myApp->Run();
  return 0;
}
