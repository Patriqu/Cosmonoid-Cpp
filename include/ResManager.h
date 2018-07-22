#ifndef RESMANAGER_H
#define RESMANAGER_H

//#include <SDL.h>
#include <SDL.h>
#include "SDL_image.h"

#include <string>

#include "Image.h"

// Klasa Mened�er Zasob�w jest singletonem, poniewa� chc� aby utworzy�a si� pojedyncza instancja z dost�pem globalnym.
// Inne modu�y ca�ego programu maj� w razie potrzeby dost�p do r�nego rodzaju zasob�w, czyli Tekstury (obrazki), pliki
// d�wi�kowe i muzyczne. Te modu�y uzyskuj� dost�p w taki spos�b: ResManager:: getInstance().metoda();
// Do ka�dego modu�u, kt�ry wykorzystuje metody z ResManager nale�y zainkludowa� "ResManager.h"

// Utworzenie instancji, czyli pierwsze u�ycie ResManagera nast�puje w g��wnej klasie "main".
// Wtedy po uruchomieniu gry, przed g��wn� p�tl� gry nast�puje za�adowanie do pami�ci obrazk�w Paletki, blok�w i pi�ki
// Robimy to w ten spos�b: ResManager:: getInstance().loadMainImages();

class ResManager
{
    public:
        // Destruktor musi by� publiczny (w singletonie r�wnie�), w przeciwnym razie wyst�pi b��d:
        virtual ~ResManager();

        // Metoda za pierwszym razem tworz�ca jedyn�, statyczn� instancj� klasy ResManager. P�niej tego nie robi,
        // poniewa� sprawdza, �e ten obiekt statyczny jest ju� utworzony:
        static ResManager getInstance()
        {
          //Inicjalizacja statycznego obiektu.
          //Obiekt zostanie utworzony przy pierwszym wywo�aniu tej metody
          //i tylko wtedy nast�pi inicjalizacja przy pomocy konstruktora.
          //Ka�de nast�pne wywo�anie jedynie zwr�ci referencj� tego obiektu.

          // res_manager = new ResManager();

          static ResManager res_manager;
          return res_manager;
        }

        // Za�adowanie g��wnych obrazk�w gry do pami�ci:
        // void loadMainImages();
        SDL_Surface* loadImageMenu(std:: string res);
        SDL_Surface* loadImageSelection();

        SDL_Surface* loadImageBall();
        SDL_Surface* loadImagePaddle();
        SDL_Surface* loadImagePaddleWar();
        SDL_Surface* loadImageBullet();
        SDL_Surface* loadImageBlocks();

        // �adowanie obrazk�w bonus�w:
        SDL_Surface* loadImageGunPack();
        SDL_Surface* loadImageSlowPack();
        SDL_Surface* loadImageDupPack();
        SDL_Surface* loadImageLivePack();

        // Metody u�ywane do pobierania zasob�w, kt�re wybrali�my jako parametr metody w razie potrzeby.
        // U�ywane w r�nych klasach operuj�cych na obiektach zasob�w gry:
        SDL_Surface* getImage ( std:: string img );

        // Pobierz kolor t�a ekranu:
        SDL_Color getBgdColor();

        // Pobieranie informacji o r�nych obrazkach (np. wysoko��) w razie potrzeby. U�ywane analogicznie w r�nych
        // klasach jak powy�sze metody:
        int getImageWidth( std::string attr );
        int getImageHeight( std::string attr );


    private:
        // Te konstruktury s� prywatne, poniewa� chcemy tylko raz utworzy� statyczn� instancj� ResManager:
        ResManager();

        // Konstruktor kopiuj�cy (dla kopiowania z jednej instancji danej klasy do drugiej instancji danej klasy)
        ResManager(const ResManager &) {};

        // Prze�adowanie operatora przypisania dla instancji tej klasy
        ResManager& operator=(const ResManager&);

        // Wska�niki do adres�w le��cych w pami�ci zasob�w. Do tych obiekt�w s� przypisywane istniej�ce pliki zasob�w w metodach loadImages():
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
