#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <qpoint.h>
#include <qrect.h>

class collisionPointFinder
{

    /*
     * line equations:
     *   - explicit:  y = mx + q
     *   - implicit:  ax + by + c = 0
     *
     *  ==> a = (y2 - y1)
     *  ==> b = (x1 - x2)
     *  ==> c = -(ax1 + by1)
     *
     *  ==> m = -a/b = (y1 - y2)/(x1 - x2)
     *  ==> q = -c/b = (ax1 + by1)/b = ((y2 - y1)x1 + (x1 - x2)y1)/(x1 - x2) = (y2 - y1)/(x1 - x2)x1 + y1
     *
     *  m = atan(dir)
     *  q = y - mx = x1 - atan(dir)*y1
     *
     * the move vector is the vector between the initial position and the final position of the entity.
        QLineF move_vector = QLineF(_model->prev_pos_x, _model->prev_pos_y, _model->pos_x, _model->pos_y);
     */

public:
    static double find(double a, double b, double old_x, double step, unsigned short iteration);


    static QPointF find_point_simple(QRectF m, QRectF b, QPointF old_pos, QPointF step, unsigned short iteration);


    static QPointF find_point(QRectF m, QRectF b, QPointF curr_pos, QPointF step, unsigned short iteration, int correction_sign);

    static QPointF find_substep(QRectF m, QRectF b, QPointF old_pos, QPointF step, unsigned short num_sub_steps);


    static QPointF find_substep2(QRectF m, QRectF b, QPointF old_pos, QPointF step, unsigned short num_sub_steps);


    static QPointF find_substep3(QRectF m, QRectF b, QPointF step, unsigned short num_sub_steps);


private:
    static bool linearIntersection(double a, double b, double x);


};



#endif // ALGORITHMS_H
