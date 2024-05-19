#ifndef WINSCENE_HPP
#define WINSCENE_HPP
#include <list>
#include <allegro5/allegro_audio.h>
#include <memory>
#include <vector>
#include <sstream>
#include "Engine/IScene.hpp"

class WinScene final : public Engine::IScene {
private:
	float ticks;
	ALLEGRO_SAMPLE_ID bgmId;
	std::list<int> keyStrokes;
	std::stringstream ss;
	std::string inputText;
public:
	explicit WinScene() = default;
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void BackOnClick(int stage);
	//designed for input box
	void OnKeyDown(int keyCode) override;
	//draw the input text
	void Draw() const override;
};

#endif // WINSCENE_HPP
