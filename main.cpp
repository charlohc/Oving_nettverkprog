#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <algorithm>

//TODO: dårlig fordeling av tall, burde fordelt slik at alle fikk et av laveste tallene så et mer osv..

using namespace std;

bool isPrime(int);
int workload(int,int,int);

void foo(int start, int end, vector<int>*primes, mutex *prime_mutex) {

    for (int j = start; j <= end; j++) {

            if(isPrime(j)) {
                prime_mutex->lock();
                primes->push_back(j);
                prime_mutex->unlock();
            }
        }
    }


    bool isPrime(int n) {
        if (n == 0 || n == 1) {
            return false;
        }
        if (n == 2) {
            return true;
        }
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    }

    void createThreads(int startNum, int endNum, int threadNum, int workPerThread)  {
        vector<thread> threads(threadNum);
        vector<int> primes;
        mutex prime_mutex;

        for (int i = 1; i <= threadNum; i++) {
            //cout << "start " << startNum << endl;
            //cout << "end " << endNum << endl;
            threads.emplace_back(foo, startNum, endNum, &primes, &prime_mutex);
            startNum = (startNum + workPerThread);
            endNum = (endNum + workPerThread);

        }

        for(auto& th : threads){
            if (th.joinable())
            th.join();
        }

        vector<int>::iterator it;
        it = unique(primes.begin(), primes.end());

        primes.resize(distance(primes.begin(),it));
        sort(primes.begin(), primes.end());

        for (int prime : primes) {
            cout << prime << ", ";
        }

        cout << endl;
    }



    int workload(int startNumber, int endNumber, int threadNumber) {
        int  workPerThread = (endNumber - startNumber) / threadNumber;
        return workPerThread;
    }


int main() {
        std::cout << "Prime number finder!" << std::endl;
        int startNum, endNum, threadNum;
        cout << "Type in the start number of the interval: ";
        cin >> startNum;
        cout << "Type in the end number of the interval: ";
        cin >> endNum;
        cout << "Type in the number of threads: ";
        cin >> threadNum;

        int workPerThread = workload(startNum, endNum, threadNum);

    createThreads(startNum,(startNum + workPerThread),threadNum, workPerThread);
        return 0;
    }
