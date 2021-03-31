#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <SDL_mixer.h>

enum type
{
	MUSIC, SFX, TOTAL
};

class Audio
{
public:
	Audio();
	~Audio();

	bool LoadAudio(std::string filename, int id, type audioType, int volume);
	
	void PlayMusicTrack(int id, int loopNumber);
	void PlaySFX(int id, int loopNumber, int channel);
	void FadeMusicTrack(int id, int loopNumber, int fadeLenght);

private:
	std::vector<Mix_Chunk*> m_sfx;
	std::vector<Mix_Music*> m_music;

	Mix_Music* m_tempMusic{ nullptr };
	Mix_Chunk* m_tempChunk{ nullptr };
};

