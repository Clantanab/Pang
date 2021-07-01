//
// Created by Alumno on 23/06/2021.
//

#include "Weapons.hpp"
#include <basics/Canvas>
#include <basics/Log>

using namespace basics;
using namespace std;

namespace weapon{

    Bullet::Bullet(float _x, float _y, float _width, float _speedY, bool _permanent, bool _bullet_Type)
    {
        this->x = _x;
        this->y = _y;
        this->width = _width;
        this->halfWidth = _width/2;

        this->height = 15;

        this->speedY = _speedY;
        //Si la bala es del tipo permanente
        this->permanent = _permanent;
        //Si la bala es del tipo machine gun
        this->bullet_type = _bullet_Type;

        if(bullet_type)
        {
            height = 10;
            halfHeith = 5;
        }
        this->active = false;
    }

    void Bullet::Update(float deltaTime)
    {
        //Si esta parada saltamos el update
        if(speedY <= 0) return;
        //Si es del tipo machine gun, cambiamos su posY y la desactivamos al chocar el techo
        if(bullet_type)
        {
            this->y += speedY * deltaTime;
            if(y + height > 720)
            {
                this->active = false;
                height = 0;

            }
        }
        //Los otros tipos de balas crece la altura y dependiendo de si son permanentes o no
        //desactivamos si llegan al techo
        else{
            this->height += speedY * deltaTime;
            if(y + height > 720)
            {
                if(permanent)
                {
                    speedY = 0;
                }
                else{
                    this->active = false;
                    height = 0;
                }

            }
        }
        //Funcionamiento de la animacion
        timer += deltaTime;
        if(timer > max_Timer)
        {
            ++framePosition;
            timer = 0;
            if(framePosition >69)
            {
                framePosition = 0;
            }
        }

    }

    void Bullet::render(basics::Graphics_Context::Accessor &context)
    {
        auto * canvas = context->get_renderer< Canvas > (ID(canvas));
        //Render dependiendo de si son machine gun o no
        if (canvas)
        {
            if(bullet_type)
            {
                canvas->fill_rectangle ({ x-halfWidth, y - halfHeith }, { this->width, this->height });
            }
            else{
                canvas->fill_rectangle ({ x-halfWidth, y }, { this->width, this->height });
            }

        }
    }

    bool Bullet::CheckCollision(float EPosX, float EPosY, float EWidth, float EHeith)
    {
        //Si son del tipo machine gun calculamos si el centro de la bala esta dentro de la burbuja enemiga
        if(this->bullet_type)
        {
            return (this->x >= EPosX) && this->x <= (EPosX + EWidth) && this-> y >= EPosY && this->y <= (EPosY + EHeith);
        }
        //Si no calculamos si tienen la misma x y si la bala esta en una posicion mas alta que la burbuja
        else{
            if( this->x >= EPosX && this->x <= (EPosX + EWidth))
            {
                return (this-> y + this-> height) >= EPosY;

            }
        }
        return  false;
    }

    void Bullet::Prepare_Bullet(float _x, float _y, float _width, float _speedY, bool _permanent, bool _bullet_Type)
    {
        this->x = _x;
        this->y = _y;
        this->width = _width;
        this->halfWidth = _width/2;
        this->height = 15;
        this->speedY = _speedY;
        this->permanent = _permanent;
        this->bullet_type = _bullet_Type;
        if(bullet_type){
            height = 10;
            halfHeith = height/2;
        }
        this->active = true;
    }

    //-------------------------------------------------------------------------------------




