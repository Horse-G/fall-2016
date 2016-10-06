#include "parser.h"

int main(int argc, char **argv)
{
    // try necessary for OpenEXR API
    try{
    // memory allocation
    Parser parser;
    uint x,y,z;
    scalar d_x, d_y, ctr_x, ctr_y;
    geo_ray    iter_ray;
    Intersect  iter_sect;
    rgb_triple iter_color;
    Viewport camera;
    Imf::Array2D<Imf::Rgba> img_pixels;
    // parse the scene file
    parser.parse(argv[1]);

    camera = parser.viewport;
    d_x = camera.img_x/camera.pix_x;
    d_y = camera.img_y/camera.pix_y;
    ctr_x = camera.pix_x/2.0;
    ctr_y = camera.pix_y/2.0;

    img_pixels.resizeErase(camera.pix_y, camera.pix_x);
    
    // iterate through pixels
    for(y = 0; y < camera.pix_y; ++y)
    for(x = 0; x < camera.pix_x; ++x)
    {
        iter_ray = geo_ray(camera.eye,
              camera.u*d_x*(x - ctr_x + 0.5)
            + camera.v*d_y*(ctr_y - y + 0.5)
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
    Imf::RgbaOutputFile file_out("hw1.exr", camera.pix_x, camera.pix_y, Imf::WRITE_RGBA);
    file_out.setFrameBuffer(&img_pixels[0][0], 1, camera.pix_x);
    file_out.writePixels(camera.pix_y);
    // catch open exr exception
    }catch(const std::exception &e){std::cerr<<"!EXCEPTION CAUGHT!"<<e.what()<<std::endl;return 1;}
    return 0;
}
