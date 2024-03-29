#ifndef __MTH_h_
#define __MTH_h_

#include <cmath>

//#define Pi 3.1415926536
//#define D2R(X) ((X) * Pi / 180)
//#define R2D(X) ((X) * 180 / Pi)


#define INDEX1(X) (Perm[(X) & TAB_MASK])
#define INDEX2(X, Y) (Perm[(X + INDEX1(Y)) & TAB_MASK])
#define INDEX3(X, Y, Z) (Perm[(X + INDEX2(Y, Z)) & TAB_MASK])

#define TAB_BITS 8
#define TAB_SIZE (1 << TAB_BITS)
#define TAB_MASK (TAB_SIZE - 1)

namespace mth
{
  const double PI = 3.14159265359;

  template<typename type>
    type D2R( type Angle )
    {
      return Angle * (PI / 180.0);
    }

  template<typename type>
    type R2D( type Angle )
    {
      return Angle * (180.0 / PI);
    }


  template<typename type>
    class vec2
    {
    public: 
      type X, Y;
      vec2( void ): X(0), Y(0)
      {
      }

      vec2( type x, type y) : X(x), Y(y)
      {
      }

      vec2 &operator=( const vec2 &v2 ) 
      {
        X = v2.X; Y = v2.Y; 
        return *this;
      }
       
      type operator[]( int i ) const
      {
        return *(&X + i);
      }

      type & operator[]( int i )
      {
        return *(&X + i);
      }

    };

  template<typename type>
    class vec4
    {
    public:
      type X, Y, Z, W;
      vec4( void ): X(0), Y(0), Z(0), W(0)
      {
      }

      vec4( type x, type y, type z, type w ) : X(x), Y(y), Z(z), W(w)
      {
      }
    };

  template<typename type>
    class vec3
    {
    public:
      type X, Y, Z;

      vec3( void ): X(0), Y(0), Z(0)
      {
      }

      vec3( type x, type y, type z ) : X(x), Y(y), Z(z)
      {
      }

     vec3 &operator=( const vec3 &v2 ) 
      {
        X = v2.X; Y = v2.Y; Z = v2.Z;
        return *this;
      }

      vec3 operator+( const vec3 &v2 ) const
      {
        return vec3(X + v2.X, Y + v2.Y, Z + v2.Z);
      }

      vec3 operator+( float C ) const
      {
        return vec3(X + C, Y + C, Z + C);
      }

      vec3 operator-( const vec3 &v2 ) const
      {
        return vec3(X - v2.X, Y - v2.Y, Z - v2.Z);
      }

      vec3 operator-( float C ) const
      {
        return vec3(X - C, Y - C, Z - C);
      }
      vec3 &operator+=( const vec3 &v2 ) 
      {
        X += v2.X; Y += v2.Y; Z += v2.Z;
        return *this;
      }

      vec3 &operator-=( const vec3 &v2 ) 
      {
        X -= v2.X; Y -= v2.Y; Z -= v2.Z;
        return *this;
      }

      vec3 operator*( type N ) const
      {
        return vec3(X * N, Y * N, Z * N);
      }

      vec3 operator/( type N ) const
      {
        return vec3(X / N, Y / N, Z / N);
      }

      vec3 operator-( void ) const
      {
        return vec3(-X, -Y, -Z);
      }

      type operator!( void ) const
      {
        type a;
        a = sqrt(X * X + Y * Y + Z * Z);
        return sqrt(X * X + Y * Y + Z * Z);
      }

      type operator&( const vec3 &v2 ) const
      {
        return X * v2.X + Y * v2.Y + Z * v2.Z;
      }

      vec3 Cross( const vec3 &v2 ) 
      {
        return vec3(Y * v2.Z - Z * v2.Y,
                    Z * v2.X - X * v2.Z,
                    X * v2.Y - Y * v2.X);
      }
      vec3 Normalize( void ) const
      { 
        if (float len = *this & *this; len != 0 && len != 1)
          return *this/ sqrt(len);
        return *this;
      }
 
      
       type Angle( const vec3 &v2 ) const
      { 
        type a;
        a = (*this & v2) / (!(*this) * (!v2));
        if (a > 1) a = 1.;
        if (a < -1) a = -1.;

        return R2D(acos(a));
      }

