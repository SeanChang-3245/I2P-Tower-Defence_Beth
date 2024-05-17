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
    void PrevOnClick(int stage);
    void NextOnClick(int stage);
    void BackOnClick(int stage);
    void ReadScore();

    std::vector<struct Player> player;
    int CurrentPage;
    int TotalPage;
    int TotalPlayer;
    std::vector<Engine::Label*> row_name;
    std::vector<Engine::Label*> row_score;
};

struct Player{
    std::string name;
    std::string score;
};

#endif 