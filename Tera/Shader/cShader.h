#pragma once
class cShader
{
public:
	cShader();
	~cShader();

	static LPD3DXEFFECT LoadShader(const char* szFolder, const char* szFile);
	static LPD3DXMESH	LoadModel(const char* szFolder, const char* szFile);
};

