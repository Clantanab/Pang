//
// Created by Alumno on 23/06/2021.
//

#include "Playables.hpp"
#include <basics/Canvas>
#include <basics/Log>

using namespace basics;
using namespace std;
using namespace weapon;

namespace Playable{

    Button::Button(float _poX, float _posY, float _width, float _heigth)
    {
        this->posX = _poX;
        this->posY = _posY;
        this->width = _width;
        this->heigth = _heigth;

    }

    bool Button::Touched(float touchX, float touchY)
    {
        //Comprobamos si las coordenadas estan dentro del boton
        return touchX >= this->posX &&
                touchX <= (this->posX + this->width) &&
                touchY >= this->posY &&
                touchY <= (this->posY + this->heigth);

    }

    void Button::render(basics::Graphics_Context::Accessor &context)
    {
        auto * canvas = context->get_renderer< Canvas > (ID(canvas));
        //Render del boton, si tiene texturas renderiamoz la textura
        if (canvas)
        {
            canvas->fill_rectangle ({ this->posX, this->posY }, { this->width, this->heigth });

            if(texture)
            {
                canvas->fill_rectangle ({ this->posX + width/2, this->posY + heigth/2 }, { this->width, this->heigth }, texture);
            }
        }
    }

    //-------------------------------------------------------------------------------------------

    Player::Player(float _posX, float _posY, float _speedX, float _width, float _heigth)
    {
        this->posX = _posX;
        this->posY = _posY;
        this->speedX = _speedX;
        this->width = _width;
        this->heigth = _heigth;
        this->halfHeight = heigth/2;
        this->halfWidth = width/2;
        permanent = false;
        machine_gun = false;

        this->bullet_Pool = new Bullet_Pool(2);

        this->dirX = 0;
    }

    void Player::Load()
    {
        //Load de los slices
        slices[0] = atlas->get_slice(ID(1));
        slices[1] = atlas->get_slice(ID(2));
        slices[2] = atlas->get_slice(ID(3));
        slices[3] = atlas->get_slice(ID(4));
        slices[4] = atlas->get_slice(ID(5));
        slices[5] = atlas->get_slice(ID(6));
        slices[6] = atlas->get_slice(ID(7));
        slices[7] = atlas->get_slice(ID(8));

    }
    void Player::Shoot()
    {
        shotting = true;
        if(machine_gun)
        {
            this->bullet_Pool->Search_UnActive(this->posX + 10, this->posY + this->heigth, 550, permanent, machine_gun);
            this->bullet_Pool->Search_UnActive(this->posX - 10, this->posY + this->heigth, 550, permanent, machine_gun);
        }
        else{
            this->bullet_Pool->Search_UnActive(this->posX, this->posY + this->heigth, 500, permanent, machine_gun);
        }
    }
    float Player::Get_PositionY()
    {
        return this-> posY;
    }
    float Player::Get_PositionX()
    {
        return this->posX;
    }
    void Player::Set_DirX(float _dirX)
    {
        this->dirX = _dirX;
    }

    void Player::Update(float deltaTime)
    {
        this->posX += speedX * dirX * deltaTime;

        //Limites de movimiento del jugador
        if(this->posX - this->halfWidth < 0)
        {
            this->posX =halfWidth;
        }
        else if(this->posX + this->halfWidth > 1100)
        {
            this->posX = 1100 - halfWidth;
        }

        this->bullet_Pool->Update(deltaTime);
        //Si esta en movimiento le cambiamos la framposition
        if(dirX != 0)
        {
            timerMove += deltaTime;
            if(timerMove > maxTimeFrame)
            {
                framePosition++;
                timerMove=0;
                if(framePosition > 4)
                {
                    framePosition = 0;
                }
            }
        }
        else{
            timerMove = 0;
            framePosition = 1;
        }
        //Timer de la animacion de disparo
        if(shotting){
            timerShot+=deltaTime;
            if(timerShot > max_shotTimer){
                shotting=false;
                timerShot = 0;
            }
        }
        //Timer de la animacion de daño
        if(damaged){
            timerOuch += deltaTime;
            if(timerOuch > max_OuchTimer){
                damaged = false;
                timerOuch = 0;
            }
        }
        //Timer de la invulneravilidad
        if(invul){
            invulTimer += deltaTime;
            if(invulTimer > max_InvulTime){
                invul = false;
                invulTimer = 0;
            }
        }

    }

    void Player::Ouch(float EposX)
    {
        float f = posX - EposX;
        basics::log.d("OUCH");
        //Direcion en la que hacer la animacion dependiendo de la posicon del enemigo
        if(f>0){
            f = f/-f;
        }
        else{
           f = f/f;
        }
        this->Epos = f;
        damaged = true;
        timerOuch = 0;

        //Activamos la invulneravilidad
        invul = true;
        invulTimer = 0;

    }

    void Player::render(basics::Graphics_Context::Accessor &context)
    {
        auto * canvas = context->get_renderer< Canvas > (ID(canvas));

        if (canvas)
        {
            if(atlas)
            {
                const basics::Atlas::Slice *s;
                //Si se esta moviendo lo animamos dependiendo del framePosition
                if(abs(dirX) > 0.1 && !damaged){



                    s = slices[framePosition];

                    basics::log.d( to_string(framePosition));

                    if(s){
                        canvas->fill_rectangle( Point2f(posX , posY ), {width * dirX, heigth }, s );
                    }


                }
                else{
                    //Frame de cuando a recibido daño
                    if(damaged)
                    {
                        s = slices[7];

                        if(s){
                            canvas->fill_rectangle( Point2f(posX , posY ), {width * Epos, heigth }, s );
                        }
                    }
                    //Frame de cuando dispara
                    else if(shotting){
                        s = slices[6];

                        if(s){
                            canvas->fill_rectangle( Point2f(posX , posY ), {width, heigth }, s );
                        }
                    }
                    //Frame del idle
                    else{
                        s = slices[5];
                        if(s){
                            canvas->fill_rectangle( Point2f(posX , posY ), {width , heigth }, s );
                        }

                    }
                }


            }
        }

        this->bullet_Pool->render(context);
    }
}