#include <3ds.h>
#include <string>
#include <memory>

#include "Driver/Player.hpp"
#include "Driver/Audio3DS.hpp"
#include "Driver/Platform3DS.hpp"

static const int SAMPLE_RATE = 48000;

namespace SuperHaxagon {
	Platform3DS::Platform3DS() {
		romfsInit();
		ndspInit();
		gfxInitDefault();

		// Setup NDSP
		ndspChnReset(0);
		ndspSetOutputMode(NDSP_OUTPUT_STEREO);
		ndspChnSetInterp(0, NDSP_INTERP_POLYPHASE);
		ndspChnSetRate(0, SAMPLE_RATE);
		ndspChnSetFormat(0, NDSP_FORMAT_STEREO_PCM16);
	}

	Platform3DS::~Platform3DS() {
		gfxExit();
		ndspExit();
		romfsExit();
	}

	bool Platform3DS::hasScreen(Screen test) {
		return test == Screen::TOP || test == Screen::BOTTOM;
	}

	std::string Platform3DS::getPath(const std::string& partial) {
		return std::string("sdmc:/3ds/data/haxagon") + partial;
	}

	std::string Platform3DS::getPathRom(const std::string& partial) {
		return std::string("romfs:") + partial;
	}

	std::unique_ptr<Audio> Platform3DS::loadAudio(const std::string& path) {
		return std::make_unique<Audio3DS>(path);
	}

	// Note: If there are no available channels the audio is silently discarded
	void Platform3DS::playSFX(Audio& audio) {
		int channel = 1;
		for (auto& player : sfx) {
			if (!player || player->isDone()) {
				player = audio.instantiate();
				player->setChannel(channel);
				player->setLoop(false);
				player->play();
			}

			channel++;
		}
	}

	void Platform3DS::playBGM(Audio& audio) {
		bgm = audio.instantiate();
		bgm->setChannel(0);
		bgm->setLoop(true);
		bgm->play();
	}

	void Platform3DS::stopBGM() {
		if (bgm) bgm->stop();
	}

	void Platform3DS::pollButtons() {
		hidScanInput();
	}

	Buttons Platform3DS::getDown() {
		return toButtons(hidKeysDown());
	}

	Buttons Platform3DS::getPressed() {
		return toButtons(hidKeysHeld());
	}

	Point Platform3DS::getScreenDim() const {
		return {screen == Screen::TOP ? 400 : 320, 240};
	}

	Point Platform3DS::getShadowOffset() const {
		return {4, 4};
	}

	void Platform3DS::drawRect(const Color& color, const Point& point, const Point& size) const {

	}

	void Platform3DS::drawTriangle(const Color& color, const std::array<Point, 3>& points) const {

	}

	void Platform3DS::drawFont(const Font& font, const Point& point, const std::string& text) const {

	}

	Buttons Platform3DS::toButtons(u32 input) {
		Buttons buttons{};
		buttons.select = (bool)(input & KEY_A);
		buttons.back = (bool)(input & KEY_B);
		buttons.quit = (bool)(input & KEY_START);
		buttons.left = (bool)(input & (KEY_L | KEY_ZL | KEY_CSTICK_LEFT | KEY_CPAD_LEFT | KEY_DLEFT | KEY_Y));
		buttons.right = (bool)(input & (KEY_R | KEY_ZR | KEY_CSTICK_RIGHT | KEY_CPAD_RIGHT | KEY_DRIGHT | KEY_X));
	}
}
