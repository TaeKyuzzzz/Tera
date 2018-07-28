#pragma once

#define SHADERMANAGER cShaderManager::GetInstance()

class cShader;

class cShaderManager
{
	SINGLETONE(cShaderManager);

private :
	map<string, cShader*> m_mapShader;
public :

	void AddShader(string key, const char * szFolder, const char* szFile);
	cShader* GetShader(string key);
};

