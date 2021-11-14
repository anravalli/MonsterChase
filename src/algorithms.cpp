
#include "algorithms.h"
#include <math.h>

#define positive 1
#define negative -1

double collisionPointFinder::find(double a, double b, double old_x, double step, unsigned short iteration)
{
    double new_x = old_x;
    double half_step;

    iteration--;
    //if the step is big enough let's iterate one more time
    if (iteration > 0)
    {
        half_step = step/2;
        new_x = old_x - step;

        //depending on the intersection we will decide in wich direction we shall proceed in the next iteration
        if (linearIntersection(a, b, new_x))
        {
            new_x = collisionPointFinder::find(a, b, old_x, half_step, iteration);
        }
    }

    return new_x;
}

QPointF collisionPointFinder::find_point_simple(QRectF m, QRectF b, QPointF old_pos, QPointF step, unsigned short iteration)
{
    QPointF new_pos = old_pos;
    QPointF half_step;

    //a negative value of dir move closer to the obstacle in the next iteration
    //vice versa, a positive will move away
    //if the step is big enough let's iterate one more time
    if (iteration > 0)
    {
        new_pos = old_pos - step;
        half_step = step / 2;
        m.moveCenter(new_pos);
        //depending on the intersection we will decide in wich direction we shall proceed in the next iteration
        if (m.intersects(b))
        {
            iteration--;

            new_pos = collisionPointFinder::find_point_simple(m, b, old_pos, half_step, iteration);
        }
    }

    return new_pos;
}

QPointF collisionPointFinder::find_point(QRectF m, QRectF b, QPointF curr_pos, QPointF step, unsigned short iteration, int correction_sign)
{
    QPointF new_pos = curr_pos;
    QPointF half_step;

    //a negative correction_sign states we must move closer to the obstacle
    //vice versa, if positive, we must move away from it.
    //iteration is stopped in absence of collision with a step <= (0.1,0.1)
    if (iteration > 0)
    {
        new_pos = curr_pos - step;
        m.moveCenter(new_pos);

        half_step = step / 2;
        int sign = positive; //do not change the sign of "step"

        //depending on the intersection we will decide in wich direction we shall proceed in the next iteration
        if (m.intersects(b))
        {
            if(positive != correction_sign)
            {
                sign = negative;
                correction_sign = positive;
            }
        }
        else
        {
            if(negative != correction_sign)
            {
                sign = negative;
                correction_sign = negative;
            }
            if (abs(half_step.x()) <= 0.1) half_step.setX(0);
            if (abs(half_step.y()) <= 0.1) half_step.setY(0);
        }

        if (half_step.x() != 0 or half_step.y() != 0)
        {
            iteration--;

            new_pos = collisionPointFinder::find_point(m, b, new_pos, sign * half_step, iteration, correction_sign);
        }
    }

    return new_pos;
}

QPointF collisionPointFinder::find_substep(QRectF m, QRectF b, QPointF old_pos, QPointF step, unsigned short num_sub_steps)
{
    QPointF sub_step = step/num_sub_steps;
    QPointF new_pos = old_pos;

    m.moveCenter(new_pos + sub_step);

    while (not m.intersects(b))
    {
        new_pos = m.center();
        m.moveCenter(new_pos + sub_step);
    }

    return new_pos;
}

QPointF collisionPointFinder::find_substep2(QRectF m, QRectF b, QPointF old_pos, QPointF step, unsigned short num_sub_steps)
{
    QPointF sub_step = step/num_sub_steps;
    QPointF new_pos = old_pos;
    m.moveCenter(old_pos + sub_step);

    unsigned int remaining_iteration = 10;
    while (not m.intersects(b) and remaining_iteration > 0)
    {
        new_pos = m.center();
        m.translate(sub_step);
        remaining_iteration--;
    }

    return new_pos;
}


QPointF collisionPointFinder::find_substep3(QRectF m, QRectF b, QPointF step, unsigned short num_sub_steps)
{
    QPointF sub_step = step/num_sub_steps;

    m.translate(-sub_step);

    while (m.intersects(b))
    {
        m.translate(-sub_step);
    }

    return m.center();
}

bool collisionPointFinder::linearIntersection(double a, double b, double x) {
    if (x>a and x<b)
        return true;
    else
        return false;
}
