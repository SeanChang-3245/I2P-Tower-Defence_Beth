#ifndef SCOREBOARDSCENE_HPP
#define SCOREBOARDSCENE_HPP
#include <allegro5/allegro_audio.h>
#include <memory>
#include <vector>
#include "Engine/IScene.hpp"

class ScoreBoardScene final : public Engine::IScene{
private:
	std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
public:
	explicit ScoreBoardScene() = default;
	void Initialize() override;
	void Terminate() override;
    void PrevOnClick();
    void NextOnClick();
    void BackOnClick(int stage);
    void ReadScore();

    std::vector<struct Player> player;
    int CurrentPage;
    int TotolPage;
    int TotalPlayer;
};

struct Player{
    std::string name;
    std::string score;
};

#endif 