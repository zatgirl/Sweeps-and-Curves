#ifndef __VECTOR_3_H__
#define __VECTOR_3_H__


class Vector3
{
public:
   float x, y, z;

   Vector3()
   {
      x = y = z = 0;
   }

   Vector3(float _x, float _y, float _z)
   {
       x = _x;
       y = _y;
       z = _z;
   }

   void set(float _x, float _y, float _z)
   {
       x = _x;
       y = _y;
       z = _z;
   }

   void normalize()
   {
       float norm = (float)sqrt(x*x + y*y);

       if(norm==0.0)
       {
          printf("\n\nNormalize::Divisao por zero");
          x = 1;
          y = 1;
          return;
       }
       x /= norm;
       y /= norm;
   }

   Vector3 operator - (const Vector3& v)
   {
        Vector3 aux( x - v.x, y - v.y, z - v.z);
        return( aux );
   }

   Vector3 operator + (const Vector3& v)
   {
       Vector3 aux( x + v.x, y + v.y, z + v.z);
       return( aux );
   }

      Vector3 operator + (const float s)
   {
       Vector3 aux( x + s, y + s, z + s);
       return( aux );
   }

   Vector3 operator + (const int s)
   {
       Vector3 aux( x + s, y + s, z + s);
       return( aux );
   }

   Vector3 operator * (const float s)
   {
       Vector3 aux( x * s, y * s, z * s);
       return( aux );
   }

   Vector3 operator * (const double s)
   {
       Vector3 aux( x * s, y * s, z * s);
       return( aux );
   }

   //Adicionem os demais overloads de operadores aqui.


};

#endif
