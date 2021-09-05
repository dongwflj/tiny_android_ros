/*********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Filename      : Astar.h
 * Last modified : 2015-08-25
 * Description   : 
 *********************************************************/

#ifndef _ASTAR_H_
#define _ASTAR_H_


#include <list>
#include <vector>
#include <math.h>
#include <iostream>
#include <assert.h>
#include "core/SdkDefine.h"
#include "Object.h"
#include "QuadTreeNode.h"

using namespace std;
// 坐标点
typedef struct  _point
{
	int x;
	int y;
	int isblock;
	_point()
	{
		x = 0;
		y = 0;
	}
	_point(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
}point;
//结点
typedef struct _Node
{
	point pt;
	int f, g, h;
	struct _Node *preNode;//父节点
}Node;

class CAStar{
public:
	CAStar(void);
	~CAStar(void);
public:
	static const int SPEND_H = 10;//H值耗费
	static const int SPEND_G_FAR = 14;//远的G值耗费
	static const int SPEND_G_NEAR = 10;//近的G值耗费
	list<Node*> psOpenList;	//开放列表
	list<Node*> psCloseList;//封闭列表
	Node *sStartNode;	//起始节点
	Node *sEndNode;	//终止节点
	Node *pcurrNode;//是否是终点? NOT NULL : NULL
public:
	void SetStartNode(point st){sStartNode->pt.x = st.x;sStartNode->pt.y = st.y;};//设定起始节点
	void SetEndNode(point et){sEndNode->pt.x = et.x;sEndNode->pt.y = et.y;};//设定结束节点
	void SetQuadTree(CQuadTreeNode<CObject>* pTree){ m_pTree = pTree;};//设定结束节点
    ERESULT Search(vector<point> & path);
	void AddToOpenList(Node *src);//添加到开放列表
	void GetNodeByPoint(Node *pareNode, int _x, int _y);//通过坐标添加到开放列表
	bool IsClosed(Node *src);//坐标点是否在封闭列表中
	bool IsInOpenList(Node *src);//坐标点是否在开放列表中
	bool IsBlock(Node *src);//坐标点是否是阻挡点
	void SetH(Node *node);//设定H的耗费
	void SetG(Node *node);//设定G的耗费
	void SetF(Node *node);//设定F的耗费
	Node* GetBestNode(); //得到最优的节点(F值最低的节点)
	bool isPath(list<point> *path, int i, int j);
private:
    CQuadTreeNode<CObject>* m_pTree;
    EDIRECTION m_LastDirection;
};

#endif
