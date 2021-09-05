/*********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Filename      : Object.h
 * Last modified : 2015-08-25
 * Description   : 
 *********************************************************/

#ifndef _ORBOBJECT_H_
#define _ORBOBJECT_H_

class CObject
{
public:
	CObject(float _x,float _y,float _width,float _height);
	~CObject();
public:
	//对象的属性，例如坐标和长宽，以左上角为锚点
	float x;
	float y;
	float width;
	float height;
};

#endif