      type operator[]( int i ) const
      {
        return *(&X + i);
      }

      type & operator[]( int i )
      {
        return *(&X + i);
      }
    };

  template<typename type>
    class matr
    {
    public:
      type M[4][4];

      matr( void )
      {
        M[0][0] = 1; M[0][1] = 0; M[0][2] = 0; M[0][3] = 0;
        M[1][0] = 0; M[1][1] = 1; M[1][2] = 0; M[1][3] = 0;
        M[2][0] = 0; M[2][1] = 0; M[2][2] = 1; M[2][3] = 0;
        M[3][0] = 0; M[3][1] = 0; M[3][2] = 0; M[3][3] = 1;
      }

      vec3<type> PointTransform( const vec3<type> &V ) const //V * M4x3
      {
        return vec3<type>(V.X * M[0][0] + V.Y * M[1][0] + V.Z * M[2][0] + 1 * M[3][0],
                          V.X * M[0][1] + V.Y * M[1][1] + V.Z * M[2][1] + 1 * M[3][1],
                          V.X * M[0][2] + V.Y * M[1][2] + V.Z * M[2][2] + 1 * M[3][2]);
      }

      vec3<type> VecTransform( const vec3<type> &V ) const    //V * M3x3
      {
        return vec3<type>(V.X * M[0][0] + V.Y * M[1][0] + V.Z * M[2][0],
                          V.X * M[0][1] + V.Y * M[1][1] + V.Z * M[2][1],
                          V.X * M[0][2] + V.Y * M[1][2] + V.Z * M[2][2]);
      }
      vec3<type> VecMulMatr( const vec3<type> &V ) const // V*M4x4/w
      {
        return (*this).PointTransform(V) / (V.X * M[0][3] + V.Y * M[1][3] + V.Z * M[2][3] + M[3][3]);
      }

      matr( type A00, type A01, type A02, type A03,
            type A10, type A11, type A12, type A13,
            type A20, type A21, type A22, type A23,
            type A30, type A31, type A32, type A33 ) :
        M
        {
          {A00, A01, A02, A03},
          {A10, A11, A12, A13},
          {A20, A21, A22, A23},
          {A30, A31, A32, A33},
        }
      {
        M[0][0] = A00; M[0][1] = A01; M[0][2] = A02; M[0][3] = A03;
        M[1][0] = A10; M[1][1] = A11; M[1][2] = A12; M[1][3] = A13;
        M[2][0] = A20; M[2][1] = A21; M[2][2] = A22; M[2][3] = A23;
        M[3][0] = A30; M[3][1] = A31; M[3][2] = A32; M[3][3] = A33;
      }

      static matr Identity(void)
      {
        return matr(1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1);
      }

      static matr Translate( const vec3<type> &T )
      {
        return matr(1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    T.X, T.Y, T.Z, 1);
      }   
 
      static matr Scale( const vec3<type> &S )
      {
         return matr(S.X, 0, 0, 0,
                     0, S.Y, 0, 0,
                     0, 0, S.Z, 0,
                     0, 0, 0, 1);
      } 

      static matr RotateX( type AngleInDegree )
      {
        type a;
        a = D2R(AngleInDegree);
        type c = cos(a), s = sin(a);
      
        return matr(1, 0, 0, 0,
                    0, c,-s, 0,
                    0, s, c, 0,
                    0, 0, 0, 1);
      }

      static matr RotateY( type AngleInDegree )
      {
        type a;
        a = D2R(AngleInDegree);
        type c = cos(a), s = sin(a);
      
        return matr( c, 0, s, 0,
                     0, 1, 0, 0,
                    -s, 0, c, 0,
                     0, 0, 0, 1);
      }

      static matr RotateZ( type AngleInDegree )
      {
        type a;
        a = D2R(AngleInDegree);
        type c = cos(a), s = sin(a);
      
       return matr(c,-s, 0, 0,
                   s, c, 0, 0,
                   0, 0, 1, 0,
                   0, 0, 0, 1);
      }

