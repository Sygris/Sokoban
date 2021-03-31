#include "Audio.h"

Audio::Audio()
{
	// Frequency value (KHz), audio format, number of channels, total chunk size (sample size) 
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 512);
}

Audio::~Audio()
{
	if (&m_music != NULL)
	{
		for (int i = 0; i < m_music.size(); i++)
		{
			Mix_FreeMusic(m_music[i]);
		}
	}

	if (&m_sfx != NULL)
	{
		for (int i = 0; i < m_sfx.size(); i++)
		{
			Mix_FreeChunk(m_sfx[i]);
		}
	}

	m_tempChunk = nullptr;
	m_tempMusic = nullptr;

	Mix_CloseAudio();
}

bool Audio::LoadAudio(std::string filename, int id, type audioType, int volume)
{
	if (audioType == MUSIC)
	{
		m_tempMusic = Mix_LoadMUS(filename.c_str());

		if (!m_tempMusic)
		{
			std::cout << "Unable to load music file: " << Mix_GetError() << std::endl;
			return false;
		}

		m_music.push_back(m_tempMusic);
		Mix_VolumeMusic(volume);

		return true;
	}
	else if (audioType == SFX)
	{
		m_tempChunk = Mix_LoadWAV(filename.c_str());

		if (!m_tempChunk)
		{
			std::cout << "Unable to load SFX file: " << Mix_GetError() << std::endl;
			return false;
		}

		m_sfx.push_back(m_tempChunk);
		Mix_VolumeChunk(m_tempChunk, volume);

		return true;
	}

	return false;
}

void Audio::PlayMusicTrack(int id, int loopNumber)
{
	Mix_PlayMusic(m_music[id], loopNumber);
}

void Audio::PlaySFX(int id, int loopNumber, int channel)
{
	if (!Mix_Playing(channel))
	{
		Mix_PlayChannel(channel, m_sfx[id], loopNumber);
	}
}

void Audio::FadeMusicTrack(int id, int loopNumber, int fadeLenght)
{
	if (Mix_PlayingMusic())
	{
		Mix_FadeOutMusic(fadeLenght);
	}

	Mix_FadeInMusic(m_music[id], loopNumber, fadeLenght);
}
