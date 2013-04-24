/* AVL */

#include <iostream>
#include <sstream>
using namespace std;

class AVLNode
{
        private:
                string data;
                int height;
                AVLNode * parent;
                AVLNode * left_child;
                AVLNode * right_child;
        public:
                AVLNode(string val)
                {
                        data = val;
                        height = 0;
                        parent = (AVLNode*)0;
                        left_child = (AVLNode*)0;
                        right_child = (AVLNode*)0;
                }
                string getData()
                {
                        return data;
                }
                int getHeight()
                {
                        return height;
                }
                int updateHeight()
                {
                        if(left_child != 0 && right_child != 0)
                        {
                                if(left_child->getHeight() > right_child->getHeight())
                                        height = left_child->getHeight() + 1;
                                else
                                        height = right_child->getHeight() + 1;
                        }
                        else if(left_child != 0)
                                height = left_child->getHeight() + 1;
                        else if(right_child != 0)
                                height = right_child->getHeight() + 1;
                        else
                                height = 0;
                        return height;
                }
                int getBalance()
                {
                        AVLNode * n = this;
                        if(n->getLeftChild() != 0 && n->getRightChild() !=0)
                                return n->getLeftChild()->getHeight() - n->getRightChild()->getHeight();
                        else if(n->getLeftChild() != 0)
                                return n->getLeftChild()->getHeight() + 1;
                        else if(n->getRightChild() != 0)
                                return (-1) * (n->getRightChild()->getHeight() + 1);
                        else
                                return 0;
                }
                AVLNode* getParent()
                {
                        return parent;
                }
                void removeParent()
                {
                        parent = (AVLNode*)0;
                }
                AVLNode* getLeftChild()
                {
                        return left_child;
                }
                AVLNode* setLeftChild(AVLNode* new_left)
                {
                        if(new_left != 0) new_left->parent = this;
                        left_child = new_left;
                        updateHeight();
                        return left_child;
                }
                AVLNode* getRightChild()
                {
                        return right_child;
                }
                AVLNode* setRightChild(AVLNode* new_right)
                {
                        if(new_right != 0) new_right->parent = this;
                        right_child = new_right;
                        updateHeight();
                        return right_child;
                }
};

class AVLTree
{
        private:
                AVLNode * root;
 
        public:
                AVLTree()
                {
                        root = (AVLNode*)0;
                }
 
                AVLTree(string val)
                {
                        root = new AVLNode(val);
                }
 
                AVLTree * findSubtree(string val)
                {
                        AVLNode* target;
                        target = findNode(val);
 
                        if(target != 0)
                        {
                                AVLTree* subtree = new AVLTree();
                                subtree->root = target;
                                return subtree;
                        }
                        else
                                return (AVLTree*)0;
                }
 
                //Successful insertion : true, else : false
                void insert(string val)
                {
                        AVLNode* added_node;
                        if(root == 0)
                        {
                                root = new AVLNode(val);
                                return;
                        }
                        else
                        {
                                AVLNode* temp = root;
 
                                while(true)
                                {
                                        if(temp->getData() > val)
                                        {
                                                if((temp->getLeftChild()) == 0)
                                                {
                                                        added_node = temp->setLeftChild(new AVLNode(val));
                                                        break;
                                                }
                                                else
                                                {
                                                        temp = temp->getLeftChild();
                                                }
 
                                        }
                                        else if(temp->getData() < val)
                                        {
                                                if((temp->getRightChild()) == 0)
                                                {
                                                        added_node = temp->setRightChild(new AVLNode(val));
                                                        break;
                                                }
                                                else
                                                {
                                                        temp = temp->getRightChild();
                                                }
 
                                        }
                                        else
                                        {
                                                return;
                                        }
                                }
                                // The following code is for updating heights and balancing.
                                temp = added_node;
                                while(temp != 0)
                                {
                                        temp->updateHeight();
                                        balanceAtNode(temp);
                                        temp = temp->getParent();
                                }
                        }
                }
                
