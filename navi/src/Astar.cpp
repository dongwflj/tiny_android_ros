/*********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Filename      : Astar.cpp
 * Last modified : 2015-08-25
 * Description   : 
 *********************************************************/

#include "Astar.h"
#include "common/CommonLog.h"
#include <string>

CAStar::CAStar(void)
{
	sStartNode = new Node();
	sEndNode = new Node();
	pcurrNode = NULL;
    m_pTree = NULL;
    m_LastDirection = DIR_STOP;
}
CAStar::~CAStar(void)
{
    /*for(list<Node*>::iterator iter = psOpenList.begin(); iter != psCloseList.end(); ++iter) {
        if(*iter != sStartNode && *iter != sEndNode && *iter != pcurrNode) {
            delete *iter;
        }
    }
    for(list<Node*>::iterator iter = psCloseList.begin(); iter != psCloseList.end(); ++iter) {
        if(*iter != sStartNode && *iter != sEndNode && *iter != pcurrNode) {
            delete *iter;
        }
    }*/
	delete sStartNode;
	delete sEndNode;
	delete pcurrNode;
}

ERESULT CAStar::Search(vector<point> & path) {
    LOG_DBG("Search entry\n");
    ERESULT ret = E_OK;
	Node *currentNode;//当前节点
	currentNode = sStartNode;
	currentNode->preNode = NULL;//初始节点的父节点为空
	currentNode->g = 0;
	SetH(currentNode);
	SetF(currentNode);
	psOpenList.push_front(sStartNode);//添加起始点到开放列表
	do 
	{
		currentNode = GetBestNode();//从开放列表得到最优节点
		//遍历当前结点周围的结点并加入开放列表，当前节点从开放列表中移到封闭列表中
		AddToOpenList(currentNode);
		
		psCloseList.push_front(currentNode);//添加到关闭列表中
		if(psOpenList.size() < 1 || pcurrNode) {
            if (psOpenList.size() < 1) {
                LOG_WARN("A star can't find a path, exit\n");
                ret = E_FAIL;
            }
            break; //如果目标节点已经存在于开放列表或开放列表是空则退出
        }
	} while (true);
    if (ret != E_OK) {
        return ret;
    }
    string strPath;
	do {
		path.push_back(currentNode->pt);
        //LOG_INFO("Path point:" << currentNode->pt.x << "\t" 
        //        << currentNode->pt.y << endl);
#ifdef __ANDROID_NDK__
        std::ostringstream ssx, ssy;
        ssx << currentNode->pt.x;
        ssy << currentNode->pt.y;
        strPath =  "(" + ssx.str() + "," + ssy.str() + ") " + strPath;
#else
        strPath =  "(" + to_string(currentNode->pt.x) + "," + to_string(currentNode->pt.y) + ") " + strPath;
#endif
        if(currentNode->pt.x == sStartNode->pt.x && currentNode->pt.y == sStartNode->pt.y) {
            break;
        }
        currentNode = currentNode->preNode;
    } while (true);
    LOG_INFO("Search exit path:" << strPath << endl);
    return ret;
}

bool CAStar::isPath(list<point> *path, int i, int j)
{
    for(list<point>::iterator openIterator = path->begin(); openIterator != path->end(); ++openIterator)
    {
        if((*openIterator).x == i && (*openIterator).y == j){return true;}
    }
    return false;
}

