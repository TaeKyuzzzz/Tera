#include "stdafx.h"
#include "Manager\cItemManager.h"

enum eITextTitle
{
	GOLD = 1,
	ITEMVALUE
};


void cItemManager::UITextList()
{

	//����(1), ��ġ(3), �۾�ũ��(2), �÷�(3)
#pragma region �Ҹ�ǰ����
	CreateUICTextData
	(
		{ "�Ҹ�ǰ����", "�����ϱ�", "ȸ������", "�߱�ȸ������", "���ȸ������", "��������", "�߱޸�������", "��޸�������" }
		, { { 200,10,0 },{ 310, 256, 0 },{ 65, 93, 0 },{ 240, 93, 0 },{ 65, 132, 0 },{ 241, 129, 0 },{ 65,172,0 },{ 241,172,0 } }
		, { { 25, 15 },{ 15, 5 },{ 20, 10 },{ 20, 10 },{ 20, 10 },{ 20, 10 },{ 20, 10 },{ 20, 10 } }
		, { { 211, 254, 255 },{ 211, 254, 255 },{ 200, 50, 55 },{ 200, 50, 55 },{ 200, 50, 55 } ,{ 200, 50, 55 } ,{ 200, 50, 55 } ,{ 200, 50, 55 } }
	);
	tagText t1;
	t1.Type = CONSTCHAR;
	t1.szTextName = "�Ҹ�ǰ����";
	t1.szParrentName = "ConsumablesShop";
	CreateText(t1);

#pragma endregion


#pragma region �κ��丮
	CreateUIITextData
	(
		//�κ��丮
		{ GOLD, m_nGold }
		, { { 50,10,0 },{ 200,334,0 } }
		, { { 25,15 } ,{ 15,8 } }
		, { { 128,128,128 },{ 255,255,255 } }
	);

	tagText t4;
	t4.Type = VARIABLEVALUE;
	t4.nIdentyfyNum = GOLD;
	t4.szParrentName = "Inventory";
	CreateText(t4);
#pragma endregion



#pragma region ����������
	CreateUICTextData
	(
		{ "�̸�","�ɷ�", "����:", "�����ǳ���"}
		, { { 50,10,0 },{ 50,40,0 },{ 10,90,0 }, {30, 120, 0} }
		, { { 25,15 },{ 25,15 },{ 25,15 }, {25, 15} }
		, { { 135,132,255 },{ 200,200,200 },{ 128,128,128 }, {128,128,128}}
	);

	tagText t2;
	t2.Type = CONSTCHAR;
	t2.szTextName = "�̸�";
	t2.szParrentName = "ItemExplaneWindow";
	CreateText(t2);


	CreateUIITextData
	(
		{ ITEMVALUE, ZEROVALUE}
		, { { 800, 100, 0 },{ 155, 38, 0 }}
		, { { 50, 15 },{ 30, 15 } }
		, { { 230, 230, 230 },{ 230, 50, 230 } }
	);

	tagText t3;
	t3.Type = VARIABLEVALUE;
	t3.nIdentyfyNum = ITEMVALUE;
	t3.szParrentName = "ItemExplaneWindow";
	CreateText(t3);
#pragma endregion

	TextExplane();
}

void cItemManager::TextExplane()
{



	textExplane["�ϱ�ȸ������"] = "�ҷ��� HP�� \n ȸ����Ų��";
	textExplane["�߱�ȸ������"] = "�������� HP��\n ȸ����Ų��";
	textExplane["���ȸ������"] = "�뷮�� HP��\n ȸ����Ų��";
	textExplane["�ϱ޸�������"] = "�ҷ��� MP��\n ȸ����Ų��";
	textExplane["�߱޸�������"] = "�������� MP��\n ȸ����Ų��";
	textExplane["��޸�������"] = "�뷮�� MP��\n ȸ����Ų��";
	textExplane["�̽��׸�����"] = "���� �ź���\n ���� �Ͼ��";
	textExplane["������ȯ��"] = "����� ������\n ��ȯ�Ѵ�";
	textExplane["���"] = "Ŀ�ٶ� ��, \n������ ���̴�.";
	textExplane["����"] = "Į���� �� ����,\n ���� �� ����";
	textExplane["���̽��ҵ�"] = "������ ����ȭ�� \n ���� ��";
	textExplane["��ī�̼ҵ�"] = "�ϴ��� �����\n ��Ƹ��� ��";
	textExplane["���������ǿ�"] = "��� ������ ���\n�� ���� ��";
	textExplane["���������ǽŹ�"] = "��� ������ ���\n�� ���� �Ź�";
	textExplane["�����������尩"] = "��� ������ ���\n�� ���� �尩";
	textExplane["�����Ƹ�"] = "������ �����\n ���� ����";
	textExplane["��������"] = "������ ����\n ���� �Ź�";
	textExplane["�����۷κ�"] = "������ �����\n ���� �尩";
	textExplane["��ī�̾Ƹ�"] = "�ϴ��� �����\n ��� ���� ��";
	textExplane["��ī�̽���"] = "�ϴ��� �����\n ��� ���� �Ź�";
	textExplane["��ī�̱۷κ�"] = "�ϴ��� �����\n ��� ���� �尩";
	

	 


}









