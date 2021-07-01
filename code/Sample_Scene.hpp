/*
 * SAMPLE SCENE
 * Copyright © 2018+ Ángel Rodríguez Ballesteros
 *
 * Distributed under the Boost Software License, version  1.0
 * See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt
 *
 * angel.rodriguez@esne.edu
 */

#include "Playables.hpp"
#include <list>
#include <basics/Atlas>
#include <map>
#include <memory>
#include <basics/Scene>
#include <basics/Texture_2D>
#include <basics/Id>
#include <cstdlib>
#include "Bubble.hpp"
#include "Objects.hpp"



namespace example
{

    class Sample_Scene : public basics::Scene
    {

        typedef std::shared_ptr< basics::Texture_2D > Texture_Handle;
        typedef std::map < basics::Id, Texture_Handle> Texture_Map;

    public:

        enum State
        {
            LOADING,
            RUNNING,
        };

        State          state;
        bool           suspended;
        bool paused;
        bool inHelp = false;

        unsigned       canvas_width;
        unsigned       canvas_height;

        Texture_Handle texture, background, heart, pause, resume_Texture, help, helpScreen, quit;
        float          x, y, dirX, dirY;




    public:

        Sample_Scene();

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

        Bubble::Enemy_Pool *pool;

        Playable::Button *button_right;
        Playable::Button *button_left;
        Playable::Button *shoot_button;
        Playable::Button *button_pause, *button_resume, *button_help, *button_quit;


        Playable::Player *player;

        objects::Power_Ups_Pool *power_Pool;

        bool time_suspended ;
        float timer_suspended = 0;
        float max_Time_Suspended = 5;

        float timer_exit=0;
        float max_TimeExit = 2;

        Texture_Map    textures;


        static struct Texture_Data { basics::Id id; const char * path; } textures_data[];

        static unsigned textures_count;

    };

}
