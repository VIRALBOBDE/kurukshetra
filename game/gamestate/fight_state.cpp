#include "fight_state.h"


void fight_scene::poll_events(GLFWwindow* window , state_manager* manager)
{
    Input inputs = NONE;

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        inputs = UP;
    }
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        inputs = DOWN;
    }
    else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        inputs = LEFT;
    }
    else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        inputs = RIGHT;
    }
    else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        inputs = SHIFT;
    }
    else if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
    {
        inputs = ENTER;
    }

    switch (inputs)
    {
    case UP:
        if (current_selection == UP)
            break;

        previous_selection = current_selection;
        current_selection = UP;
        break;

    case DOWN:
        if (current_selection == DOWN)
            break;

        previous_selection = current_selection;
        current_selection = DOWN;
        break;

    case LEFT:
        if (current_selection == LEFT)
            break;

        previous_selection = current_selection;
        current_selection = LEFT;
        break;

    case RIGHT:
        if (current_selection == RIGHT)
            break;

        previous_selection = current_selection;
        current_selection = RIGHT;
        break;

    case SHIFT:
        if (current_selection == NONE)
            break;

        current_selection = previous_selection;
        break;

    case ENTER:
        execute_selection();
        break;

    case NONE:
        break;
    }
}

void fight_scene::execute_selection()
{
    switch (current_selection)
    {
    case UP:
        break;

    case DOWN:
        break;

    case LEFT:
        break;

    case RIGHT:
        break;

    case NONE:
    default:
        break;
    }
}