#pragma once
#include "raylib.h" 

typedef struct{
    Rectangle rect;
    Color color;
} Button;


void init_button(Button *button, Rectangle rect, Color color);
bool is_mouse_over_button(Button button);
bool button_in_action(Button button);
void button_color_change(Button *button, Color primary_color, Color changed_color);