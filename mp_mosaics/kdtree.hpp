/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>
using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if(first[curDim]<second[curDim])
    {
      return true;
    }
    else if(first[curDim]>second[curDim])
    {
      return false;
    }
    else
    {
      return first<second;
    }
    
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double sum1=0;
    double sum2=0;
    for (int i = 0; i < Dim; ++i)
    {
      sum1+=(target[i]-currentBest[i])*(target[i]-currentBest[i]);
    }
    for (int i = 0; i < Dim; ++i)
    {
      sum2+=(target[i]-potential[i])*(target[i]-potential[i]);
    }
    if(sum2<sum1)
      return true;
    else if(sum1<sum2)
      return false;
    else
      return potential<currentBest;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findKthSmallest(vector<Point<Dim>> points, int k,int start, int d)
{
  for(int i=start+1; i<(int)(points.size()); i++)
  {
    if(points[start][d]>points[i][d])
    {
      Point<Dim> temp=points[start];
      points[start]=points[i];
      points[i]=temp;
    }
    else if(points[start][d]==points[i][d]&&points[i]<points[start])
    {
      Point<Dim> temp=points[start];
      points[start]=points[i];
      points[i]=temp;
    }
  }
  if(k==0)
    return points[start];
  else
    return findKthSmallest(points,k-1,start+1,d);
}

template <int Dim>
void KDTree<Dim>::KDTreeBuildHelper(const vector<Point<Dim>>& newPoints, KDTreeNode *& rt, int d)
{
  if((int)(newPoints.size())==0)
  {
    rt=NULL;
    return;
  }
  else if((int)(newPoints.size())==1)
  {
    rt=new KDTreeNode(newPoints[0]);
    return;
  }

  int midIdx=(int)(newPoints.size()-1)/2;
  Point<Dim> midPoint=findKthSmallest(newPoints,midIdx,0,d);
  rt=new KDTreeNode(midPoint);

  vector<Point<Dim>> L;
  vector<Point<Dim>> R;
  for(int i=0; i< (int)(newPoints.size()); i++)
  {
    if(newPoints[i]!=midPoint)
    {
      if(newPoints[i][d]<midPoint[d])
      {
        L.push_back(newPoints[i]);
      }
      else if(newPoints[i][d]>midPoint[d])
      {
        R.push_back(newPoints[i]);
      }
      else if(newPoints[i][d]==midPoint[d])
      {
        if(newPoints[i]<midPoint)
        {
          L.push_back(newPoints[i]);
        }
        else
        {
          R.push_back(newPoints[i]);
        }
      } 
    }   
  }

  KDTreeBuildHelper(L,rt->left,(d+1)%Dim);
  KDTreeBuildHelper(R,rt->right,(d+1)%Dim);
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    size=newPoints.size();
    KDTreeBuildHelper(newPoints,root,0);
}


template <int Dim>
void KDTree<Dim>::KDTreeCopyHelper(const KDTreeNode*& otherNode, KDTreeNode*& rt)
{
  /**
   * @todo Implement this function!
   */
  if(otherNode!=NULL)
  {
    rt=new KDTreeNode(otherNode->point);
    KDTreeCopyHelper(otherNode->left, rt->left);
    KDTreeCopyHelper(otherNode->right, rt->right);
  }
}




template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) 
{
  /**
   * @todo Implement this function!
   */
  size=other.size;
  KDTreeCopyHelper(other.root, root);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  KDTreeCopyHelper(rhs.root, root);
  return *this;
}


template <int Dim>
void KDTree<Dim>::destroy(KDTreeNode*& rt)
{  
  if(rt!=NULL)
  {
    if(rt->left!=NULL)
    {
      KDTreeNode*& l = rt->left;
      destroy(l);
    }
    if(rt->right!=NULL)
    {
      KDTreeNode*& r = rt->right;
      destroy(r);
    }
    delete rt;
    rt=NULL;    
  }
}



template <int Dim>
KDTree<Dim>::~KDTree() 
{
  /**
   * @todo Implement this function!
   */
  destroy(root);
}

template <int Dim>
double dist(Point<Dim> p1, Point<Dim> p2)
{
  double sum=0.0;
  for(int i=0;i<Dim;i++)
  {
    sum+=(p1[i]-p2[i])*(p1[i]-p2[i]);
  }
  return sqrt(sum);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighborHelper(const Point<Dim>& query,KDTreeNode* rt,int d) const
{
  if(rt==NULL)
    return Point<Dim>();
  
  if(rt->left==NULL&&rt->right==NULL)
    return rt->point;

  Point<Dim> bestCurrent;
  if(query[d]<(rt->point)[d])
  {
    bestCurrent=findNearestNeighborHelper(query,rt->left,(d+1)%Dim);
  }
  else if(query[d]>(rt->point)[d])
  {
    bestCurrent=findNearestNeighborHelper(query,rt->right,(d+1)%Dim);
  }
  else
  {
    if(query<rt->point)
    {
      bestCurrent=findNearestNeighborHelper(query,rt->left,(d+1)%Dim);
    }
    else
    {
      bestCurrent=findNearestNeighborHelper(query,rt->right,(d+1)%Dim);
    }
  }


  if(rt->point!=bestCurrent && shouldReplace(query,bestCurrent,rt->point))
    bestCurrent=rt->point;
  
  Point<Dim> potential=bestCurrent;
  if(abs(query[d]-rt->point[d])<=dist(query,bestCurrent))
  {
    if(query[d]<rt->point[d])
    {
      if(rt->right!=NULL)
        potential=findNearestNeighborHelper(query,rt->right,(d+1)%Dim);
    }
    else if(query[d]>rt->point[d])
    {
      if(rt->left!=NULL)
        potential=findNearestNeighborHelper(query,rt->left,(d+1)%Dim);
    }
    else
    {
      if(query<rt->point)
      {
        if(rt->right!=NULL)
          potential=findNearestNeighborHelper(query,rt->right,(d+1)%Dim);
      }
      else
      {
        if(rt->left!=NULL)
          potential=findNearestNeighborHelper(query,rt->left,(d+1)%Dim);
      }
    }
  }
  if(potential!=bestCurrent && shouldReplace(query,bestCurrent,potential))
    bestCurrent=potential;
  return bestCurrent;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return findNearestNeighborHelper(query, root, 0);    
}