//添加到开放列表
void CAStar::AddToOpenList(Node *src){
    //添加当前坐标的周围坐标(一共8个方向)
    GetNodeByPoint(src, src->pt.x, src->pt.y + 1);//上
    GetNodeByPoint(src, src->pt.x, src->pt.y - 1);//下
    GetNodeByPoint(src, src->pt.x - 1, src->pt.y);//左
    GetNodeByPoint(src, src->pt.x + 1, src->pt.y);//右
    GetNodeByPoint(src, src->pt.x - 1, src->pt.y + 1);//左上
    GetNodeByPoint(src, src->pt.x - 1, src->pt.y - 1);//左下
    GetNodeByPoint(src, src->pt.x + 1, src->pt.y + 1);//右上
    GetNodeByPoint(src, src->pt.x + 1, src->pt.y - 1);//右下
}
void CAStar::GetNodeByPoint(Node *pareNode, int _x, int _y)
{
    //如果坐标已经越界则不添加---具体参数读配置文件
    //if(_x < -10 || _y < -5 || _x > 10 || _y > 70) {
    if(_x < -50 || _y < -50 || _x > 50 || _y > 50) {
        LOG_INFO("Point is out of scope:" << _x << ',' << _y << endl);
        return ;
    }
    Node *sNode = new Node();
    //设定坐标值
    sNode->pt.x = _x;
    sNode->pt.y = _y;
    //如果此坐标存在于封闭列表或是阻挡物的话，不进行添加
    if(IsClosed(sNode) || IsBlock(sNode))
    {
        delete sNode;
        return;
    }
    else
    {
        //设定父结点
        sNode->preNode = pareNode;
        SetG(sNode);SetH(sNode);SetF(sNode);//设定各种耗费
        psOpenList.push_front(sNode);//添加到开放列表
        if(sNode->pt.x == sEndNode->pt.x && sNode->pt.y == sEndNode->pt.y)
            pcurrNode = sNode;//终点坐标已经存在于开放列表
    }
}
//是否存在于封闭列表
bool CAStar::IsClosed(Node *src)
{
    for(list<Node*>::iterator openIterator = psCloseList.begin(); openIterator != psCloseList.end(); ++openIterator)
    {
        if((*openIterator)->pt.x == src->pt.x && (*openIterator)->pt.y == src->pt.y){return true;}
    }
    return false;
}
//是否存在于开放列表
bool CAStar::IsInOpenList(Node *src)
{
    for(list<Node*>::iterator openIterator = psOpenList.begin(); openIterator != psOpenList.end(); ++openIterator)
    {
        if((*openIterator)->pt.x == src->pt.x && (*openIterator)->pt.y == src->pt.y){return true;}
    }
    return false;
}
//是否是阻挡坐标
bool CAStar::IsBlock(Node *src)
{
    list<CObject *> resObjects=m_pTree->GetObjects(src->pt.x, src->pt.y, 1, 1);
    /*	if (resObjects.size()>0) {
        cout << "Found object x:" << src->pt.x << ",y:" << src->pt.y
        << " obj count:" << resObjects.size() << endl;
        }*/
    list<CObject *>::iterator iter;
    int ratio = 0;
    for(iter=resObjects.begin(); iter!=resObjects.end(); iter++) {
        if ((int)(*iter)->x == src->pt.x && (int)(*iter)->y == src->pt.y) {
            ratio++;
            if (ratio > 10) {
                LOG_DBG("Found obstacle:" << src->pt.x << "," << src->pt.y << endl);
                return true;
            }
        }
    }
    return false;
}
//计算从B点(某点)到终点的耗费
void CAStar::SetH(Node *node)
{
    node->h = (abs(node->pt.x - sEndNode->pt.x) + abs(node->pt.y - sEndNode->pt.y)) * SPEND_H;
}
//计算从起点到B点(某点)的耗费
void CAStar::SetG(Node *node)
{
    if(node->pt.x != node->preNode->pt.x && node->pt.y != node->preNode->pt.y)
        node->g = node->preNode->g + SPEND_G_FAR;
    else
        node->g = node->preNode->g + SPEND_G_NEAR;
}
//计算总体耗费 F = G + H
void CAStar::SetF(Node *node)
{
    node->f = node->g + node->h;
}
//从开放列表中得到最优值(F值最低)
Node* CAStar::GetBestNode()
{
    Node* bNode = NULL;
    int bestF = 9999999;
    list<Node*>::iterator iterT;//记录最优值的位置方便删除
    for(list<Node*>::iterator openIterator = psOpenList.begin(); openIterator != psOpenList.end(); ++openIterator)
    {
        if(bestF > (*openIterator)->f){
            bestF = (*openIterator)->f; bNode = *openIterator;
            iterT = openIterator;
        }
    }
    if(bNode)
        psOpenList.erase(iterT);//找到最优值后从开放列表中删除
    return bNode;
}


