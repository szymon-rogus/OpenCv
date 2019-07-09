#ifndef OBJECT_DETECTION_PICTURE_HPP
#define OBJECT_DETECTION_PICTURE_HPP

#include "My_Exeption.hpp"
#include "Colors.hpp"

using namespace cv;

/// Picture class with image and name of its source
class Picture{
private:
    string file_name;
    Mat image;

    /// private function used only in detecting squares
    static double angle( Point &pt1, Point &pt2, Point &pt0 ) {
        double dx1 = pt1.x - pt0.x;
        double dy1 = pt1.y - pt0.y;
        double dx2 = pt2.x - pt0.x;
        double dy2 = pt2.y - pt0.y;
        return (dx1 * dx2 + dy1 * dy2) / sqrt((dx1 * dx1 + dy1 * dy1) * (dx2 * dx2 + dy2 * dy2) + 1e-10);
    }

public:
    /// constructor of Picture cannot be default
    Picture() = delete;
    explicit Picture(const string &fileName);
    /// destructor
    virtual ~Picture();

    /// getters and setters
    const string &getFileName() const;
    void setFileName(const string &fileName);
    const Mat &getImage() const;

    /// some methods that operates on color or shape
    const void show_original() const;
    void change_color(string old_color, string &new_color);
    void draw_every_color();
    void change_size( double how_much);
    void edge_detection();
    void circle_detection();
    void square_detection();
    void triangles_detection();
};

#endif //OBJECT_DETECTION_PICTURE_HPP