                //Successful remove : true, else : false
                bool removeByPart(string val)				//this method is identical for this scenario
                {
                        if(root == 0) return false;
                        AVLNode *replacement, *replacement_parent, *temp_node;
                        AVLNode * to_be_removed = findNodeByPart(val);                   
                        if(to_be_removed == 0) return false;
 
                        AVLNode * p = to_be_removed->getParent();
 
                        enum {left, right} side;
                        if(p != 0)
                        {
                                if(p->getLeftChild() == to_be_removed) side = left;
                                else side = right;
                        }
 
                        int bal = to_be_removed->getBalance();
 
                        if(to_be_removed->getLeftChild() == 0 && to_be_removed->getRightChild() == 0)
                        {
                                if(p != 0)
                                {
                                        if(side == left) p->setLeftChild((AVLNode*)0);
                                        else p->setRightChild((AVLNode*)0);
 
                                        delete to_be_removed;
                                        p->updateHeight();
                                        balanceAtNode(p);
                                }
                                else
                                {
                                        setRoot((AVLNode*)0);
                                        delete to_be_removed;
                                }
 
                        }
                        else if(to_be_removed->getRightChild() == 0)
                        {
                                if(p != 0)
                                {
                                        if(side == left) p->setLeftChild(to_be_removed->getLeftChild());
                                        else p->setRightChild(to_be_removed->getLeftChild());
 
                                        delete to_be_removed;
                                        p->updateHeight();
                                        balanceAtNode(p);
                                }
                                else
                                {
                                        setRoot(to_be_removed->getLeftChild());
                                        delete to_be_removed;
                                }
                        }
 
                        else if(to_be_removed->getLeftChild() == 0)
                        {
                                if(p != 0)
                                {
                                        if(side == left) p->setLeftChild(to_be_removed->getRightChild());
                                        else p->setRightChild(to_be_removed->getRightChild());
 
                                        delete to_be_removed;
                                        p->updateHeight();
                                        balanceAtNode(p);
                                }
                                else
                                {
                                        setRoot(to_be_removed->getRightChild());
                                        delete to_be_removed;
                                }
                        }
                        else
                        {
                                if(bal > 0)
                                {
                                        if(to_be_removed->getLeftChild()->getRightChild() == 0)
                                        {
                                                replacement = to_be_removed->getLeftChild();
                                                replacement->setRightChild(to_be_removed->getRightChild());
 
                                                temp_node = replacement;
 
 
                                        }
                                        else
                                        {
                                                replacement = to_be_removed->getLeftChild()->getRightChild();
                                                while(replacement->getRightChild() != 0)
                                                {
                                                        replacement = replacement->getRightChild();
                                                }
                                                replacement_parent = replacement->getParent();
                                                replacement_parent->setRightChild(replacement->getLeftChild());
 
                                                temp_node = replacement_parent;
 
                                                replacement->setLeftChild(to_be_removed->getLeftChild());
                                                replacement->setRightChild(to_be_removed->getRightChild());
                                        }
                                }
                                else
                                {
                                        if(to_be_removed->getRightChild()->getLeftChild() == 0)
                                        {
                                                replacement = to_be_removed->getRightChild();
                                                replacement->setLeftChild(to_be_removed->getLeftChild());
 
                                                temp_node = replacement;
 
 
                                        }
                                        else
                                        {
                                                replacement = to_be_removed->getRightChild()->getLeftChild();
                                                while(replacement->getLeftChild() != 0)
                                                {
                                                        replacement = replacement->getLeftChild();
                                                }
                                                replacement_parent = replacement->getParent();
                                                replacement_parent->setLeftChild(replacement->getRightChild());
 
                                                temp_node = replacement_parent;
 
                                                replacement->setLeftChild(to_be_removed->getLeftChild());
                                                replacement->setRightChild(to_be_removed->getRightChild());
                                        }
                                }               
                                if(p != 0)
                                {
                                        if(side == left) p->setLeftChild(replacement);
                                        else p->setRightChild(replacement);
 
                                        delete to_be_removed;
                                }
                                else
                                {
                                        setRoot(replacement);
                                        delete to_be_removed;
                                }
 
                                balanceAtNode(temp_node);
                        }
                        return true; 
                }
                int getHeight()
                {
                        return root->getHeight();
                }
 
