#include "AlanAnimation.h"
#include "Alan.h"
#include "AlanActionControl.h"
#include "Sound.h"

AlanAnimation::alanAnimation(GameObject &associated) : Component(associated) 
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

AlanAnimation::~AlanAnimation() {}

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

void AlanAnimation::update(float dt) 
{
    if (currentState == State::DANCIN || currentState == State::DEAD) return;

    Sprite *sprite = associated.getComponent<Sprite *>();
    Alan *alan = associated.getComponent<Alan *>();

    if (sprite->frameTimePassed() &&
        alan->getMovementDirection() == AlanActionControl::Direction::NONE &&
        currentState != State::FALLIN) 
        {
        if ((oldState == State::CLIMBIN || currentState == State::CLIMBIN) &&
            currentState != State::IDLE) 
            {
            oldState = currentState;
            currentState = State::CLIMBIN;
            if (currentDirection != Direction::LEFT &&
                currentDirection != Direction::RIGHT)
                currentDirection = oldDirection;
            sprite->open(AState[currentState], currentDirection);
        } else 
        {
            oldState = currentState;
            currentState = State::IDLE;
            sprite->open(AState[currentState], Direction::LEFT);
        }
    }
}

void AlanAnimation::setAction(Transition trans, Direction dir) 
{
    switch (currentState) 
    {
        case NONE_S:
            oldState = currentState;
            std::cout << "STATE NONE!" << std::endl;

            currentState = State::IDLE;
            break;

        case IDLE:
            switch (trans) 
            {
                case FALL:
                    oldState = currentState;
                    currentState = State::FALLIN;
                    break;

                case WALK:
                    oldState = currentState;
                    currentState = State::WALKIN;
                    break;

                case CLIMB:
                    oldState = currentState;
                    currentState = State::CLIMBIN;
                    break;

                case DIG_T:
                    oldState = currentState;
                    currentState = State::DIG;
                    break;

                case DANCE:
                    oldState = currentState;
                    currentState = State::DANCIN;
                    break;

                case DIE:
                    oldState = currentState;
                    currentState = State::DEAD;
                    break;

                default:
                    return;
                    break;
            }
            break;

        case WALKIN:
            switch (trans) 
            {
                case FALL:
                    oldState = currentState;
                    currentState = State::FALLIN;
                    break;

                case NONE_T:
                    oldState = currentState;
                    currentState = State::IDLE;
                    break;

                case DANCE:
                    oldState = currentState;
                    currentState = State::DANCIN;
                    break;

                case DIE:
                    oldState = currentState;
                    currentState = State::DEAD;
                    break;

                default:
                    return;
                    break;
            }
            break;

        case FALLIN:
            switch (trans) 
            {
                case FLOOR:
                    oldState = currentState;
                    currentState = State::IDLE;
                    break;

                case NONE_T:
                    oldState = currentState;
                    currentState = State::IDLE;
                    break;

                case DANCE:
                    oldState = currentState;
                    currentState = State::DANCIN;
                    break;

                case DIE:
                    oldState = currentState;
                    currentState = State::DEAD;
                    break;

                default:
                    return;
                    break;
            }
            break;

        case DIG:
            switch (trans) 
            {
                case FALL:
                    oldState = currentState;
                    currentState = State::FALLIN;
                    break;

                case NONE_T:
                    oldState = currentState;
                    currentState = State::IDLE;
                    break;

                case DANCE:
                    oldState = currentState;
                    currentState = State::DANCIN;
                    break;

                case DIE:
                    oldState = currentState;
                    currentState = State::DEAD;
                    break;

                default:
                    return;
                    break;
            }
            break;

        case CLIMBIN:
            switch (trans) 
            {
                case NONE_T:
                    oldState = currentState;
                    currentState = State::IDLE;
                    break;
                case WALK:
                    oldState = currentState;
                    currentState = State::WALKIN;
                    break;

                case STOP_CLIMB:
                    oldState = currentState;
                    currentState = State::FALLIN;
                    break;

                case DIG_T:
                    oldState = currentState;
                    currentState = State::DIG_CLIMB;
                    break;

                default:
                    return;
                    break;
            }
            break;

        case DIG_CLIMB:

            break;

        case DANCIN:

            break;

        case DEAD:

            break;

        default:
            return;
            break;
    }
    playSound(trans);

    oldDirection = currentDirection;
    currentDirection = dir;

    Sprite *sprite = associated.getComponent<Sprite *>();
    sprite->open(AState[currentState], dir);
}
