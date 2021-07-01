//
// Created by Alumno on 30/06/2021.
//


#include "intro.hpp"
#include <basics/Director>


using namespace basics;

namespace intro
{



    intro::intro()
    {
        canvas_width  = 1280;
        canvas_height =  720;
    }

    bool intro::initialize ()
    {

        state     = LOADING;
        suspended = false;
        x         = 640;
        y         = 360;

        return true;
    }


    void intro::suspend ()
    {
        suspended = true;
    }

    void intro::resume ()
    {
        suspended = false;
    }

    void intro::handle (Event & event)
    {
        if (state == RUNNING)
        {

            switch (event.id)
            {
                case ID(touch-started):
                {
                }
                case ID(touch-moved):
                case ID(touch-ended):
                {
                    break;
                }
            }
        }
    }

    void intro::update (float time)
    {
        switch (state)
        {
            case LOADING: load ();     break;
            case RUNNING: run  (time); break;
        }
    }

    void intro::render (basics::Graphics_Context::Accessor & context)
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

                if(logo)
                {
                    canvas->fill_rectangle ({ 600, 400 }, { 300, 300 }, logo.get ());
                }

            }
        }
    }

    void intro::load ()
    {
        if (!suspended)
        {
            Graphics_Context::Accessor context = director.lock_graphics_context ();

            if (context)
            {
                logo = Texture_2D::create (ID(esne), context, "esne.png");

                if(logo)
                {
                    context->add(logo);
                    state = RUNNING;
                }
            }
        }
    }

    void intro::run(float time)
    {
        //Cuando pase el tiempo estimado cambiamos de escena
        timer += time;
        if(timer > max_timer)
        {
            director.run_scene (std::shared_ptr< Scene >(new menu::menu));
        }
    }
}
