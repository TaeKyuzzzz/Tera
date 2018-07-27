#include "stdafx.h"
#include "Manager\cItemManager.h"

enum eITextTitle
{
	GOLD = 1,
	ITEMVALUE,
	CHARACTERSPEC
};


void cItemManager::UITextList()
{

	//����(1), ��ġ(3), �۾�ũ��(2), �÷�(3)
#pragma region �Ҹ�ǰ����
	CreateUICTextData
	(
		{ "�Ҹ�ǰ����", "����", "�ϱ�ȸ������", "�߱�ȸ������", "���ȸ������", "�ϱ޸�������", "�߱޸�������", "��޸�������", "�̽��׸�����", "������ȯ��" }
		, { { 200,10,0 },{ 310, 256, 0 },{ 65, 93, 0 },{ 240, 93, 0 },{ 65, 132, 0 },{ 241, 129, 0 },{ 65,172,0 },{ 241,172,0 },{ 65, 210, 0 },{ 240, 210, 0 } }
		, {  MID, SMALL, MID, MID, MID, MID, MID, MID, MID, MID }
		, { { 211, 254, 255 },{ 211, 254, 255 },{ 200, 50, 55 },{ 200, 50, 55 },{ 200, 50, 55 } ,{ 200, 50, 55 } ,{ 200, 50, 55 } ,{ 200, 50, 55 },{ 200, 50, 55 },{ 200, 50, 55 } }
	);
	tagText t1;
	t1.Type = CONSTCHAR;
	t1.szTextName = "�Ҹ�ǰ����";
	t1.szParrentName = "ConShop";
	CreateText(t1);

#pragma endregion


#pragma region �κ��丮
	CreateUIITextData
	(
		//�κ��丮
		{ GOLD, m_nGold }
		, { { 50,10,0 },{ 200,334,0 } }
		, { MID, SMALL }
		, { { 128,128,128 },{ 255,255,255 } }
	);

	tagText t4;
	t4.Type = VARIABLEVALUE;
	t4.nIdentyfyNum = GOLD;
	t4.szParrentName = "Inventory";
	CreateText(t4);
#pragma endregion

#pragma region �������ͽ�â
	CreateUICTextData
	(
		{ "����", "���ݷ�", "����" }
		, { {129,9,0}, {15,261,0}, {145,261,0} }
		, { MID, MID, MID }
		, { {236,139,255}, {50,79,255},{ 50,79,255} }
	);

	tagText t5;
	t5.Type = CONSTCHAR;
	t5.szTextName = "����";
	t5.szParrentName = "Status";
	CreateText(t5);

	CreateUIITextData
	(
		{ CHARACTERSPEC, ZEROVALUE, ZEROVALUE }
		, { {0,0,0},		{92,261,0},		{230 ,261,0 } }
		, { MID, MID, MID }
		, { {0,0,0},		{6,255,54},		{6,255,54} }
	);

	tagText t6;
	t6.Type = VARIABLEVALUE;
	t6.nIdentyfyNum = CHARACTERSPEC;
	t6.szParrentName = "Status";
	CreateText(t6);
	

#pragma endregion



#pragma region ����������
	CreateUICTextData
	(
		{ "����������","�ɷ�", "����:", "�����ǳ���", "�ǸŶǴ±��Ű���"}
		, { { 50,10,0 },{ 50,40,0 },{ 10,90,0 }, {30, 120, 0}, {30, 200,0 }}
		, { MID, MID, MID, MID, SMALL }
		, { { 135,132,255 },{ 200,200,200 },{ 128,128,128 }, {128,128,128}, {255,255,255} }
	);

	tagText t2;
	t2.Type = CONSTCHAR;
	t2.szTextName = "����������";
	t2.szParrentName = "ItemExplaneWindow";
	CreateText(t2);


	CreateUIITextData
	(
		{ ITEMVALUE, ZEROVALUE, ZEROVALUE}
		, { { 0, 0, 0 },{ 155, 38, 0 }, {130, 200, 0} }
		, { MID, MID, SMALL }
		, { { 0, 0, 0 },{ 230, 50, 230 }, {255, 255, 255} }
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
	textExplane["��ġ"] = "Į���� �� ��ġ,\n ���� �� ����";
	textExplane["���̽��ҵ�"] = "������ ����ȭ�� \n ���� ��";
	textExplane["��ī�̼ҵ�"] = "�ϴ��� �����\n ��Ƹ��� ��";
	textExplane["���������ǿ�"] = "��� ������ ���\n�� ���� ��";
	textExplane["���������ǽŹ�"] = "��� ������ ���\n�� ���� �Ź�";
	textExplane["�����������尩"] = "��� ������ ���\n�� ���� �尩";
	textExplane["�����Ƹ�"] = "������ �����\n ���� ����";
	textExplane["��������"] = "������ ����\n ���� �Ź�";
	textExplane["�����۷���"] = "������ �����\n ���� �尩";
	textExplane["�����÷��Ƹ�"] = "����� õ�� \n����� ���� ��";
	textExplane["�����÷�����"] = "����� õ�� \n����� ���� �Ź�";
	textExplane["�����÷��۷���"] = "����� õ�� \n����� ���� �尩";
	

	 


}









