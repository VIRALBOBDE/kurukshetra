#include "InputHandling.h"

void InputHandler::setspeed(float speed_in_pixels)
{
    speed = speed_in_pixels;
}


//======================================Box Characters Input===================================================================


void InputHandler::ProcessInput(GLFWwindow* window, BoxCharacter& bheem, BoxCharacter& duryodhan, InputHandler& handler, float delta_time)
{

    //--------BHEEM------------

    bool moved = false;

    //----------------bheem right movement and dash---------------------


    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        bheem.isFacingRight = true;
        moved = true;

        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && bheem.canDash)
        {
            bheem.current_state = bheem.DASHING;
            bheem.velocityX = apply_dash(0, 1);
            bheem.currentCooldown = 2.0f;
            bheem.dashTimer = 0.2f;
            bheem.isGhostMode = true;
            bheem.canDash = false;

        }
        else
        {
            bheem.current_state = bheem.WALKING;
            bheem.body.x += bheem.walkSpeed * delta_time;

        }
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE)
    {
        if (bheem.current_state == bheem.WALKING)
        {
            bheem.current_state = bheem.IDLE;
        }
    }



    //---------------bheem left movement and dash-----------------------


    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        bheem.isFacingRight = false;
        moved = true;

        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && bheem.canDash)
        {
            bheem.current_state = bheem.DASHING;
            bheem.velocityX = apply_dash(0, -1);
            bheem.currentCooldown = 2.0f;
            bheem.dashTimer = 0.2f;
            bheem.isGhostMode = true;
            bheem.canDash = false;

        }
        else
        {
            bheem.current_state = bheem.WALKING;
            bheem.body.x -= bheem.walkSpeed * delta_time;

        }
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE)
    {
        if (bheem.current_state == bheem.WALKING)
        {
            bheem.current_state = bheem.IDLE;
        }
    }





    //--------------bheem jump------------------------------

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && bheem.wReleased)
    {
        if (bheem.Jump(delta_time))
        {
            bheem.current_state = bheem.JUMPING;
        }
        bheem.wReleased = false;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE) bheem.wReleased = true;






    //-------------bheem crouch-----------------------------

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && !bheem.isDashing && bheem.isGrounded)
    {
        bheem.current_state = bheem.CROUCHING;


    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE &&
        bheem.current_state == bheem.CROUCHING)
    {
        bheem.current_state = bheem.IDLE;
    }




    //--------------bheem attack-----------------------------

    bool space_now = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;

    if (space_now && !bheem.spacepressed)
    {
        bheem.spacepressed = true;

        // Naya Attack Start
        if (bheem.current_state != bheem.ATTACKING)
        {
            bheem.current_state = bheem.ATTACKING;
            bheem.attack_delta_time = 0.5f;     //  timing logic
            bheem.hasDealtDamage = false; // Reset damage flag
        }
    }
    else if (!space_now)
    {
        bheem.spacepressed = false;
    }




    //------------sliding logic-----------------------

    if (Physics::checkcollision(bheem.body, duryodhan.body) && !bheem.isGhostMode)
    {
        // Bheem ke feet
        float bheemBottom = bheem.body.y;
        // Duryodhan ka "Shoulder" level (70% height)
        float duryodhanShoulder = duryodhan.body.y + (duryodhan.body.height * 0.7f);
        // ASLI LOGIC: Sirf tabhi side mein dhakelo jab Bheem 'niche' ho
        if (bheemBottom < duryodhanShoulder - 40.0f)
        {
            float bheemCenter = bheem.body.x + (bheem.body.width / 2.0f);
            float duryodhanCenter = duryodhan.body.x + (duryodhan.body.width / 2.0f);

            if (bheemCenter < duryodhanCenter)
            {
                bheem.body.x = duryodhan.body.x - bheem.body.width - 3.0f; // Left Snap
            }
            else
            {
                bheem.body.x = duryodhan.body.x + duryodhan.body.width + 3.0f; // Right Snap
            }
        }
    }

}








//======================================Circular Characters Input===================================================================

void InputHandler::CircleProcess(GLFWwindow* window, Character& bheem, Character& duryodhan, InputHandler& handler, float deltaTime)
{
    {

        //--------BHEEM------------

        float oldX1 = bheem.body.x;

        //bheem movement and dash
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            float current_bheem = bheem.body.x;
            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && bheem.canDash)
            {
                bheem.body.x = apply_dash(bheem.body.x, 1);
                bheem.canDash = false;
                bheem.currentCooldown = 2.0f;
                bheem.dashTimer = 0.2f;
                bheem.isGhostMode = true;
            }
            else bheem.body.x += bheem.walkSpeed * deltaTime;
            if (Physics::isColliding(bheem.body, duryodhan.body) && !bheem.isGhostMode)
                bheem.body.x = current_bheem;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            float current_bheem = bheem.body.x;

            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && bheem.canDash)
            {
                bheem.body.x = apply_dash(bheem.body.x, -1);
                bheem.canDash = false;
                bheem.currentCooldown = 2.0f;
                bheem.dashTimer = 0.2;
                bheem.isGhostMode = true;
            }
            else
            {
                bheem.body.x -= bheem.walkSpeed * deltaTime;
            }
            if (Physics::isColliding(bheem.body, duryodhan.body) && !bheem.isGhostMode)
                bheem.body.x = current_bheem;
        }

        //bheem jump
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            float current_bheem = bheem.body.y;

            bheem.body.y += bheem.walkSpeed * deltaTime;
            if (Physics::isColliding(bheem.body, duryodhan.body))
                bheem.body.y = current_bheem;
            /*bheem.Jump();
            bheem.Jump();
            bheem.wReleased = false;
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE)
            bheem.wReleased = true;*/
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            float current_bheem = bheem.body.y;

            bheem.isCrouching = true;
            if (Physics::isColliding(bheem.body, duryodhan.body))
                bheem.body.y = current_bheem;
            /*bheem.Jump();
            bheem.wReleased = false;
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE)
            bheem.wReleased = true;*/
        }
        if (Physics::isColliding(bheem.body, duryodhan.body))
        {
            std::cout << "COLLIDING\n";

            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            {
                std::cout << "HIT!\n";
                duryodhan.health -= 20;
            }
        }

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            std::cout << "SPACE PRESSED\n";
        }
    }
}




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