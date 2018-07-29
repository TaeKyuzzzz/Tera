#include "stdafx.h"
#include "cBoundingBoxLoader.h"

#include "Scene/11_MapEdit/cBoundingObject.h"
#include "Scene/11_MapEdit/cSceneMapEdit.h"
#include "Scene/11_MapEdit/Ray_toCube.h"
#include "Spere/cSpere.h"
#include "BoundingBox/cBoundingBox.h"


cBoundingBoxLoader::cBoundingBoxLoader()
{
	m_pEditor = new cSceneMapEdit;
}


cBoundingBoxLoader::~cBoundingBoxLoader()
{
	SAFE_DELETE(m_pEditor);
}

void cBoundingBoxLoader::Setup()
{
	m_pEditor->ObjectLoad();
	//m_pEditor->Update();
}

void cBoundingBoxLoader::Update()
{
	m_pEditor->FG_Sight();

}

void cBoundingBoxLoader::Render()
{
	m_pEditor->Render();
}
