//
// Created by Alumno on 30/06/2021.
//


#include "menu.hpp"
#include <basics/Director>
#include <basics/Log>


using namespace basics;

namespace menu
{



    menu::menu()
    {
        canvas_width  = 1280;
        canvas_height =  720;

        button_play = new Playable::Button(500, 360, 420, 75);
    }

    bool menu::initialize ()
    {

        state     = LOADING;
        suspended = false;
        x         = 640;
        y         = 360;

        return true;
    }


    void menu::suspend ()
    {
        suspended = true;
    }

    void menu::resume ()
    {
        suspended = false;
    }

    void menu::handle (Event & event)
    {
        if (state == RUNNING)
        {

            switch (event.id)
            {
                case ID(touch-started):
                {
                    //Si se presiona el boton cambiamos de escena
                    if(button_play->Touched(x,y)){
                        director.run_scene (std::shared_ptr< Scene >(new example::Sample_Scene));
                    }
                }
                case ID(touch-moved):
                case ID(touch-ended):
                {
                    break;
                }
            }
        }
    }

    void menu::update (float time)
    {
        switch (state)
        {
            case LOADING: load ();     break;
            case RUNNING: run  (time); break;
        }
    }

    void menu::render (basics::Graphics_Context::Accessor & context)
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

                if(play)
                {
                    canvas->fill_rectangle ({ 600, 400 }, { 300, 300 }, play.get ());
                }

            }
        }
    }

    void menu::load ()
    {
        basics::log.d( "HEMOS ACERTADO BOYS");
        if (!suspended)
        {
            Graphics_Context::Accessor context = director.lock_graphics_context ();

            if (context)
            {
                play = Texture_2D::create(ID(esne), context, "resume.png");

                if(play)
                {
                    context->add(play);
                    button_play->texture = play.get();

                    state = RUNNING;
                }
            }
        }
    }

    void menu::run(float time)
    {

    }
}