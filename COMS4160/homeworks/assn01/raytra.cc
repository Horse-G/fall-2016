#include <ImfRgbaFile.h>
#include <ImfStringAttribute.h>
#include <ImfMatrixAttribute.h>
#include <ImfArray.h>

#include "debug_input.h"
#include "struct_input.h"

int main(int argc, char **argv)
{
    DebugInputParser p1;
    StructInputParser p2;
    p1.parse(argv[1]);
    p2.parse(argv[1]);
    // try necessary for OpenEXR API
    try{
    int x,y,z;
    Ray        iter_ray;
    Intersect  iter_sect = Intersect();
    rgb_triple iter_color;
    Viewport camera = p2.viewport;

    int pix_width  = camera.pixel_x;
    int pix_height = camera.pixel_y;
    double img_width  = camera.img_x;
    double img_height = camera.img_y;
    double d_width  = img_width/pix_width;
    double d_height = img_height/pix_height;

    Imf::Array2D<Imf::Rgba> img_pixels;
    img_pixels.resizeErase(pix_height,pix_width);

    // iterate through pixels
    for(y = pix_height-1; y >= 0; --y)
        for(x = pix_width-1; x >= 0; --x)
        {
            cout << x << ", " << y << endl;
            iter_ray = Ray(camera.eye,
                camera.u*d_width*(x - pix_width + 1)/2.0
                + camera.v*d_height*(y - pix_height + 1)/2.0
                - camera.w*camera.fl);
            for(z = p2.objects.size() - 1; z >= 0; --z)
            {
                iter_sect = p2.objects[z]->find_intersection(iter_ray);
                if(iter_sect.yes_no)
                    break;
            }
            Imf::Rgba &px = img_pixels[y][x];
            iter_color =
                iter_sect.yes_no
                ? p2.materials[iter_sect.mat_ptr].get_mat()
                : rgb_triple(0.0,0.0,0.0);
            px.r = iter_color.r;
            px.g = iter_color.g;
            px.b = iter_color.b;
            px.a = 1.0;
        }
    //write to file
    Imf::RgbaOutputFile file_out("hw1.exr", img_width, img_height, Imf::WRITE_RGBA);
    file_out.setFrameBuffer(&img_pixels[0][0], 1, img_width);
    file_out.writePixels(img_height);
    // catch open exr exception
    }catch(const std::exception &e){cerr<<"!EXCEPTION CAUGHT!"<<e.what()<<endl;return 1;}
    return 0;
}
