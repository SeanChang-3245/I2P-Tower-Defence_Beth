#include <functional>
#include <string>
#include <sstream>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/Group.hpp"
#include "WinScene.hpp"
#include "PlayScene.hpp"
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
	// Change to select scene.
	Engine::GameEngine::GetInstance().ChangeScene("start");
}

void WinScene::OnKeyDown(int keyCode) {
	IScene::OnKeyDown(keyCode);
	//show the input after press any character
	if(keyCode == ALLEGRO_KEY_BACKSPACE){
		keyStrokes.pop_back();
	} else if(keyCode >= ALLEGRO_KEY_A && keyCode <= ALLEGRO_KEY_Z){
		LOG(INFO) << "Key Down: " << keyCode;
		keyStrokes.push_back(keyCode);
		ss << (char)(keyCode - ALLEGRO_KEY_A + 'A');
		inputText = ss.str();
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
	//LOG(INFO) << "Draw input text: " << inputText;
	Engine::Label label("Hi", "pirulen.ttf", 48, halfW, halfH/4 + 30, 225, 225, 225, 1, 0.5, 0.5);
	label.Anchor = Engine::Point(0.5, 0.5);	
	label.Draw();
}
