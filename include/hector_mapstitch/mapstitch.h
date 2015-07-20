#ifndef MAPSTITCH_H
#define MAPSTITCH_H

#include <stdio.h>
#include <math.h>
#include <opencv/cv.h>

using namespace cv;
using namespace std;

class StitchedMap
{
public:
  StitchedMap(Mat &im1, Mat &im2, float max_distance=5.);
  ~StitchedMap();

  Mat get_debug();
  Mat get_stitch();

  void printDebugOutput();
  bool isValid();

  Mat getTransformForThreePoints(const vector<DMatch>& matches,
                                 const vector<KeyPoint>& dest,
                                 const vector<KeyPoint>& input,
                                 const vector<int>& indices);

  bool isScaleValid(const cv::Mat& rigid_transform, double threshold_epsilon);

  Mat estimateHomographyRansac(const vector<DMatch>& matches,
                               const vector<KeyPoint>& dest,
                               const vector<KeyPoint>& input);


  Mat H; // transformation matrix
  double rot_deg,rot_rad,transx,transy,scalex,scaley;

protected:

  Mat image1, image2,
      dscv1_q, dscv2_t;
  bool is_valid;

  vector<KeyPoint> kpv1_q,kpv2_t;

  std::vector<cv::Point2f> input_inliers;
  std::vector<cv::Point2f> dest_inliers;

  vector<DMatch>   matches;
  vector<DMatch>   matches_robust;
  vector<DMatch>   matches_filtered;

};

#endif // MAPSTITCH_H