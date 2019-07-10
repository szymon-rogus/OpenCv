#ifndef OBJECT_DETECTION_VIDEO_HPP
#define OBJECT_DETECTION_VIDEO_HPP

#include "My_Exeption.hpp"
#include "Colors.hpp"

using namespace cv;

class Video{
private:
    string video_name;
    VideoCapture video;

public:
    /// constructor of Video cannot be default
    Video() = delete;
    explicit Video(string &fileName);
    /// destructor
    virtual ~Video();

    /// getters and setters
    const string &getVideoName() const;
    void setVideoName(const string &videoName);
    const VideoCapture &getVideo() const;

    /// some useful methods
    void show_canny_edges();
    void show_as_hsv();
    void show_gray();
    void show_with_swaped_colors(string Color, const string &new_color);
};

#endif //OBJECT_DETECTION_VIDEO_HPP