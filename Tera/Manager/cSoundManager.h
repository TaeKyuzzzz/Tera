#pragma once


#include "../inc/fmod.hpp"

#pragma comment(lib,"lib/fmodex_vc.lib")
using namespace FMOD;

#define SOUNDMANAGER cSoundManager::GetInstance()


// ä�� ����, ���� ����
#define EXTRACHANNELBUFFER 100
#define SOUNDBUFFER 100

// �� ���� ����
#define TOTALSOUNDBUFFER (SOUNDBUFFER + EXTRACHANNELBUFFER)

class cSoundManager
{
private:
	SINGLETONE(cSoundManager);

	typedef map<string, Sound**> arrSounds;
	typedef map<string, Sound**>::iterator arrSoundIter;

	System * m_system;		// fmod�� �ý��� Ŭ����
	Sound** m_sound;		// fmod�� ���� Ŭ����
	Channel** m_channel;	// fmod�� ä��   Ŭ����

	arrSounds m_totalSounds;


	float bgmVolume = 0.5f;
	float effectVolume = 0.5f;

	string bgmKey;

	/*
	ä���� ������ ���� ���¸� ����
	*/


	// ������� ��ũ�� �� ���� ����!!!

	// �ϴ� ���͸� ���� ��Ʈ�� �־����

	vector<int> m_vBeat;
	vector<int>::iterator m_viBeat;

	// �� ���͸� �ʿ� �����ؼ� �ߺ����� �ε���� �ʰ�

	map<string, vector<int>>m_mBeat;
	map<string, vector<int>>::iterator m_miBeat;
	// ���Ϳ� ���� ��Ʈ ������ Ž�� ���� �����Ͱ� �ʿ���
	FILE * fp;

public:

	void Setup();
	void Release();
	void Update();
	void Render();

	// ���� �߰� (Ű��, �����̸�, BGM, LOOP)
	void AddSound(string KeyName, string fileName,
		bool bgm = FALSE, bool LOOP = false);

	// ���� �÷��� (Ű��, ���� ) 0.0 ~ 1.0;
	void Play(string KeyName, float volume = 1.0f);
	// ���� ����
	void Stop(string KeyName);
	// ���� �Ͻ� ����
	void Pause(string KeyName);
	// ���� �ٽ� ���
	void resume(string KeyName, float volume);
	// �÷��� ������ ���� Ȯ��
	bool isPlaySound(string KeyName);
	// �Ͻ�����
	bool IspauserSound(string KeyName);

	// ��� ���
	void PlayBGM(string KeyName);
	// ����Ʈ ���
	void PlayEffect(string KeyName);

	// ���� ���� ����
	void SetVolume(string key, float vol);

	// �� ��� ���� ����

	void SetBGMVolume(string key, float vol);

	// ��� �Ҹ� ��ž
	void AllStop();

	//////////////////////////////////
	//
	// ���� ���ʹ� ��ũ�δ� ���� �Լ�1
	//
	/////////////////////////////////

	// ��ũ�� �� �������� ������ ��� ����� ���� Ʈ�� �Լ�
	void PlayZoneBGM(string key, float vol);

	void PauseZoneBGM(string key);

	void ResumeZoneBGM(string key, float vol);

	void SetBgm(string key) { bgmKey = key; }

	void PlayBGM() { Play(bgmKey, bgmVolume); }
	void PauseBGM() { Pause(bgmKey); }

	float GetBgmVolum() { return bgmVolume; }
	float GetEffectVolum() { return effectVolume; }

	void SetBgmVolum(float n) { bgmVolume = n; }
	void SetEffectVolum(float n) { effectVolume = n; }

	string GetBgmKey() { return bgmKey; }

};