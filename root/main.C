#include <iostream>
#include <fstream>
#include "Util.h" 

#include "UsefulAdu5Pat.h" 
#include "Adu5Pat.h"

bool isFinal(RawAnitaHeader *hdPtr) {

long num = hdPtr->eventNumber;
long eventNums[13] = {3791983,4700968,5873098,6787259,11699126,12416660,19361634,22603190,29679912,46741778,48151355,53332751,57215430};

for(int i =0; i < 13; i++) { if (num == eventNums[i]) {return true;}
}
return false;
}




bool isInBaseRegion(double sourceLat, double sourceLon) {

//south pole base
if (sourceLat < -87.6) {return true;}

//Mcmurdo
if ( (sourceLat < -73 & sourceLat > -80) & ((sourceLon < 180 & sourceLon > 150) || (sourceLon > -180 &  sourceLon < -175))) {return true;}

//WAIS
if ( (sourceLat < -79 & sourceLat > -81) & (sourceLon > -125 & sourceLon < -104)) {return true;}

//UnknownBase1
if( (sourceLat < -77  & sourceLat > -81) & (sourceLon > -87 & sourceLon < -72)) {return true;}

//UnknownBase2
if( (sourceLat <-80 & sourceLat > -82) & (sourceLon > -26 & sourceLon < -6.5)) {return true;}

//Coast Base
if ((sourceLat <-77.8 & sourceLat > -79) & (sourceLon > -35 & sourceLon < -27)) {return true;}

//domeFuji
if ((sourceLat < -77 & sourceLat > -78) & (sourceLon > 37.5 & sourceLon < 42)) {return true;}

//UnknownBase3
if ((sourceLat <-84 & sourceLat > -86) & (sourceLon > -130.5 & sourceLon < -114)) {return true;}

//UnknownBase4
if ((sourceLat <-81 & sourceLat > -83) & (sourceLon > -93 & sourceLon <  -86)) {return true;}

return false;

}


bool isNotClustered(RawAnitaHeader *hdPtr) {

long clusterTimes[278]= {1480692734,1480692788,1480708016,1480708070,1480708934,1480709042,1480709852,1480709906,1480709960,1480710014,1480712498,1480712660,1480712714,1480712822,1480712876,1480712930,1480713092,1480713200,1480713308,1480713362,1480713470,1480713578,1480713632,1480713902,1480713956,1480714010,1480714118,1480714172,1480714226,1480714334,1480714388,1480714496,1480714550,1480714874,1480714982,1480715036,1480715414,1480715468,1480715900,1480715954,1480716008,1480716224,1480716278,1480716332,1480717466,1480717682,1480721948,1480722056,1480722110,1480723298,1480723352,1480725458,1480725512,1480725566,1480725674,1480725728,1480725836,1480725890,1480725944,1480726052,1480726160,1480726214,1480726268,1480726376,1480726430,1480726538,1480726592,1480726700,1480726754,1480726808,1480726862,1480727024,1480727078,1480727132,1480727240,1480727294,1480727348,1480727402,1480727456,1480727564,1480727834,1480727942,1480727996,1480728212,1480728320,1480728374,1480728482,1480728536,1480728590,1480728806,1480729346,1480730102,1480730156,1480730696,1480730750,1480730966,1480731020,1480731236,1480731344,1480731776,1480731830,1480731884,1480731938,1480732532,1480732586,1480732802,1480732856,1480732910,1480733720,1480734746,1480734800,1480735664,1480735718,1480736690,1480742792,1480742846,1480746248,1480746302,1480746410,1480746464,1481141852,1481141906,1481158430,1481158484,1481198174,1481198282,1481199956,1481200010,1481202872,1481202926,1481205464,1481205518,1481205626,1481205680,1481208002,1481208056,1481209784,1481209838,1481211998,1481212052,1481213618,1481213672,1481214104,1481214158,1481216696,1481216750,1481217776,1481217830,1481221664,1481221718,1481221934,1481222042,1481226902,1481226956,1481227550,1481227658,1481228090,1481228144,1481234678,1481234732,1481277878,1481277986,1481284520,1481284574,1481286356,1481286410,1481315354,1481315408,1481315570,1481315624,1481343758,1481343866,1481344190,1481344244,1481344298,1481344352,1481501870,1481501924,1481502086,1481502140,1481551010,1481551118,1481565536,1481565590,1481813558,1481813612,1481867990,1481868044,1481952446,1481952554,1481952608,1481952932,1481989220,1481989328,1482042518,1482042572,1482042950,1482043058,1482053480,1482053534,1482076052,1482076106,1482085286,1482085340,1482247934,1482247988,1482328448,1482328556,1482338222,1482338276,1482347402,1482347510,1482347564,1482347618,1482360308,1482360362,1482361766,1482361820,1482369218,1482369812,1482370244,1482370352,1482399944,1482400484,1482415496,1482415658,1482416198,1482416252,1482433478,1482433586,1482440120,1482440282,1482440390,1482440606,1482629228,1482629282,1482630308,1482630362,1482631226,1482631280,1482637598,1482637868,1482638246,1482638300,1482638354,1482638462,1482678206,1482678692,1482778322,1482778376,1482778646,1482778700,1482858620,1482858674,1482861158,1482861428,1482887294,1482887402,1482888482,1482888536,1482888590,1482888644,1482891398,1482891452,1482896852,1482896960,1482897770,1482897824,1482898148,1482898256,1482898796,1482898958,1482899012,1482899066,1482901280,1482901334,1482916724,1482916778};


long eventTime = hdPtr->payloadTime;

for( int i =0; i < 278 - 1; i+=2) {

   if (eventTime >= clusterTimes[i] & eventTime < clusterTimes[i+1]) {
      return false;

   }
}

return true;


}

bool isUHENLike(RawAnitaHeader *hdr) {
   if (hdr->getImagePeak() < 0.131) {
      if(hdr->getCoherentSumPeak() < 290) {
         return false;
      } else {
         return true;
      }
   } else {
      return true;
   
}
}