      static matr Rotate( vec3<type> V, type AngleInDegree )
      {
        type a;
        a = D2R(AngleInDegree);
        type c = cos(a), s = sin(a);
      
        vec3<type>
          A = V.Normalize();
        return matr( c + A.X * A.X * (1 - c), A.X * A.Y * (1 - c) + A.Z * s, A.X * A.Z * (1 - c) - A.Y * s, 0,
                     A.Y * A.X * (1 - c) - A.Z * s, c + A.Y * A.Y * (1 - c), A.Y * A.Z * (1 - c) + A.X * s, 0,
                     A.Z * A.X * (1 - c) + A.Y * s, A.Z * A.Y * (1 - c) - A.X * s, c + A.Z * A.Z * (1 - c), 0,
                     0, 0, 0, 1);
      }
      static matr View( vec3<type> Loc, vec3<type> At, vec3<type> Up1 )
      {
        vec3<type>     Dir, Right, Up;
          Dir = (At - Loc);
          Dir = Dir.Normalize();
          Right = (Dir.Cross(Up1)).Normalize();
          Up = Right.Cross(Dir);
        return matr(Right.X, Up.X, -Dir.X, 0,
                    Right.Y, Up.Y, -Dir.Y, 0,
                    Right.Z, Up.Z, -Dir.Z, 0,
                    -Loc & Right, -Loc & Up, Loc & Dir, 1);
      }

      static matr Ortho( double Left, double Right, double Bottom, double Top, double Near, double Far )
      {
        return matr(      2 / (Right - Left),                                0,                                0,  0,
                                           0,               2 / (Top - Bottom),                                0,  0,
                                           0,                                0,                -2 / (Far - Near),  0,
            -(Right + Left) / (Right - Left), -(Top + Bottom) / (Top - Bottom),     -(Near + Far) / (Far - Near),  1);
      }

      static matr Frustum( double Left, double Right, double Bottom, double Top, double Near, double Far )
      {
        return matr(      2 * Near / (Right - Left),                               0,                               0,  0,
                                                  0,       2 * Near / (Top - Bottom),                               0,  0,
                    (Right + Left) / (Right - Left), (Top + Bottom) / (Top - Bottom),    -(Far + Near) / (Far - Near), -1,
                                                  0,                               0, -2 * Near * Far / (Far - Near) ,  0);
      }
      matr operator*( const matr &M2 ) const
      {

        return matr(M[0][0] * M2.M[0][0] + M[0][1] * M2.M[1][0] + M[0][2] * M2.M[2][0] + M[0][3] * M2.M[3][0],
                    M[0][0] * M2.M[0][1] + M[0][1] * M2.M[1][1] + M[0][2] * M2.M[2][1] + M[0][3] * M2.M[3][1],
                    M[0][0] * M2.M[0][2] + M[0][1] * M2.M[1][2] + M[0][2] * M2.M[2][2] + M[0][3] * M2.M[3][2],
                    M[0][0] * M2.M[0][3] + M[0][1] * M2.M[1][3] + M[0][2] * M2.M[2][3] + M[0][3] * M2.M[3][3],

                    M[1][0] * M2.M[0][0] + M[1][1] * M2.M[1][0] + M[1][2] * M2.M[2][0] + M[1][3] * M2.M[3][0],
                    M[1][0] * M2.M[0][1] + M[1][1] * M2.M[1][1] + M[1][2] * M2.M[2][1] + M[1][3] * M2.M[3][1],
                    M[1][0] * M2.M[0][2] + M[1][1] * M2.M[1][2] + M[1][2] * M2.M[2][2] + M[1][3] * M2.M[3][2],
                    M[1][0] * M2.M[0][3] + M[1][1] * M2.M[1][3] + M[1][2] * M2.M[2][3] + M[1][3] * M2.M[3][3],

                    M[2][0] * M2.M[0][0] + M[2][1] * M2.M[1][0] + M[2][2] * M2.M[2][0] + M[2][3] * M2.M[3][0],
                    M[2][0] * M2.M[0][1] + M[2][1] * M2.M[1][1] + M[2][2] * M2.M[2][1] + M[2][3] * M2.M[3][1],
                    M[2][0] * M2.M[0][2] + M[2][1] * M2.M[1][2] + M[2][2] * M2.M[2][2] + M[2][3] * M2.M[3][2],
                    M[2][0] * M2.M[0][3] + M[2][1] * M2.M[1][3] + M[2][2] * M2.M[2][3] + M[2][3] * M2.M[3][3],

                    M[3][0] * M2.M[0][0] + M[3][1] * M2.M[1][0] + M[3][2] * M2.M[2][0] + M[3][3] * M2.M[3][0],
                    M[3][0] * M2.M[0][1] + M[3][1] * M2.M[1][1] + M[3][2] * M2.M[2][1] + M[3][3] * M2.M[3][1],
                    M[3][0] * M2.M[0][2] + M[3][1] * M2.M[1][2] + M[3][2] * M2.M[2][2] + M[3][3] * M2.M[3][2],
                    M[3][0] * M2.M[0][3] + M[3][1] * M2.M[1][3] + M[3][2] * M2.M[2][3] + M[3][3] * M2.M[3][3]);
      }
      static type Determ3x3( type A11, type A12, type A13,
                             type A21, type A22, type A23,
                             type A31, type A32, type A33 )
      {
        return A11 * A22 * A33 - A11 * A23 * A32 - A12 * A21 * A33 +
          A12 * A23 * A31 + A13 * A21 * A32 - A13 * A22 * A31;
      }

