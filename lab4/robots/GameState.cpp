/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#include "GameState.h"
#include "utilities.h"
#include "constants.h"
#include "vector"

GameState::GameState(){}

GameState::GameState (const GameState& state) {

    for (Robot* r: state.robots) {
        robots.push_back(r);
    }

}

GameState::~GameState() {
    for (Robot* r: robots) {
        delete r;
    }
}

  GameState& GameState::operator =(const GameState& state) {
    robots = state.robots;
    return *this;
    /*
     *Copy the elements.
     * NOT LIKE ABOVE
     */
}

GameState::GameState(int numberOfRobots) {
    for (int i = 0; i < numberOfRobots; i++) {
        Robot *robot;
        do {robot = new Robot();}
        while (!isEmpty (*robot));
        robots.push_back(robot);
    }
    teleportHero();
}

void GameState::draw(QGraphicsScene *scene) const {
    scene->clear();
    for (size_t i = 0; i < robots.size(); ++i)
        robots[i]->draw(scene);
    hero.draw(scene);
}

void GameState::teleportHero() {
    do hero.teleport();
    while (!isEmpty(hero));
}

void GameState::moveRobots() {
    for (unsigned int i = 0; i < robots.size(); i++)
        robots[i]->moveTowards (hero);
}

int GameState::countCollisions() {
    int numberDestroyed = 0;
    unsigned int i = 0;
    while (i < robots.size()) {
        bool collision = (countRobotsAt (*robots[i]) > 1);
        if (collision) {
            robots[i] = new Junk(*robots[i]);
            numberDestroyed++;

        }
        i++;
    }
    return numberDestroyed;
}

bool GameState::anyRobotsLeft() const {
    for (int i=0; i < robots.size(); i++) {
        if (!robots[i]->isJunk()) {
            return true;
        }
    }
    return false;
}

bool GameState::heroDead() const {
    return !isEmpty(hero);
}

bool GameState::isSafe(const Unit& unit) const {
    for (unsigned int i = 0; i < robots.size(); i++)
        if (robots[i]->attacks(unit)) return false;
    if (countRobotsAt(unit) > 0) return false;
    return true;
}

void GameState::moveHeroTowards(const Unit& dir) {
    hero.moveTowards(dir);
}

Hero GameState::getHero() const {return hero;}

/*
 * Free of robots and junk only
 */
bool GameState::isEmpty(const Unit& unit) const {
    return (countRobotsAt(unit) == 0);
}



/*
 * How many robots are there at unit?
 */
int GameState::countRobotsAt(const Unit& unit) const {
    int count = 0;
    for (size_t i = 0; i < robots.size(); ++i) {
        if (robots[i]->at(unit))
            count++;
    }
    return count;
}
