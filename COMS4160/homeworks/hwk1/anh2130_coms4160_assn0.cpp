/*
 * Filename:    anh2130_coms4160_assn1.cpp
 * Author:      Adam Hadar, anh2130
 * Last edited: 2016-09-18
 * Purpose:     Writes a partitioned channel image to `hw0.exr`.
 *     Reads a given .exr file from command line, and converts it according to a prompt.
 */

#include "anh2130_coms4160_assn1.h"

int main(int argc, char *argv[])
{
    // try necessary for OpenEXR API
    try{
    // allocate program memory
    int width, height;
    int width_partition, height_partition;
    int x, y;
    Box2i dw;
    Array2D<Rgba> pixels;
    half tmp;
    /*
    RgbaInputFile file_in   (line 42)
    RgbaOutputFile file_out (line 70)
    */
    // incorrect program call
    if(argc != 2)
    {
        cout << "error: incorrect usage" << endl;
        cout << "`prog_out <filename>`" << endl;
        cout << "where <filename> is a path to an existing .exr file" << endl;
        return 1;
    }
    // incorrect file reference
    if(access(argv[1],F_OK) == -1)
    {
        cout << "error: reading file `" << argv[1] << "`" << endl;
        cout << "make sure you put a valid path" << endl;
        return 1;
    }
    // read in file
    RgbaInputFile file_in (argv[1]);
    dw = file_in.dataWindow();
    width = dw.max.x - dw.min.x + 1;
    height = dw.max.y - dw.min.y + 1;
    pixels.resizeErase(height,width);
    file_in.setFrameBuffer(&pixels[0][0] - dw.min.x - dw.min.y * width, 1, width);
    file_in.readPixels(dw.min.y, dw.max.y);
    // prompt-specific partitions 
    width_partition = floor(width/3);
    height_partition = floor(height/2);
    // implementing prompt
    for (y = height-1; y; --y)
        for (x = width-1; x; --x) {
            Rgba &px = pixels[y][x];
            tmp = y<height_partition||x<width_partition?(px.r+px.g+px.b)/3.0:0.2126*px.r+0.7152*px.g+0.0722*px.b;
            px.a = 1;
            if(y < height_partition || x < width_partition)
                // top-left :: red channel
                if(y < height_partition && x < width_partition) px.r += tmp, px.g = 0,    px.b = 0;
                // bottom-left :: green channel
                else if(y < height_partition)                   px.r = 0,    px.g += tmp, px.b = 0;
                // top-right :: blue channel
                else                                            px.r = 0,    px.g = 0,    px.b += tmp;
            // bottom-right :: luminance
            else                                                px.r = tmp,  px.g = tmp,  px.b = tmp;
            // reduce transparency to 0
        }
    // write to file
    RgbaOutputFile file_out("hw0.exr", width, height, WRITE_RGBA);
    file_out.setFrameBuffer(&pixels[0][0], 1, width);
    file_out.writePixels(height);
    // catch OpenEXR exception
    }catch(const std::exception &e){cerr<<"!EXCEPTION CAUGHT!"<<e.what()<<endl;return 1;}
    // return 0
    return 0;
}
