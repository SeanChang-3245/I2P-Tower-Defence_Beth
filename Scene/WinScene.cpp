#include <functional>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "ScoreBoardScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/Group.hpp"
#include "WinScene.hpp"
#include "Engine/LOG.hpp"
using Engine::LOG;
using Engine::INFO;

void WinScene::Initialize() {
	ticks = 0;
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
	int halfH = h / 2;
	AddNewObject(new Engine::Image("win/benjamin-sad.png", halfW, halfH, 0, 0, 0.5, 0.5));
	AddNewObject(new Engine::Label("You Win!", "pirulen.ttf", 48, halfW, halfH / 4 -10, 255, 255, 255, 255, 0.5, 0.5));
	Engine::ImageButton* btn;
	btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
	btn->SetOnClickCallback(std::bind(&WinScene::BackOnClick, this, 2));
	AddNewControlObject(btn);
	AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
	bgmId = AudioHelper::PlayAudio("win.wav");

	//add input box
	keyStrokes.clear();
}
void WinScene::Terminate() {
	IScene::Terminate();
	AudioHelper::StopBGM(bgmId);
}
void WinScene::Update(float deltaTime) {
	ticks += deltaTime;
	if (ticks > 4 && ticks < 100 &&
		dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"))->MapId == 2) {
		ticks = 100;
		bgmId = AudioHelper::PlayBGM("happy.ogg");
	}
}
void WinScene::BackOnClick(int stage) {
	// Store inputText to the file
	std::fstream f1, f2;

	PlayScene* scenen = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));

	f1.open("Resource/scoreboard.txt", std::ios::app);
	if(!f1) LOG(INFO) << "File 1 not opened";
	f1 << "\n" << inputText << " " << scenen->GetLives() * 10;
	f1.close();

	f2.open("..//Resource/scoreboard.txt", std::ios::app);
	if(!f2) LOG(INFO) << "File 2 not opened";
	f2 << "\n" << inputText << " " << scenen->GetLives() * 10;
	f2.close();
	// Change to select scene.
	Engine::GameEngine::GetInstance().ChangeScene("start");
}

void WinScene::OnKeyDown(int keyCode) {
	IScene::OnKeyDown(keyCode);
	//show the input after press any character
	if(keyCode == ALLEGRO_KEY_BACKSPACE){
		LOG(INFO) << "Key Down: " << keyCode;
		if(keyStrokes.size() > 0) keyStrokes.pop_back();
		inputText = "";
		for(auto c: keyStrokes){
			inputText = inputText + (char)(c - ALLEGRO_KEY_A + 'A');
		}
		LOG(INFO) << "Input text: " << inputText;
	} else if(keyCode >= ALLEGRO_KEY_A && keyCode <= ALLEGRO_KEY_Z){
		LOG(INFO) << "Key Down: " << keyCode;
		keyStrokes.push_back(keyCode);
		inputText = "";
		for(auto c: keyStrokes){
			inputText = inputText + (char)(c - ALLEGRO_KEY_A + 'A');
		}
		LOG(INFO) << "Input text: " << inputText;
		keyCode = 0;

	}	
}

void WinScene::Draw() const {
	IScene::Draw();
	//draw the input text
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
	int halfH = h / 2;
	Engine::Label label(inputText, "pirulen.ttf", 48, halfW, halfH/4 + 50, 255, 255, 255, 255, 0.5, 0.5);
	label.Anchor = Engine::Point(0.5, 0.5);	
	label.Draw();
}
