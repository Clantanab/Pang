//
// Created by Alumno on 21/06/2021.
//

#include "Bubble.hpp"
#include <basics/Canvas>
#include <basics/Log>

using namespace basics;
using namespace std;

namespace Bubble{

    Enemy::Enemy(float _x , float _y, float _phase, float _dirX ,float _gravity_Speed , float _jump_Heith)
    {
        posX = _x;
        posY = _y;
        phase = _phase;
        jump_Heith = _jump_Heith * phase;
        temporal_Jump_Heith = _y;

        width = 50 * phase;
        heigth = 50 * phase;


        dirX = _dirX;
        gravity_Speed = _gravity_Speed / phase;
        this->jump_Speed = this->gravity_Speed * -1;
        orignial_Speed = jump_Speed;

        jump_Distance = posY;
        falling = true;
        active = true;

    }

    void Enemy::Set_dirX(float _dirX)
    {
        dirX = _dirX;
    }

    void Enemy::Set_Pos(float _x, float _y)
    {
        posX = _x;
        posY = _y;
    }

    void Enemy::Set_Phase(float _phase)
    {
        phase = _phase;
    }

    void Enemy::Hit()
    {

    }
    void Enemy::Update(float deltaTime)
    {
        //Si esta cayendo
        if(falling)
        {
            //La velocidad es negativa
            posY = posY + (jump_Speed * deltaTime * -1);

            //Desacelerar considerando la distancia recorrida de salto
            //Reducimos la altura con el suelo
            jump_Distance = jump_Distance - (jump_Speed * deltaTime) ;

            float c;
            //En caso de que sea el primera caida y este mas alto de lo que deberia
            if(temporal_Jump_Heith != 0){
                c = (jump_Distance/temporal_Jump_Heith);
            }//Coeficiente entre la altura recorrida y la altura maxima de salto
            else{
                c = (jump_Distance / jump_Heith);
            }
            //Reducimos o aumentamos la velocidad segun el coeficiente
            jump_Speed = orignial_Speed - (orignial_Speed * (c * c)) + 10;


        }
        //Si esta saltando
        if(!falling){
            //la velocidad es positiva
            posY = posY + (jump_Speed * deltaTime);

            //Desacelerar considerando la distancia recorrida de salto (no funciona, demasiado lento)

            //aumentamos la distancia de salto recorrida
            jump_Distance =   jump_Distance + (jump_Speed * deltaTime);
            //coeficiente entre la altura recorrida y la altura maxima de salto
            float c = (jump_Distance / jump_Heith);
            //basics::log.d( to_string(c));
            //reducimos la velocidad segun el coeficiente
            jump_Speed = orignial_Speed - (orignial_Speed * (c * c)) + 10;
            //SI la altura de salto es mayor que la altura maxima invertimos el moviemiento
            if(jump_Distance >= jump_Heith)
            {
                falling = true;
                jump_Distance = jump_Heith;
            }
        }
        //Si choca contra el suelo invertimos el movimiento y ponemos a cero la altura temporal
        else if (posY < 60)
        {
            falling = false;
            this->jump_Speed = gravity_Speed * -1;
            jump_Distance = 0;
            temporal_Jump_Heith = 0;


        }

        posX = posX + (dirX * deltaTime);
        //Choque contra las paredes laterales
        if((this->posX + this->width)  > 1100 || this->posX < 0)
        {
            dirX = dirX * -1;
        }
    }
    void Enemy::render(basics::Graphics_Context::Accessor &context)
    {
        Canvas * canvas = context->get_renderer< Canvas > (ID(canvas));

        if (canvas)
        {
            canvas->fill_rectangle ({ this->posX, this->posY }, { this->width, this->heigth });
        }
    }
    void Enemy::Split() {}

    bool Enemy::CheckCollisionBullet(float bulletX, float bulletY)
    {
        //Realemente calcula si choca contra el jugador
        return bulletX >= this->posX &&
                bulletX <= (this->posX + this->width) &&
                bulletY >= this->posY &&
                bulletY <= (this->posY + this->heigth);

    }

