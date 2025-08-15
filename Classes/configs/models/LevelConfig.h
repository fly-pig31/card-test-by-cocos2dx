#pragma once
#include "models/CardModel.h"

/// <summary>
/// ���ſ��Ƶ�������Ϣ�ṹ�壨���ڹؿ����ã�
/// �洢���Ƶĳ�ʼ���ԣ���ֵ����ɫ��λ�ã�
/// </summary>
struct CardConfig {
    CardFaceType face; // ������ֵ��A��2��...��K��
    CardSuitType suit; // ���ƻ�ɫ��÷�������顢���ҡ����ң�
    cocos2d::Vec2 position; // ���Ƴ�ʼλ�ã���������ϵ��
};

/// <summary>
/// �ؿ����ýṹ�壬�洢һ���ؿ������г�ʼ������Ϣ
/// ��Ϊ��Ϸ�����ƺ��ƶѿ���������
/// </summary>
struct LevelConfig {
    std::vector<CardConfig> playfield; // ��Ϸ����ʼ��������
    std::vector<CardConfig> stack; // �ƶѳ�ʼ��������
};
