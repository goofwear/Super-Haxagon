#include "DriverWin/FontWin.hpp"
#include "DriverWin/PlatformWin.hpp"

namespace SuperHaxagon {
	FontWin::FontWin(PlatformWin& platform, const std::string& path, const double size) :
		_platform(platform),
		_scale(1),
		_size(size) {
		_loaded = _font.loadFromFile(path + ".ttf");
	}

	FontWin::~FontWin() = default;

	void FontWin::setScale(const double scale) {
		// scale up at half rate so it looks nice I guess?
		_scale = (scale - 1) / 2 + 1;
	}

	double FontWin::getHeight() const {
		return _size * _scale;
	}

	double FontWin::getWidth(const std::string& text) const {
		if (!_loaded) return 0;
		sf::Text sfText;
		sfText.setFont(_font);
		sfText.setCharacterSize(static_cast<int>(_size * _scale));
		sfText.setString(text);
		return sfText.getLocalBounds().width;
	}

	void FontWin::draw(const Color& color, const Point& position, Alignment alignment, const std::string& text) const {
		if (!_loaded) return;
		sf::Text sfText;
		sf::Vector2f sfPosition;
		sfPosition.y = static_cast<float>(position.y);
		sfText.setFont(_font);
		sfText.setCharacterSize(static_cast<int>(_size * _scale));
		sfText.setFillColor({color.r, color.g, color.b, color.a});
		sfText.setString(text);

		const auto width = sfText.getLocalBounds().width;
		if (alignment == Alignment::LEFT) sfPosition.x = static_cast<float>(position.x);
		if (alignment == Alignment::CENTER) sfPosition.x = static_cast<float>(position.x - width / 2);
		if (alignment == Alignment::RIGHT) sfPosition.x = static_cast<float>(position.x - width);
		sfText.setPosition(sfPosition);

		_platform.getWindow().draw(sfText);
	}
}
