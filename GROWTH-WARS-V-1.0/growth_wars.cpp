#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include "raylib.h"

class Ball{
    public:
    double x , y;
    double velocity = 10;
    const double gravity = 9.81;
    std::int64_t power;
};
enum class Screen{
    Menu,Run,End
};

int main(){

    std::ios::sync_with_stdio(false);

    Screen currentScreen = Screen::Menu;
    Ball ball1 , ball2;
    int resetY = 370;
    int blockHealth1;
    int blockHealth2;
    std::string choice,choice1;
    const int time = 1;
    float closeTime = 4.0f;
    ball1.x = 540;
    ball1.y = 100;
    ball2.x = 640;
    ball2.y = 100;
    ball1.power = 1;
    ball2.power = 1;
    int ball1_multiplier = 2;
    int ball2_add = 10000;
    Rectangle buttonBound = {300,270,180,60};
    Color buttonColor = BLUE;
    int clickCount = 0;
    bool shouldExit = false;
    std::string winnerText = "";

    std::cout << "ENTER BLOCK HEALTH- ";
    std::cin >> blockHealth1;
    blockHealth2 = blockHealth1;

    std::cout << "SET INIITIAL POWER FOR BALLS(yes/no)- ";
    std::cin >> choice;
    if(choice == "yes"){
        std::cout << "Enter Ball1 Power- ";
        std::cin >> ball1.power;
        std::cout << "Enter Ball2 Power- ";
        std::cin >> ball2.power;
    }else if(choice == "no"){
        std::cout << "Okay Enjoy the Simulation With Initial Powers" << std::endl;
    }else{
        std::cerr << "Please Enter (yes/no) and try again" << std::endl;
        return -1;
    }
    std::cout << "Edit Ball Attributes(yes/no)- ";
    std::cin >> choice1;
    if(choice1 == "yes" || choice1 == "YES" || choice1 == "Yes" ){
        std::cout << "ENTER BALL 1 MULTIPLIER- ";
        std::cin >> ball1_multiplier;
        std::cout << "ENTER BALL 2 ADD MULTIPLIER- ";
        std::cin >> ball2_add;
    }else if(choice1 == "no" || choice1 == "No" || choice1 == "NO"){
        std::cout << "SETTINGS SET TO DEFAULT" << std::endl;
    }else{
        std::cerr << "INVALID INPUT PLEASE TRY AGAIN" << std::endl;
        return -1;
    }

    InitWindow(800,400,"Gravity");
    SetTargetFPS(60);
    
    while(WindowShouldClose() == false && shouldExit == false){
        if(currentScreen == Screen::Menu){
            BeginDrawing();
            Vector2 mousePosition = GetMousePosition();
            bool isHovered = CheckCollisionPointRec(mousePosition,buttonBound);
            if(isHovered){
                buttonColor = SKYBLUE;
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    clickCount++;
                    buttonColor = DARKBLUE;
                    currentScreen = Screen::Run;
                }else{
                    buttonColor = BLUE;
                }
            }
            ClearBackground(RAYWHITE);
            DrawText("Welcome To Growth Wars", 90,100,50,BLACK);
            DrawRectangleRec(buttonBound,buttonColor);
            DrawRectangleLinesEx(buttonBound,2,DARKBLUE);
            DrawText("START",buttonBound.x + 50, buttonBound.y + 20,20,WHITE);
            EndDrawing();
        }else if(currentScreen == Screen::Run){
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawCircle(ball1.x, ball1.y, 30, BLUE); 
            DrawCircle(ball2.x,ball2.y,30, RED); 

            std::string powerText1 = "Ball1 Power --- " + std::to_string(ball1.power);
            std::string powerText2 = "Ball2 Power --- " + std::to_string(ball2.power);
            DrawText(powerText1.c_str(), 55, 100, 25, GREEN);
            DrawText(powerText2.c_str(), 55, 135, 25, GREEN);
            DrawText(TextFormat("Block_Health1  ---     %i", blockHealth1 ),55,170,20,BLACK);
            DrawText(TextFormat("Block_Health2  ---     %i", blockHealth2 ),55,200,20,BLACK);

            float DeltaTime = GetFrameTime();
            ball1.velocity += ball1.gravity * DeltaTime;
            ball2.velocity += ball2.gravity * DeltaTime;
            ball1.y += ball1.velocity * DeltaTime;
            ball2.y += ball2.velocity * DeltaTime;

            if(ball1.y >= resetY && ball2.y >= resetY){
                ball1.y = 100;
                ball2.y = 100;
                ball1.power *= ball1_multiplier;
                ball2.power += ball2_add;
                blockHealth1 -= ball1.power;
                blockHealth2 -= ball2.power;
            }
            if(blockHealth1 <= 0){
                winnerText = "BALL 1 or BLUE BALL won";
                currentScreen = Screen::End;
            }else if(blockHealth2 <= 0){
                winnerText = "BALL 2 or RED BALL won";
                currentScreen = Screen::End;
            }
            EndDrawing();
        }else if(currentScreen == Screen::End){ 
            closeTime -= GetFrameTime();
            if(closeTime <= 0.0f){
                shouldExit = true;
            }
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText(winnerText.c_str(), 100, 150, 40, RED);
            DrawText(TextFormat("Closing in %i", (int)closeTime + 1), 100, 220, 40, DARKGRAY);
            EndDrawing();
        }
    }
    CloseWindow();
    return 0;
}
