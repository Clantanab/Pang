//
// Created by Alumno on 23/06/2021.
//



#include <memory>
#include <basics/Scene>
#include <basics/Canvas>
#include <list>
#include <cstdlib>
#include <basics/Texture_2D>
#include "Weapons.hpp"
#include <basics/Atlas>



namespace Playable
{

   class Button{

    public:
        Button(float _posX, float _posY, float _width, float heigth);

        bool Touched(float touchX, float touchY);

        void render     (basics::Graphics_Context::Accessor & context);

        basics::Texture_2D * texture;


    private:

        float posX;
        float posY;
        float width;
        float heigth;


    };

    class Player{
    public:
        Player(float _posX, float _posY, float _speedX, float _width, float _heigth);

        void Update(float deltaTime);
        void render     (basics::Graphics_Context::Accessor & context);

        void Shoot();

        void Set_DirX(float _dirX);

        float Get_PositionX();
        float Get_PositionY();

        void Ouch(float EposX);

        bool permanent;
        bool machine_gun;

        const basics::Atlas::Slice* slices[8];
        basics::Atlas * atlas;

        void Load();

        int life = 3;
        bool invul;


        weapon::Bullet_Pool* bullet_Pool;
    private:
        float posX;
        float posY;
        float width;
        float heigth;
        float halfHeight;
        float halfWidth;
        float dirX;
        float speedX;

        float timerShot = 0;
        float max_shotTimer = 0.20;
        bool shotting = false;

        float timerOuch = 0;
        float max_OuchTimer = 0.20;
        bool damaged = false;
        float Epos;

        float invulTimer = 0;
        float max_InvulTime = 1;

        float timerMove= 0;
        int framePosition = 0;
        float maxTimeFrame = 0.10;
    };

}