      type Determ( void ) const
      {
        return
          M[0][0] * Determ3x3(M[1][1], M[1][2], M[1][3],
                                  M[2][1], M[2][2], M[2][3],
                                  M[3][1], M[3][2], M[3][3]) +
         -M[0][1] * Determ3x3(M[1][0], M[1][2], M[1][3],
                                  M[2][0], M[2][2], M[2][3],
                                  M[3][0], M[3][2], M[3][3]) +
          M[0][2] * Determ3x3(M[1][0], M[1][1], M[1][3],
                                  M[2][0], M[2][1], M[2][3],
                                  M[3][0], M[3][1], M[3][3]) +
         -M[0][3] * Determ3x3(M[1][0], M[1][1], M[1][2],
                                  M[2][0], M[2][1], M[2][2],
                                  M[3][0], M[3][1], M[3][2]);
      }

      matr Inverse( void ) const
      {
        matr r;
        type det = Determ();
      
        if (det == 0)
          return Identity();
      
        r.M[0][0] =  Determ3x3(M[1][1], M[1][2], M[1][3],
                                   M[2][1], M[2][2], M[2][3],
                                   M[3][1], M[3][2], M[3][3]) / det;
        r.M[1][0] = -Determ3x3(M[1][0], M[1][2], M[1][3],
                                   M[2][0], M[2][2], M[2][3],
                                   M[3][0], M[3][2], M[3][3]) / det;
        r.M[2][0] =  Determ3x3(M[1][0], M[1][1], M[1][3],
                                   M[2][0], M[2][1], M[2][3],
                                   M[3][0], M[3][1], M[3][3]) / det;
        r.M[3][0] = -Determ3x3(M[1][0], M[1][1], M[1][2],
                                   M[2][0], M[2][1], M[2][2],
                                   M[3][0], M[3][1], M[3][2]) / det;
      
        r.M[0][1] = -Determ3x3(M[0][1], M[0][2], M[0][3],
                                   M[2][1], M[2][2], M[2][3],
                                   M[3][1], M[3][2], M[3][3]) / det;
        r.M[1][1] =  Determ3x3(M[0][0], M[0][2], M[0][3],
                                   M[2][0], M[2][2], M[2][3],
                                   M[3][0], M[3][2], M[3][3]) / det;
        r.M[2][1] = -Determ3x3(M[0][0], M[0][1], M[0][3],
                                   M[2][0], M[2][1], M[2][3],
                                   M[3][0], M[3][1], M[3][3]) / det;
        r.M[3][1] =  Determ3x3(M[0][0], M[0][1], M[0][2],
                                   M[2][0], M[2][1], M[2][2],
                                   M[3][0], M[3][1], M[3][2]) / det;
      
        r.M[0][2] =  Determ3x3(M[0][1], M[0][2], M[0][3],
                                   M[1][1], M[1][2], M[1][3],
                                   M[3][1], M[3][3], M[3][3]) / det;
        r.M[1][2] = -Determ3x3(M[0][0], M[0][2], M[0][3],
                                   M[1][0], M[1][2], M[1][3],
                                   M[3][0], M[3][2], M[3][3]) / det;
        r.M[2][2] =  Determ3x3(M[0][0], M[0][1], M[0][3],
                                   M[1][0], M[1][1], M[1][3],
                                   M[3][0], M[3][1], M[3][3]) / det;
        r.M[3][2] = -Determ3x3(M[0][0], M[0][1], M[0][2],
                                   M[1][0], M[1][1], M[1][2],
                                   M[3][0], M[3][1], M[3][2]) / det;

        r.M[0][3] =  -Determ3x3(M[0][1], M[0][2], M[0][3],
                                   M[1][1], M[1][2], M[1][3],
                                   M[2][1], M[2][2], M[2][3]) / det;
        r.M[1][3] =  Determ3x3(M[0][0], M[0][2], M[0][3],
                                   M[1][0], M[1][2], M[1][3],
                                   M[2][0], M[2][2], M[2][3]) / det;
        r.M[2][3] = -Determ3x3(M[0][0], M[0][1], M[0][3],
                                   M[1][0], M[1][1], M[1][3],
                                   M[2][0], M[2][1], M[2][3]) / det;
        r.M[3][3] =  Determ3x3(M[0][0], M[0][1], M[0][2],
                                   M[1][0], M[1][1], M[1][2],
                                   M[2][0], M[2][1], M[2][2]) / det;
        return r;
      
        
      }         
  }; 

  
  class noise
  {
  public:
    double TabNoise[TAB_SIZE];
    int Perm[TAB_SIZE];
    int Oct = 4;

