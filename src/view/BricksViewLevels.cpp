#include "view/BricksViewLevels.h"


BricksViewLevels::BricksViewLevels(int level)
    : screen(SDL_GetWindowSurface(SDL_GetWindowFromID(1))),
      bricks_level(nullptr),
      is_valid_state(false)
{
    getLevelData(level);
}

BricksViewLevels::~BricksViewLevels()
{
    // free ( bricks_level );
    SDL_FreeSurface(screen);

    delete bricks_level;
    delete screen;
}

void BricksViewLevels::getLevelData(int level)
{
    switch (level)
    {
    case 1:
        bricks_level = new BricksLevel1();
        break;

    case 2:
        bricks_level = new BricksLevel2();
        break;

    case 3:
        bricks_level = new BricksLevel3();
        break;

    case 4:
        bricks_level = new BricksLevel4();
        break;

    default:
        bricks_level = new BricksLevel1();
        break;
    }
}

void BricksViewLevels::changeDisplayLevel(int level)
{
    getLevelData(level);
}

void BricksViewLevels::placeAllBricks()
{
    std::map<const int, SDL_Rect*>* p_src_bricks = &bricks_level->getSourceBricks();
    std::map<const int, SDL_Rect*>* p_dst_bricks = &bricks_level->getAllBricks();
    std::vector<int>* p_bricks_to_ignore = &bricks_level->getTableOfIgnoredBricks();

    // temporary maps
    std::map<const int, SDL_Rect*> temp_src_bricks;
    std::map<const int, SDL_Rect*> temp_dst_bricks;
    std::vector<int> temp_bricks_to_ignore;

    /* Copy content of charged tables to new temporary tables */
    unsigned int i = 1;
    unsigned int j = 1;
    unsigned int k = 0;

    // iterating with source bricks rectangles
    for (std::map<const int, SDL_Rect*>::const_iterator src_iter = p_src_bricks->begin(); src_iter != p_src_bricks->end();
         ++src_iter)
    {
        temp_src_bricks.insert(std::pair<const int, SDL_Rect*>(src_iter->first, src_iter->second));
        i++;
    }

    // iterating with destination bricks rectangles
    for (std::map<const int, SDL_Rect*>::const_iterator dst_iter = p_dst_bricks->begin(); dst_iter != p_dst_bricks->end();
         ++dst_iter)
    {
        temp_dst_bricks.insert(std::pair<const int, SDL_Rect*>(dst_iter->first, dst_iter->second));
        j++;
    }

    // iterating with bricks to ignore
    for (std::vector<int>::const_iterator ignore_iter = p_bricks_to_ignore->begin(); ignore_iter != p_bricks_to_ignore->end();
         ++ignore_iter)
    {
        temp_bricks_to_ignore.push_back(*ignore_iter);
        k++;
    }

    /* Iterations of blits with choose, which bricks not to display at screen (after destroy) */
    bool ignore = false;

    for (unsigned int i = 1; i < temp_dst_bricks.size() + 1; i++)
    {
        // Find bricks to ignore to place at screen
        for (int j = 0; j < temp_bricks_to_ignore.size(); j++)
        {
            if (temp_bricks_to_ignore[j] == i)
            {
                ignore = true;
                break;
            }
        }

        if (ignore == true)
        {
            bricks_level->destroyBrick(i);

            ignore = false;
            continue;
        }

        SDL_BlitSurface(ResManager::getInstance().getImage("blocks"), temp_src_bricks[i], screen, temp_dst_bricks[i]);
    }
}
