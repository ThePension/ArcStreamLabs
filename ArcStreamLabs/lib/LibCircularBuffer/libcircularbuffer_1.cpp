// STD
#include <iostream>
// LOCAL INCLUDES
#include "LibCircularBuffer/libcircularbuffer_1.h"

namespace ArcStreamLabs
{
    namespace LibCircularBuffer{
        CircularBuffer::CircularBuffer(int maxSize)
        {
            this->maxSize = maxSize;
            this->buffer = std::unique_ptr<cv::Mat[]>(new cv::Mat[maxSize]);
            this->isFull = false;
            this->head = 0;
            this->tail = 0;
        }

        void CircularBuffer::put(cv::Mat data){
            std::lock_guard<std::mutex> lock(this->mutex);

            this->buffer[this->head] = data;

            if(this->isFull) this->tail = (this->tail + 1) % this->maxSize;

            this->head = (this->head + 1) % this->maxSize;

            this->isFull = this->head == this->tail;
        }

        bool CircularBuffer::empty(){
            if(isFull) return false;
            else return this->head == this->tail;
        }

        bool CircularBuffer::full(){
            return this->isFull;
        }

        cv::Mat CircularBuffer::read(){
            std::lock_guard<std::mutex> lock(this->mutex);

            if(empty()) return cv::Mat();

            cv::Mat data = this->buffer[this->tail];
            this->isFull = false;
            this->tail = (this->tail + 1) % this->maxSize;

            return data;
        }

        void CircularBuffer::reset(){
            std::lock_guard<std::mutex> lock(this->mutex);
            this->head = this->tail;
            this->isFull = false;
        }

        int CircularBuffer::getCurrentSize(){
            if(this->isFull) return this->maxSize;
            int size = (this->head - this->tail);
            return (size >= 0 ? size : -size); // absolute value
        }

        int CircularBuffer::getMaxSize(){
            return this->maxSize;
        }

        int CircularBuffer::getHead(){
            return this->head;
        }

        int CircularBuffer::getTail(){
            return this->tail;
        }
    }
}