/**
 * Determines whether or not we think an event is a WAIS Pulser. Further
 * implmentation of isWAISHpol /Vpol in UCorrelator/Util.cc as time delay
 * settings where changed sometime after run 133. No checks on wether
 * specfic run number has a headFile to read from.
 *
 * @param pat a pointer of type UsefulAdu5Pat, contains event GPS data.
 * @param hdr a pointer of type RawAnitaHeader, contains event head data.
 * @param runNum an integer the represents current run number. 
 * @return true if event is WAIS Pusler event, false otherwise.
 */
bool isWAISPulser(UsefulAdu5Pat * pat, RawAnitaHeader * hdr, int run) {
      if (strcmp(hdr->trigTypeAsString(),"RF") != 0) {return false;}
      if ((hdr->priority&0xf) > 3) {return false;}
      int triggerTime = hdr->triggerTimeNs;
      int timeToWAIS = pat->getWaisDivideTriggerTimeNs();
      int diff = triggerTime - timeToWAIS;
      if ((diff < -500 & diff > -1500) || (diff < -10500 & diff > - 11500)) {
         return true;
      }
      return false;
}



void WAISDist() {


int WAISPulserCounterV = 0;
int WAISPulserCounterH =0;
int testWaisCounter = 0;


TH1F *waisDtVPol;
waisDtVPol = new TH1F("waisDtVPol", "",1000,-20000,20000);


//iterate over all runs
for(int run = 120;run <160; run++) {

char headerName[100];
sprintf(headerName,"/unix/anita3/anita4/flight1617/telem/root/run%d/headFile%d.root",run,run);

char Adu5PatName[100];
sprintf(Adu5PatName,"/unix/anita3/anita4/flight1617/telem/root/run%d/gpsEvent%d.root",run,run);

RawAnitaHeader *hdPtr = 0;
Adu5Pat *patPtr = 0; 
UsefulAdu5Pat *usefulPatPtr = 0;

//check if run actually has a head file.
bool fileStat = false;
std::ifstream infile(headerName);
fileStat =  infile.good();

if (fileStat) {

//Gps tree
TFile *fpPat = new TFile(Adu5PatName);
TTree *Adu5PatTree = (TTree*) fpPat->Get("adu5PatTree");
Adu5PatTree->SetBranchAddress("pat",&patPtr);


// Head tree
TFile *fpHead = new TFile(headerName);
TTree *headTree = (TTree*) fpHead->Get("headTree");
headTree->SetBranchAddress("header",&hdPtr);


Long64_t numEntries=headTree->GetEntries();


for(Long64_t entry=0;entry<numEntries;entry++) {


     
   headTree->GetEntry(entry);
   Adu5PatTree->GetEntry(entry);
   
   usefulPatPtr = new UsefulAdu5Pat(patPtr);

   int triggerTime = hdPtr->triggerTimeNs;
   int timeToWAIS = usefulPatPtr->getWaisDivideTriggerTimeNs();
   int diff = triggerTime - timeToWAIS;
   
   
   waisDtVPol->Fill(diff,1);
   testWaisCounter++;
 
}

}

}

cout << "TestWais Counter" << testWaisCounter << endl;

//cout << "Vpol WAIS Pulser Events: " << WAISPulserCounterV << endl;
//cout << "Hpol WAIS Pulser Events: " << WAISPulserCounterH << endl;

//plotting stuff.
TCanvas* ced = new TCanvas("ced","WAISDt",1200,1200);
ced->Draw();


//gPad->SetLogy();
gStyle->SetOptStat(0);
gStyle->SetLegendBorderSize(0);
waisDtVPol->GetYaxis()->SetTitleOffset(1.5);

//waisDtVPol->SetTitle("");
waisDtVPol->GetYaxis()->SetTitle("Number of Events");
waisDtVPol->GetXaxis()->SetTitle("(Trigger Time - Time to WAIS)[Ns]");
waisDtVPol->SetLineColor(2);
waisDtVPol->SetFillColor(46);
waisDtVPol->SetFillStyle(3002);

waisDtVPol->Draw();
//waisDtHPol->Draw("same");


}


