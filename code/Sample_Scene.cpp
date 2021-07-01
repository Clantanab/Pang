/*
 * SAMPLE SCENE
 * Copyright © 2018+ Ángel Rodríguez Ballesteros
 *
 * Distributed under the Boost Software License, version  1.0
 * See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt
 *
 * angel.rodriguez@esne.edu
 */

#include "menu.hpp"
#include <basics/Canvas>
#include <basics/Director>
#include <basics/Log>
#include <basics/Scaling>
#include <basics/Rotation>
#include <basics/Translation>

using namespace basics;
using namespace std;
using namespace Bubble;
using namespace Playable;
using namespace objects;

namespace example
{

    Sample_Scene::Sample_Scene()
    {
        canvas_width  = 1280;
        canvas_height =  720;

        //Inicializacion de pools, botones y powerUps
        pool = new Enemy_Pool(1);


        player = new Player(640, 80, 150, 70, 70);

        button_left = new Button(0, 0, 426, 720);
        button_right = new Button(853, 0, 1280, 720);
        shoot_button = new Button(426, 0, 853, 720);
        button_pause = new Button(100, 600, 75, 75);
        button_resume = new Button(550, 360, 220, 100 );
        button_help = new Button(550, 250, 220, 100 );
        button_quit = new Button(100, 600, 75, 75);

        power_Pool = new Power_Ups_Pool(1);



    }

    bool Sample_Scene::initialize ()
    {
        //Semilla del aleatorio
        srand(unsigned(time(nullptr)));

        state     = LOADING;
        suspended = false;
        x         = 640;
        y         = 360;

        dirX = 100;
        dirY = 100;

        time_suspended = false;



        return true;
    }

    void Sample_Scene::suspend ()
    {
        suspended = true;
    }

    void Sample_Scene::resume ()
    {
        suspended = false;
    }

    void Sample_Scene::handle (Event & event)
    {
        if (state == RUNNING)
        {

            switch (event.id)
            {
                case ID(touch-started):
                {
                    x = *event[ID(x)].as< var::Float > ();
                    y = *event[ID(y)].as< var::Float > ();

                    //Calculo de si alguno de los botones ha sido pausado
                    if(inHelp && button_quit->Touched(x,y)){
                        paused = true;
                        inHelp = false;
                    }
                    else if(!inHelp && button_pause->Touched(x,y)){
                        paused = true;
                    }
                    else if(!inHelp && paused && button_resume->Touched(x,y)){
                        paused = false;
                    }
                    else if(!inHelp && paused && button_help->Touched(x,y)){
                        paused= false;
                        inHelp = true;
                    }
                    else if(!inHelp && !paused && button_left->Touched(x,y))
                    {
                        player->Set_DirX(-1);
                    }
                    else if (!inHelp && !paused && button_right->Touched(x,y))
                    {
                        player->Set_DirX(1);
                    }
                    else if (!inHelp && !paused && shoot_button->Touched(x,y))
                    {
                        player->Shoot();
                    }
                    break;
                }
                case ID(touch-moved):
                case ID(touch-ended):
                {
                   /* x = *event[ID(x)].as< var::Float > ();
                    y = *event[ID(y)].as< var::Float > ();*/
                   player->Set_DirX(0);
                    break;
                }
            }
        }
    }

    void Sample_Scene::update (float time)
    {
        switch (state)
        {
            case LOADING: load ();     break;
            case RUNNING: run  (time); break;
        }
    }

