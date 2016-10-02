#include "parse.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;

void Parser::parse(const char *file)
{
    ifstream in(file);
    char buffer[1025];
    string cmd;
    for (int line = 1; in.good(); line++)
    {
        in.getline(buffer,1024);
        buffer[in.gcount()]=0;

        cmd="";
        istringstream iss(buffer);
    
        iss >> cmd;
        // comment
        if (cmd[0] == '/' or cmd.empty())
        {
            continue;
        }
        // sphere
        else if (cmd=="s")
        {
            geo_point pos; float r;
            iss >> pos >> r;
            parse_sphere(pos,r);
        }
        // triangle
        /*
        else if (cmd=="t")
        {
            float3 a,b,c;
            iss >> a,b,c;
            triangle(a,b,c);
        }
        */
        // plane
        /*
        else if (cmd=="p")
        {
            float3 n; float d;
            iss >> n >> d;
            plane(n,d);
        }
        */
        // camera
        else if (cmd=="c")
        {
            geo_point pos; geo_vector dir; float d,iw,ih; int pw,ph;
            iss >> pos >> dir >> d >> iw >> ih >> pw >> ph;
            parse_camera(pos,dir,d,iw,ih,pw,ph);
        }
        // light
        /*
        else if (cmd=="l")
        {
            iss >> cmd;
            if (cmd=="p")
            {
                float3 pos,rgb;
                iss >> pos >> rgb;
                pointLight(pos,rgb);
            }
            else if (cmd=="d")
            {
                float3 dir,rgb;
                iss >> dir >> rgb;
                directionalLight(dir,rgb);
            }
            else if (cmd=="a")
            {
                float3 rgb;
                iss >> rgb;
                ambientLight(rgb);
            }
            else
            {
                cout << "Parser error: invalid light at line " << line << endl;
            }
        }
        */
        else if (cmd=="m")
        {
            rgb_triple diff,spec,refl; float r;
            iss >> diff >> spec >> r >> refl;
            parse_material(diff,spec,r,refl);
        }
        else
        {
            cout << "Parser error: invalid command at line " << line << endl;
        }
    }
    in.close();
}
