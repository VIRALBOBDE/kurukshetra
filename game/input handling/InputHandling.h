#pragma once
#include"../game's dustbin/Character.h"
#include <GLFW/glfw3.h>
#include"../game's dustbin/circular character.h"
#include<iostream>
#include<vector>
#include"../game's dustbin/moves.h"
#include"../physics.h"
//  , const std::vector<Box>& walls
class InputHandler
{
private:
    float speed = 0.8f;
public:
    void setspeed(float speed_in_pixels);


    //==============================================Box character input handling==============================================


    static void ProcessInput(GLFWwindow* window, BoxCharacter& bheem, BoxCharacter& duryodhan, InputHandler& handler, float delta_time);




    //======================================Circular Characters Input===================================================================

    static void CircleProcess(GLFWwindow* window, Character& bheem, Character& duryodhan, InputHandler& handler, float deltaTime);


};
    
