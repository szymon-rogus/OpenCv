#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "Picture.hpp"

Picture::Picture(const string &fileName) : file_name(fileName) {
    image = imread(fileName);
    if(!image.data){
        My_Exeption ex = My_Exeption("Unknown picture!");
        ex.throw_it();
    }
}

Picture::~Picture() {
    this -> image.release();
}

/// now a few setters and getters, just pass it by :)
const string &Picture::getFileName() const {
    return file_name;
}

void Picture::setFileName(const string &fileName) {
    file_name = fileName;
    this -> image = imread(fileName);

    if(!image.data){
        My_Exeption ex = My_Exeption("Unknown picture!");
        ex.throw_it();
    }
}

const Mat &Picture::getImage() const {
    return image;
}

/// useful methods

const void Picture::show_original() const {
    /// show original picture
    namedWindow("Original", WINDOW_AUTOSIZE);
    imshow("Original", this -> image);
    waitKey();
}

/// change color from old to new one
void Picture::change_color(string old_color, string &new_color) {
    string window = old_color + " changed to " + new_color;

    namedWindow(window, WINDOW_AUTOSIZE);

    Mat colorDetection, new_image;

    cvtColor(this -> image, colorDetection, COLOR_BGR2HSV);
    cvtColor(this -> image, new_image, COLOR_BGR2HSV);
    Scale scale;

    /// no matter if color name was written with CAPS LOCK or not
    transform(old_color.begin(), old_color.end(), old_color.begin(), ::tolower);
    scale = convert_string_to_enum(old_color);

    /// detecting old color and settting it all to new one
    inRange(colorDetection, Scalar(scale.min_h, 50, 50), Scalar(scale.max_h, 255, 255), colorDetection);
    new_image.setTo(Scalar(get_new_color(new_color), 255, 255), colorDetection);

    cvtColor(new_image, new_image, COLOR_HSV2BGR);
    imshow(window, new_image);
    waitKey();
}

/// animate every color appearance on the image
void Picture::draw_every_color() {
    string window = "draw";
    string final = "final";
    namedWindow(window, WINDOW_AUTOSIZE);

    Mat new_image[181], picture[181], sum;
    int k = 0;

    /// extract every single hue values of HSV model from 0 to 179
    for(int i = 0; i < 180; i += 1){
        k = i;

        /// a few magic lines which extract every hue and dispaly it on the image
        cvtColor(this -> image, new_image[k], COLOR_BGR2HSV);
        cvtColor(this -> image, picture[k], COLOR_BGR2HSV);
        inRange(new_image[k], Scalar(i, 0, 0), Scalar(i + 2, 255, 255), new_image[k]);
        picture[k].setTo(Scalar(i, 255, 255), new_image[k]);
        cvtColor(picture[k], picture[k], COLOR_HSV2BGR);
        imshow(window, picture[k]);


        /// cumulating single hue values in one image
        if(k > 0)
            addWeighted(picture[k-1], 0.5, picture[k], 0.5, 0.0, picture[k]);

        waitKey(50);
    }

    cvtColor(picture[k], picture[k], COLOR_HSV2BGR);
    imshow(final, picture[k]);

    waitKey();
}

/// resize picture with how_much parameter
void Picture::change_size(double how_much) {
    resize(this -> image, this -> image, Size(), how_much, how_much);
}

/// detect edges
void Picture::edge_detection() {
    string canny = "Canny";
    namedWindow(canny, WINDOW_AUTOSIZE);
    Mat edges;
    cvtColor(this -> image, edges, COLOR_RGB2GRAY);

    /// detecting using Canny function
    Canny(this -> image, edges, 100, 200);

    imshow(canny, edges);
    waitKey();
}