void DistPulserTime() {

int minEpoch = 1481220000;
int maxEpoch = 1481490000;

int pulserCount =0;

TH1F *pulserDist;
pulserDist = new TH1F("puslerDist", "Run Number",100,minEpoch,maxEpoch);

TH1F *pulserDistTest;
pulserDistTest = new TH1F("puslerDistTest", "Run Number",100,minEpoch,maxEpoch);

Double_t time[90294]; 
Double_t dist[90294];

for( int i=0;i<90294; i++) {

time[i] =0;
dist[i] =0;
}
int pos = 0;

for(int run =123;run <156; run++) {


char headerName[100];
sprintf(headerName,"/unix/anita3/anita4/flight1617/telem/root/run%d/headFile%d.root",run,run);

char Adu5PatName[100];
sprintf(Adu5PatName,"/unix/anita3/anita4/flight1617/telem/root/run%d/gpsEvent%d.root",run,run);

RawAnitaHeader *hdPtr = 0;
Adu5Pat *patPtr = 0;
UsefulAdu5Pat *usefulPatPtr = 0;

//check if run actually has a head file.
bool fileStat = false;
std::ifstream infile(headerName);
fileStat =  infile.good();

if (fileStat) {

//Gps tree
TFile *fpPat = new TFile(Adu5PatName);
TTree *Adu5PatTree = (TTree*) fpPat->Get("adu5PatTree");
Adu5PatTree->SetBranchAddress("pat",&patPtr);


// Head tree
TFile *fpHead = new TFile(headerName);
TTree *headTree = (TTree*) fpHead->Get("headTree");
headTree->SetBranchAddress("header",&hdPtr);


Long64_t numEntries=headTree->GetEntries();


for(Long64_t entry=0;entry<numEntries;entry++) {



   headTree->GetEntry(entry);
   Adu5PatTree->GetEntry(entry);

   usefulPatPtr = new UsefulAdu5Pat(patPtr);
   
    
   
    
   if (isWAISPulser(usefulPatPtr, hdPtr, run)) {
      time[pos] = hdPtr->payloadTime;
      dist[pos] = usefulPatPtr->getWaisDivideTriggerTimeNs() *  0.299792 / 1000;
      pos++;
      pulserCount++;
      if ( entry % 4 == 0) { 
         pulserDist->Fill(hdPtr->payloadTime,1);
      } else {
         pulserDistTest->Fill(hdPtr->payloadTime,1);
   }
  }      
}


}





}

cout << pulserCount << endl;

TCanvas* ced = new TCanvas("PulserDist","Run Number",500,600);
ced->Draw();
Float_t small = 1e-5;
ced->Divide(1,2,small,small);


gStyle->SetPadBorderMode(0);
gStyle->SetFrameBorderMode(0);
gStyle->SetOptStat(0);
gStyle->SetLegendBorderSize(0);

pulserDist->GetYaxis()->SetTitleOffset(1.5);


mylegend = new TLegend(0.20,0.70,0.40,0.80); // create legend
mylegend->SetFillColor(0); // white background
mylegend->SetBorderSize(0); // get rid of the box
mylegend->SetTextSize(0.045); // set text size
mylegend->AddEntry(pulserDistTest,"Training Set: 8421" ,"f");
mylegend->AddEntry(pulserDist,"Testing Set: 3609" ,"f"); // options: p,l,f




ced->cd(1);
pulserDist->SetTitle(""); 
pulserDist->GetYaxis()->SetTitle("Number of WAIS Pulser Events");
pulserDist->GetYaxis()->SetRangeUser(1,600);
pulserDist->SetLineColor(2);
pulserDist->SetFillColor(2);
pulserDist->SetFillStyle(3002);
//pulserDist->SetMarkerStyle(24);
//pulserDist->SetMarkerSize(0.4);
pulserDist->GetXaxis()->SetLabelOffset(999);
gPad->SetBottomMargin(small);


pulserDistTest->SetLineColor(4);
pulserDistTest->SetFillColor(4);
pulserDistTest->SetFillStyle(3003);
//pulserDistTest->SetMarkerStyle(24);
//pulserDistTest->SetMarkerSize(0.4);

pulserDist->Draw();
pulserDistTest->Draw("same");
mylegend->Draw();

ced->cd(2);
gPad->SetTopMargin(small);
gPad->SetTickx();


TGraph* gr = new TGraph(10000,time,dist);
gr->SetTitle(""); 
gr->GetXaxis()->SetTitle("Unix Time [s]");
gr->GetYaxis()->SetTitle("Distance to Wais [km]");
gr->Draw("AC");
gr->GetYaxis()->SetTitleOffset(1.5);
gr->GetXaxis()->SetRangeUser(minEpoch,maxEpoch);
gr->GetYaxis()->SetRangeUser(0,899);
gr->Draw("AC"); 


ced->Update();
}

/** Writes WAIS pulser / noise training data to a CSV file for 
 * a range of runs. Format for each event [priority,ImagePeak,
 * CoherentSumPeak,Pulser/Noise flag]. 1 = Pulser, 0 = Noise.
 *
 * @param minRun an integer representing the minimum run to
 * start looking for pulser / noise events to be written.
 * @param maxRun an integer representing the max run to look
 * for pulser/noise events to be written 
 *
 * @return Writes a csv file with the training set of data.
*/
void WriteTrainingSet(int minRun, int maxRun) {
   
   int testPulserCount = 0;
   int testNoiseCount = 0;
   int trainPulserCount = 0;
   int trainNoiseCount = 0;

   char trainingName[100];
   sprintf(trainingName,"TrainingSet.csv");

   char testName[100];
   sprintf(testName,"TestingSet.csv");

   char geoDataName[100];
   sprintf(geoDataName,"afterTimeCluster.csv");  
 
   ofstream training;
   training.open(trainingName);

   ofstream testing;
   testing.open(testName);  

   ofstream geoData;
   geoData.open(geoDataName);
   
   
   for (int run =minRun; run < maxRun;run++) {

      char headerName[100];
      sprintf(headerName,"/unix/anita3/anita4/flight1617/telem/root/run%d/headFile%d.root",run,run);
       
      char Adu5PatName[100];
      sprintf(Adu5PatName,"/unix/anita3/anita4/flight1617/telem/root/run%d/gpsEvent%d.root",run,run);

      RawAnitaHeader *hdPtr = 0;
      Adu5Pat *patPtr = 0;
      UsefulAdu5Pat *usefulPatPtr = 0;

      //check if run actually has a head file.
      bool fileStat = false;
      std::ifstream infile(headerName);
      fileStat =  infile.good();

      if (fileStat) {
         
         //headTree
         TFile *fpHead = new TFile(headerName);
         TTree *headTree = (TTree*) fpHead->Get("headTree");
         headTree->SetBranchAddress("header",&hdPtr);
          

         //Gps tree
         TFile *fpPat = new TFile(Adu5PatName);
         TTree *Adu5PatTree = (TTree*) fpPat->Get("adu5PatTree");
         Adu5PatTree->SetBranchAddress("pat",&patPtr);
         

         Long64_t numEntries=headTree->GetEntries();

         for(Long64_t entry=0;entry<numEntries;entry++) {

            headTree->GetEntry(entry);
             
            headTree->GetEntry(entry);
            Adu5PatTree->GetEntry(entry);
            usefulPatPtr = new UsefulAdu5Pat(patPtr);

            Float_t imagePeak = hdPtr->getImagePeak();
            Float_t coherentSumPeak = hdPtr->getCoherentSumPeak();
            Float_t priority = hdPtr->priority&0xf;
           
            
            Double_t theta = hdPtr->getPeakThetaRad();
            Double_t phi = hdPtr->getPeakPhiRad();

            Double_t sourceLon,sourceLat;
            sourceLon = 0;
            sourceLat = 0;
           
            Double_t lat = patPtr->latitude;
            Double_t lon =  patPtr->longitude;

            int solved = 0;
            if ( theta < 0) {
               solved = usefulPatPtr->getSourceLonAndLatAltZero(phi,-1*theta, sourceLon, sourceLat);
            }

            if ( solved == 0) {
               solved =usefulPatPtr->getSourceLonAndLatAltZero(phi,6.5*TMath::DegToRad(),sourceLon,sourceLat);
            }
           
           //if (entry % 2000 == 0 & lat < -70) {
             // geoData << lat << "," << lon << endl;
           // }
   
          

           if ((strcmp(hdPtr->trigTypeAsString(),"RF") == 0) & (solved > 0) & (!isWAISPulser(usefulPatPtr,hdPtr,run)) & (isUHENLike(hdPtr)) & sourceLat < -68 & (!isNotClustered(hdPtr))) {
              geoData << sourceLat << "," << sourceLon << "\n";  
           }
            
            if ( entry % 16 == 0) {
              if (isWAISPulser(usefulPatPtr,hdPtr,run)){ 
                  
                  testing << coherentSumPeak << ',' << theta << ',' << imagePeak <<  "," << "1\n";          
                  testPulserCount++;
               } else if (strcmp(hdPtr->trigTypeAsString(),"RF") != 0 & testNoiseCount < 3105) {
                  testNoiseCount++;
                  testing << coherentSumPeak << "," << theta << "," << imagePeak << "," << "0\n";   
               } 
            } else if (entry % 4 ==0 ) {
               if (isWAISPulser(usefulPatPtr,hdPtr,run)){         
                  trainPulserCount++;
                  training << coherentSumPeak << "," << theta << "," << imagePeak << "," << "1\n";

               } else if (strcmp(hdPtr->trigTypeAsString(),"RF") != 0 & trainNoiseCount < 9075) {
                  trainNoiseCount++;
                  training << coherentSumPeak << "," << theta <<  "," << imagePeak <<"," <<  "0\n";
               } 
           }

   }
   }
}
  
   
    
   training.close();
   testing.close();
   geoData.close();
   cout << "Number of test Pulser Events: " << testPulserCount << endl;
   cout << "Number of test Noise Events: " << testNoiseCount << endl;
   cout << "Number of train Pulser Event: " << trainPulserCount << endl;
   cout << "NUMber of train Noise Events " << trainNoiseCount << endl;
   cout << "Total test set sample: " << testPulserCount + testNoiseCount << endl;
   cout << "Total train set sample: " << trainPulserCount + trainNoiseCount << endl;


}

