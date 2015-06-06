#include<iostream>
#include<vector>
#include<string>

class NukagaLinkedList{
private:
	std::string str = "";
public:
	struct NukagaLinkedList *prev = NULL;
	struct NukagaLinkedList *next = NULL;
	std::string getValue(){
		return str;
	}
	void setValue(std::string str){
		NukagaLinkedList::str = str;
	}
};

NukagaLinkedList *root = NULL;

int size(){
	int count = 0;
	NukagaLinkedList *p = root;
	while(p!=NULL){
		p = p->next;
		count++;
	}
	return count-1;
}

void squeezeElement(){
	NukagaLinkedList *p = root;
	std::vector<std::string> str_list;

	while(p != NULL){

		std::string str = p->getValue();
		bool alreadyExist = false;
		for(auto it = str_list.begin(); it != str_list.end(); it++){
			if(*it == str){
				alreadyExist = true;
				break;
			}
		}

		if(alreadyExist){
			NukagaLinkedList *delete_target = p;
			if(p->next == NULL){
				p = p->prev;
				p->next = NULL;
				delete delete_target;
			}else{
				p = p->prev;
				p->next = p->next->next;
				p->next->prev = p;
				delete delete_target;
			}
		}else{
			str_list.push_back(p->getValue());
		}
		p = p->next;
	}
}

void addValue(std::string str){
	if(root == NULL){
		root = new NukagaLinkedList;
		root->setValue(str);
		return;
	}

	NukagaLinkedList *fp = root->next;
	NukagaLinkedList *lp = root;

	while(fp != NULL){
		fp = fp->next;
		lp = lp->next;
	}

	lp->next = new NukagaLinkedList;
	lp->next->setValue(str);
	lp->next->prev = lp;
}

void deleteValue(std::string str){
	NukagaLinkedList *p = root;

	while(p != NULL){
		if(p->getValue() == str){
			if(p == root){
				root = root->next;
				delete p;
				p = root;
				continue;
			}

			NukagaLinkedList *delete_target = p;
			if(p->next == NULL){
				p = p->prev;
				p->next = NULL;
				delete delete_target;
			}else{
				p = p->prev;
				p->next = p->next->next;
				p->next->prev = p;
				delete delete_target;
			}
		}
		p = p->next;
	}
}

void showList(){
	NukagaLinkedList *p = root;

	while(p != NULL){
		std::cout << p->getValue() << std::endl;
		p = p->next;
	}
}

void freeList(NukagaLinkedList* p){
	if(p->next != NULL){
		freeList(p->next);
	}
	delete p;
}