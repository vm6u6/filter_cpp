# include "filter.h"

void general_filter::ghost_filter(Mat &img){
    //偏移量两两配合，分别是左下，左上，右上，右下
    int OffsetJ[4] = { 4, -4, -4, 4 };
    int OffsetI[4] = { -4, -4, 4, 4 };

    int sumB,sumG,sumR;
    for(int j = 0;j<img.rows;j++){
        for(int i = 0;i<img.cols;i++){
            sumB = 0;sumG = 0;sumR = 0;
            for(int k = 0;k<4;k++){
                int JJ = j + OffsetJ[k];
                int II = i + OffsetI[k];

                //防止越界
                if(JJ < 0){
                    JJ = 0;
                }else if(JJ >= img.rows){
                    JJ = img.rows - 1;
                }
                if(II < 0){
                    II = 0;
                }else if(II >= img.cols){
                    II = img.cols - 1;
                }

                //累加，求当前像素点的左下，左上，右上，右下四个偏移量的和
                sumB += img.at<Vec3b>(JJ,II)[0];
                sumG += img.at<Vec3b>(JJ,II)[1];
                sumR += img.at<Vec3b>(JJ,II)[2];
            }
            //求平均值，求平均值(sum+2)/4,
            //为什么要+2，就为了四舍五入。比如如果计算结果为108.6，则取像素109更为合理     
            img.at<Vec3b>(j,i)[2] = (sumR+2)>>2;
            img.at<Vec3b>(j,i)[1] = (sumG+2)>>2;
            img.at<Vec3b>(j,i)[0] = (sumB+2)>>2;
         }
    }
    imshow("重影濾鏡",img);
    waitKey();
}

void general_filter::dark_img(Mat &srcImage){
    int rowNum = srcImage.rows;
    int colNum = srcImage.cols * srcImage.channels();

    for(int j = 0;j<rowNum;j++){
        uchar* row = srcImage.ptr<uchar>(j);
        for(int i = 0;i<colNum;i++){
            row[i] = row[i] * row[i] >>8;
        }
    }
    imshow("暗調濾鏡",srcImage);
    waitKey();
}

void general_filter::nice_skin(Mat &srcImage){
    int value = 40;
    Mat new_img;
    bilateralFilter(srcImage, new_img, value, value * 2, value / 2);
    cout << "[INFO] 美顏成功！" << endl;

    imshow("美顏濾鏡", new_img);
    waitKey();
}