void DistAll() {

//hist params for ImagePeak
int NUM_BINS_I = 50;
int MIN_I = 0;
int MAX_I = 1;


//hist params for priority
int NUM_BINS_P = 50;
int MIN_P = 0;
int MAX_P = 9;

//histparams for coherent sum peak
int NUM_BINS_C = 50;
int MIN_C = 0;
int MAX_C = 1000;

//histparams for Theta 
int NUM_BINS_T = 50;
double MIN_T = -1.5;
double MAX_T = 1.5;



TCanvas* ced = new TCanvas("headtail","Priority Vs ImagePeak",1000,1000);
ced->Draw();

//set up cummilitative histogram for image peak.
TH1F *tot;
tot = new TH1F("tot", "a. Image Peak", NUM_BINS_I, MIN_I, MAX_I);
tot->GetXaxis()->SetTitle("Image Peak [no units]");
tot->GetYaxis()->SetTitle("Number of Events");

TH1F *totU;
totU = new TH1F("totU", "a. Image Peak", NUM_BINS_I, MIN_I, MAX_I);

//set up cumilative histgram for priority.
TH1F *totP;
totP = new TH1F("totP", "c. Priority", NUM_BINS_P, MIN_P, MAX_P);
totP->GetXaxis()->SetTitle("Priority");
totP->GetYaxis()->SetTitle("Number of Events");

TH1F *totPU;
totPU = new TH1F("totPU", "c. Priority", NUM_BINS_P, MIN_P, MAX_P);

//set up cumilitative histogram for coherent sum peak.
TH1F *totC;
totC  = new TH1F("totC", "b. Coherent Sum Peak", NUM_BINS_C, MIN_C, MAX_C);
totC->GetXaxis()->SetTitle("Coherent Sum Peak [mV]");
totC->GetYaxis()->SetTitle("Number of Events");

TH1F *totCU;
totCU  = new TH1F("totCU", "b. Coherent Sum Peak", NUM_BINS_C, MIN_C, MAX_C);

//set up cumulative histogram for theta 
TH1F *totT;
totT = new TH1F("totT", "d. Theta", NUM_BINS_T, MIN_T, MAX_T);
totT->GetXaxis()->SetTitle("Peak Theta Bin [Radians]");
totT->GetYaxis()->SetTitle("Number of Events");

TH1F *totTU;
totTU = new TH1F("totTU", "d. Theta", NUM_BINS_T, MIN_T, MAX_T);

for (int run =1; run < 390;run++) {

      char headerName[100];
      sprintf(headerName,"/unix/anita3/anita4/flight1617/telem/root/run%d/headFile%d.root",run,run);

      char Adu5PatName[100];
      sprintf(Adu5PatName,"/unix/anita3/anita4/flight1617/telem/root/run%d/gpsEvent%d.root",run,run);

      RawAnitaHeader *hdPtr = 0;
      Adu5Pat *patPtr = 0;
      UsefulAdu5Pat *usefulPatPtr = 0;

      //check if run actually has a head file.
      bool fileStat = false;
      std::ifstream infile(headerName);
      fileStat =  infile.good();
      
      if (fileStat) {
         //headTree
         TFile *fpHead = new TFile(headerName);
         TTree *headTree = (TTree*) fpHead->Get("headTree");
         headTree->SetBranchAddress("header",&hdPtr);
     
         //Gps tree
         TFile *fpPat = new TFile(Adu5PatName);
         TTree *Adu5PatTree = (TTree*) fpPat->Get("adu5PatTree");
         Adu5PatTree->SetBranchAddress("pat",&patPtr);
                                                                                                                 Long64_t numEntries=headTree->GetEntries();                                                             
         for(Long64_t entry=0;entry<numEntries;entry++) {
      
           headTree->GetEntry(entry);  
           Adu5PatTree->GetEntry(entry);
           usefulPatPtr = new UsefulAdu5Pat(patPtr);

           Float_t imagePeak = hdPtr->getImagePeak();
           Float_t coherentSumPeak = hdPtr->getCoherentSumPeak();
           Float_t priority = hdPtr->priority&0xf;
           Double_t theta = hdPtr->getPeakThetaRad();
  
           if (strcmp(hdPtr->trigTypeAsString(),"RF") == 0) {

           tot->Fill(imagePeak,1);
           totC->Fill(coherentSumPeak,1);
           totP->Fill(priority,1);
           totT->Fill(theta,1);
         
           //if (isFinal(hdPtr)) {
           if (!isWAISPulser(usefulPatPtr,hdPtr,run) & isUHENLike(hdPtr)) {
           //cout << priority << endl;
           //cout << theta << endl;

           totU->Fill(imagePeak,1);
           totCU->Fill(coherentSumPeak,1);
           totPU->Fill(priority,1);
           totTU->Fill(theta,1);
           }
           }
        }

      }

}

mylegend = new TLegend(0.85,0.80,0.40,0.70); // create legend
mylegend->SetFillColor(0); // white background
mylegend->SetBorderSize(0); // get rid of the box
mylegend->SetTextSize(0.045); // set text size
mylegend->AddEntry(tot,"All" ,"f");
mylegend->AddEntry(totU,"CART Selected" ,"f"); // options: p,l,f
//mylegend->Draw();

//draw cummilitative histogram
ced->Divide (2,2);
ced->cd(1);
gStyle->SetPadTickY(3);
gPad->SetLogy();
gStyle->SetOptStat(0);
tot->SetFillColor(16);
tot->SetLineWidth(0);
totU->SetFillColor(46);
totU->SetFillStyle(3002);
totU->SetLineWidth(1);
totU->SetLineColor(46);
tot->Draw();
totU->Draw("same");
mylegend->Draw();

ced->cd(3);
gStyle->SetOptStat(0);
gStyle->SetPadTickY(2);
gPad->SetLogy();
totP->SetFillColor(16);
totP->SetLineWidth(0);
totPU->SetFillStyle(3003);
totPU->SetFillColor(46);
totPU->SetLineWidth(1);
totPU->SetLineColor(46);
totP->Draw();
totPU->Draw("same");


ced->cd(2);
gStyle->SetOptStat(0);
gStyle->SetPadTickY(2);
totC->SetFillColor(16);
totC->SetLineWidth(0);
totCU->SetFillColor(46);
totCU->SetLineWidth(1);
totCU->SetLineColor(46);
totCU->SetFillStyle(3002);
gPad->SetLogy();
totC->Draw();
totCU->Draw("same");

ced->cd(4);

gStyle->SetOptStat(0);
gStyle->SetPadTickY(2);
totT->SetFillColor(16);
totT->SetLineWidth(0);
totTU->SetFillColor(46);
totTU->SetLineWidth(1);
totTU->SetLineColor(46);
totTU->SetFillStyle(3002);
gPad->SetLogy();
totT->Draw();
totTU->Draw("same");


}



