//
// Created by Alumno on 21/06/2021.
//





#include <memory>
#include <basics/Id>
#include <basics/Scene>
#include <basics/Atlas>
#include <basics/Canvas>
#include <list>
#include <basics/Texture_2D>



#include <cstdlib>

namespace Bubble
{



    class Enemy{

    public:

        Enemy(float _x , float _y, float _phase, float _dirX, float _gravity_Speed, float _jump_Heith);

        float posX, posY, jump_Heith, dirX, gravity_Speed;
        float phase;
        bool falling;
        bool active;
        float width;
        float heigth;
        float rectangle[4];

        void Set_Pos(float _x , float _y);
        void Set_Phase(float _phase);
        void Set_dirX(float _dirX);
        void Hit();
        void Prepare_Bubble(float _x, float _y, float _phase, float _dirX, float _gravity_Speed, float _jumpHeith);



        void Update(float deltaTime);
        void render     (basics::Graphics_Context::Accessor & context);
        void Split();

        bool CheckCollisionBullet(float bulletX, float bulletY);

        float temporal_Jump_Heith;
        bool charged = false;

    private:

        float jump_Speed;
        float jump_Distance;
        float orignial_Speed;



    };

    class Enemy_Pool{


    public:

        Enemy_Pool(int number);
        void Search_UnActive(float x, float y, float dirX, float phase);
        void DeactivateEnemy(Enemy e);
        void Update(float deltaTime);
        void render     (basics::Graphics_Context::Accessor & context);

        std::list< Enemy> Active_Enemys;

        basics::Atlas* atlas;



    };




}


