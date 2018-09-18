#include "AlanAnimation.h"
#include "Alan.h"
#include "AlanActionControl.h"
#include "Sound.h"

// Constructor with GameObject as parameter. Also heritage Component.
AlanAnimation::AlanAnimation(GameObject &associated) : Component(associated) 
{
    AState[State::IDLE] = {"assets/img/alan/idle.png", 2, 2, -1};
    AState[State::WALKIN] = {"assets/img/alan/walkin.png", 2, 4, 0.1};
    AState[State::FALLIN] = {"assets/img/alan/fallin.png", 2, 2, 0.1};
    AState[State::DIG] = {"assets/img/alan/dig.png", 2, 8, 0.1};
    AState[State::CLIMBIN] = {"assets/img/alan/climb.png", 2, 4, 0.2};
    AState[State::DIG_CLIMB] = {"assets/img/alan/idle.png", 2, 2, 0.2};
    AState[State::DANCIN] = {"assets/img/alan/dance.png", 10, 10, -1};
    AState[State::DEAD] = {"assets/img/alan/die.png", 3, 3, -0.5};
}

// Destructor method, runs when the class is deallocated.
AlanAnimation::~AlanAnimation() {}

// Method to play game sounds in specific player transitions. 
void AlanAnimation::playSound(Transition trans) 
{
    Sound *s = associated.getComponent<Sound *>();
    switch (trans) {
        case Transition::WALK:
            s->open("assets/audio/andando.wav");
            break;
        case Transition::DIG_T:
            s->open("assets/audio/cavando.wav");
            break;
        case Transition::HIT_T:
            s->open("assets/audio/dor.wav");
            break;
        default:
            return;
    }

    s->setVolume(100);
    s->play();
}

// Function to update game during its different conditional states.
void AlanAnimation::update(float dt) 
{
    if (current_state == State::dancin || current_state == State::dead) return;

    Sprite *sprite = associated.getComponent<Sprite *>();
    Alan *alan = associated.getComponent<Alan *>();

    if (sprite->frameTimePassed() &&
        alan->getMovementDirection() == AlanActionControl::Direction::none &&
        current_state != State::fallin) 
        {
        if ((old_state == State::climbin || current_state == State::climbin) &&
            current_state != State::idle) 
            {
            old_state = current_state;
            current_state = State::climbin;
            if (current_direction != Direction::left &&
                current_direction != Direction::right)
                current_direction = old_direction;
            sprite->open(AState[current_state], current_direction);
        } else 
        {
            old_state = current_state;
            current_state = State::idle;
            sprite->open(AState[current_state], Direction::left);
        }
    }
}

// Method to setup different actions depending on transition and directions.
void AlanAnimation::setAction(Transition trans, Direction dir) 
{
    switch (currentState) 
    {
        case none_s:
            old_state = current_state;
            std::cout << "STATE NONE!" << std::endl;

            current_state = State::idle;
            break;

        case IDLE:
            switch (trans) 
            {
                case fall:
                    old_state = current_state;
                    current_state = State::fallin;
                    break;

                case walk:
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

                case DIE:
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
                    current_state = State::fallin;
                    break;

                case none_t:
                    old_state = current_state;
                    current_state = State::idle;
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

        case fallin:
            switch (trans) 
            {
                case floor:
                    old_state = current_state;
                    current_state = State::idle;
                    break;

                case none_t:
                    old_state = current_state;
                    current_state = State::idle;
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
                    current_state = State::fallin;
                    break;

                case none_t:
                    old_state = current_state;
                    current_state = State::idle;
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
                    current_state = State::idle;
                    break;
                case walk:
                    old_state = current_state;
                    current_state = State::walkin;
                    break;

                case stop_climb:
                    old_state = current_state;
                    current_state = State::fallin;
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

    Sprite *sprite = associated.getComponent<Sprite *>();
    sprite->open(AState[currentState], dir);
}