void UHENLikeTimeDist() {

int unixStartTime = 1480400000;
int unixEndTime = 1483100000;


//set up cumilative histgram 
TH1F *tott;
tott = new TH1F("tott", "",50000 ,unixStartTime ,unixEndTime);
tott->GetXaxis()->SetTitle("Time");
tott->GetYaxis()->SetTitle("Number of Events");

TH1F *Occ;
Occ = new TH1F("Occ", "",200, 0,850);
Occ->GetXaxis()->SetTitle("Occupancy Number");
Occ->GetYaxis()->SetTitle("Number of Bins");

double timeLDB[10000];
double distLDB[10000];

double timeWAIS[10000];
double distWAIS[10000];

for( int i=0;i<10000; i++) {

timeLDB[i] =0;
distLDB[i] =0;

timeWAIS[i] =0;
distWAIS[i]=0;

}
int posLDB = 0;
int posWAIS =0;
int count = 0;


for (int run =37; run <356;run++) {

      char headerName[100];
      sprintf(headerName,"/unix/anita3/anita4/flight1617/telem/root/run%d/headFile%d.root",run,run);

      char Adu5PatName[100];
      sprintf(Adu5PatName,"/unix/anita3/anita4/flight1617/telem/root/run%d/gpsEvent%d.root",run,run);

      RawAnitaHeader *hdPtr = 0;
      Adu5Pat *patPtr = 0;
      UsefulAdu5Pat *usefulPatPtr = 0;

      //check if run actually has a head file.
      bool fileStat = false;
      std::ifstream infile(headerName);
      fileStat =  infile.good();
      
      if (fileStat) {
         //headTree
         TFile *fpHead = new TFile(headerName);
         TTree *headTree = (TTree*) fpHead->Get("headTree");
         headTree->SetBranchAddress("header",&hdPtr);
      
         //Gps tree
         TFile *fpPat = new TFile(Adu5PatName);
         TTree *Adu5PatTree = (TTree*) fpPat->Get("adu5PatTree");
         Adu5PatTree->SetBranchAddress("pat",&patPtr);
         Long64_t numEntries=headTree->GetEntries(); 
                                                    
         for(Long64_t entry=0;entry<numEntries;entry++) {     
            headTree->GetEntry(entry);                        
            Adu5PatTree->GetEntry(entry);
            usefulPatPtr = new UsefulAdu5Pat(patPtr);
            
            Float_t imagePeak = hdPtr->getImagePeak();
            Float_t coherentSumPeak = hdPtr->getCoherentSumPeak();
            Float_t priority = hdPtr->priority&0xf;
            Double_t theta = hdPtr->getPeakThetaRad();
            int unixTime = hdPtr->payloadTime;
            double distToWAIS = usefulPatPtr->getWaisDivideTriggerTimeNs() *  0.299792 / 1000;
            double distToLDB = usefulPatPtr->getLDBTriggerTimeNs() * 0.299792 / 1000;
            //(!isNotClustered(hdPtr))

            if (isUHENLike(hdPtr) & !isWAISPulser(usefulPatPtr,hdPtr,run) & strcmp(hdPtr->trigTypeAsString(),"RF") == 0) {
               tott->Fill(unixTime,1);
            

               count++;
               if (count % 10 == 0 & distToLDB < 700) {
               timeLDB[posLDB] = unixTime;
               distLDB[posLDB] = distToLDB;
               posLDB++;              
               }
          
               
            //if (distToWAIS < 700) {
              //    count++;
                //  if (count % 20 ==0) {
                //  timeWAIS[posWAIS] = unixTime;
                 // distLDB[posWAIS] = distToWAIS;
                 // posWAIS++;
                 // }

              }
              
         }
       }
}


for (int i=0; i < 50000 -1; i++) {
  //cout << tott->GetBinContent(i+1) << endl; 
  Occ->Fill(tott->GetBinContent(i+1));
}

TCanvas* ced = new TCanvas("ced","Run Number",600,300);
ced->Draw();
Float_t small = 1e-5;
//ced->Divide(1,2,small,small);


//gStyle->SetPadBorderMode(0);
//gStyle->SetFrameBorderMode(0);
//gStyle->SetOptStat(0);
//gStyle->SetLegendBorderSize(0);

//tott->GetYaxis()->SetTitleOffset(1.5);

ced->cd(1);
//tott->SetTitle("");
//tott->GetYaxis()->SetTitle("Number of Events");
//tott->SetLineColor(9);
//tott->SetFillColor(38);
//tott->SetFillStyle(3002);
//tott->SetMarkerStyle(24);
//tott->SetMarkerSize(0.4);
//tott->GetXaxis()->SetTitle("Unix Time [s]");
//tott->GetXaxis()->SetTimeDisplay(1)
//tott->GetXaxis()->SetLabelOffset(999);
//gPad->SetBottomMargin(small);
gPad->SetLogy();
gStyle->SetOptStat(0);
//tott->Draw();
//gStyle->SetOptStat(0);
Occ->SetLineColor(9);Occ->SetFillColor(38);
Occ->SetFillStyle(3002);
Occ->Draw();

/*
TGraph* grLDB = new TGraph(10000,timeLDB,distLDB);
grLDB->SetTitle("");
grLDB->SetMarkerColor(kRed);
grLDB->GetXaxis()->SetTitle("Unix Time [s]");
grLDB->GetYaxis()->SetTitle("Distance [km]");
grLDB->GetYaxis()->SetTitleOffset(1.5);
grLDB->Draw("ap");
grLDB->GetXaxis()->SetRangeUser(unixStartTime,unixEndTime);
grLDB->GetYaxis()->SetRangeUser(0,700);
grLDB->Draw("ap");


TGraph* grWAIS = new TGraph(10000,timeWAIS,distWAIS);
grWAIS->SetMarkerColor(kBlue);
grWAIS->SetTitle("");
grWAIS->GetXaxis()->SetTitle("Unix Time [s]");
grWAIS->GetYaxis()->SetTitle("Distance [km]");
grWAIS->Draw("ap");
grWAIS->GetYaxis()->SetTitleOffset(1.5);
grWAIS->GetXaxis()->SetRangeUser(unixStartTime,unixEndTime);
grWAIS->GetYaxis()->SetRangeUser(0,700);
grWAIS->Draw("ap");


TMultiGraph *mg = new TMultiGraph();

mg->Add(grLDB);
mg->Add(grWAIS);
mg->GetXaxis()->SetTitle("Unix Time [s]");
mg->GetYaxis()->SetTitle("Distance [km]");
mg->GetYaxis()->SetTitleOffset(1.5);
//mg->GetXaxis()->SetRangeUser(unixStartTime,unixEndTime);
//mg->GetYaxis()->SetRangeUser(0,700);

ced->cd(2);
gPad->SetTopMargin(small);
gPad->SetTickx();



mg->Draw("ap");

gPad->Modified();
mg->GetXaxis()->SetRange(unixStartTime,unixEndTime);
mg->GetYaxis()->SetRange(0,700);
*/


ced->Update();
}

