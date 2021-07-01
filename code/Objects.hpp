//
// Created by Alumno on 24/06/2021.
//

#ifndef BASICS_PROJECT_TEMPLATE_OBJECTS_HPP
#define BASICS_PROJECT_TEMPLATE_OBJECTS_HPP

#endif //BASICS_PROJECT_TEMPLATE_OBJECTS_HPP

#include <memory>
#include <basics/Scene>
#include <basics/Canvas>
#include <basics/Atlas>
#include <list>
#include <cstdlib>


namespace objects{

    class Power_Up{
    public:
        Power_Up(float _x, float _y, float _heigth, float _width, float _max_Duration, int _type, float _gravity);

        void Update(float deltaTime);
        void render     (basics::Graphics_Context::Accessor & context);
        void Prepare_Power_Up(float _x, float _y, float _max_Duration, int _type);

        bool CheckCollisionPlayer(float playerX, float playerY);


        int type;
        bool active;
        float x;
        float y;
        float heigth;
        float width;
    private:

        float max_Duration;
        float timer;
        float gravity;


    };


    class Power_Ups_Pool{


    public:

        Power_Ups_Pool(int number);

        void Search_UnActive(float x, float y, float _max_Duration, int _type);

        void Update(float deltaTime);
        void render     (basics::Graphics_Context::Accessor & context);

        std::list<Power_Up> All_Power_Ups;

        basics::Atlas* atlas;


    private:

    };
}