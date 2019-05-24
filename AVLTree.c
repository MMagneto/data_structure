/*二叉平衡h树*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct AVLNode * Position;
typedef Position AVLTree;
typedef struct AVLTree {
	ElmentType Data;	/*结点数据*/
	AVLTree Left;		/*指向左子树*/
	AVLTree Right;		/*指向右子树*/
	int height;			/*树高*/
};

int Max(int a, int b) {
	return a>b?a:b;
}

AVLTree Insert(AVLTree T, ElementType X) {
	/*将 X x插入 AVL 树 T 中，并且返回调整后的 AVL 树 */
	if(!T) { /*若插入空树，则新建包含一个结点的树*/
		T = (AVLTree)malloc(sizeof(struct AVLNode));
		T->Data = X;
		T->Height = 1;
		T->Left = T->Right = NULL;
	} /* if (插入空树) 结束*/
	else if(X < T->Data ) {
		/*插入 T 的左子树 */
		T->Left = Insert(T->Left, X);
		/*如果需要左旋 */
		if(GetHeight(T->Left) - GetHeight(T->Right) == 2) {
			if(X < T->Left->Data) {
				T = SingleLeftRotation(T); /*左单旋*/
			} else {
				T = DoubleLeftRightRotation(T); /*左-右双旋*/
			}
		} 
	}/* else if(插入左子树) 结束 */
	
	else if(X > T->Data) {
		/*插入 T 的右子树 */
		T->Right = Insert(T->Right, X);
		/*如果需要右旋*/
		if(GetHeight(T->Left) - GetHeight(T->Right) == -2 ) {
			if(X > T->Right->Data) {
				T = SingleRightRotation(T); /*右单旋*/
			} else {
				T = DoubleRightLeftRotation(T); /*右-左双旋*/
			}
		}
	}/* else if (插入右子树) 结束 */

	/* else X == T->Data 无需插入 */

	/* 更新树高 */
	T->Height = Max(GetHeight(T->Left), GetHeight(T->Right)) + 1;

	return T;
}

AVLTree SingleLeftRotation(AVLTree A) {
	/* 注意： A 必须有一个左子结点 B */
	/* 将 A 与 B 做如图 4.35 所示的左单旋，
	 * 更新左