/*
void removeClustering() {
    int unixStartTime = 1480400000;
    int GNUM_BINS = 50;
    int NUM_BINS = 50; 
    TH1F *hist;
    hist = new TH1F("hist", "",NUM_BINS,unixStartTime ,unixEndTime);
    hist->GetXaxis()->SetTitle("Time");
    hist->GetYaxis()->SetTitle("Number of Events");

    TH1F *GeoOcc;
    GeoOcc = new TH1F("GeoOcc", "",40,1,100);
    GeoOcc->GetXaxis()->SetTitle("Occupancy Number");
    GeoOcc->GetYaxis()->SetTitle("Number of Bins");

    TH2F *GeoHist;
    GeoHist =  new TH2F("GeoHist","Lat & Lon",GNUM_BINS,-90,-65,GNUM_BINS,-180,179.9);
    
   for (int run =37; run <356;run++) {

      char headerName[100];
      sprintf(headerName,"/unix/anita3/anita4/flight1617/telem/root/run%d/headFile%d.root",run,run);

      char Adu5PatName[100];
      sprintf(Adu5PatName,"/unix/anita3/anita4/flight1617/telem/root/run%d/gpsEvent%d.root",run,run);

      RawAnitaHeader *hdPtr = 0;
      Adu5Pat *patPtr = 0;
      UsefulAdu5Pat *usefulPatPtr = 0;

      
      bool fileStat = false;
      std::ifstream infile(headerName);
      fileStat =  infile.good();

      if (fileStat) {
      
      TFile *fpHead = new TFile(headerName);
      TTree *headTree = (TTree*) fpHead->Get("headTree");
      headTree->SetBranchAddress("header",&hdPtr);

      
      TFile *fpPat = new TFile(Adu5PatName);
      TTree *Adu5PatTree = (TTree*) fpPat->Get("adu5PatTree");
      Adu5PatTree->SetBranchAddress("pat",&patPtr);
      Long64_t numEntries=headTree->GetEntries();

      for(Long64_t entry=0;entry<numEntries;entry++) {
         headTree->GetEntry(entry);
         Adu5PatTree->GetEntry(entry);
         usefulPatPtr = new UsefulAdu5Pat(patPtr);
         int unixTime = hdPtr->payloadTime;
       
         Double_t theta = hdPtr->getPeakThetaRad();
         Double_t phi = hdPtr->getPeakPhiRad();

         Double_t sourceLon,sourceLat;
         sourceLon = 0;
         sourceLat = 0;

         int solved = 0;
         if ( theta < 0) {
            solved = usefulPatPtr->getSourceLonAndLatAltZero(phi,-1*theta, sourceLon, sourceLat);
         }

         if ( solved == 0) {
            solved =usefulPatPtr->getSourceLonAndLatAltZero(phi,6.5*TMath::DegToRad(),sourceLon,sourceLat);
         }         

         if ((solved > 0 ) & isUHENLike(hdPtr) & !isWAISPulser(usefulPatPtr,hdPtr,run) & strcmp(hdPtr->trigTypeAsString(),"RF") == 0) {
            hist->Fill(unixTime,1);
            GeoHist->Fill(sourceLat,sourceLon);
            
         }

      }
           fpPat->Close();
           fpHead->Close();    
      }
           //GeoHist->Draw("CONT");

   }       
           long binbounds[NUM_BINS][2];
           double binHeights[NUM_BINS];
 
           for (int i = 1; i < NUM_BINS; i++) {
              double binHeight = hist->GetBinContent(i);
              long timeLower = hist->GetBinLowEdge(i);
              long timeUpper = hist->GetBinLowEdge(i+1);
               
              binbounds[i-1][0] = timeLower;
              binbounds[i-1][1] = timeUpper;
              
              binHeights[i-1] = binHeight;
           
    
          }
           
        //  for (int i =0; i < NUM_BINS; i++) {
        //  if ( binHeights[i] != 0) {
        //  cout << "{" << binbounds[i][0] << "," << binbounds[i][1] << "," << binHeights[i] << "}" << endl;
        //  }
        //  }


         double GeoBinBounds[GNUM_BINS][GNUM_BINS][4];
         double GeobinHeights[GNUM_BINS][GNUM_BINS];

         for (int i = 1; i < GNUM_BINS; i++) {
            for(int j =1; j < GNUM_BINS; j++) {

             double GeobinHeight = GeoHist->GetBinContent(i,j);
             double latLower = GeoHist->GetXaxis()->GetBinLowEdge(i);
             double latUpper = GeoHist->GetXaxis()->GetBinLowEdge(i+1);
             double lonLower = GeoHist->GetYaxis()->GetBinLowEdge(j);
             double lonUpper = GeoHist->GetYaxis()->GetBinLowEdge(j+1);


              

              GeoBinBounds[i-1][j-1][0] = latLower;
              GeoBinBounds[i-1][j-1][1] = latUpper;
              GeoBinBounds[i-1][j-1][2] = lonLower;
              GeoBinBounds[i-1][j-1][3] = lonUpper;

              GeobinHeights[i-1][j-1] = GeobinHeight;


          }

       }


       for (int i =0; i < GNUM_BINS; i++) {
          for(int j=0; j < GNUM_BINS; j++) {
          if ( GeobinHeights[i][j] > 0 ) {
          cout << "{" << GeoBinBounds[i][j][0] << "," << GeoBinBounds[i][j][1] << "," << GeoBinBounds[i][j][2]<< "," << GeoBinBounds[i][j][3] << "," << GeobinHeights[i][j] << "}" << endl;
      } 
      }
      }


      //not iterate over all runs again to remove clusters 
      int remainCount = 0;


      char geoDataName[100];
      sprintf(geoDataName,"EventRun16k.csv");

      ofstream GeoData;
      GeoData.open(geoDataName);

      for (int run =37; run <356;run++) {

      char headerName[100];
      sprintf(headerName,"/unix/anita3/anita4/flight1617/telem/root/run%d/headFile%d.root",run,run);

      char Adu5PatName[100];
      sprintf(Adu5PatName,"/unix/anita3/anita4/flight1617/telem/root/run%d/gpsEvent%d.root",run,run);

      RawAnitaHeader *hdPtr = 0;
      Adu5Pat *patPtr = 0;
      UsefulAdu5Pat *usefulPatPtr = 0;


      bool fileStat = false;
      std::ifstream infile(headerName);
      fileStat =  infile.good();

      if (fileStat) {

      TFile *fpHead = new TFile(headerName);
      TTree *headTree = (TTree*) fpHead->Get("headTree");
      headTree->SetBranchAddress("header",&hdPtr);


      TFile *fpPat = new TFile(Adu5PatName);
      TTree *Adu5PatTree = (TTree*) fpPat->Get("adu5PatTree");
      Adu5PatTree->SetBranchAddress("pat",&patPtr);
      Long64_t numEntries=headTree->GetEntries();

      for(Long64_t entry=0;entry<numEntries;entry++) {
         headTree->GetEntry(entry);
         Adu5PatTree->GetEntry(entry);
         usefulPatPtr = new UsefulAdu5Pat(patPtr);
         int unixTime = hdPtr->payloadTime;
         Float_t priority = hdPtr->priority&0xf;
         long eventNumber = hdPtr->eventNumber; 

         Double_t theta = hdPtr->getPeakThetaRad();
         Double_t phi = hdPtr->getPeakPhiRad();

         Double_t sourceLon,sourceLat;
         sourceLon = 0;
         sourceLat = 0;

         int solved = 0;
         if ( theta < 0) {
            solved = usefulPatPtr->getSourceLonAndLatAltZero(phi,-1*theta, sourceLon, sourceLat);
         }

         if ( solved == 0) {
            solved =usefulPatPtr->getSourceLonAndLatAltZero(phi,6.5*TMath::DegToRad(),sourceLon,sourceLat);
         }

         
          if ((solved > 0 ) & (priority < 5) & isUHENLike(hdPtr) & !isWAISPulser(usefulPatPtr,hdPtr,run) & strcmp(hdPtr->trigTypeAsString(),"RF") == 0 & (!isInBaseRegion(sourceLat,sourceLon))) {
          //if (isWAISPulser(usefulPatPtr,hdPtr,run)) {
             int timeBin = hist->GetXaxis()->FindBin(unixTime);
             int LatBin = GeoHist->GetXaxis()->FindBin(sourceLat);
             int LonBin = GeoHist->GetYaxis()->FindBin(sourceLon);
             
             GeoOcc->Fill(GeobinHeights[LatBin][LonBin]);

             if (1==1) {
                remainCount++;
                GeoData << sourceLat << "," << sourceLon << "," << eventNumber << "," << run << "," << priority << "," << theta <<"\n";  
             }
            
          }

    
     


          
        

      }
         fpPat->Close();
         fpHead->Close();
      } 
}

GeoOcc->SetLineColor(9);
GeoOcc->SetFillColor(38);
GeoOcc->SetFillStyle(3002);
GeoOcc->Draw();
GeoData.close();
cout << remainCount << endl;
}
*/
void getBaseTimes() {
    int unixStartTime = 1480400000;
    int unixEndTime = 1483100000;
    int NUM_BINS =50000;

    
    TH1F *hist;
    hist = new TH1F("hist", "",NUM_BINS,unixStartTime ,unixEndTime);
    hist->GetXaxis()->SetTitle("Time");
    hist->GetYaxis()->SetTitle("Number of Events");



   for (int run =37; run <356;run++) {

      char headerName[100];
      sprintf(headerName,"/unix/anita3/anita4/flight1617/telem/root/run%d/headFile%d.root",run,run);

      char Adu5PatName[100];
      sprintf(Adu5PatName,"/unix/anita3/anita4/flight1617/telem/root/run%d/gpsEvent%d.root",run,run);

      RawAnitaHeader *hdPtr = 0;
      Adu5Pat *patPtr = 0;
      UsefulAdu5Pat *usefulPatPtr = 0;

   
      bool fileStat = false;
      std::ifstream infile(headerName);
      fileStat =  infile.good();
      
      if (fileStat) {
   
      TFile *fpHead = new TFile(headerName);
      TTree *headTree = (TTree*) fpHead->Get("headTree");
      headTree->SetBranchAddress("header",&hdPtr);
     
     
      TFile *fpPat = new TFile(Adu5PatName);
      TTree *Adu5PatTree = (TTree*) fpPat->Get("adu5PatTree");
      Adu5PatTree->SetBranchAddress("pat",&patPtr);
      Long64_t numEntries=headTree->GetEntries();
     
      for(Long64_t entry=0;entry<numEntries;entry++) {
         headTree->GetEntry(entry);
         Adu5PatTree->GetEntry(entry);
         usefulPatPtr = new UsefulAdu5Pat(patPtr);         
         int unixTime = hdPtr->payloadTime;
        
         if (isUHENLike(hdPtr) & !isWAISPulser(usefulPatPtr,hdPtr,run) & strcmp(hdPtr->trigTypeAsString(),"RF") == 0) {
            hist->Fill(unixTime,1);
            
         }

      }

      
      fpPat->Close();
      fpHead->Close();
    }

}

   int CRIT_BIN_HEIGHT = 25;
   bool duringBaseTime = false;
   int counter = 0;
   int baseCounter = 0;


   long baseTimes[1000];

   for(int i =0; i < 1000; i++) {
      baseTimes[i] = 0;
   }


   
   for(int i=1; i < NUM_BINS; i++) {
      double binHeight = hist->GetBinContent(i);
      long time = hist->GetBinLowEdge(i);
      cout << binHeight << " , " << time << endl;
      if ( (binHeight > CRIT_BIN_HEIGHT) & (!duringBaseTime)) {
         baseCounter++;
         duringBaseTime = true;
         baseTimes[counter] = time;
         counter++;
      } 
     
      if ( (binHeight < CRIT_BIN_HEIGHT) & (duringBaseTime)) {
         duringBaseTime = false;
         baseTimes[counter] = time;
         counter++;
      }
       
   }


   cout << "The Number of Bases detected is: " << baseCounter << endl;

   //cout << "Base time periods are: " << endl;
   
   cout << "{";

   for (int i = 0; i < 1000; i++) {
     cout << baseTimes[i] << ",";
   }   
   
   cout << "}";

}


