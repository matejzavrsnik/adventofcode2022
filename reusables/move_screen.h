//
// Created by matej on 08/11/23.
//

#ifndef RECREATIONAL_REUSABLES_GRABBAG_CPP_MOVE_SCREEN_H
#define RECREATIONAL_REUSABLES_GRABBAG_CPP_MOVE_SCREEN_H


#include <nature/vector.h>
#include <abstract/direction.h>

// screen: like pixels on screen
//
// 0 → 1
// ↓
// 1
//
// cell = {x, y}
// east = x -> increase
// north = y -> decrease

template<class T>
mzlib::vector2_t<T> move_screen(mzlib::vector2_t<T> c, const mzlib::direction d)
{
   switch (d)
   {
   case mzlib::direction::n: c += mzlib::vector2_t<T>{0,-1}; break;
   case mzlib::direction::s: c += mzlib::vector2_t<T>{0,1}; break;
   case mzlib::direction::e: c += mzlib::vector2_t<T>{1,0}; break;
   case mzlib::direction::w: c += mzlib::vector2_t<T>{-1,0}; break;

   case mzlib::direction::ne: c += mzlib::vector2_t<T>{1,-1}; break;
   case mzlib::direction::nw: c += mzlib::vector2_t<T>{-1,-1}; break;
   case mzlib::direction::se: c += mzlib::vector2_t<T>{1,1}; break;
   case mzlib::direction::sw: c += mzlib::vector2_t<T>{-1,1}; break;
   case mzlib::direction::centre: break;
   }
   return c;
}

#endif //RECREATIONAL_REUSABLES_GRABBAG_CPP_MOVE_SCREEN_H
