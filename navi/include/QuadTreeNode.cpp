/*********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Filename      : QuadTreeNode.cpp
 * Last modified : 2015-08-25
 * Description   : 
 *********************************************************/

template <typename T>
CQuadTreeNode<T>::CQuadTreeNode(
	float _x,float _y,float _width,float _height,
	int _level,int _maxLevel,
	QuadType _quadType,
	CQuadTreeNode *_parent):
	quadType(_quadType),
	x(_x),
	y(_y),
	width(_width),
	height(_height),
	level(_level),
	maxLevel(_maxLevel)
{
	parent=_parent;
	upRightNode=nullptr;
	upLeftNode = nullptr;
	bottomLeftNode=nullptr;
	bottomRightNode=nullptr;
}

template <typename T>
CQuadTreeNode<T>::~CQuadTreeNode()
{
	typename std::list<T*>::iterator iter; 
    for(iter=objects.begin(); iter!=objects.end(); iter++) {
        delete *iter;
    }
    objects.clear();
	if(level==maxLevel)
		return;
	//如果不是叶子节点，就销毁子节点
	parent=nullptr;
    
	delete upRightNode;
	delete upLeftNode;
	delete bottomLeftNode;
	delete bottomRightNode;
}
// Check if the input object is contained by input rect
template <typename T>
bool CQuadTreeNode<T>::IsRectContainObject(float px,float py,float w,float h,T *object) const 
{
	if(object->x>=px
		&&object->x+object->width<=px+w
		&&object->y>=py
		&&object->y+object->height<=py+h) {
		return true;
    }
	return false;
}

// Check if the input node is contained by the input rect
template <typename T>
bool CQuadTreeNode<T>::IsContained(float px,float py,float w,float h) const
{
	if(x>=px && x+width<=px+w && y>=py
		&& y+height<=py+h) {
		return true;
    }
	return false;
}
// Check if the input rect is contained by the quad node's rect
template <typename T>
bool CQuadTreeNode<T>::IsContain(float px,float py,float w,float h) const
{
	if(x<=px && x+width>=px+w && y<=py && y+height>=py+h) {
		return true;
    }
	return false;
}

template <typename T>
void CQuadTreeNode<T>::InsertObject(T *object) {
	//如果是叶子节点，则存在叶子节点
	if(level==maxLevel) {
		objects.push_back(object);
		return;
	}
	
	//非叶子节点，如果下层节点可以包含该对象，则递归构建子节点并插入对象,边构建边插入
	if(IsRectContainObject(x+width/2,y,width/2,height/2,object)) {
		if(!upRightNode) //避免重复创建覆盖掉原来的节点
			upRightNode=new CQuadTreeNode(x+width/2,y,width/2,height/2,level+1,maxLevel,UP_RIGHT,this);//如果没有子节点就创建子节点，parent节点是当前节点
		upRightNode->InsertObject(object);
		return;
	}
	else if(IsRectContainObject(x,y,width/2,height/2,object))
	{
		if(!upLeftNode)
			upLeftNode=new CQuadTreeNode(x,y,width/2,height/2,level+1,maxLevel,UP_LEFT,this);
		upLeftNode->InsertObject(object);
		return;
	}
	else if(IsRectContainObject(x,y+height/2,width/2,height/2,object))
	{
		if(!bottomLeftNode)
			bottomLeftNode=new CQuadTreeNode(x,y+height/2,width/2,height/2,level+1,maxLevel,BOTTOM_LEFT,this);
		bottomLeftNode->InsertObject(object);
		return;
	}
	else if(IsRectContainObject(x+width/2,y+height/2,width/2,height/2,object))
	{
		if(!bottomRightNode)
			bottomRightNode=new CQuadTreeNode(x+width/2,y+height/2,width/2,height/2,level+1,maxLevel,BOTTOM_RIGHT,this);
		bottomRightNode->InsertObject(object);
		return;
	}
	//下层节点不能完全包含改对象，则插入到当前非叶子节点
    objects.push_back(object);
}

