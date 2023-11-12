//
// Created by matej on 09/11/23.
//

#ifndef RECREATIONAL_REUSABLES_GRABBAG_H_MOVE_DRAWING_H
#define RECREATIONAL_REUSABLES_GRABBAG_H_MOVE_DRAWING_H

#include "grabbag.h"
#include "apply_drawing.h"
#include "drawing_operation.h"

inline bool move_drawing(
   mnvt& canvas,
   const mnvt& drawing,
   const mc2d& coor_from,
   const mc2d& coor_to
)
{
   return apply_drawing(canvas, drawing, coor_from, drawing_operation::subtract)
      && apply_drawing(canvas, drawing, coor_to, drawing_operation::add);
}

#endif //RECREATIONAL_REUSABLES_GRABBAG_H_MOVE_DRAWING_H