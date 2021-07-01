//
// Created by Alumno on 30/06/2021.
//

#ifndef BASICS_PROJECT_TEMPLATE_INTRO_HPP
#define BASICS_PROJECT_TEMPLATE_INTRO_HPP

#endif //BASICS_PROJECT_TEMPLATE_INTRO_HPP

#include "menu.hpp"
#include <basics/Scene>
#include <basics/Texture_2D>



namespace intro{

    class intro : public basics::Scene{

    public:
        enum State
        {
            LOADING,
            RUNNING,
        };

        State          state;
        bool           suspended;

        unsigned       canvas_width;
        unsigned       canvas_height;

        float          x, y;

        std::shared_ptr< basics::Texture_2D > logo;

    public:

        intro();

        basics::Size2u get_view_size () override
        {
            return { canvas_width, canvas_height };
        }

        bool initialize () override;
        void suspend    () override;
        void resume     () override;

        void handle     (basics::Event & event) override;
        void update     (float time) override;
        void render     (basics::Graphics_Context::Accessor & context) override;


    private:

        void load ();
        void run  (float time);


        float timer=0;
        float max_timer=1.25;

    };

}