    Bullet_Pool::Bullet_Pool(int number)
    {

        Bullet* b;
        for(std::size_t a = 0; a < number; ++a)
        {
            b = new Bullet(0, 0, 25, 125, false, false);
            this->Active_Bullets.push_back(*b);
            this->All_Bullets.push_back(*b);
        }
        this->max_Bullets_Active = number;

    }
    void Bullet_Pool::Load()
    {
        //Load de los slices
        slices[0] = atlas->get_slice(ID(0));
        slices[1] = atlas->get_slice(ID(1));
        slices[2] = atlas->get_slice(ID(2));
        slices[3] = atlas->get_slice(ID(3));
        slices[4] = atlas->get_slice(ID(4));
        slices[5] = atlas->get_slice(ID(5));
        slices[6] = atlas->get_slice(ID(6));
        slices[7] = atlas->get_slice(ID(7));
        slices[8] = atlas->get_slice(ID(8));
        slices[9] = atlas->get_slice(ID(9));
        slices[10] = atlas->get_slice(ID(10));
        slices[11] = atlas->get_slice(ID(11));
        slices[12] = atlas->get_slice(ID(12));
        slices[13] = atlas->get_slice(ID(13));
        slices[14] = atlas->get_slice(ID(14));
        slices[15] = atlas->get_slice(ID(15));
        slices[16] = atlas->get_slice(ID(16));
        slices[17] = atlas->get_slice(ID(17));
        slices[18] = atlas->get_slice(ID(18));
        slices[19] = atlas->get_slice(ID(19));
        slices[20] = atlas->get_slice(ID(20));
        slices[21] = atlas->get_slice(ID(21));
        slices[22] = atlas->get_slice(ID(22));
        slices[23] = atlas->get_slice(ID(23));
        slices[24] = atlas->get_slice(ID(24));
        slices[25] = atlas->get_slice(ID(25));
        slices[26] = atlas->get_slice(ID(26));
        slices[27] = atlas->get_slice(ID(27));
        slices[28] = atlas->get_slice(ID(28));
        slices[29] = atlas->get_slice(ID(29));
        slices[30] = atlas->get_slice(ID(30));
        slices[31] = atlas->get_slice(ID(31));
        slices[32] = atlas->get_slice(ID(32));
        slices[33] = atlas->get_slice(ID(33));
        slices[34] = atlas->get_slice(ID(34));
        slices[35] = atlas->get_slice(ID(35));
        slices[36] = atlas->get_slice(ID(36));
        slices[37] = atlas->get_slice(ID(37));
        slices[38] = atlas->get_slice(ID(38));
        slices[39] = atlas->get_slice(ID(39));
        slices[40] = atlas->get_slice(ID(40));
        slices[41] = atlas->get_slice(ID(41));
        slices[42] = atlas->get_slice(ID(42));
        slices[43] = atlas->get_slice(ID(43));
        slices[44] = atlas->get_slice(ID(44));
        slices[45] = atlas->get_slice(ID(45));
        slices[46] = atlas->get_slice(ID(46));
        slices[47] = atlas->get_slice(ID(47));
        slices[48] = atlas->get_slice(ID(48));
        slices[49] = atlas->get_slice(ID(49));
        slices[50] = atlas->get_slice(ID(50));
        slices[51] = atlas->get_slice(ID(51));
        slices[52] = atlas->get_slice(ID(52));
        slices[53] = atlas->get_slice(ID(53));
        slices[54] = atlas->get_slice(ID(54));
        slices[55] = atlas->get_slice(ID(55));
        slices[56] = atlas->get_slice(ID(56));
        slices[57] = atlas->get_slice(ID(57));
        slices[58] = atlas->get_slice(ID(58));
        slices[59] = atlas->get_slice(ID(59));
        slices[60] = atlas->get_slice(ID(60));
        slices[61] = atlas->get_slice(ID(61));
        slices[62] = atlas->get_slice(ID(62));
        slices[63] = atlas->get_slice(ID(63));
        slices[64] = atlas->get_slice(ID(64));
        slices[65] = atlas->get_slice(ID(65));
        slices[66] = atlas->get_slice(ID(66));
        slices[67] = atlas->get_slice(ID(67));
        slices[68] = atlas->get_slice(ID(68));
        slices[69] = atlas->get_slice(ID(69));
        slices[70] = atlas->get_slice(ID(70));
        slices[71] = atlas->get_slice(ID(71));
        slices[72] = atlas->get_slice(ID(72));
        slices[73] = atlas->get_slice(ID(73));
        slices[74] = atlas->get_slice(ID(74));
        slices[75] = atlas->get_slice(ID(75));
        slices[76] = atlas->get_slice(ID(76));
        slices[77] = atlas->get_slice(ID(77));
        slices[78] = atlas->get_slice(ID(78));
        slices[79] = atlas->get_slice(ID(79));
        slices[80] = atlas->get_slice(ID(80));
        slices[81] = atlas->get_slice(ID(81));
        slices[82] = atlas->get_slice(ID(82));
        slices[83] = atlas->get_slice(ID(83));
        slices[84] = atlas->get_slice(ID(84));
        slices[85] = atlas->get_slice(ID(85));
        slices[86] = atlas->get_slice(ID(86));
        slices[87] = atlas->get_slice(ID(87));
        slices[88] = atlas->get_slice(ID(88));
        slices[89] = atlas->get_slice(ID(89));
        slices[90] = atlas->get_slice(ID(90));
        slices[91] = atlas->get_slice(ID(91));
        slices[92] = atlas->get_slice(ID(92));
        slices[93] = atlas->get_slice(ID(93));
        slices[94] = atlas->get_slice(ID(94));
        slices[95] = atlas->get_slice(ID(95));
        slices[96] = atlas->get_slice(ID(96));
        slices[97] = atlas->get_slice(ID(97));
        slices[98] = atlas->get_slice(ID(98));
        slices[99] = atlas->get_slice(ID(99));
        slices[100] = atlas->get_slice(ID(100));
        slices[101] = atlas->get_slice(ID(101));
        slices[102] = atlas->get_slice(ID(102));
        slices[103] = atlas->get_slice(ID(103));
        slices[104] = atlas->get_slice(ID(104));
        slices[105] = atlas->get_slice(ID(105));
        slices[106] = atlas->get_slice(ID(106));
        slices[107] = atlas->get_slice(ID(107));
        slices[108] = atlas->get_slice(ID(108));
        slices[109] = atlas->get_slice(ID(109));
        slices[110] = atlas->get_slice(ID(110));
        slices[111] = atlas->get_slice(ID(111));
        slices[112] = atlas->get_slice(ID(112));
        slices[113] = atlas->get_slice(ID(113));
        slices[114] = atlas->get_slice(ID(114));
        slices[115] = atlas->get_slice(ID(115));
        slices[116] = atlas->get_slice(ID(116));
        slices[117] = atlas->get_slice(ID(117));
        slices[118] = atlas->get_slice(ID(118));
        slices[119] = atlas->get_slice(ID(119));
        slices[120] = atlas->get_slice(ID(120));
        slices[121] = atlas->get_slice(ID(121));
        slices[122] = atlas->get_slice(ID(122));
        slices[123] = atlas->get_slice(ID(123));
        slices[124] = atlas->get_slice(ID(124));
        slices[125] = atlas->get_slice(ID(125));
        slices[126] = atlas->get_slice(ID(126));
        slices[127] = atlas->get_slice(ID(127));
        slices[128] = atlas->get_slice(ID(128));
        slices[129] = atlas->get_slice(ID(129));
        slices[130] = atlas->get_slice(ID(130));
        slices[131] = atlas->get_slice(ID(131));
        slices[132] = atlas->get_slice(ID(132));
        slices[133] = atlas->get_slice(ID(133));
        slices[134] = atlas->get_slice(ID(134));
        slices[135] = atlas->get_slice(ID(135));
        slices[136] = atlas->get_slice(ID(136));
        slices[137] = atlas->get_slice(ID(137));
        slices[138] = atlas->get_slice(ID(138));
        slices[139] = atlas->get_slice(ID(139));
        slices[140] = atlas->get_slice(ID(140));
        slices[141] = atlas->get_slice(ID(141));
    }
    void Bullet_Pool::Set_Max_Bullets(float max)
    {
        this->max_Bullets_Active = max;
    }
    void Bullet_Pool::Update(float deltaTime)
    {
        auto ptr = this->Active_Bullets.begin();
        //Recorremos la pool de balas y hacemos update de las activas
        for(std::size_t i = 0; i < this->Active_Bullets.size() && ptr != this->Active_Bullets.end() ; ++i , ++ptr)
        {
            if( ptr == this->Active_Bullets.end() ) {
                // list too short
            }
            else {
                if(ptr->active){
                    ptr->Update(deltaTime);
                }
            }
        }
    }

