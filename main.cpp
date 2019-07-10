#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <X11/Xlib.h>
#include <unistd.h>
#include "Picture.hpp"
#include "Video.hpp"

using namespace cv;
using namespace std;

int main(void){

    int x;
    string file_name, color, new_color;
    cout << "1 - Picture\n2 - Video" << endl;

    cin >> x;

    if(x == 1){
        cout << "Give picture" << endl;
        cin >> file_name;
        Picture picture = Picture(file_name);
        picture.change_size(0.6);

        cout << "Give na option\n 1 - show original\n 2 - change color\n 3 - draw every color" << endl;
        cout << "4 - draw edges\n 5 - detect circles\n 6 - detect squares\n 7 - detect triangles" << endl;
        cin >> x;

        switch(x){
            case 1 : picture.show_original(); break;
            case 2 : {
                cin >> color;
                cin >> new_color;
                picture.change_color(color, new_color); break;
            }
            case 3 : picture.draw_every_color(); break;
            case 4 : picture.edge_detection(); break;
            case 5 : picture.circle_detection(); break;
            case 6 : picture.square_detection(); break;
            case 7 : picture.triangles_detection(); break;
            default : {
                My_Exeption ex = My_Exeption("Unknown option!");
                ex.throw_it();
            }
        }
    }else if(x == 2){
        cout << "Give video/gif" << endl;
        cin >> file_name;
        Video video = Video(file_name);

        cout << "Give na option\n 1 - show with swapped colors\n 2 - show in hsv model" << endl;
        cout << " 3 - show edges only\n 4 - show as gray" << endl;
        cin >> x;

        switch(x){
            case 1 : {
                cin >> color;
                cin >> new_color;
                video.show_with_swaped_colors(color, new_color);
            }
            case 2 : video.show_as_hsv(); break;
            case 3 : video.show_canny_edges(); break;
            case 4 : video.show_gray(); break;
            default : {
                My_Exeption ex = My_Exeption("Unknown option!");
                ex.throw_it();
            }
        }
    }else{
        My_Exeption ex = My_Exeption("Unknown option!");
        ex.throw_it();
    }
    return 0;
}