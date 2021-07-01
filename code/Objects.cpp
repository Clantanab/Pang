//
// Created by Alumno on 24/06/2021.
//


#include "Objects.hpp"
#include <basics/Canvas>
#include <basics/Log>

using namespace basics;
using namespace std;


namespace objects{

    Power_Up::Power_Up(float _x, float _y, float _heigth, float _width, float _max_Duration, int _type, float _gravity)
    {
        this->x = _x;
        this->y = _x;
        this->heigth = _heigth;
        this->width = _width;
        this->max_Duration = _max_Duration;
        this->type = _type;
        this->gravity = _gravity;
        this->timer = 0;
        this->active = false;
    }


    void Power_Up::Update(float deltaTime)
    {
        //Timer de desaparicion
        this->timer += deltaTime;
        if(this->timer > this->max_Duration)
        {
            this->active = false;
        }
        //Si llega abajo dejamos de updatear
        if(this->y <= 60) return;
        //bajada
        this->y += gravity * deltaTime;
    }

    void Power_Up::render(basics::Graphics_Context::Accessor &context)
    {
        auto * canvas = context->get_renderer< Canvas > (ID(canvas));

        if (canvas)
        {
            canvas->fill_rectangle ({ x, y }, { this->width, this->heigth });
        }
    }
    void Power_Up::Prepare_Power_Up(float _x, float _y, float _max_Duration, int _type)
    {
        this->x = _x;
        this->y = _y;
        this->max_Duration = _max_Duration;
        this->type = _type;
        this->timer = 0;
        this->active = true;
    }

    bool Power_Up::CheckCollisionPlayer(float playerX, float playerY)
    {
        //Si las coordenadas estan dentro del objeto es que estan colisionando
        return playerX >= this->x &&
                playerX <= (this->x + this->width) &&
                playerY >= this->y &&
                playerY <= (this->y + this->heigth);

    }

    //------------------------------------------------------------------------------------------




    Power_Ups_Pool::Power_Ups_Pool(int number)
    {
        Power_Up* p;
        for(std::size_t a = 0; a < number; ++a)
        {
            p = new Power_Up(0, 0, 75, 75, 5, 1, -150);
            this->All_Power_Ups.push_back(*p);
            this->All_Power_Ups.push_back(*p);
        }

    }

    void Power_Ups_Pool::Update(float deltaTime)
    {
        auto ptr = this->All_Power_Ups.begin();
        //Recorremos la pool updateando PowerUp activos
        for(std::size_t i = 0; i < this->All_Power_Ups.size() && ptr != this->All_Power_Ups.end() ; ++i , ++ptr)
        {
            if( ptr == this->All_Power_Ups.end() ) {
                // list too short
            }
            else {
                if(ptr->active){
                    ptr->Update(deltaTime);
                }
            }
        }
    }

    void Power_Ups_Pool::render(basics::Graphics_Context::Accessor &context)
    {
        auto ptr = this->All_Power_Ups.begin();
        //Recorremos la pool renderizando powerUps actios
        for(std::size_t i = 0; i < this->All_Power_Ups.size() && ptr != this->All_Power_Ups.end() ; ++i , ++ptr)
        {
            if( ptr == this->All_Power_Ups.end() ) {
                // list too short
            }
            else{
                if(ptr->active){

                    if(atlas) {

                        const basics::Atlas::Slice *s;
                        //Dependiendo del tipo le damos un slice del atlas u otro
                        switch (__convert_to_integral(ptr->type)) {
                            case 3:
                                s = atlas->get_slice(ID(3));
                                break;
                            case 2:
                                s = atlas->get_slice(ID(2));
                                break;
                            case 1:
                                s = atlas->get_slice(ID(1));
                                break;
                            case 0:
                                s = atlas->get_slice(ID(0));
                                break;

                        }

                        if (s) {

                            auto *canvas = context->get_renderer<Canvas>(ID(canvas));

                            canvas->fill_rectangle(
                                    Point2f(ptr->x + ptr->width / 2, ptr->y + ptr->heigth / 2),
                                    {ptr->width, ptr->heigth}, s);

                        }
                    }

                }
            }
        }
    }

    void Power_Ups_Pool::Search_UnActive(float x, float y, float _max_Duration, int _type)
    {



        auto ptr = this->All_Power_Ups.begin();

        //Buscamos si hay powerUps que no esten activamos y los preparamos para el uso
        for(std::size_t i = 0; i < this->All_Power_Ups.size() && ptr != this->All_Power_Ups.end() ; ++i , ++ptr)
        {
            if( ptr == this->All_Power_Ups.end() ) {
                // list too short
            }
            else {
                if(!ptr->active){
                    ptr->active = true;
                    ptr->Prepare_Power_Up(x, y, _max_Duration, _type);
                    return;
                }
            }
        }
        //Si todos estan en uso creamos uno
        Power_Up* p;
        p = new Power_Up(x, y, 75, 75, 5, _type ,-150);
        p->active = true;
        this->All_Power_Ups.push_back(*p);
    }



}