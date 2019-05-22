#include <stdio.h>
#include <stdlib.h>

typedef struct PolyNode *Polynomial;
struct PolyNode {
	int coef;
	int expon;
	Polynomial link;
};

Polynomial ReadPoly();
void Attach(int c, int e, Polynomial *pRear);
Polynomial Add(Polynomial P1, Polynomial P2);
Polynomial PrintPoly(Polynomial P);
Polynomial Mult(Polynomial P1, Polynomial P2);

int main(int argc, const char *argv[])
{
	Polynomial P1, P2, PP, PS;

	P1 = ReadPoly();
	P2 = ReadPoly();

	PP = Mult(P1, P2);
	PrintPoly(PP);

	PS = Add(P1,P2);
	PrintPoly(PS);


	return 0;
}

Polynomial ReadPoly() {
	int N, e, c;
	Polynomial P, Rear, t;

	scanf("%d", &N);
	/*����ͷ�ս��*/
	P = (Polynomial)malloc(sizeof(struct PolyNode));
	P->link = NULL;
	Rear = P;
	while(N--) {
		scanf("%d %d", &c, &e);
		Attach(c,e,&Rear);
	}
	t = P;
	P = P->link;
	free(t); /*ɾ����ʱ���ɵ�ͷ���*/

	return P;
}

void Attach(int c, int e, Polynomial *pRear) {
	Polynomial P;
	if( e == 0 ) {
	
		P = (Polynomial)malloc(sizeof(struct PolyNode));
		P->coef = c; /*���½�㸳ֵ*/
		P->expon = e;
		P->link = NULL;
		(*pRear)->link = P;
		*pRear = P; /*�޸�pRearֵ*/
	} else {
		if(c != 0 ) {
			P = (Polynomial)malloc(sizeof(struct PolyNode));
			P->coef = c; /*���½�㸳ֵ*/
			P->expon = e;
			P->link = NULL;
			(*pRear)->link = P;
			*pRear = P; /*�޸�pRearֵ*/
		}
	}

}

Polynomial Add(Polynomial P1, Polynomial P2) {
	Polynomial P, Rear;
	Polynomial t1 = P1, t2 = P2, t;
	P = (Polynomial)malloc(sizeof(struct PolyNode));
	P->link = NULL;
	Rear = P;
	while(t1!=NULL && t2!=NULL) {
		if( (t1->expon) > (t2->expon)) {
			Attach(t1->coef, t1->expon, &Rear);
			t1 = t1->link;
		} else if ((t1->expon) < (t2->expon)) {
			Attach(t2->coef, t2->expon, &Rear);
			t2 = t2->link;
		} else if ((t1->expon) == (t2->expon) ) {
			int newc = t1->coef + t2->coef;
			if(newc != 0 ) {
				Attach(newc, t1->expon, &Rear);
			} else if( newc == 0 && (t1->expon) == 0) {
				Attach(0,0, &Rear);
			}
			t1 = t1->link;
			t2 = t2->link;
		} else {
			t1 = t1->link;
			t2 = t2->link;
		}
		
	}

	while(t1!=NULL) {
		Attach(t1->coef, t1->expon, &Rear);
		t1 = t1->link;
	}
	while(t2!=NULL) {
		Attach(t2->coef, t2->expon, &Rear);
		t2 = t2->link;
	}
	t = P;
	P = P->link;
	free(t);

	return P;
}

	
Polynomial PrintPoly(Polynomial P) {
	Polynomial Rear = P;
	if(Rear!= NULL) {
		while(Rear->link) { 
			printf("%d %d ", Rear->coef, Rear->expon);
			Rear = Rear->link;
		}
		printf("%d %d\n", Rear->coef, Rear->expon);
	} else {
		printf("%d %d\n", 0,0);
	}
}
Polynomial Mult(Polynomial P1, Polynomial P2) {
	Polynomial t1 = P1, t2 = P2;
	//����k�ж� P1 P2 �Ƿ�Ϊ��
	if(t1==NULL || t2==NULL) {
		return t1;
	}
	Polynomial P, newP, t, Rear;
	P = (Polynomial)malloc(sizeof(struct PolyNode));
	P->link = NULL;
	Rear = P;
	//��һ�����
	while(t2) {
		Attach(t1->coef*t2->coef,t1->expon + t2->expon, &Rear);
		t2 = t2->link;
	}
	t = P;
	P = P->link;
	free(t);
	t1 = t1->link;
	t2 = P2;
	//�ǵ�һ�����
	newP = (Polynomial)malloc(sizeof(struct PolyNode));
	newP->link = NULL;
	Rear = newP;

	while(t1) {
		while(t2) {
			Attach(t1->coef*t2->coef, t1->expon + t2->expon, &Rear);
			t2 = t2->link;
		}
		Rear = newP->link;
		P = Add(P, Rear);
		t1 = t1->link;
		t2 = P2;
		//�ͷ���ʱ���
		while(Rear) {
			t = Rear;
			Rear = Rear->link;
			free(t);
		}
		//��Rear����ָ�� newP
		Rear = newP;

	}
	//�ͷ� newP ��t��ͷ���
	free(newP);
	
	return P;
}



