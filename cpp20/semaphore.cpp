// https://en.cppreference.com/w/cpp/thread/counting_semaphore
#include <random>
#include <chrono>
#include <iostream>

#include <semaphore>
#include <thread>


// global binary semaphore instances
// object counts are set to zero
// objects are in non-signaled state
std::binary_semaphore
    smphSignalMainToThread{0},
    smphSignalThreadToMain{0};

void ThreadProc()
{
    // wait for a signal from the main proc
    // by attempting to decrement the semaphore
    smphSignalMainToThread.acquire();

    // this call blocks until the semaphore's count
    // is increased from the main proc

    std::cout << "[thread] Got the signal\n"; // response message

    // simulate work
    std::random_device r;
    std::default_random_engine reng(r());
    std::uniform_int_distribution<int> uniform_dist(1, 500);
    int milliseconds = uniform_dist(reng);
    std::cout << "Thread sleeping for " << milliseconds << " milliseconds.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));


    std::cout << "[thread] Send the signal\n"; // message

    // signal the main proc back
    smphSignalThreadToMain.release();
}

int main()
{
    // create some worker thread
    std::thread thrWorker(ThreadProc);

    std::cout << "[main] Send the signal\n"; // message

    // signal the worker thread to start working
    // by increasing the semaphore's count
    smphSignalMainToThread.release();

    // wait until the worker thread is done doing the work
    // by attempting to decrement the semaphore's count
    smphSignalThreadToMain.acquire();

    std::cout << "[main] Got the signal\n"; // response message
    thrWorker.join();
}
