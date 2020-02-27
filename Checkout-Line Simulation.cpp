#include <iostream>
#include <queue>
#include <fstream>
#include <ctime>
#include <stdlib.h>
#include <iomanip>
using namespace std;

struct customer {
    int time;
    int arrival;
    int leave;
} ;

bool randomChance(double prob) {
    double rv = rand() / (double(RAND_MAX) + 1);
    return (rv < prob);
}

int randomInt(int min, int max) {
    return (rand() % (max - min) + min);
}    double ArrivRate;



void initialize(int &simtime, double &ArrivRate, int &MinServeTime,int &MaxServeTime, int &MaxLineSize,int &IrateCustomerThreshold, int &ServeTime,       //initializes all of the variables at the beginning of the while loop
                int &ServingTime, int &CustomerServed, int &CustomerLeave, int &TotalServeTime, int &irate, int &TotalWaitTime, float &AveServeTime,
                float &AveWaitTime, int &QueueSize, bool &CashierOccupied,int timeper)
        {
        simtime = 0;
        ArrivRate = 0;
        MinServeTime = 0;
        MaxServeTime = 0;
        MaxLineSize = 0;
        IrateCustomerThreshold = 0;
        ServeTime = 0;
        ServingTime = 0;
        CustomerServed = 0;
        CustomerLeave = 0;
        TotalServeTime = 0;
        irate = 0;
        TotalWaitTime = 0;
        AveServeTime = 0;
        AveWaitTime = 0;
        CashierOccupied = false;
        QueueSize = 0;
        timeper = 0;
        }
int main() {
    srand(time(0));
    ifstream myfile;
    myfile.open("simulation-2.txt");
    double ArrivRate;
    int irate, simtime, MinServeTime, MaxServeTime, MaxLineSize,
        ServeTime,ServingTime,CustomerServed, CustomerLeave,
        TotalServeTime,TotalWaitTime, OverallTime, QueueSize, timeper,
        IrateCustomerThreshold;
    float AveQSize, AveServeTime,AveWaitTime;
    bool CustomerArrive, CashierOccupied;
    customer cust;
    queue<customer> CashierQ;
    if(myfile.eof()){
    return 1;
        }
    while(myfile){
        while(!myfile.eof()){
        initialize(simtime, ArrivRate, MinServeTime,MaxServeTime,MaxLineSize,IrateCustomerThreshold,ServeTime,
                ServingTime, CustomerServed,CustomerLeave, TotalServeTime,irate,TotalWaitTime,AveServeTime,
                AveWaitTime,QueueSize, CashierOccupied, timeper);
        CustomerArrive;
        myfile >> simtime >> ArrivRate >> MinServeTime >> MaxServeTime >> MaxLineSize >> IrateCustomerThreshold;
        OverallTime = simtime;
        while(simtime--){
            CustomerArrive = randomChance(ArrivRate);

            if(CashierOccupied){
              TotalServeTime ++;
              ServingTime--;
            }

            if(ServingTime == 0){
                CashierOccupied = false;
            }
            if(CustomerArrive && CashierQ.size() < MaxLineSize){  //adds someone to the queue
                ServeTime = randomInt(MinServeTime, MaxServeTime);
                cust.arrival = simtime;
                cust.time = ServeTime;
                CashierQ.push(cust);
            }else if(CustomerArrive && CashierQ.size() >= MaxLineSize){
                CustomerLeave++;
            }
            if(!CashierQ.empty() && !CashierOccupied){
                ServingTime = CashierQ.front().time;
                CashierOccupied = true;
                CashierQ.front().leave = simtime;
                timeper = (CashierQ.front().arrival - CashierQ.front().leave);
                TotalWaitTime = TotalWaitTime +  (CashierQ.front().arrival - CashierQ.front().leave);
                if(timeper > IrateCustomerThreshold){ //if the the total wait time for each cx is longer than the irate thres hold
                    irate++;                          // it will make the customer irate. This if loop is also makes sure that the customer
                }                                     // does not leave
                CashierQ.pop();
                CustomerServed ++;
            }
            QueueSize += CashierQ.size();

            if(simtime == 0) { //calculates the averages and outputs results of simulation
                AveServeTime = (float)(TotalServeTime) / (float)CustomerServed;
                AveWaitTime = (float)(TotalWaitTime) / (float)(CustomerServed);
                AveQSize = (float)(QueueSize) / (float)(OverallTime);

                cout << "Simulation Results" << "\n"
                     << "------------------" << "\n"
                     << "Simulation Time: " << OverallTime <<"\n"
                     << "Arrival rate: " << ArrivRate << "\n"
                     << "Minimum service time: " << MinServeTime << "\n"
                     << "Maximum service time: " << MaxServeTime << "\n"
                     << "Maximum line size " << MaxLineSize << "\n"
                     << "Average Serve Time " << fixed << setprecision(2) << AveServeTime << "\n"
                     << "\n"
                     << "Customers serviced: " << CustomerServed << "\n"
                     << "Customers leaving: " << CustomerLeave << "\n"
                     << "Average time spent in line: " << AveWaitTime <<"\n"
                     << "Average line length: " << AveQSize << "\n"
                     << "Irate Customers: " << irate
                     << "\n";
                while(CashierQ.size()){
                    CashierQ.pop();
                }
            }

        }
        }
    }
    myfile.close(); //myfile.close
    return 0;
}
