#pragma once

#define CAMERAMANAGER cCameraManager::GetInstance()

class cCamera;

enum CAMERA_TYPE
{
	CAMERA_FREE,
	CAMERA_FIX
};
class cCameraManager
{
	SINGLETONE(cCameraManager);

private :

	SYNTHESIZE(CAMERA_TYPE, m_type, Type);
	
	cCamera*		m_pCamera;

	float			m_fShakingTime;
public :

	void Create();
	void Update();

	void Shaking(float time);
	void Destroy();

};

