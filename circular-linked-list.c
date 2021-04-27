/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout);
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){
	listNode* p = h->rlink;

	listNode* prev = NULL;
	while(p != h) {
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h);
	return 0;
}
void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);

	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
	listNode* last=(listNode*)malloc(sizeof(listNode));
	listNode* New =(listNode*)malloc(sizeof(listNode)); //새로운 노드를 할당해준다.
	New->key=key;
	New->rlink=NULL; //링크 필드는 아직 받지 않았기에 공백 할당.
	New->llink=NULL;

	if(h->rlink==h){ // h의 rlink가 h 자기자신을 가리킬 떄
		New->llink=h; //New의 llink가 h를 가리키게한다.
		New->rlink=h->rlink; //New의 rlink와 h의 rlink가 같게 지정해준다.
		h->rlink->llink=New; //h의 rlink의 llink가 New를 가리키게한다.
		h->rlink=New; //h의 rlink를 New를 가리키게한다.
		return 0;}
	last=h->rlink; //h의 rlink가 가리키는 값을 last로 놓는다.
	while(last->rlink!=h)// h가 나오지 않을때까지 반복해 마지막 노드를 찾는다.
		{last=last->rlink;}//last노드의 rlink가 가리키는 곳을 last로 바꾼다.

	New->rlink=last->rlink; //New의 rlink와 last의 rlink가 같게 지정해준다.
	New->llink=last; //New의 llink가 last를 가리키게한다.
	last->rlink=New; //last의 rlink가 New를 가리키게한다.
	h->llink=New; // h의 llink가 New를 가리키게한다.
	return 1;
}
/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
	listNode* del;
	listNode* pre;

	pre = h->rlink; // 삭제할 노드의 앞의 노드를 첫번째로 지정.
	del = h->rlink->rlink; //삭제할 노드를 두번째로 지정.
	if (h->rlink == h) return -1; //빈노드면 종료.
	if (del == h) { //노드가 한개라면
		h->rlink = h->rlink->rlink; //h의 rlink가 h의 rlink의 rlink 링크값을 가르키도록 지정.
		free(pre); //del 할당해제
		return 0;
	}
	else {
		while (del->rlink != h) {//노드를 끝까지 반복한다.
			pre = del; //pre에 del값을 넣어준다.
			del = del->rlink; // del의 r링크가 가르키는 값으로 del을 바꿔준다.
		}
		free(del); //del을 할당 해제해준다.
		pre->rlink = h;
		h->llink=pre;
	}
	return 1;
}
/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
	listNode *Node = (listNode *)malloc(sizeof(listNode));
		Node->llink=NULL;
		Node->rlink=NULL;
		Node->key=key;
		Node->rlink=h->rlink; //노드의 rlink와 h의rlink를 같게해준다.
		h->rlink->llink=Node; //h의 rlink의 llink가 node를 가리키게 한다.
		Node->llink=h;
		h->rlink=Node; //h의rlink가 Node를 가리키게 지정해준다.
		return 1;
}
/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
	listNode* del;
		if (h->rlink == h) { return 0; }  // 공백일시 함수 나간다.
		del = h->rlink;//h의 rlink가 del을 가르키게한다.
		h->rlink = h->rlink->rlink; //h의 rlink가 h의 rlink의 rlink 링크값을 가르키도록 지정.
		h->rlink->llink=h;
		free(del); //del 할당해제
		return 0;
}
/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {


	return 0;
}

/**
 *  리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
 **/
int insertNode(listNode* h, int key) {

	listNode *New=(listNode*)malloc(sizeof(listNode));
	listNode *temp=(listNode*)malloc(sizeof(listNode));
	listNode *pre=(listNode*)malloc(sizeof(listNode));
	New->key=key; temp->key=key;
	New->llink=NULL;	New->rlink=NULL;
	pre->llink=NULL;	pre->rlink=NULL;
	temp=h->rlink;

	if(h->rlink==h){ // h의 rlink가 자기 자신이라면
		New->rlink=h->rlink; //노드의 rlink를 h의 rlink와 같게해준다.
		h->rlink->llink=New; //h의 rlink의 llink가 New를 가리키게 한다.
		New->llink=h;
		h->rlink=New; //h의 rlink가 New를 가리키게 해준다.
		return 0;}
	while((temp->key) < key){//입력받은 키값보다 리스트안의 키값이 클때까지 반복한다.
		if(temp->rlink==h){//모든 수보다 입력한 키값이 크다면 마지막에 넣어준다.
			New->rlink=temp->rlink;//temp의 rlink가 가리키는 값을 New도 가리킨다.
			New->llink=temp;//New의 llink를 temp를 가리키게한다.
			temp->rlink=New; //temp의 rlink로 New를 가리키게한다.
			h->llink=New; //h의 llink를 New를 가리키게 바꾼다.
			return 0;
		}
		pre=temp; //temp를 pre에 복사.
		temp=temp->rlink; //temp노드가 가르키는 곳을 temp로 바꾼다.
	}
	if(pre->rlink==NULL){ //첫번째 값으로 넣어줄때.
		New->rlink=h->rlink; //노드의 rlink를 h의 rlink와 같게한다.
		h->rlink->llink=New; //r의 rlink의 llink가 New를 가리키게 한다.
		New->llink=h; //New의 llink가 h를 가리키게한다.
		h->rlink=New; // h의 rlink가 New를 가리키게한다.
		return 0;
	}
	New->rlink=pre->rlink;//New의 rlink값을 pre의 rlink값과 같게한다.
	New->llink=pre; //New의 llink로 pre를 가리킨다.
	pre->rlink->llink=New;//pre의 다음값의 llink로 New를 가리킨다.
	pre->rlink=New; // pre의 다음값으로 New를 지정한다.
	return 0;
}
/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
	listNode* find = (listNode*)malloc(sizeof(listNode));
	listNode* pre = (listNode*)malloc(sizeof(listNode));
	listNode* del;
	pre->rlink = NULL;
	find = h->rlink; // h의 rlink를 find로 놓는다.
	while (find->key != key) {//find의 키값과 같은 값이 나올때까지 반복해 원하는 노드를 찾는다.
		if (find->rlink == h) return 0; //모든 값이 다른경우 함수에서 나간다.
		pre = find;//find값을 pre에 넣어준다.
		del = find->rlink;//find가 가르키는 곳을 del이 가르키게 한다.
		find = find->rlink;//find노드가 가르키는 곳을 find로 바꾼다.

	}
	if (pre->rlink == NULL){ //첫번째 값이 같다면.
		del = h->rlink;//h의 rlink가 del을 가르키게한다.
		h->rlink = h->rlink->rlink; //h의 rlink가 h의 rlink의 rlink 링크값을 가르키도록 지정.
		h->rlink->llink=h;
		free(del); //del 할당해제
		return 0;
	}
	pre->rlink = find->rlink; //find가 가르키고있는 값을 pre가 가르킨다.
	find->rlink->llink=pre;
	free(del);
	return 0;
}


