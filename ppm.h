//Process a binary PPM file
using namespace std;

struct pixel{
        unsigned char r;
        unsigned char g;
        unsigned char b;
};


class ppm {

private:
    void init(int _width, int _height);
    //info about the PPM file (height and width)
    unsigned int nr_lines;
    unsigned int nr_columns;
public:
    vector<vector<pixel>> bitmap;
    unsigned int height;
    unsigned int width;
    unsigned int max_col_val;
    //total number of elements (pixels)
    unsigned int size;

    ppm();
    //create a PPM object and fill it with data stored in fname 
    ppm(const std::string &fname);
    //create an "epmty" PPM image with a given width and height;the R,G,B arrays are filled with zeros
    ppm(int _width, int _height);
    //read the PPM image from fname
    void read(const std::string &fname);
    //write the PPM image in fname
    void write(const std::string &fname);

};

