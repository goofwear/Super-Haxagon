#include "Driver3DS/Player3DS.hpp"

namespace SuperHaxagon {
	Player3DS::Player3DS(u8* data, const u32 sampleRate, const u32 dataSize, const u16 channels, const u16 bitsPerSample, const u16 ndspFormat) :
			_data(data),
			_sampleRate(sampleRate),
			_dataSize(dataSize),
			_channels(channels),
			_bitsPerSample(bitsPerSample),
			_ndspFormat(ndspFormat)
	{}

	Player3DS::~Player3DS() {
		Player3DS::stop();
		ndspChnWaveBufClear(_channel);
	}

	void Player3DS::play() {
		stop();
		float mix[12]{};
		mix[0] = 1.0;
		mix[1] = 1.0;
		ndspChnReset(_channel);
		ndspChnSetInterp(_channel, NDSP_INTERP_LINEAR);
		ndspChnSetRate(_channel, _sampleRate);
		ndspChnSetFormat(_channel, _ndspFormat);
		ndspChnSetMix(_channel, mix);
		_buffer.data_vaddr = &_data[0];
		_buffer.nsamples = _dataSize / _bitsPerSample * 8;
		_buffer.looping = _loop;
		_buffer.offset = 0;
		DSP_FlushDataCache(_data, _dataSize);
		ndspChnWaveBufAdd(_channel, &_buffer);
	}

	void Player3DS::stop() {
		ndspChnWaveBufClear(_channel);
	}

	bool Player3DS::isDone() {
		return _buffer.status == NDSP_WBUF_DONE;
	}
}
