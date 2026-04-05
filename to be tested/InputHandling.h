#pragma once
#include <GLFW/glfw3.h>
#include"Character.h"
#include<iostream>
#include<vector>
#include"moves.h"
#include"physics.h"

class InputHandler {
public:
    static void ProcessInput(GLFWwindow* window, Character& bheem, Character& duryodhan, const std::vector<Box>& walls) {

        float speed = 0.008f;

        //--------BHEEM------------

        float oldX1 = bheem.body.x;

        //bheem movement and dash
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 
        {
            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
                bheem.body.x = apply_dash(bheem.body.x, 1);
            else bheem.body.x += speed;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
        {
            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
                bheem.body.x = apply_dash(bheem.body.x, -1);
            else bheem.body.x -= speed;
        }

        //bheem jump
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && bheem.wReleased) 
        {
            bheem.Jump();
            bheem.wReleased = false;
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE)
            bheem.wReleased = true;

        //bheem crouch
        /*if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
        {
            bheem.body.radius = get_crouch_height(bheem.normalRadius);
            bheem.isCrouching = true;
        }
        else {
            bheem.body.radius = bheem.normalRadius;
            bheem.isCrouching = false;
        }*/

        /*//---------DURYODHAN---------
         
        float oldX2 = duryodhan.body.x;

        //Duryodhan movement and dash
       
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            if (glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS)
                duryodhan.body.x = apply_dash(duryodhan.body.x, 1);
            else duryodhan.body.x += speed;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            if (glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS)
                duryodhan.body.x = apply_dash(duryodhan.body.x, -1);
            else duryodhan.body.x -= speed;
        }*/

        /*//DURYODHAN jump
        static bool upReleased = true;
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && upReleased)
        {
            duryodhan.Jump(); upReleased = false;
        }
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE)
            upReleased = true;

        //duryodhan crouch
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            duryodhan.body.radius = get_crouch_height(duryodhan.normalRadius);
            duryodhan.isCrouching = true;
        }
        else {
            duryodhan.body.radius = duryodhan.normalRadius;
            duryodhan.isCrouching = false;
        }

        // Bheem vs Walls
        for (const auto& w : walls) 
        {
            if (Physics::CheckCircleBox(bheem.body, w)) bheem.body.x = oldX1;
        }
        // Duryodhan vs Walls
        for (const auto& w : walls) 
        {
            if (Physics::CheckCircleBox(duryodhan.body, w)) duryodhan.body.x = oldX2;
        }

        // Character vs Character
        if (Physics::isColliding(bheem.body, duryodhan.body)) {
            bheem.body.x = oldX1;
            duryodhan.body.x = oldX2;

            float overlapDist = (bheem.body.radius + duryodhan.body.radius) -
                std::abs(bheem.body.x - duryodhan.body.x);

            float pushAmount = overlapDist * 0.5f + 0.001f; 

            if (bheem.body.x < duryodhan.body.x) {
                bheem.body.x -= pushAmount;      // Bheem left mein hai, aur left dhakelo
                duryodhan.body.x += pushAmount;  // Duryodhan right mein hai, aur right dhakelo
            }
            else {
                bheem.body.x += pushAmount;
                duryodhan.body.x -= pushAmount;
            }
        }*/
    }
};

