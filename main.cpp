#include <iostream>
#include <fstream>

class TreeNode{
private:
	TreeNode * left;
	int value;
	TreeNode * right;
	TreeNode * parent;
public:
	void setLeft(TreeNode * tn){ left = tn; }
	void setValue(int v){ value = v; }
	void setRight(TreeNode * tn){ right = tn; }
	void setParent(TreeNode * tn){ parent = tn; }

	TreeNode * getLeft(){ return left; }
	int getValue(){ return value; }
	TreeNode * getRight(){ return right; }
	TreeNode * getParent(){ return parent; }

	TreeNode(int v):left(NULL),value(v),right(NULL),parent(NULL){}
	~TreeNode(){}
};

void insert(TreeNode **rt, int v ){
	TreeNode * newTreeNode = new TreeNode(v);
	if( *rt == NULL){
		*rt = newTreeNode;
	}
	else{
		if(v<(*rt)->getValue()){
			if((*rt)->getLeft()==NULL){
				(*rt)->setLeft(newTreeNode);
			}
			else{
				TreeNode * lc = (*rt)->getLeft();
				insert(&lc, v);
			}
		}
		else{
			if((*rt)->getRight()==NULL){
				(*rt)->setRight(newTreeNode);
			}
			else{
				TreeNode * rc = (*rt)->getRight();
				insert(&rc, v);
			}
		}
	}
}

void print(std::fstream & op, TreeNode ** rt){
	if( *rt == NULL ){
		return;
	}
	op << "\""<< (*rt)->getValue() << "\"[label=\"<f0>left|<f1>"<<(*rt)->getValue()<<"|<f2>right\",shape=Mrecord]" << std::endl;
	if( (*rt)->getLeft() ){
		op << "\"" << (*rt)->getValue() << "\":f0->\"" << (*rt)->getLeft()->getValue() << "\"" << std::endl;
		TreeNode * lc;
		lc = (*rt)->getLeft();
		print(op, &lc);
	}
	if( (*rt)->getRight() ){
		op << "\"" << (*rt)->getValue() << "\":f2->\"" << (*rt)->getRight()->getValue() << "\"" << std::endl;
		TreeNode * rc;
		rc = (*rt)->getRight();
		print(op, &rc);
	}
	if( (*rt)->getParent() ){
		op << "\"" << (*rt)->getValue() << "\":f1->\"" << (*rt)->getParent()->getValue() << "\"" << std::endl;
	}
}

void find(TreeNode ** rt, int v){
	TreeNode * p = *rt;
	int flag = 0;
	while(p!=NULL){
		if(p->getValue() == v){
			flag = 1;
			std::cout << v << " has been found" << std::endl;
			break;
		}
		else if(v < p->getValue()){
			p = p->getLeft();
		}
		else{
			p = p->getRight();
		}
	}
	if(flag == 0){
		std::cout << v << " not found" << std::endl;
	}
}

void findMin(TreeNode ** rt){
	TreeNode * p = *rt;
	while( p->getLeft() != NULL ){
		p=p->getLeft();
	}
	std::cout << "Min " << p->getValue() << std::endl;
}

void findMax(TreeNode ** rt){
	TreeNode * p = *rt;
	while( p->getRight() != NULL ){
		p=p->getRight();
	}
	std::cout << "Max " << p->getValue() << std::endl;
}

void attachToParent(TreeNode ** tn, TreeNode * parent){
	(*tn)->setParent(parent);
	if( (*tn)->getLeft() ){
		TreeNode * lc = (*tn)->getLeft();
		attachToParent(&lc, *tn);
	}
	if( (*tn)->getRight() ){
		TreeNode * rc = (*tn)->getRight();
		attachToParent(&rc, *tn);
	}
}

int main(){
	TreeNode * root = NULL;

	insert(&root, 34);
	insert(&root, 12);
	insert(&root, 66);
	insert(&root, 23);
	insert(&root, 76);
	insert(&root, 29);
	insert(&root, 87);
	insert(&root, 99);
	insert(&root, 14);
	insert(&root, 22);
	insert(&root, 40);
	insert(&root, 85);
	insert(&root, 223);

	std::fstream output;
	output.open("tree.gv", std::ios::out);
	output << "digraph G{" << std::endl;
	print(output, &root);
	output << "}" << std::endl;
	output.close();

	find(&root, 87);
	find(&root, 89);

	findMin(&root);

	findMax(&root);

	attachToParent(&root, NULL);

	std::fstream output1;
	output1.open("treewithparent.gv", std::ios::out);
	output1 << "digraph G{" << std::endl;
	print(output1, &root);
	output1 << "}" << std::endl;
	output1.close();

}