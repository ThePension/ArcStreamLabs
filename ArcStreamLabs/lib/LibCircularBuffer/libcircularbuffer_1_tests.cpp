#include <gtest/gtest.h>
// LOCAL INCLUDES
#include "LibCircularBuffer/libcircularbuffer_1.h"

using namespace ArcStreamLabs::LibCircularBuffer;

TEST(LibCircularBuffer, CircularBuffer)
{
    CircularBuffer cb(10);

    EXPECT_EQ(cb.empty(), true);
    EXPECT_EQ(cb.getHead(), 0);
    EXPECT_EQ(cb.getTail(), 0);
    EXPECT_EQ(cb.getMaxSize(), 10);
    EXPECT_EQ(cb.getCurrentSize(), 0);
}

TEST(LibCircularBuffer, put)
{
    CircularBuffer cb(10);

    cv::Mat mat;
    cb.put(mat);

    EXPECT_EQ(cb.empty(), false);
    EXPECT_EQ(cb.getHead(), 1);
    EXPECT_EQ(cb.getTail(), 0);
    EXPECT_EQ(cb.getMaxSize(), 10);
    EXPECT_EQ(cb.getCurrentSize(), 1);
}

TEST(LibCircularBuffer, read)
{
    CircularBuffer cb(10);
    cv::Mat emptyMat;
    cv::Mat readMat = cb.read();
    bool isEqual = (emptyMat.cols == readMat.cols && emptyMat.rows == readMat.rows && emptyMat.dims == readMat.dims);

    EXPECT_EQ(isEqual, true);


    cv::Mat initialMat(12, 6, 5);
    cb.put(initialMat);

    readMat = cb.read();
    isEqual = (initialMat.cols == readMat.cols && initialMat.rows == readMat.rows && initialMat.dims == readMat.dims);

    EXPECT_EQ(isEqual, true);
}

TEST(LibCircularBuffer, reset)
{
    CircularBuffer cb(10);

    cv::Mat mat;
    cb.put(mat);
    cb.reset();

    EXPECT_EQ(cb.empty(), true);
    EXPECT_EQ(cb.getHead(), 0);
    EXPECT_EQ(cb.getTail(), 0);
    EXPECT_EQ(cb.getCurrentSize(), 0);
}
