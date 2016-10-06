#include "parser.h"

int main(int argc, char **argv)
{
    // try necessary for OpenEXR API
    try{
    Parser parser;
    uint x,y;
    uint z;
    geo_ray    iter_ray;
    Intersect  iter_sect;
    rgb_triple iter_color;
    Viewport camera;

    parser.parse(argv[1]);

    camera = parser.viewport;
    uint pix_width  = camera.pix_x;
    uint pix_height = camera.pix_y;
    scalar img_width  = camera.img_x;
    scalar img_height = camera.img_y;
    scalar d_width  = img_width/pix_width;
    scalar d_height = img_height/pix_height;

    scalar w_center = pix_width/2.0;
    scalar h_center = pix_height/2.0;

    Imf::Array2D<Imf::Rgba> img_pixels;
    img_pixels.resizeErase(pix_height,pix_width);
    
    // iterate through pixels
    for(y = pix_height - 1; y >= 0; --y)
    for(x = pix_width - 1; x >= 0; --x)
    {
        iter_ray = geo_ray(camera.eye,
              camera.u*d_width *(x - w_center + 0.5)
            + camera.v*d_height*(h_center - y + 0.5)
            - camera.w*camera.fl);
        for(z = 0; z < parser.surfaces.size(); ++z)
        {
            iter_sect = parser.surfaces[z]->find_intersection(iter_ray);
            if(iter_sect.yes_no)
                break;
        }
        Imf::Rgba &px = img_pixels[y][x];
        iter_color =
            iter_sect.yes_no
            ? parser.materials[iter_sect.mat_ptr - 1].get_mat()
            : rgb_triple(0.0,0.0,0.0);
        px.r = iter_color.r;
        px.g = iter_color.g;
        px.b = iter_color.b;
        px.a = 1.0;
    }
    //write to file
    Imf::RgbaOutputFile file_out("hw1.exr", pix_width, pix_height, Imf::WRITE_RGBA);
    file_out.setFrameBuffer(&img_pixels[0][0], 1, pix_width);
    file_out.writePixels(pix_height);
    // catch open exr exception
    }catch(const std::exception &e){std::cerr<<"!EXCEPTION CAUGHT!"<<e.what()<<std::endl;return 1;}
    return 0;
}
