/*********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Filename      : QuadTreeNode.h
 * Last modified : 2015-08-25
 * Description   : 
 *********************************************************/

#ifndef _QUADTREENODE_H_
#define _QUADTREENODE_H_
#include <list>

enum QuadType
{
	ROOT,         
	UP_RIGHT,     
	UP_LEFT,      
	BOTTOM_LEFT,  
	BOTTOM_RIGHT  
};

template <typename T>
class CQuadTreeNode
{
public:
	CQuadTreeNode(float _x,float _y,float _width,float _height,int _level,int _maxLevel,QuadType _quadType,CQuadTreeNode *_parent);
	~CQuadTreeNode();
public:
	void InsertObject(T *object); 
	std::list<T *> GetObjectsAt(float px,float py,float w,float h); 
    // 返回给定区域内的物体
	std::list<T *> GetObjects(float px,float py,float w,float h); 
	void RemoveObjectsAt(float px,float py,float w,float h); 

private:
	bool IsRectContainObject(float px,float py,float w,float h,T *object) const; 
	bool IsContained(float px,float py,float w,float h) const; 
	bool IsContain(float px,float py,float w,float h) const; 
private:
	std::list<T *> objects; 
	
	CQuadTreeNode *parent;
	CQuadTreeNode *upRightNode;
	CQuadTreeNode *upLeftNode;
	CQuadTreeNode *bottomLeftNode;
	CQuadTreeNode *bottomRightNode;
	
	QuadType quadType;
	
	float x;
	float y;
	float width;
	float height;

	int level; 
	int maxLevel; 
};

#include "QuadTreeNode.cpp"
#endif 
