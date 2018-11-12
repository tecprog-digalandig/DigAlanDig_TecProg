#include "AlanAnimation.h"
#include "Alan.h"
#include "AlanActionControl.h"
#include "Sound.h"

AlanAnimation::AlanAnimation(GameObject &associated) : Component(associated) 
{
    AState[State::IDLE] = {"assets/img/alan/IDLE.png", 2, 2, -1};
    AState[State::walkin] = {"assets/img/alan/WALKin.png", 2, 4, 0.1};
    AState[State::fallin_var] = {"assets/img/alan/fallin.png", 2, 2, 0.1};
    AState[State::dig] = {"assets/img/alan/dig.png", 2, 8, 0.1};
    AState[State::climbin] = {"assets/img/alan/climb.png", 2, 4, 0.2};
    AState[State::dig_climb] = {"assets/img/alan/IDLE.png", 2, 2, 0.2};
    AState[State::dancin] = {"assets/img/alan/dance.png", 10, 10, -1};
    AState[State::dead] = {"assets/img/alan/die.png", 3, 3, -0.5};     
}

AlanAnimation::~AlanAnimation() {}

void AlanAnimation::playSound(Transition trans) 
{
    Sound *s = associated.GetComponent<Sound *>();
    switch (trans) {
        case Transition::WALK:
            s->Open("assets/audio/andando.wav");
            break;
        case Transition::dig_t:
            s->Open("assets/audio/cavando.wav");
            break;
        case Transition::hit_t:
            s->Open("assets/audio/dor.wav");
            break;
        default:
            return;
    }

    s->setVolume(100);
    s->play_func();
}

void AlanAnimation::update(float delta_time) 
{
    if (current_state == State::dancin || current_state == State::dead) return;

    Sprite *sprite =associated.GetComponent<Sprite *>();
    Alan *alan = associated.GetComponent<Alan *>();

    if (sprite->frameTimePassed() &&
        alan->getMovementDirection() == AlanActionControl::Direction::NONE &&
        current_state != State::fallin_var) 
        {
        if ((old_state == State::climbin || current_state == State::climbin) &&
            current_state != State::IDLE) 
            {
            old_state = current_state;
            current_state = State::climbin;
            if (current_direction != Direction::left &&
                current_direction != Direction::right)
                current_direction = old_direction;
            sprite->Open(AState[current_state], current_direction);
        } else 
        {
            old_state = current_state;
            current_state = State::IDLE;
            sprite->Open(AState[current_state], Direction::left);
        }
    }
}

void AlanAnimation::setAction(Transition trans, Direction dir) 
{
    switch (current_state) 
    {
        case none_s:
            old_state = current_state;
            std::cout << "STATE NONE!" << std::endl;

            current_state = State::IDLE;
            break;

        case IDLE:
            switch (trans) 
            {
                case fall:
                    old_state = current_state;
                    current_state = State::fallin_var;
                    break;

                case WALK:
                    old_state = current_state;
                    current_state = State::walkin;
                    break;

                case climb:
                    old_state = current_state;
                    current_state = State::climbin;
                    break;

                case dig_t:
                    old_state = current_state;
                    current_state = State::dig;
                    break;

                case dance:
                    old_state = current_state;
                    current_state = State::dancin;
                    break;

                case die:
                    old_state = current_state;
                    current_state = State::dead;
                    break;

                default:
                    return;
                    break;
            }
            break;

        case walkin:
            switch (trans) 
            {
                case fall:
                    old_state = current_state;
                    current_state = State::fallin_var;
                    break;

                case none_t:
                    old_state = current_state;
                    current_state = State::IDLE;
                    break;

                case dance:
                    old_state = current_state;
                    current_state = State::dancin;
                    break;

                case die:
                    old_state = current_state;
                    current_state = State::dead;
                    break;

                default:
                    return;
                    break;
            }
            break;

        case fallin_var:
            switch (trans) 
            {
                case floor:
                    old_state = current_state;
                    current_state = State::IDLE;
                    break;

                case none_t:
                    old_state = current_state;
                    current_state = State::IDLE;
                    break;

                case dance:
                    old_state = current_state;
                    current_state = State::dancin;
                    break;

                case die:
                    old_state = current_state;
                    current_state = State::dead;
                    break;

                default:
                    return;
                    break;
            }
            break;

        case dig:
            switch (trans) 
            {
                case fall:
                    old_state = current_state;
                    current_state = State::fallin_var;
                    break;

                case none_t:
                    old_state = current_state;
                    current_state = State::IDLE;
                    break;

                case dance:
                    old_state = current_state;
                    current_state = State::dancin;
                    break;

                case die:
                    old_state = current_state;
                    current_state = State::dead;
                    break;

                default:
                    return;
                    break;
            }
            break;

        case climbin:
            switch (trans) 
            {
                case none_t:
                    old_state = current_state;
                    current_state = State::IDLE;
                    break;
                case WALK:
                    old_state = current_state;
                    current_state = State::walkin;
                    break;

                case stop_climb:
                    old_state = current_state;
                    current_state = State::fallin_var;
                    break;

                case dig_t:
                    old_state = current_state;
                    current_state = State::dig_climb;
                    break;

                default:
                    return;
                    break;
            }
            break;

        case dig_climb:

            break;

        case dancin:

            break;

        case dead:

            break;

        default:
            return;
            break;
    }
    playSound(trans);

    old_direction = current_direction;
    current_direction = dir;

    Sprite *sprite =associated.GetComponent<Sprite *>();
    sprite->Open(AState[current_state], dir);
}
