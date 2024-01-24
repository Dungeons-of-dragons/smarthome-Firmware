#ifndef ACS_H
#define ACS_H 

static const long intervolt = 8000;
static int mVperAmp = 185;           // this the 5A version of the ACS712 -use 100 for 20A Module and 66 for 30A Module
static int Watt = 0;
static double Voltage = 0;
static double VRMS = 0;
static double AmpsRMS = 0;

double getWatts();
double getAmps();
float readvoltage();


#endif