void countUhenLike() {

int uhenCount =0;
int totalCount =0;

//iterate over all runs
for(int run = 0;run <400; run++) {

char headerName[100];
sprintf(headerName,"/unix/anita3/anita4/flight1617/telem/root/run%d/headFile%d.root",run,run);

char Adu5PatName[100];
sprintf(Adu5PatName,"/unix/anita3/anita4/flight1617/telem/root/run%d/gpsEvent%d.root",run,run);

RawAnitaHeader *hdPtr = 0;
Adu5Pat *patPtr = 0;
UsefulAdu5Pat *usefulPatPtr = 0;

//check if run actually has a head file.
bool fileStat = false;
std::ifstream infile(headerName);
fileStat =  infile.good();

if (fileStat) {

//Gps tree
TFile *fpPat = new TFile(Adu5PatName);
TTree *Adu5PatTree = (TTree*) fpPat->Get("adu5PatTree");
Adu5PatTree->SetBranchAddress("pat",&patPtr);


//Head tree
TFile *fpHead = new TFile(headerName);
TTree *headTree = (TTree*) fpHead->Get("headTree");
headTree->SetBranchAddress("header",&hdPtr);


Long64_t numEntries=headTree->GetEntries();


for(Long64_t entry=0;entry<numEntries;entry++) {
   headTree->GetEntry(entry);
   Adu5PatTree->GetEntry(entry);
 
   usefulPatPtr = new UsefulAdu5Pat(patPtr);
   Float_t priority = hdPtr->priority&0xf;
   
   if (strcmp(hdPtr->trigTypeAsString(),"RF") == 0) {
   totalCount++;
   }

   if ((strcmp(hdPtr->trigTypeAsString(),"RF") == 0) & (isUHENLike(hdPtr)) & (!isWAISPulser(usefulPatPtr,hdPtr, run)) & (isNotClustered(hdPtr))) {
       uhenCount++;
   }

}

fpPat->Close();
fpHead->Close();
}
}
cout << "Number of UHEN like events " << uhenCount << endl;
cout << "totalNumber of events " << totalCount << endl;

}


