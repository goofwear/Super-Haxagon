#ifndef SUPER_HAXAGON_PLAY_HPP
#define SUPER_HAXAGON_PLAY_HPP

#include "State.hpp"

namespace SuperHaxagon {
	class Game;
	class Audio;
	class Level;
	class LevelFactory;
	class Platform;

	class Play : public State {
	public:
		static constexpr int PULSE_TIME = 75;
		static constexpr double PULSE_TIMES = 2.0;
		static constexpr double SKEW_MAX = 0.3;
		static constexpr double SKEW_MIN_FRAMES = 120.0;

		Play(Game& game, LevelFactory& factory, LevelFactory& selected, double startScore);
		Play(Play&) = delete;
		~Play() override;

		std::unique_ptr<State> update(double dilation) override;
		void drawTop(double scale) override;
		void drawBot(double scale) override;
		void enter() override;
		void exit() override;

	private:
		Game& _game;
		Platform& _platform;
		LevelFactory& _factory;
		LevelFactory& _selected;
		std::unique_ptr<Level> _level;

		double _scalePrev = 0;
		double _scoreWidth = 0;
		double _score = 0;
		double _skewFrame = 0.0;
		double _skewDirection = 1.0;
	};
}

#endif //SUPER_HAXAGON_PLAY_HPP
