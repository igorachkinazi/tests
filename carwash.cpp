// carwash.cpp
// what is the average waiting time in queue for averages 
#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>

struct Car {
  int arrivalTime;
  int serviceTime;
};

const int simulationTime = 600; // Total simulation time, minutes
const int arrivalRate = 10; // Average time between arrivals, minutes
const int serviceRate = 15; // Average service time, minutes

using namespace std;

int main() {
   queue<Car> carwashQueue;
   int currentTime = 0;
   int totalWaitTime = 0;
   int numCarsWashed = 0;

   srand(std::time(0)); 

   while (currentTime < simulationTime) {
      // Simulate car arrival
      if (rand() % arrivalRate == 0) {
          Car newCar;
          newCar.arrivalTime = currentTime;
          newCar.serviceTime = rand() % serviceRate + 1;
          carwashQueue.push(newCar);
      }

      // Simulate car departure
      if (!carwashQueue.empty()) {
         Car &firstCar = carwashQueue.front();
         if (currentTime - firstCar.arrivalTime >= firstCar.serviceTime) {
            totalWaitTime += currentTime - firstCar.arrivalTime;
            carwashQueue.pop();
            numCarsWashed++;
         }
      }

      currentTime++;
   }

   double averageWaitTime = static_cast<double>(totalWaitTime) / numCarsWashed;
   cout << numCarsWashed << " cars washed" << endl;
   cout << "Average wait time for cars: " << averageWaitTime << " minutes." << endl;

   return 0;
}

