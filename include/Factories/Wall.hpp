#ifndef SUPER_HAXAGON_WALL_HPP
#define SUPER_HAXAGON_WALL_HPP

#include <memory>
#include <array>

#include "Core/Structs.hpp"

namespace SuperHaxagon {
	class Wall {
	public:

		//Overflow so you don't get glitched lines between hexagons.
		//This is really just some arbitrary number so yeah...
		static constexpr double WALL_OVERFLOW = TAU/900.0;

		Wall(double distance, double height, int side);

		void advance(double speed);
		Movement collision(double cursorHeight, double cursorPos, double cursorStep, int sides) const;
		std::array<Point, 4> calcPoints(const Point& focus, double rotation, double sides, double hexLength) const;
		static Point calcPoint(const Point& focus, double rotation, double overflow, double distance, double sides, int side);

		double getDistance() const {return distance;}
		double getHeight() const {return height;}
		int getSide() const {return side;}

	private:
		double distance;
		double height;
		int side;
	};

	class WallFactory {
	public:
		static constexpr int MIN_WALL_HEIGHT = 4;

		WallFactory(std::ifstream& file, int maxSides);

		std::unique_ptr<Wall> instantiate(double offsetDistance, int offsetSide, int sides) const;

	private:
		uint16_t distance = 0;
		uint16_t height = 0;
		uint16_t side = 0;
	};
}

#endif //SUPER_HAXAGON_WALL_HPP