    void Enemy::Prepare_Bubble(float _x, float _y, float _phase, float _dirX, float _gravity_Speed, float _jumpHeith)
    {
        this->posX = _x;
        this->posY = _y;
        this->phase = _phase;
        falling = true;
        this->dirX = _dirX;
        this->gravity_Speed = _gravity_Speed / phase;
        this->jump_Heith = _jumpHeith * phase;

        this->width = 50 * phase;
        this->heigth = 50 * phase;

        this->jump_Speed = this->gravity_Speed * -1;
        this->orignial_Speed = jump_Speed;

        this->jump_Distance = posY;
        this->temporal_Jump_Heith = _y;
        active = true;

    }



    //---------------------------------------------------------------------------------------------


    Enemy_Pool::Enemy_Pool(int number)
    {
        Enemy* e;
        for(std::size_t a = 0; a < number; ++a)
        {
            e = new Enemy(400, 300, 4, -50, -600, 150);
            this->Active_Enemys.push_back(*e);
        }

    }
    void Enemy_Pool::Update(float deltaTime)
    {
        auto ptr = this->Active_Enemys.begin();
        //Recorremos la pool de burbujas y updateamos las activas
        for(std::size_t i = 0; i < this->Active_Enemys.size() && ptr != this->Active_Enemys.end() ; ++i , ++ptr)
        {
            if( ptr == this->Active_Enemys.end() ) {
                // list too short
            }
            else {
                if(ptr->active){
                    ptr->Update(deltaTime);
                }
            }
        }
    }

    void Enemy_Pool::render(basics::Graphics_Context::Accessor &context)
    {
        auto ptr = this->Active_Enemys.begin();
        //Renderizamos las burbujas activamos de la pool depnediendo de su tipo
        for(std::size_t i = 0; i < this->Active_Enemys.size() && ptr != this->Active_Enemys.end() ; ++i , ++ptr)
        {
            if( ptr == this->Active_Enemys.end() ) {
                // list too short
            }
            else{
                if(ptr->active)
                {
                    if(atlas)
                    {
                       const basics::Atlas::Slice* s;

                       switch (__convert_to_integral(ptr->phase)){
                           case 4:
                               s = atlas->get_slice(ID(3));
                               break;
                           case 3:
                               s = atlas->get_slice(ID(2));
                               break;
                           case 2:
                               s = atlas->get_slice(ID(1));
                               break;
                           case 1:
                               s = atlas->get_slice(ID(0));
                               break;

                       }


                       if(s)
                       {

                           auto * canvas = context->get_renderer< Canvas > (ID(canvas));

                           canvas->fill_rectangle( Point2f(ptr->posX + ptr->width/2, ptr->posY + ptr->heigth/2), {ptr->width, ptr->heigth}, s );

                       }
                    }
                    else{
                        ptr->render(context);
                    }
                }

            }
        }
    }

    void Enemy_Pool::DeactivateEnemy(Enemy e)
    {
        e.active = false;
    }
    void Enemy_Pool::Search_UnActive(float x, float y, float dirX, float phase)
    {

        auto ptr = this->Active_Enemys.begin();
        //Recorremos la pool en busca de burbujas inactivamos y las preparamos para el uso
        for(std::size_t i = 0; i < this->Active_Enemys.size() && ptr != this->Active_Enemys.end() ; ++i , ++ptr)
        {
            if( ptr == this->Active_Enemys.end() ) {
                // list too short
            }
            else {
                if(!ptr->active){
                      ptr->Prepare_Bubble(x, y, phase,dirX, -600, 150 );
                      return;
                }
            }
        }
        //Si estan todas activas creamos una nueva burbuja
        Enemy* e;
        e = new Enemy(x, y, phase, dirX, -600, 150);
        this->Active_Enemys.push_back(*e);
    }
//-----------------------------------------------------------------------------------------------

}
