
extern int ImageAvgStdDev(Image *I,float *RedAvg, float *GreenAvg,float *BlueAvg,float *RedStd, float *GreenStd, float *BlueStd);
/* This function takes an Input Image I and computes the Average and standard deviation for Red,Green,Blue. */

extern float sq(float x);
/* A convenience function that squares a double */

extern int ThresholdImage(Image *In,float RedAvg,float GreenAvg,float BlueAvg,float RedStd,float GreenStd,float BlueStd,int ThresholdValue,Image *Out);
/* Takes in an image and RGB average and standard deviation, a threshold value, and it returns the thresholded image */

extern int RemoveBackground(Image *thresholded_image) ;
/* Takes a thresholeded image (binary) and removes the largest contiguous blob of pixels. */