    noise( void )
    {
      for (int i = 0; i < TAB_SIZE; i++)
        TabNoise[i] = (double)rand() / RAND_MAX;

      for (int i = 0; i < TAB_SIZE; i++)
        Perm[i] = i;
      for (int i = 0; i < TAB_SIZE * 8; i++)
      {
        int 
          a = rand() & TAB_MASK,
          b = rand() & TAB_MASK,
          tmp = Perm[a];
        Perm[a] = Perm[b];
        Perm[b] = tmp;
      }
    }

    double Noise1D( double X )
    {
      int ix = int(floor(X)), ix1;
      double fx;

      fx = X - ix;
      ix &= TAB_MASK;
      ix1 = (ix + 1) & TAB_MASK;
      return TabNoise[ix] * (1 - fx) + TabNoise[ix1] * fx;
    }

    double Noise2D( double X, double Y )
    {
      int ix = int(floor(X)), ix1, iy = int(floor(Y)), iy1;
      double fx, fy;

      fx = X - ix;
      fx = (3 - 2 * fx) * fx * fx;
      fy = Y - iy;
      fy = (3 - 2 * fy) * fy * fy;
      ix &= TAB_MASK;
      ix1 = (ix + 1) & TAB_MASK;
      iy &= TAB_MASK;
      iy1 = (iy + 1) & TAB_MASK;
      return 
        TabNoise[INDEX2(iy, ix)] * (1 - fx) * (1 - fy) + 
        TabNoise[INDEX2(iy, ix1)] * fx * (1 - fy) + 
        TabNoise[INDEX2(iy1, ix)] * (1 - fx) * fy + 
        TabNoise[INDEX2(iy1, ix1)] * fx * fy;
    }

    double NoiseTurb1D( double X, int Octaves )
    {
      int frac = 1;
      double val = 0;

      for (int i = 0; i < Octaves; i++ )
      {
        val += Noise1D(X) / frac;
        X = (X + 30.03) * 2;
        frac *= 2;
      }
      return val * ( 1 << (Octaves - 1)) / ((1 << Octaves) - 1);
    }

    double NoiseTurb2D( double X, double Y, int Octaves )
    {
      int frac = 1;
      double val = 0;

      for (int i = 0; i < Octaves; i++ )
      {
        val += Noise2D(X, Y) / frac;
        X = (X + 30.03) * 2;
        Y = (Y + 17.33) * 2;
        frac *= 2;
      }
      return val * ( 1 << (Octaves - 1)) / ((1 << Octaves) - 1);
    }
  };
}

namespace dlgl
{
  typedef mth::vec2<float> vec2;
  typedef mth::vec3<float> vec3;
  typedef mth::vec4<float> vec4;
  typedef mth::matr<float> matr;
  typedef mth::noise noise;
}

 /*
void f( void )
{
  dlgl::vec3 v(1, 2, 3);
  dlgl::matr m;

  m = dlgl::matr::Identity();
}
*/



#endif /* __MTH_h_ */