                void setRoot(AVLNode* n)
                {
                        root = n;
                        if(root != 0) root->removeParent();
                }
 
 
                AVLNode* findNode(string val)
                {
                        AVLNode* temp = root;
                        while(temp != 0)
                        {
                                if(val == temp->getData())
                                        return temp;
 
                                else if(val < temp->getData())
                                        temp = temp->getLeftChild();
 
                                else
                                        temp = temp->getRightChild();
                        }
                        return (AVLNode*)0;
                }
                AVLNode* findNodeByPart(string val)		//this method is identical for this scenario
                {
                        AVLNode* temp = root;
                        while(temp != 0)
                        {
                                if(val == (temp->getData()).substr (0,val.length()))
                                        return temp;
 
                                else if(val < temp->getData())
                                        temp = temp->getLeftChild();
 
                                else
                                        temp = temp->getRightChild();
                        }
                        return (AVLNode*)0;
                }
                void rotateLeft(AVLNode * n)
                {
                        AVLNode * p = n->getParent();
                        enum {left, right} side;
                        if(p != 0)
                        {
                                if(p->getLeftChild() == n)
                                        side = left;
                                else
                                        side = right;
                        }
                        AVLNode * temp = n->getRightChild();
                        n->setRightChild(temp->getLeftChild());
                        temp->setLeftChild(n);
                        
                        if(p != 0)
                        {
                                if(side == left)
                                        p->setLeftChild(temp);
                                if(side == right)
                                        p->setRightChild(temp);
                        }
                        else
                        {
                                setRoot(temp);
                        }
                }
 
                void rotateRight(AVLNode * n)
                {
                        AVLNode * p = n->getParent();
                        enum {left, right} side;
                        if(p != 0)
                        {
                                if(p->getLeftChild() == n)
                                        side = left;
                                else
                                        side = right;
                        }
                        AVLNode * temp = n->getLeftChild();
                        n->setLeftChild(temp->getRightChild());
                        temp->setRightChild(n);
                        
                        if(p != 0)
                        {
                                if(side == left)
                                        p->setLeftChild(temp);
                                if(side == right)
                                        p->setRightChild(temp);
                        }
                        else
                        {
                                setRoot(temp);
                        }
                }
 
                void balanceAtNode(AVLNode* n)
                {                       
                        int bal = n->getBalance();
                        if(bal > 1)
                        {
                                if(n->getLeftChild()->getBalance() < 0)
                                        rotateLeft(n->getLeftChild());
                                rotateRight(n);
                        }
                        else if(bal < -1)
                        {
                                if(n->getRightChild()->getBalance() > 0)
                                        rotateRight(n->getRightChild());
                                rotateLeft(n);
                        }
                }
 
                
};
 
 
 
int main () 
{ 
	AVLTree avl;
	string str;
	int n, m;
	
	getline (cin, str);
	stringstream(str) >> n;
	
	for (int i=0; i<n; i++)			//get messages
	{
		getline (cin, str);
		while (str.at(0)!=' ') { 
	    	str=str.substr (1);
  		}
  		str=str.substr (1);
		avl.insert(str);
	}
	
	getline (cin, str);
	stringstream(str) >> m;
	
	for (int i=0; i<m; i++)			//assign with receivers
	{
		getline (cin, str);
		str=str.substr (2);
		if(avl.removeByPart(str))
			cout << "YOU'RE CONNECTED\n"; 
		else
			cout << "YOU'RE NOT CONNECTED\n"; 
	}
  
  return 0; 
} 