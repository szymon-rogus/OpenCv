#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <unistd.h>
#include "Video.hpp"

Video::Video(string &fileName) : video_name(fileName) {
    video.open(video_name);
    if(!video.isOpened()){
        My_Exeption ex = My_Exeption("Unknown video!");
        ex.throw_it();
    }
}

Video::~Video() {
    this -> video.release();
}

/// now a few setters and getters, just pass it by :)
const string &Video::getVideoName() const {
    return video_name;
}

void Video::setVideoName(const string &videoName) {
    video_name = videoName;
    video.open(video_name);
    if(!video.isOpened()){
        My_Exeption ex = My_Exeption("Unknown video!");
        ex.throw_it();
    }
}

const VideoCapture &Video::getVideo() const {
    return video;
}

/// useful methods

void Video::show_canny_edges() {
    Mat edges;
    namedWindow("edges",WINDOW_AUTOSIZE);

    while(this -> video.isOpened()){
        Mat frame;
        /// get new frame from camera
        this->video >> frame;
        /// check if its loaded correctly
        if(!frame.empty()){
            cvtColor(frame, edges, COLOR_BGR2GRAY);
            GaussianBlur(edges, edges, Size(7,7), 2, 2);
            Canny(edges, edges, 0, 30, 3);
            imshow("edges", edges);
            if(waitKey(50) >= 0) break;
        }
        if(waitKey(50) >= 0) break;
    }
}

void Video::show_gray() {
    Mat edges;
    namedWindow("edges",WINDOW_AUTOSIZE);

    while(this -> video.isOpened()){
        Mat frame;
        /// get new frame from camera
        this->video >> frame;

        /// check if its loaded correctly
        if(!frame.empty()){
            cvtColor(frame, edges, COLOR_BGR2GRAY);
            imshow("edges", edges);
            if(waitKey(50) >= 0) break;
        }
        if(waitKey(50) >= 0) break;
    }
}

void Video::show_with_swaped_colors(string old_color, const string &new_color) {
    namedWindow("edges",WINDOW_AUTOSIZE);

    while(this -> video.isOpened()){
        Mat frame;
        /// get new frame from camera
        this->video >> frame;

        /// check if its loaded correctly
        if(!frame.empty()){
            Mat edges, edges_new;
            int* scale;

            cvtColor(frame, edges, COLOR_BGR2HSV);
            cvtColor(frame, edges_new, COLOR_BGR2HSV);

            transform(old_color.begin(), old_color.end(), old_color.begin(), ::tolower);
            scale = convert_string_to_enum(old_color);

            inRange(edges, Scalar(scale[0], 50, 50), Scalar(scale[1], 255, 255), edges_new);
            edges.setTo(Scalar(get_new_color(new_color), 255, 255), edges_new);

            cvtColor(edges, edges, COLOR_HSV2BGR);

            usleep(1000);
            imshow("edges", edges);
            delete [] scale;
            if(waitKey(50) >= 0) break;
        }
        if(waitKey(50) >= 0) break;
    }
}

void Video::show_as_hsv() {
    Mat edges;
    namedWindow("edges",WINDOW_AUTOSIZE);

    while(this -> video.isOpened()){
        Mat frame;

        /// get new frame from camera
        this->video >> frame;
        /// check if its loaded correctly
        if(!frame.empty()){
            cvtColor(frame, edges, COLOR_BGR2HSV);
            imshow("edges", edges);
            if(waitKey(50) >= 0) break;
        }
        if(waitKey(50) >= 0) break;
    }
}