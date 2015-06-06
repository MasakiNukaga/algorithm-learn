#include<iostream>

struct LinkedList {
	std::string date;
	struct LinkedList *next;
};

class Result {
public:
	bool result;
	LinkedList *node;

	Result(bool res,LinkedList *n){
		result = res;
		node   = n;
	}
};

int size(LinkedList *root){
	int count = 0;
	LinkedList *p = root;
	while(p!=NULL){
		p = p->next;
		count++;
	}
	return count-1;
}


Result isRecurseList(LinkedList *node, int length) {

	if(node == NULL || length == 0){
		return Result(true,NULL);
	}else if(length == 1){
		return Result(true,node->next);
	}else if(length == 2){
		return Result(node->next->date == node->date,node->next->next);
	}

	Result res = isRecurseList(node->next,length-2);
	if(!res.result || res.node == NULL){
		return res;
	}else{
		res.result = node->date == res.node->date;
		res.node = node->next;
		return res;
	}
}

bool isRecurse(LinkedList *root){
	Result res = isRecurseList(root,size(root));
	return res.result;
}
