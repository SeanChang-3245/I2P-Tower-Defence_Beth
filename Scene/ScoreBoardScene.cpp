#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>
#include <fstream>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "UI/Component/Slider.hpp"
#include "ScoreBoardScene.hpp"

void ScoreBoardScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton* btn;

    //ScoreBoard Title
    AddNewObject(new Engine::Label("ScoreBoard", "pirulen.ttf", 48, halfW, halfH / 3 - 80, 0, 255, 64, 255, 0.5, 0.5));

    //Back Button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreBoardScene::BackOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));

    //Prev Button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", (halfW - 200)/ 2 - 150, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreBoardScene::BackOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Prev", "pirulen.ttf", 48, halfW/2 - 100, halfH * 3 / 2, 0, 0, 0, 255, 0.25, 0.5));

    //Next Button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", (halfW -200)*3/2 + 150, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreBoardScene::BackOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Next", "pirulen.ttf", 48, halfW*3/2 + 100, halfH * 3 / 2, 0, 0, 0, 255, 0.75, 0.5));

    //show the first page
    for(int p = 0; p < 6; p++){
        Engine::IObject *row = new Engine::Label("ScoreBoard", "pirulen.ttf", 48, halfW, halfH / 3 - 80, 0, 255, 64, 255, 0.5, 0.5);
        AddNewObject(row);
    }
}

void ScoreBoardScene::Terminate(){
    IScene::Terminate();
}

void ScoreBoardScene::PrevOnClick(){
    if(CurrentPage > 0) CurrentPage--;
}

void ScoreBoardScene::NextOnClick(){
    if(CurrentPage < TotolPage) CurrentPage++;
}

void ScoreBoardScene::BackOnClick(int stage){
    Engine::GameEngine::GetInstance().ChangeScene("StageSelect");
}

void ScoreBoardScene::ReadScore(){
    std::string score;
    std::string name;
    std::ifstream fin("scoreboard.txt");
    TotalPlayer = 0;
    while(fin >> name && fin >> score){
        Player tmp;
        tmp.name = name;
        tmp.score = score;
        player.push_back(tmp);
        TotalPlayer++;
    }
    TotolPage = TotalPlayer%6 == 0 ? TotalPlayer/6 : TotalPlayer/6 +1 ;
    fin.close();
}