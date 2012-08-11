#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "ball.h"
#include "bar.h"

// Prototype
void updateLeftBar(Bar &bar);
void updateRightBar(Bar &bar);
void updateBall(Ball &ball);
void resetBall(Ball &ball);
void handleCollision(Bar &bar1, Bar &bar2, Ball &ball);

//BACKGROUND_COLOR = al_map_rgb(0, 0, 0);
int FPS = 60;
int DISPLAY_WIDTH = 600;
int DISPLAY_HEIGHT = 300;
enum KEYS {S, D, J, K};
bool keys[4] = {false, false, false, false};

// Game state
int score1 = 0;
int score2 = 0;
int WINNING_SCORE = 3;

// Game objects
Ball *ball = new Ball(DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, 5);
float height = 60;
float width = 5;
Bar *bar1 = new Bar(0, DISPLAY_HEIGHT/2 - height/2, width, height); 
Bar *bar2 = new Bar(DISPLAY_WIDTH - width, DISPLAY_HEIGHT/2 - height/2, width, height); 

int main()
{
    bool done = false;
    bool redraw = true;
    bool is_game_over = false;
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *events = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_FONT *font20 = NULL;
    ALLEGRO_FONT *font40 = NULL;

    if (!al_init())
        return 1;
    display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    if (!display)
        return 1;    

    // Initialize add-ons
    al_init_primitives_addon();
    al_install_keyboard();
    al_init_font_addon();
    al_init_ttf_addon();

    timer = al_create_timer(1.0 / FPS);
    events = al_create_event_queue();
    al_register_event_source(events, al_get_keyboard_event_source());
    al_register_event_source(events, al_get_timer_event_source(timer));

    font20 = al_load_font("arial.ttf", 20, 0);
    font40 = al_load_font("arial.ttf", 40, 0);

    al_start_timer(timer);
    while (!done)
    {        
        // Events handling
        ALLEGRO_EVENT ev;
        al_wait_for_event(events, &ev);

        if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch (ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_J:
                    keys[J] = false;
                    break;
                case ALLEGRO_KEY_K:
                    keys[K] = false;
                    break;
                case ALLEGRO_KEY_S:
                    keys[S] = false;
                    break;
                case ALLEGRO_KEY_D:
                    keys[D] = false;
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    done = true;
                    break;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;

            if (!is_game_over)
            {
                updateBall(*ball);
                updateLeftBar(*bar1);
                updateRightBar(*bar2);
                handleCollision(*bar1, *bar2, *ball);

                if (score1 == WINNING_SCORE || score2 == WINNING_SCORE)
                    is_game_over = true;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_J:
                    keys[J] = true;
                    break;
                case ALLEGRO_KEY_K:
                    keys[K] = true;
                    break;
                case ALLEGRO_KEY_S:
                    keys[S] = true;
                    break;
                case ALLEGRO_KEY_D:
                    keys[D] = true;
                    break;
            }
        }
        
        if (redraw && al_is_event_queue_empty(events))
        {
            redraw = false;
            if (!is_game_over)
            {
                // Rendering
                al_clear_to_color(al_map_rgb(0, 0, 0));
                ball->render();
                bar1->render();
                bar2->render();
                al_draw_textf(font20, al_map_rgb(255, 255, 255), DISPLAY_WIDTH/2, DISPLAY_HEIGHT - 40, ALLEGRO_ALIGN_CENTRE, "%d : %d", score1, score2);
                al_flip_display();
            }
            else
            {
                al_clear_to_color(al_map_rgb(0, 0, 0));
                if (score1 == WINNING_SCORE)
                    al_draw_text(font40, al_map_rgb(255, 255, 255), DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2 - 20, ALLEGRO_ALIGN_CENTRE, "PLAYER 1 WON");
                else if (score2 == WINNING_SCORE)
                    al_draw_text(font40, al_map_rgb(255, 255, 255), DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2 - 20, ALLEGRO_ALIGN_CENTRE, "PLAYER 2 WON");
                al_draw_text(font20, al_map_rgb(255, 255, 255), DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2 + 40, ALLEGRO_ALIGN_CENTRE, "Press 'r' to start a new game");
                al_flip_display();
            }
            
        }
    }

    // House cleaning
    delete ball;
    delete bar1;
    delete bar2;
    al_destroy_font(font20);
    al_destroy_font(font40);
    al_destroy_display(display);
    al_destroy_event_queue(events);

    return 0;
}

void updateRightBar(Bar &bar)
{
    // Update bars
    if (keys[J] && !keys[K])
        bar.moveUp();
    else if (!keys[J] && keys[K])
        bar.moveDown();
    if (bar.getPos().y < 0)
        bar.getPos().y = 0;
    else if (bar.getPos().y + bar.getHeight() > DISPLAY_HEIGHT)
        bar.getPos().y = DISPLAY_HEIGHT - bar.getHeight();
}

void updateLeftBar(Bar &bar)
{
    if (keys[S] && !keys[D])
        bar.moveUp();
    else if (!keys[S] && keys[D])
        bar.moveDown();
    if (bar.getPos().y < 0)
        bar.getPos().y = 0;
    else if (bar.getPos().y + bar.getHeight() > DISPLAY_HEIGHT)
        bar.getPos().y = DISPLAY_HEIGHT - bar.getHeight();
}

void updateBall(Ball &ball)
{
    // Update ball
    ball.update(4);
    if (ball.getPos().x - ball.getRadius() <= 0 && ball.getVel().x < 0)
    {
        resetBall(ball);
        score2 += 1;
    }
    else if (ball.getPos().x + ball.getRadius() >= DISPLAY_WIDTH && ball.getVel().x > 0)
    {
        resetBall(ball);
        score1 += 1;
    }
    if (ball.getPos().y - ball.getRadius() <= 0 && ball.getVel().y < 0)
        ball.vReflect();
    else if (ball.getPos().y + ball.getRadius() >= DISPLAY_HEIGHT && ball.getVel().y > 0)
        ball.vReflect();
}

void resetBall(Ball &ball)
{
    ball.getPos().x = DISPLAY_WIDTH/2;
    ball.getPos().y = DISPLAY_HEIGHT/2;
    ball.hReflect();
}

void handleCollision(Bar &bar1, Bar &bar2, Ball &ball)
{
    // Check collision with left bar
    if (ball.getVel().x < 0)
    {
        if (ball.getPos().x - ball.getRadius() < bar1.getWidth()
            && bar1.getPos().y <= ball.getPos().y
            && bar1.getPos().y + bar1.getHeight() >= ball.getPos().y)
            ball.hReflect();
    }
    else if(ball.getVel().x > 0)
    {
        if (ball.getPos().x + ball.getRadius() > DISPLAY_WIDTH - bar2.getWidth()
            && bar2.getPos().y <= ball.getPos().y
            && bar2.getPos().y + bar2.getHeight() >= ball.getPos().y)
            ball.hReflect();
    }
}
