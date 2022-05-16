#include "helper.h"

using namespace cv;

Helper::Helper() { }

QPixmap Helper::cvMatToQPixmap(const cv::Mat &inMat)
{
    return QPixmap::fromImage(cvMatToQImage(inMat));
}

QImage Helper::cvMatToQImage(const cv::Mat &inMat)
{
    switch (inMat.type())
    {
    // 8-bit, 4 channel
    case CV_8UC4:
    {
        QImage image(inMat.data,
                     inMat.cols, inMat.rows,
                     static_cast<int>(inMat.step),
                     QImage::Format_ARGB32);

        return image;
    }

        // 8-bit, 3 channel
    case CV_8UC3:
    {
        QImage image(inMat.data,
                     inMat.cols, inMat.rows,
                     static_cast<int>(inMat.step),
                     QImage::Format_RGB888);

        return image.rgbSwapped();
    }

        // 8-bit, 1 channel
    case CV_8UC1:
    {
        QImage image(inMat.data,
                     inMat.cols, inMat.rows,
                     static_cast<int>(inMat.step),
                     QImage::Format_Grayscale8);

        return image;
    }

    default:
        qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
        break;
    }

    return QImage();
}

Mat Helper::transformMatWithKernel(Mat src, Mat_<float> kernel)
{
    Mat dst;
    // Apply filter
    transform(src, dst, kernel);

    return dst;
}

Mat Helper::transformMatWithKernel(Mat src,
                                            float x0y0, float x1y0, float x2y0,
                                            float x0y1, float x1y1, float x2y1,
                                            float x0y2, float x1y2, float x2y2)
{
    Mat dst;
    Mat kernel = (Mat_<float>(3, 3)
                      << x0y0, x1y0, x2y0,
                  x0y1, x1y1, x2y1,
                  x0y2, x1y2, x2y2);

    // Apply filter
    transform(src, dst, kernel);

    return dst;
}

Mat Helper::loadMatFromQrc(QString qrc, int flag)
{
    QFile file(qrc);
    cv::Mat mat;
    if(file.open(QIODevice::ReadOnly))
    {
        qint64 sz = file.size();
        std::vector<uchar> buf(sz);
        file.read((char*)buf.data(), sz);
        mat = cv::imdecode(buf, flag);
    }

    return mat;
}

bool Helper::doesFolderExists(std::string folderPath)
{
    if ( access( folderPath.c_str(), 0 ) == 0 )
       {
          struct stat status;
          stat( folderPath.c_str(), &status );

          if ( status.st_mode & S_IFDIR )
          {
              return true;
          }
          else
          {
              return false;
          }
       }

    return false;
}


