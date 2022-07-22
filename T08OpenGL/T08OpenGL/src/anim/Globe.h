#ifndef __GLOBE_H_
#define __GLOBE_H_

#include "anim/prim.h"

 namespace rnd
 {
   class globe : public prim
   {
     static const int GLOBE_H = 30, GLOBE_W = 30;
     dlgl::vec3 Geom[GLOBE_H][GLOBE_W];
     dlgl::vec3 pos;

     void GeomSet( double R )
     {
       int i, j;
       double theta = 0, phi = 0, tmp;
       for (i = 0, theta = 0; i < GLOBE_H; i++, theta += mth::PI / (GLOBE_H - 1))
         for (j = 0, phi = 0; j < GLOBE_W; j++, phi += 2 * mth::PI / (GLOBE_W - 1))
         {
           tmp = R * sin(theta) * sin(phi);
           Geom[i][j] = dlgl::vec3(R * sin(theta) * sin(phi),
                                   R * cos(theta),
                                   R * sin(theta) * cos(phi));
         }
     } // End of 'GeomSet' function

   public:
     globe( void )
     {
        NumOfV = GLOBE_H * GLOBE_W;
        NumOfI = (GLOBE_H - 1) * (GLOBE_W - 1) * 6;
        Create(NumOfV, NumOfI);
        GeomSet(0.2);
        GlobeSet();

        float Rx = (float) rand()/RAND_MAX - 0.5;
        float Ry = (float) rand()/RAND_MAX - 0.5;
        pos = dlgl::vec3(3 * Rx, 0, 3 * Ry);
        MatrWorld = dlgl::matr::Translate(pos);
     }

     ~globe( void )
     {
       delete[] Geom;
     }
     void GlobeSet( void )
     {
       int c = 0;
       for (int i = 0; i < GLOBE_H; i++)
       {
         for (int j = 0; j < GLOBE_W; j++)
         {
           prim::V[i * GLOBE_W + j].P = Geom[i][j];

           if (i != GLOBE_H - 1 && j != GLOBE_W - 1)
           {
             prim::I[c]     = i * GLOBE_H + j;
             prim::I[c + 1] = i * GLOBE_H + j + 1;
             prim::I[c + 2] = (i + 1) * GLOBE_H + j + 1;

             prim::I[c + 3] = i * GLOBE_H + j;
             prim::I[c + 4] = (i + 1) * GLOBE_H + j + 1;
             prim::I[c + 5] = (i + 1) * GLOBE_H + j;
             c += 6;
           }
         } //end for j
       } //end for i

     } //End of "GlobeSet" function

     void Response( void ) override
     {
       this->SetWorldTransormation(dlgl::matr::Translate(dlgl::vec3(0,0.05 * sin(T.Time * 3 - 30 * pos.X + pos.Y), 0)));
     }
     
   };
 }

#endif /* __GLOBE_H_ */