    void Sample_Scene::render (basics::Graphics_Context::Accessor & context)
    {
        if (!suspended && state == RUNNING)
        {
            Canvas * canvas = context->get_renderer< Canvas > (ID(canvas));

            if (!canvas)
            {
                canvas = Canvas::create (ID(canvas), context, {{ canvas_width, canvas_height }});
            }

            if (canvas)
            {
                canvas->clear        ();
                canvas->set_color    (1, 1, 1);
                //Render del background
                if (texture)
                {
                    canvas->fill_rectangle ({ 640, 200 }, { 1280, 1200 }, texture.get ());
                }
                //Render de las vidas del jugador
                if(heart && player)
                {
                    for(int i = 0; i < player->life; ++i)
                    {
                        canvas->fill_rectangle ({ 900 +(i * 75) , 600 }, { 75, 75 }, heart.get ());
                    }
                }

                pool->render(context);
                //No hace falta renderizar estos porque queremos que sean transparentes
                //button_right->render(context);
                //button_left->render(context);
                //shoot_button->render(context);

                //Si estamos en pausa renderizamos los botones del menu de pausa
                if(inHelp){
                    canvas->fill_rectangle ({ 640, 360 }, { 1280, 760 }, helpScreen.get ());
                    button_quit->render(context);
                }
                else if(!inHelp && paused){
                    button_resume->render(context);
                    button_help->render(context);
                }
                //Si no renderizamos el boton de pausa
                else if(!inHelp){
                    button_pause->render(context);
                    //Render del player y powerUps
                    player->render(context);
                    power_Pool->render(context);
                }

            }
        }
    }

    void Sample_Scene::load ()
    {
        if (!suspended)
        {
            Graphics_Context::Accessor context = director.lock_graphics_context ();

            if (context)
            {
                //Load de texturas
                texture = Texture_2D::create (ID(background), context, "background.png");
                heart = Texture_2D::create (ID(corazon), context, "corazon.png");
                pause = Texture_2D::create(ID(pause), context, "pause.png" );
                resume_Texture = Texture_2D::create(ID(resume), context, "resume.png");
                help =  Texture_2D::create(ID(resume), context, "HelpButton.png");
                quit = Texture_2D::create(ID(quit), context, "quit.png");
                helpScreen = Texture_2D::create(ID(helpScreen), context, "helpScreen.png");

                //Si alguna no ha cargado, no le damos permiso al running
                if (texture && heart && pause && resume_Texture && help && quit)
                {
                    context->add (texture);
                    context->add(heart);
                    context->add( pause);
                    context->add( resume_Texture);
                    context->add(help);
                    context->add(quit);
                    context->add(helpScreen);

                    //Le pasamos a los botones sus texturas
                    button_pause->texture = pause.get();
                    button_resume->texture= resume_Texture.get();
                    button_help->texture = help.get();
                    button_quit->texture = quit.get();

                    state = RUNNING;
                }
                //Le pasamos a los pools los atlas de las animaciones
                pool->atlas = new Atlas("ballons.sprites", context);
                power_Pool->atlas = new Atlas("objects.sprites", context);
                player->atlas = new Atlas("player.sprites", context);
                player->Load();
                player->bullet_Pool->atlas = new Atlas("harpon.sprites", context);
                player->bullet_Pool->Load();
            }
        }
    }

