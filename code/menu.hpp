//
// Created by Alumno on 30/06/2021.
//

#ifndef BASICS_PROJECT_TEMPLATE_MENU_HPP
#define BASICS_PROJECT_TEMPLATE_MENU_HPP

#endif //BASICS_PROJECT_TEMPLATE_MENU_HPP


#include "Sample_Scene.hpp"
#include <basics/Scene>
#include <basics/Texture_2D>



namespace menu{

    class menu : public basics::Scene{

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

        Playable::Button *button_play;

        float          x, y;

        std::shared_ptr< basics::Texture_2D > play;

    public:

        menu();

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


    };

}