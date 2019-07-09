#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include "Picture.hpp"
#include "Video.hpp"

using namespace cv;
using namespace std;

int main(void){

    string file_name, color, new_color;

    cout << "Podaj obraz lub film/gif" << endl;
    cin >> file_name;
    cout << "Podaj kolor zamieniany" << endl;
    cin >> color;
    cout << "Podaj kolor na który zamieniasz" << endl;
    cin >> new_color;

    ///Picture picture = Picture(file_name);

    ///picture.change_size(0.5);
    ///picture.show_original();
    ///picture.change_color(color, new_color);
    ///picture.draw_every_color();
    ///picture.edge_detection();
    ///picture.circle_detection();
    ///picture.square_detection();
    ///picture.triangles_detection();

    ///Video video = Video(file_name);
    ///video.show_with_swaped_colors(color, new_color);
    ///video.show_as_hsv();
    ///video.show_canny_edges();
    ///video.show_gray();

    return 0;
}