/// now it's time for shape detecting!
void Picture::circle_detection() {
    Mat src_gray;
    /// operate without colors
    cvtColor( this -> image, src_gray, COLOR_BGR2GRAY );

    /// Reduce the noise so we avoid false circle detection
    GaussianBlur( src_gray, src_gray, Size(9, 9), 1.5, 1.5 );

    vector<Vec3f> circles;

    /// Apply the Hough Transform to find the circles
    HoughCircles( src_gray, circles, HOUGH_GRADIENT, 1, src_gray.rows/8.0, 200, 100);

    /// Draw the circles detected
    for( auto i = 0; i < circles.size(); i++ )
    {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);

        circle( this -> image, center, 3, Scalar(0, 0,0), 3, LINE_AA, 0 );

        circle( this -> image, center, radius, Scalar(0,0,255), 3, LINE_AA, 0 );
    }

    namedWindow( "Circle detection", WINDOW_AUTOSIZE );
    imshow( "Circle detection", this -> image );

    waitKey();
}

void Picture::square_detection() {
    vector<vector<Point> > squares;
    string wndname = "Square detection";
    namedWindow(wndname, WINDOW_AUTOSIZE);
    int thresh = 50, N = 11;

    squares.clear();

    Mat pyr, timg, gray0(image.size(), CV_8U), gray;

    /// down-scale and upscale the image to filter out the noise
    pyrDown(image, pyr, Size(image.cols/2, image.rows/2));
    pyrUp(pyr, timg, image.size());
    vector<vector<Point> > contours;

    /// find squares in every color plane; of the image
    for( int c = 0; c < 3; c++ ){
        int ch[] = {c, 0};
        mixChannels(&timg, 1, &gray0, 1, ch, 1);

        /// try several threshold levels
        for( int l = 0; l < N; l++ ){
            /// hack: use Canny instead of zero threshold level
            if( l == 0 ){
                Canny(gray0, gray, 0, thresh, 5);
                /// dilate canny output to remove potential
                /// holes between edge segments
                dilate(gray, gray, Mat(), Point(-1,-1));
            }
            else{
                /// apply threshold if l!=0:
                gray = gray0 >= (l+1)*255/N;
            }

            /// find contours and store them all as a list
            findContours(gray, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
            vector<Point> approx;

            /// test each contour
            for( size_t i = 0; i < contours.size(); i++ ){
                /// approximate contour with accuracy proportional
                approxPolyDP(contours[i], approx, arcLength(contours[i], true)*0.02, true);

                /// square contours should have 4 vertices after approximation
                if( approx.size() == 4 && fabs(contourArea(approx)) > 1000 && isContourConvex(approx) ){
                    double maxCosine = 0;

                    for( int j = 2; j < 5; j++ ){
                        /// find the maximum cosine of the angle between joint edges
                        double cosine = fabs(angle(approx[j%4], approx[j-2], approx[j-1]));
                        maxCosine = MAX(maxCosine, cosine);
                    }

                    /// if cosines of all angles are small
                    if( maxCosine < 0.3 )
                        squares.push_back(approx);
                }
            }
        }
    }

    /// just dispaly detected squares
    for( size_t i = 0; i < squares.size(); i++ ){
        const Point* p = &squares[i][0];
        int n = (int)squares[i].size();
        polylines(image, &p, &n, 1, true, Scalar(0,255,0), 3, LINE_AA);
    }

    imshow(wndname, image);
    waitKey();
}

void Picture::triangles_detection() {
    Mat img_rgb,img_gray,canny_output,drawing;
    img_rgb  = this -> image;

    cvtColor(img_rgb,img_gray,COLOR_RGB2GRAY);
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    Canny( img_gray, canny_output, 100, 200, 3 );
    findContours( canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );
    drawing = Mat::zeros( canny_output.size(), CV_8UC3 );

    vector<Point> approxTriangle;
    for(auto i = 0; i < contours.size(); i++){
        approxPolyDP(contours[i], approxTriangle, arcLength(Mat(contours[i]), true)*0.04, true);

        if(approxTriangle.size() == 3){
            drawContours(drawing, contours, i, Scalar(0, 255, 255), FILLED); // fill GREEN
            vector<Point>::iterator vertex;

            for(vertex = approxTriangle.begin(); vertex != approxTriangle.end(); ++vertex){
                circle(drawing, *vertex, 3, Scalar(0, 0, 255), 1);
            }
        }
    }

    string windname = "Triangle detection";
    namedWindow(windname, WINDOW_AUTOSIZE);
    imshow(windname, drawing);
    waitKey();
}