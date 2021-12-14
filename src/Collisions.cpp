#include "Collisions.h"

int Collisions::nr_brick_collided = 0;

Collisions::Collisions()
    : coll_side(NONE),
      is_brick_collided(false),
      return_text(""),
      bottleneck("false")
{
}

Collisions::~Collisions()
{
}

/* *** DETECT COLLISION OF SINGLE OBJECT WITH OBJECT FROM TABLE *** */
std::string Collisions::detectCollision(SDL_Rect A, std::map<const int, SDL_Rect*>& B)
{
    int left_A = A.x;
    int right_A = A.x + A.w;
    int top_A = A.y;
    int bottom_A = A.y + A.h;

    int ball_middle_x = right_A - (A.w / 2);
    int ball_middle_y = bottom_A - (A.h / 2);

    int left_B = 0;
    int right_B = 0;
    int top_B = 0;
    int bottom_B = 0;
    int brick_middle_x = 0;
    int brick_middle_y = 0;

    for (unsigned int i = 1; i < B.size() + 1; i++)
    {
        left_B = B[i]->x;
        right_B = B[i]->x + B[i]->w;
        top_B = B[i]->y;
        bottom_B = B[i]->y + B[i]->h;

        brick_middle_x = right_B - (B[i]->w / 2);
        brick_middle_y = bottom_B - (B[i]->h / 2);

        int horizont_left = left_B + 2;
        int horizont_right = right_B - 2;


        if ((((top_A <= bottom_B) && (top_A > top_B)) || ((bottom_A >= top_B) && (bottom_A < bottom_B))) && (right_A >=
            left_B) && (left_A <= right_B))
        {
            // COLLISION DETECTED
            coll_side = VERTICAL;

            return_text = "Vertical";
            nr_brick_collided = i;

            std::cout << "Collision Brick: " << return_text << std::endl
                << "nr_brick_collided: " << i << std::endl << std::endl;

            break;
        }

        else if (((left_A <= right_B) && (right_A >= left_B)) && (top_A <= bottom_B) && (bottom_A >= top_B))
        {
            // COLLISION DETECTED
            coll_side = HORIZONTAL;

            return_text = "Horizontal";
            nr_brick_collided = i;

            break;
        }

            // IF NO COLLISION
        else
        {
            return_text = "None";
        }
    }
    return return_text;
}

/* *** DETECT COLLISION OF TWO SINGLE OBJECTS *** */
std::string Collisions::detectCollision(SDL_Rect A, SDL_Rect B)
{
    int left_A = A.x;
    int right_A = A.x + A.w;
    int top_A = A.y;
    int bottom_A = A.y + A.h;

    int left_B = B.x;
    int right_B = B.x + B.w;
    int top_B = B.y;
    int bottom_B = B.y + B.h;

    int horizont_left = left_B + 7;
    int horizont_right = right_B - 7;

    // IF COLLISION VERTICAL
    if ((right_A < horizont_right) && (left_A > horizont_left) && (bottom_A >= top_B))
    {
        // COLLISION DETECTED
        coll_side = VERTICAL;

        return_text = "Vertical";

        std::cout << "Collision Paddle: " << return_text << std::endl << std::endl;
    }

        // IF COLLISION HORIZONTAL
    else if (((right_A >= horizont_right) || (left_A <= horizont_left))
        && (left_A <= right_B) && (right_A >= left_B)
        && (bottom_A > top_B) && (top_A < bottom_B))
    {
        // COLLISION DETECTED
        coll_side = HORIZONTAL;

        if ((left_A < right_B))
            bottleneck = true;

        return_text = "Horizontal";

        std::cout << "Collision Paddle: " << return_text << std::endl << std::endl;
    }

        // IF NO COLLISION
    else
    {
        return_text = "None";
    }

    return return_text;
}

int Collisions::bounceBall()
{
    return -1;
}

int Collisions::getCollidedBrick()
{
    return nr_brick_collided;
}

bool Collisions::isBottleneck()
{
    return bottleneck;
}

void Collisions::clearData()
{
    coll_side = NONE;
    is_brick_collided = false;
    nr_brick_collided = 0;
    return_text = "";
    bottleneck = false;
}