    void Sample_Scene::run (float deltaTime )
    {


        if(paused) return;
        if(inHelp) return;

        //Update de las burbujas siempre que no esten congeladas por powerUp
        if(!time_suspended)
        {
            pool->Update(deltaTime);
        }
        else{
            timer_suspended += deltaTime;
            if(timer_suspended >= max_Time_Suspended)
            {
                time_suspended = false;
                timer_suspended = 0;
            }
        }

        //Recorremos la pool de burbujas para saber si queda alguna activa
        auto p = pool->Active_Enemys.begin();
        bool none_active = true;
        for(std::size_t i = 0; i <  pool->Active_Enemys.size() && p !=  pool->Active_Enemys.end() ; ++i , ++p)
        {
            if( p == pool->Active_Enemys.end() ) {
                // list too short
            }
            else {
                if(p->active){
                    none_active = false;
                }
            }
        }
        //Si no quedan burbujas activas o vidas al jugador, salimos
        if(none_active || player->life<1){
            timer_exit += deltaTime;
            if(timer_exit>max_TimeExit)
            {
                director.run_scene (std::shared_ptr< Scene >(new menu::menu));
            }
            return;
        }
        //Updates del jugador y powerUps
        player->Update(deltaTime);
        power_Pool->Update(deltaTime);


        //Collision de las balas con las burbujas
        //Recorremos la pool de balas
        auto ptr = player->bullet_Pool->Active_Bullets.begin();
        for(std::size_t i = 0; i < player->bullet_Pool->Active_Bullets.size() && ptr != this->player->bullet_Pool->Active_Bullets.end() ; ++i , ++ptr)
        {
            if( ptr == this->player->bullet_Pool->Active_Bullets.end() ) {
                // list too short
            }
            else {
                if(ptr->active)
                {
                    auto ptr2 = pool->Active_Enemys.begin();
                    //Recorremos la pool de burbujas
                    for(std::size_t j = 0; j < pool->Active_Enemys.size() && ptr2 != pool->Active_Enemys.end(); ++j, ++ptr2)
                    {
                        //si la burbuja esta activa y la bala tambien y los dos collisionan
                        if(ptr2->active && ptr->active && ptr->CheckCollision(ptr2->posX, ptr2->posY, ptr2->width, ptr2->heigth))
                        {
                            ptr->active = false;
                            ptr2->active = false;
                            ptr2->charged = false;

                            //Mientras que todavia tenga pahses se crean dos burbujas mas
                            if(ptr2->phase > 1)
                            {
                                float f = ptr2->phase - 1;
                                pool->Search_UnActive(ptr2->posX, ptr2->posY, ptr2->dirX , f);
                                pool->Search_UnActive(ptr2->posX, ptr2->posY, ptr2->dirX * -1, f);

                            }

                            //Probabilidad de creacion de un powerUP
                            int random = rand() % 10;

                            if(random < 5)
                            {
                                //Tipo de powerUP
                                random = rand() % 4;
                                basics::log.d(to_string(random));
                                power_Pool->Search_UnActive(ptr2->posX, ptr2->posY, 5, random);
                            }
                        }
                    }

                }
            }
        }
        //Collision de los powerUps con el player
        auto powerUp_ptr = this->power_Pool->All_Power_Ups.begin();
        //Recorremos la pool de powerUps
        for(std::size_t i = 0; i < this->power_Pool->All_Power_Ups.size() && powerUp_ptr != this->power_Pool->All_Power_Ups.end() ; ++i , ++powerUp_ptr)
        {
            if( powerUp_ptr == this->power_Pool->All_Power_Ups.end() ) {
                // list too short
            }
            else {
                if(powerUp_ptr->active)
                {

                    if(powerUp_ptr->CheckCollisionPlayer(player->Get_PositionX(), player->Get_PositionY()))
                    {
                        powerUp_ptr->active = false;

                        //Dependiendo del tipo de powerUp se realizan unas acciones u otras
                        switch(powerUp_ptr->type)
                        {
                            case 0:
                                this->time_suspended = true;
                                this->timer_suspended = 0;
                                this->max_Time_Suspended = 5;
                                break;
                            case 1:
                                player->permanent = false;
                                player->machine_gun = false;
                                player->bullet_Pool->Set_Max_Bullets(2);
                                break;
                            case 2:
                                player->permanent = true;
                                player->machine_gun = false;
                                player->bullet_Pool->Set_Max_Bullets(1);
                                break;
                            case 3:
                                player->machine_gun = true;

                        }
                    }
                }
            }
        }
        //Collision del jugador con las burbujas
        if(!player->invul)
        {
            auto ptr3 = pool->Active_Enemys.begin();
            //Recorremos la pool de burbujas
            for (std::size_t i = 0; i < pool->Active_Enemys.size() && ptr3 != pool->Active_Enemys.end(); ++i, ++ptr3)
            {
                if (ptr3 == this->pool->Active_Enemys.end()) {
                    // list too short
                }
                else {

                    if (ptr3->active) {
                        //Si colisiona y el jugador no es invulnerable
                        if (ptr3->CheckCollisionBullet(player->Get_PositionX(),player->Get_PositionY()) && !player->invul)
                        {
                            player->Ouch(ptr3->posX + ptr3->width/2);
                            player->invul = true;
                            player->life = player->life - 1;
                        }
                    }
                }
            }
        }




    }

}