template <typename T>
std::list<T *> CQuadTreeNode<T>::GetObjects(float px,float py,float w,float h) {
    std::list<T *> resObjects;
    if(!IsContain(px,py,w,h)) {
        return resObjects;
	}

    //最后一层
    if(level==maxLevel) {
		resObjects.insert(resObjects.end(),objects.begin(),objects.end());
        return resObjects;
    }
	//如果有下层节点就把下层节点包含的对象加进来
	if(upRightNode) {
		std::list<T *> upRightChild;
		upRightChild=upRightNode->GetObjects(px,py,w,h);
		resObjects.insert(resObjects.end(),upRightChild.begin(),upRightChild.end());
	}		
	if(upLeftNode) {
		std::list<T *> upLeftChild;
		upLeftChild=upLeftNode->GetObjects(px,py,w,h);
		resObjects.insert(resObjects.end(),upLeftChild.begin(),upLeftChild.end());
	}	
	if(bottomLeftNode) {
		std::list<T *> bottomLeftChild;
		bottomLeftChild=bottomLeftNode->GetObjects(px,py,w,h);
		resObjects.insert(resObjects.end(),bottomLeftChild.begin(),bottomLeftChild.end());
	}
	if(bottomRightNode) {
		std::list<T *> bottomRightChild;
		bottomRightChild=bottomRightNode->GetObjects(px,py,w,h);
		resObjects.insert(resObjects.end(),bottomRightChild.begin(),bottomRightChild.end());
	}
    if(resObjects.size() == 0) {
		resObjects.insert(resObjects.end(),objects.begin(),objects.end());
	}

	return resObjects;
}
// Get the input rect contained all objects
template <typename T>
std::list<T *> CQuadTreeNode<T>::GetObjectsAt(float px,float py,float w,float h)
{
	std::list<T *> resObjects;
	//如果当前节点完全被包含，把当前节点存的对象放到列表末尾,空链表也行
	if(IsContained(px,py,w,h)) {
		resObjects.insert(resObjects.end(),objects.begin(),objects.end());
		//最后一层
		if(level==maxLevel)
			return resObjects;
	}

	//如果有下层节点就把下层节点包含的对象加进来
	if(upRightNode)
	{
		std::list<T *> upRightChild;
		upRightChild=upRightNode->GetObjectsAt(px,py,w,h);
		resObjects.insert(resObjects.end(),upRightChild.begin(),upRightChild.end());
	}		
	if(upLeftNode)
	{
		std::list<T *> upLeftChild;
		upLeftChild=upLeftNode->GetObjectsAt(px,py,w,h);
		resObjects.insert(resObjects.end(),upLeftChild.begin(),upLeftChild.end());
	}	
	if(bottomLeftNode)
	{
		std::list<T *> bottomLeftChild;
		bottomLeftChild=bottomLeftNode->GetObjectsAt(px,py,w,h);
		resObjects.insert(resObjects.end(),bottomLeftChild.begin(),bottomLeftChild.end());
	}
	if(bottomRightNode)
	{
		std::list<T *> bottomRightChild;
		bottomRightChild=bottomRightNode->GetObjectsAt(px,py,w,h);
		resObjects.insert(resObjects.end(),bottomRightChild.begin(),bottomRightChild.end());
	}
	return resObjects;
}

template <typename T>
void CQuadTreeNode<T>::RemoveObjectsAt(float px,float py,float w,float h)
{
	//如果本层节点被包含则删除本层节点的对象
	//这个判断主要是对根节点起作用，其他子节点实际在上层都做了判断
	if(IsContained(px,py,w,h))
	{
        typename std::list<T *>::iterator iter; 
        for(iter=objects.begin(); iter!=objects.end(); iter++) {
            delete *iter;
        }
		//清除本节点层的对象
		objects.clear();
		//最后一层
		if(level==maxLevel)
			return;
	}
	//如果有子节点且被包含就销毁子节点，注意别产生野指针
	//其实只要上层被包含了，下层肯定被包含，代码还需改进
	/*if(upRightNode) {
		upRightNode->RemoveObjectsAt(px,py,w,h);
	}
	if(upLeftNode) {
		upLeftNode->RemoveObjectsAt(px,py,w,h);
	}
	if(bottomLeftNode) {
		bottomLeftNode->RemoveObjectsAt(px,py,w,h);
	}
	if(bottomRightNode) {
		bottomRightNode->RemoveObjectsAt(px,py,w,h);
    }*/
    if(upRightNode&& upRightNode->IsContained(px,py,w,h))
    {
        upRightNode->RemoveObjectsAt(px,py,w,h);
        delete upRightNode;
        upRightNode=nullptr;   

    }
    if(upLeftNode&&upLeftNode->IsContained(px,py,w,h))
    {
        upLeftNode->RemoveObjectsAt(px,py,w,h);
        delete upLeftNode;
        upLeftNode=nullptr;

    }
    if(bottomLeftNode&&bottomLeftNode->IsContained(px,py,w,h))
    {
        bottomLeftNode->RemoveObjectsAt(px,py,w,h);
        delete bottomLeftNode;
        bottomLeftNode=nullptr;

    }
    if(bottomRightNode&&bottomRightNode->IsContained(px,py,w,h))
    {
        bottomRightNode->RemoveObjectsAt(px,py,w,h);
        delete bottomRightNode;
        bottomRightNode=nullptr;        
    }

}
