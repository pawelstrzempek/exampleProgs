/*----------------------------------------------------------------------------------------------------------
 * ROOTmacros
 * ==========
 * directory contains all useful ROOT based macros
 * File description:
 * graphDraw.C - macro which reads in the ASCII data from file. Data format of the file should be Xvalues<tab>Yvalues. One can give several files separated by the comma sign.
 * Usage:
 * root -l
 * .L graphDraw.C++
 * grapher("/path1/file1,/path2/file2,...")
 * */
//----------------------------------------------------------------------------------------------------------
//git test
#include <TGraph.h>
#include <TCanvas.h>
#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <TH1F.h>
#include <TLegend.h>
#include <TAxis.h>
using namespace std;
std::list <float> Xtab;
std::list <string> Files;
TH1F *hist = new TH1F("hist","hist",200,700,900);
/*_____________________________________________________________
*NAME: readIn
*DESCRIPTION: This function reads in the data from the file. The data is stored in
two lists one for X values and the other for Y values.
*/
int readIn(string FileName){
 char line[160];
 float x = 100000;
 FILE * pFile;
 pFile = fopen (FileName.c_str(),"r");
 if (pFile==0)
 {
 	cout<<"Error opening file "<<FileName<<endl;
 	return 0;
 }


 while(fgets(line, 160, pFile) != NULL)
 {
 /* get a line, up to 80 chars from pFile. done if NULL */
 	sscanf (line, "%f", &x);
 	Xtab.push_back(x);
  	std::cout << x<< "  "<<std::endl;
 }
 fclose(pFile); /* close the file prior to exiting the routine */
 return 1;
}

std::vector<string> parseFileNames(string Names)
{
	std::string str = Names;
	std::vector<string> vect;
	std::istringstream ss(str);
	std::string token;
	while(std::getline(ss, token, ',')) {
// std::cout << token << '\n';
		vect.push_back(token);
	}
return vect;
}



int histBuild(string File, string Title="", string xAxisTitle = "", string yAxisTitle = ""){
unsigned short FileQuantity = 1;
TCanvas *c1;
Int_t n = 0;
std::vector<string> FileNames;
//parse file names
FileNames = parseFileNames(File);
FileQuantity = FileNames.size();
c1 = new TCanvas("c1","Chart",200,10,700,500);
TLegend *leg = new TLegend(0.48,0.7,0.99,0.9);//relative to pad normalized coordinances (Double_t x1, Double_t y1, Double_t x2, Double_t y2)
//leg->SetHeader("The Legend Title");
for (int k = 0; k < FileQuantity ; k++){
	Xtab.clear();
	if(!readIn(FileNames[k])) return 0;
	cout<<"Finished reading file \""<<FileNames[k]<<"\"\n";
	while(!Xtab.empty())
	{
		hist->Fill(Xtab.back());
		Xtab.pop_back();
	}
	//leg->AddEntry(gr[k],(FileNames[k]).c_str(),"l");
	//mg->Add(gr[k]);
}
hist->SetTitle(Title.c_str());
hist->GetXaxis()->SetTitle(xAxisTitle.c_str());
hist->GetYaxis()->SetTitle(yAxisTitle.c_str());
hist->Draw(); 

c1->SetGrid();
c1->SaveAs((File+".svg").c_str());


//leg->Draw();
return 0;
}
