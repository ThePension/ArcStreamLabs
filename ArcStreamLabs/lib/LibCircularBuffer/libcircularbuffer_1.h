#pragma once
#include <mutex>
#include <memory> // for unique_ptr
#include <opencv2/opencv.hpp>

class CircularBuffer
{
private:

    std::unique_ptr<cv::Mat[]> buffer;
    int head;
    int tail;
    std::mutex mutex;
    int maxSize;
    bool isFull;

public:

    CircularBuffer(int maxSize);
    void put(cv::Mat);
    bool empty();
    bool full();
    cv::Mat read();
    void reset();
    int getCurrentSize();
    int getMaxSize();
    int getHead();
    int getTail();
};

