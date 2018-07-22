#ifndef RESMANAGER_H
#define RESMANAGER_H

//#include <SDL.h>
#include <SDL.h>
#include "SDL_image.h"

#include <string>

#include "Image.h"

// Klasa Mened¿er Zasobów jest singletonem, poniewa¿ chcê aby utworzy³a siê pojedyncza instancja z dostêpem globalnym.
// Inne modu³y ca³ego programu maj¹ w razie potrzeby dostêp do ró¿nego rodzaju zasobów, czyli Tekstury (obrazki), pliki
// dŸwiêkowe i muzyczne. Te modu³y uzyskuj¹ dostêp w taki sposób: ResManager:: getInstance().metoda();
// Do ka¿dego modu³u, który wykorzystuje metody z ResManager nale¿y zainkludowaæ "ResManager.h"

// Utworzenie instancji, czyli pierwsze u¿ycie ResManagera nastêpuje w g³ównej klasie "main".
// Wtedy po uruchomieniu gry, przed g³ówn¹ pêtl¹ gry nastêpuje za³adowanie do pamiêci obrazków Paletki, bloków i pi³ki
// Robimy to w ten sposób: ResManager:: getInstance().loadMainImages();

class ResManager
{
    public:
        // Destruktor musi byæ publiczny (w singletonie równie¿), w przeciwnym razie wyst¹pi b³¹d:
        virtual ~ResManager();

        // Metoda za pierwszym razem tworz¹ca jedyn¹, statyczn¹ instancjê klasy ResManager. PóŸniej tego nie robi,
        // poniewa¿ sprawdza, ¿e ten obiekt statyczny jest ju¿ utworzony:
        static ResManager getInstance()
        {
          //Inicjalizacja statycznego obiektu.
          //Obiekt zostanie utworzony przy pierwszym wywo³aniu tej metody
          //i tylko wtedy nast¹pi inicjalizacja przy pomocy konstruktora.
          //Ka¿de nastêpne wywo³anie jedynie zwróci referencjê tego obiektu.

          // res_manager = new ResManager();

          static ResManager res_manager;
          return res_manager;
        }

        // Za³adowanie g³ównych obrazków gry do pamiêci:
        // void loadMainImages();
        SDL_Surface* loadImageMenu(std:: string res);
        SDL_Surface* loadImageSelection();

        SDL_Surface* loadImageBall();
        SDL_Surface* loadImagePaddle();
        SDL_Surface* loadImagePaddleWar();
        SDL_Surface* loadImageBullet();
        SDL_Surface* loadImageBlocks();

        // £adowanie obrazków bonusów:
        SDL_Surface* loadImageGunPack();
        SDL_Surface* loadImageSlowPack();
        SDL_Surface* loadImageDupPack();
        SDL_Surface* loadImageLivePack();

        // Metody u¿ywane do pobierania zasobów, które wybraliœmy jako parametr metody w razie potrzeby.
        // U¿ywane w ró¿nych klasach operuj¹cych na obiektach zasobów gry:
        SDL_Surface* getImage ( std:: string img );

        // Pobierz kolor t³a ekranu:
        SDL_Color getBgdColor();

        // Pobieranie informacji o ró¿nych obrazkach (np. wysokoœæ) w razie potrzeby. U¿ywane analogicznie w ró¿nych
        // klasach jak powy¿sze metody:
        int getImageWidth( std::string attr );
        int getImageHeight( std::string attr );


    private:
        // Te konstruktury s¹ prywatne, poniewa¿ chcemy tylko raz utworzyæ statyczn¹ instancjê ResManager:
        ResManager();

        // Konstruktor kopiuj¹cy (dla kopiowania z jednej instancji danej klasy do drugiej instancji danej klasy)
        ResManager(const ResManager &) {};

        // Prze³adowanie operatora przypisania dla instancji tej klasy
        ResManager& operator=(const ResManager&);

        // WskaŸniki do adresów le¿¹cych w pamiêci zasobów. Do tych obiektów s¹ przypisywane istniej¹ce pliki zasobów w metodach loadImages():
        SDL_Surface* menu_img;
        SDL_Surface* selection_img;

        SDL_Surface* ball_img;
        SDL_Surface* paddle_img;
        SDL_Surface* paddle_war_img;
        SDL_Surface* bullet_img;
        SDL_Surface* blocks_img;

        SDL_Surface* gun_pack_img;
        SDL_Surface* slow_pack_img;
        SDL_Surface* dup_pack_img;
        SDL_Surface* live_pack_img;
};

#endif // RESMANAGER_H
