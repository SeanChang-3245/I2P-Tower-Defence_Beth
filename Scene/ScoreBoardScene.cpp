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
#include "Engine/LOG.hpp"
#include "UI/Component/Slider.hpp"
#include "ScoreBoardScene.hpp"
using Engine::LOG;
using Engine::INFO;

void ScoreBoardScene::Initialize() {
    LOG(INFO) << "enter scoreboardscene init";

    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton* btn;

    //ScoreBoard Title
    AddNewObject(new Engine::Label("ScoreBoard", "pirulen.ttf", 48, halfW, halfH / 3 - 80, 0, 255, 64, 255, 0.5, 0.5));
    //name column
    AddNewObject(new Engine::Label("Name", "pirulen.ttf", 55, halfW-200, halfH / 3, 0, 255, 64, 255, 0.5, 0.5));
    //score column
    AddNewObject(new Engine::Label("Score", "pirulen.ttf", 55, halfW+200, halfH / 3, 0, 255, 64, 255, 0.5, 0.5));
    //Back Button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreBoardScene::BackOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));

    //Prev Button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", (halfW - 200)/ 2 - 150, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreBoardScene::PrevOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Prev", "pirulen.ttf", 48, halfW/2 - 100, halfH * 3 / 2, 0, 0, 0, 255, 0.25, 0.5));

    //Next Button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", (halfW -200)*3/2 + 150, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreBoardScene::NextOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Next", "pirulen.ttf", 48, halfW*3/2 + 100, halfH * 3 / 2, 0, 0, 0, 255, 0.75, 0.5));

    LOG(INFO) << "before read score";

    //Read Score
    ReadScore();

    LOG(INFO) << "after read score";

    //create objects of all players
    for(int i = 0; i < TotalPlayer; i++){
        Engine::Label *tmp_name = new Engine::Label(player[i].name, "pirulen.ttf", 55, halfW-200, halfH / 3 + 90 + (i%6)*60, 0, 255, 64, 255, 0.5, 0.5);
        Engine::Label *tmp_score = new Engine::Label(player[i].score, "pirulen.ttf", 55, halfW + 200, halfH / 3 + 90 + (i%6)*60, 0, 255, 64, 255, 0.5, 0.5);
        row_name.push_back(tmp_name);
        row_score.push_back(tmp_score);
        AddNewObject(row_name[i]);
        AddNewObject(row_score[i]);
        row_name[i]->Visible = row_score[i]->Visible = false;
    }

    LOG(INFO) << "after create label";

    CurrentPage = 0;
    //show the first page
    for(int p = 0; p < 6; p++){
        row_name[p]->Visible = row_score[p]->Visible = true;
    }

    LOG(INFO) << "after add object";
}

void ScoreBoardScene::Terminate(){
    row_name.clear();
    row_score.clear();
    player.clear();
    IScene::Terminate();
}

void ScoreBoardScene::PrevOnClick(int stage){
    if(CurrentPage == 0) return;
    if(CurrentPage > 0) CurrentPage--;

    //clear previous page
    for(int i = 0; i < TotalPlayer; ++i)
        row_name[i]->Visible = row_score[i]->Visible = false;

    //show the previous page
    for(int p = CurrentPage*6; p < (CurrentPage+1)*6 && p < TotalPlayer; p++)
        row_name[p]->Visible = row_score[p]->Visible = true;
    
}

void ScoreBoardScene::NextOnClick(int stage){
    if(CurrentPage == TotalPage-1) return;
    if(CurrentPage < TotalPage) CurrentPage++;

    //clear previous page
    for(int i = 0; i < TotalPlayer; ++i)
        row_name[i]->Visible = row_score[i]->Visible = false;

    //show the next page
    for(int p = CurrentPage*6; p < (CurrentPage+1)*6 && p < TotalPlayer; p++)
        row_name[p]->Visible = row_score[p]->Visible = true;
    
}

void ScoreBoardScene::BackOnClick(int stage){
    Engine::GameEngine::GetInstance().ChangeScene("StageSelect");
}

void ScoreBoardScene::ReadScore(){
    std::string score;
    std::string name;
    std::ifstream fin("Resource/scoreboard.txt");
    TotalPlayer = 0;
    while(fin >> name && fin >> score){
        Player tmp;
        tmp.name = name;
        tmp.score = score;
        player.push_back(tmp);
        TotalPlayer++;
    }
    TotalPage = TotalPlayer%6 == 0 ? TotalPlayer/6 : TotalPlayer/6 + 1 ;
    fin.close();
}