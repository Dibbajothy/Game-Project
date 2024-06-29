#include "button.h"

void init_button(Button *button, Rectangle rect, Color color){
    button->rect = rect;
    button->color = color;
}


bool is_mouse_over_button(Button button){
    return CheckCollisionPointRec(GetMousePosition(), button.rect);
}

bool button_in_action(Button button)
{   
    if(is_mouse_over_button(button) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        return true;
    }
    return false;
}

void button_color_change(Button *button, Color primary_color, Color changed_color)
{
    if(is_mouse_over_button(*button)){
        button->color = changed_color;
    }
    else{
        button->color = primary_color;
    }
}