    void Bullet_Pool::render(basics::Graphics_Context::Accessor &context)
    {
        auto ptr = this->Active_Bullets.begin();
        auto * canvas = context->get_renderer< Canvas > (ID(canvas));

        for(std::size_t i = 0; i < this->Active_Bullets.size() && ptr != this->Active_Bullets.end() ; ++i , ++ptr)
        {
            if( ptr == this->Active_Bullets.end() ) {
                // list too short
            }
            else{
                if(ptr->active)
                {
                    //Si el atlas esta activo le damos un slice dependiendo de su framePoisiton
                    //y de su tipo
                    if(atlas)
                    {

                        const basics::Atlas::Slice *s;
                        int f = ptr->framePosition;
                        if (!ptr->permanent) {
                            f += 70;
                        }
                        if (ptr->bullet_type) {
                            f = 141;
                        }
                        s = slices[f];


                        if(s)
                        {
                            //Coeficiente para evitar estiramientos del sprite
                            float f = ptr->height/s->height;

                            canvas->fill_rectangle( Point2f(ptr->x , ptr->y + ptr->height/2 ),
                                    {ptr->width * f , ptr->height  }, s );
                        }

                    }
                }
            }
        }
    }

    void Bullet_Pool::DeactivateEnemy(Bullet b)
    {
        b.active = false;
    }
    void Bullet_Pool::Search_UnActive(float x, float y, float speed, bool permanent, bool _bullet_Type)
    {

        auto ptr = this->Active_Bullets.begin();
        //Si no es del tipo machine gun revisamos si ya hay mas de las balas permitidas activas
        if(!_bullet_Type)
        {
            float counter = 0;


            for(std::size_t i = 0; i < this->Active_Bullets.size() && ptr != this->Active_Bullets.end() ; ++i , ++ptr)
            {

                if(ptr->active){
                    ++counter;
                    if(counter >= this->max_Bullets_Active)  return;
                }

            }
        }

        ptr = this->Active_Bullets.begin();
        //Si hay balas que no estan activamos las preparamos para usarlas
        for(std::size_t i = 0; i < this->Active_Bullets.size() && ptr != this->Active_Bullets.end() ; ++i , ++ptr)
        {
            if( ptr == this->Active_Bullets.end() ) {
                // list too short
            }
            else {
                if(!ptr->active){
                     ptr->framePosition = 0;
                     ptr->active = true;
                     ptr->Prepare_Bullet(x, y,10, speed, permanent, _bullet_Type);
                     return;
                }
            }
        }
        //Si todas las balas estan en uso creamos una nueva
        Bullet* b;;
        b = new Bullet(x, y, 10, speed, permanent, _bullet_Type);
        b->framePosition = 0;
        b->active = true;
        this->Active_Bullets.push_back(*b);
    }


}