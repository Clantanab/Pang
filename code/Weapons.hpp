//
// Created by Alumno on 23/06/2021.
//

#ifndef BASICS_PROJECT_TEMPLATE_WEAPONS_H
#define BASICS_PROJECT_TEMPLATE_WEAPONS_H

#endif //BASICS_PROJECT_TEMPLATE_WEAPONS_H

#include <memory>
#include <basics/Scene>
#include <basics/Canvas>
#include <basics/Atlas>
#include <basics/Texture_2D>
#include <list>
#include <cstdlib>


namespace weapon
{

    class Bullet{
    public:

        Bullet(float _x, float _y, float _width, float _speedY, bool _permanent, bool _bullet_Type);

        void Prepare_Bullet(float _x, float _y, float _width, float _speedY, bool _permanent, bool _bullet_Type);

        void Update(float deltaTime);
        void render     (basics::Graphics_Context::Accessor & context);



        bool CheckCollision(float EPosX, float EPosY, float EWidth, float EHeigth);
        bool active;

        bool bullet_type;

        bool loaded = false;

        int framePosition=0;
        float timer= 0;
        float max_Timer = 0.015;
        bool permanent;
        float x;
        float y;
        float width;
        float height;
        float halfWidth;
        float halfHeith;
    private:

        float speedY;

    };

    class Bullet_Pool{


    public:

        Bullet_Pool(int number);
        void Search_UnActive(float x, float y, float speed, bool permanent, bool _bullet_Type);
        void DeactivateEnemy(Bullet e);
        void Update(float deltaTime);
        void render     (basics::Graphics_Context::Accessor & context);
        void Set_Max_Bullets(float max);
        void Load();

        const basics::Atlas::Slice* slices[142];

        std::list< Bullet> Active_Bullets;

        basics::Atlas * atlas;


    private:
        std::list<Bullet> All_Bullets;
        float max_Bullets_Active;
    };

}