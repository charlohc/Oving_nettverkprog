#include <iostream>
using namespace std;
class MyClass {
    pthread_mutex_t  mutex;
    int mails;

    void* routine() {
        for (int i = 0; i < 10; i++) {
            pthread_mutex_lock(&mutex);
            mails++;
            pthread_mutex_unlock(&mutex);
        }
    }

public:
    int createThreads(int threadNum) {
        pthread_t th[threadNum];
        pthread_mutex_init(&mutex, NULL);
        for (int i = 0; i < threadNum; ++i) {
            if (pthread_create(th + i, NULL, &MyClass::routine, NULL)!= 0) {
                perror("failed to create thread");
                return 1;
            }
            printf("thread %d has started\n", i);
            if (pthread_join(th[i], NULL) != 0) {
                return 2;
            }
            printf("Thread %d has finished\n", i);
        }
        pthread_mutex_destroy(&mutex);
        printf("number of mails: %d\n", mails);
    }
};
    int main() {
        std::cout << "Prime number finder!" << std::endl;
        int startNum, endNum, threadNum;
        cout << "Type in the start number of the interval: "; // Type a number and press enter
        cin >> startNum; // Get user input from the keyboard
        cout << "Type in the end number of the interval: ";
        cin >> endNum;
        cout << "Type in the number of threads: ";
        cin >> threadNum;

        MyClass obj;
        obj.createThreads(threadNum);
        return 0;
    }
