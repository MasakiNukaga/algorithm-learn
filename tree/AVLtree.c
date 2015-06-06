#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE_OF_NAME 30
#define SIZE_OF_CALLNUMBER 13
#define SIZE_OF_FILENAME 21
#define NO -1
#define RIGHT 0
#define LEFT 1

int suich;

typedef struct tree_node{
  char name[SIZE_OF_NAME];
  char call_number[SIZE_OF_CALLNUMBER];
  struct tree_node *left;
  struct tree_node *right;
}tree_node;

tree_node *tree_root = NULL;

/*--- 構造体を作成 ---*/
tree_node* create_new_node(char *name,char *call_number,tree_node *parent)
{
  tree_node *new_node;

  new_node = (tree_node*)malloc(sizeof(tree_node));

  if(new_node == NULL)
    exit(EXIT_FAILURE);
 
  strcpy(new_node->name,name);
  strcpy(new_node->call_number,call_number);
  new_node->left = NULL;
  new_node->right = NULL;
  return new_node;
}

void left_rotate(tree_node *node)
{

  tree_node *child;
  tree_node *child_left;
  tree_node *parent;
  int par_position;

  child = node->right;
  child_left = child->left;
  parent = node->par;

  if(parent == NULL){ par_position = NO; }
  else if((strcmp(parent->name, node->name)) > 0){ par_position = LEFT; }
  else if((strcmp(parent->name, node->name)) < 0){ par_position = RIGHT; }

  child->left = node;
  node->par = child;

  if(child_left == NULL){ node->right = NULL; }
  else { node->right = child_left; child_left->par = node; }

  if(par_position == NO){ child->par = NULL; tree_root = child; }
  else if(par_position == LEFT){ parent->left = child; child->par = parent; }
  else if(par_position == RIGHT){ parent->right = child; child->par = parent; }

}

int right_rotate(tree_node *node)
{

  tree_node *child;
  tree_node *child_right;
  tree_node *parent;
  int par_position;
  

  child = node->left;
  child_right = child->right;
  parent = node->par;


  if(parent == NULL){ par_position = NO; }
  else if((strcmp(parent->name, node->name)) > 0){ par_position = LEFT; }
  else if((strcmp(parent->name, node->name)) < 0){ par_position = RIGHT; }

  child->right = node;
  node->par = child;

  if(child_right == NULL){ node->left = NULL; }
  else { node->left = child_right; child_right->par = node; }

  if(par_position == NO){ child->par = NULL; tree_root = child; }
  else if(par_position == LEFT){ parent->left = child; child->par = parent; }
  else if(par_position == RIGHT){ parent->right = child; child->par = parent; }
         
}

int deep_tree(tree_node *node, int deep)
{
  int deep1=0;
  int deep2=0;

  if(node->left==NULL && node->right==NULL)
    return(deep);

  if(node->left != NULL)
    deep1 = deep_tree(node->left,deep+1);
 
  if(node->right != NULL)
    deep2 = deep_tree(node->right,deep+1);

  if(deep1 > deep2){
    return (deep1);
  } else {
    return (deep2);
  }
}

void make_AVLtree(tree_node *node)
{

  int left_deep;
  int right_deep;
  tree_node *left_child;
  tree_node *right_child;


  /* 葉を探索する */
  if(node->left != NULL)
     make_AVLtree(node->left);
 
  if(node->right != NULL)
     make_AVLtree(node->right);


  if(node->left==NULL && node->right==NULL){  /* 葉にたどり着いた。ここから根に向かっていく */

    
    while(1){
      
      node = node->par;
      if(node == NULL)
	break;

      left_child=node->left;
      right_child=node->right;

  if(node->left == NULL){ left_deep = 0; }
  else left_deep = deep_tree(node->left, 1);

  if(node->right == NULL){ right_deep = 0; }
  else right_deep = deep_tree(node->right ,1);

    /*左部分木の方が2以上高い*/
    if(left_deep - right_deep >= 2){
      suich = 1;
   
      /*左の子の左右部分木の高さを調べる*/
      if(left_child->left == NULL){ left_deep = 0; }
      else left_deep = deep_tree(left_child->left, 1);

      if(left_child->right == NULL){ right_deep = 0; }
      else right_deep = deep_tree(left_child->right, 1);

      /* 左の子　右の部分木の方が高い */
      if(right_deep > left_deep){

        left_rotate(node->left);  /*左右回転*/
	right_rotate(node);

      } else {    /* 左の子　左の部分木のほうが高い又は同じ */

	right_rotate(node);  /* 右回転 */

      }
    /*右部分木の方が2以上高い*/
    } else if(right_deep - left_deep >= 2){

      suich = 1;

      /*右の子の左右部分木の高さを調べる*/
      if(right_child->left == NULL){ left_deep = 0; }
      else left_deep = deep_tree(right_child->left, 1);


      if(right_child->right == NULL){ right_deep = 0; }
      else right_deep = deep_tree(right_child->right, 1);

      
      /*右の子　左の部分木のほうが高い*/
      if(right_deep < left_deep){

        right_rotate(node->right);  /*右左回転*/
        left_rotate(node); 

     
      } else {    /*右の子　右の部分木のほうが高い又は同じ*/
   
        left_rotate(node); /*左回転*/

      }
    }
    }
  }
  return;
}
  


/*--- データの追加 ---*/
void insert_node(char *name,char *call_number,tree_node *node)
{  

  if(node == NULL){
    tree_root = create_new_node(name,call_number,NULL);
    return;
  }

  if(strcmp(node->name,name) > 0){
    if(node->left != NULL){
      insert_node(name,call_number,node->left);
    } else {
      node->left = create_new_node(name,call_number,node);
    }
  } else if(strcmp(node->name,name) <0){

      if(node->right != NULL){
        insert_node(name,call_number,node->right);
      } else {
        node->right = create_new_node(name,call_number,node);            
      }  
  } else {
    printf("すでにデータに入っています\n");
  }

  return;
  
}

/*--- 削除 ---*/
/*削除する名前, カレントノードの親をさすポインタ, カレントノードへのポインタ, 親の左側についていたら１右側についていたら０*/
int delete_node(char *name, tree_node *parent, tree_node *carrent, int carrent_position)
{  

  tree_node *swap_node;
  tree_node *parent_swap_node;


    if(strcmp(name,carrent->name) > 0){ /*右側*/
       if(carrent->right == NULL){/*見つからなかった*/
	 return -1;
       } else {
	 return (delete_node(name, carrent, carrent->right, RIGHT));
       }
    } else if(strcmp(name,carrent->name) < 0){  /*左側*/
	 if(carrent->left == NULL){/*見つからなかった*/
	   return -1;
         } else {
           return (delete_node(name, carrent, carrent->left, LEFT));
	 }
    }
  

 
  if(parent == NULL){ /* 削除の対象が根だったら */

    if(carrent->left==NULL && carrent->right==NULL){

      tree_root=NULL;
      free(carrent);
      return 0;

    } else if(carrent->left!=NULL){
      
      right_rotate(carrent);
      parent = tree_root;

    } else if(carrent->right!=NULL){
      
      left_rotate(carrent);
      parent = tree_root;

    }
  }

  if(carrent->left == NULL && carrent->right == NULL){ /*削除の対象が葉だった場合*/

    if(carrent_position == LEFT){ /*親の左についていた場合*/
      parent->left = NULL;
    } else { /*右についていた場合*/
      parent->right = NULL;
    }
  }

       /*削除対象ノードの右側に子があり、左側にない場合*/
  else if(carrent->left == NULL && carrent->right != NULL){ 
    if(carrent_position == LEFT){ /*削除対象が親の左側にある場合*/
       parent->left = carrent->right;
       carrent->right->par = parent;
    } else {                 /*削除対象が親の右側にある場合*/
       parent->right = carrent->right;
       carrent->right->par = parent;    
    }
 
  }
      /*削除対象ノードの左側に子があり、右側にない場合*/
  else if(carrent->left != NULL && carrent->right == NULL){ 
    if(carrent_position == LEFT) {

       parent->left = carrent->left;
       carrent->left->par = parent;

    } else {
       parent->right = carrent->left;
       carrent->left->par = parent;
    }
  }

  /*削除対象のノードに左右に子ノードがあった場合*/
  else if(carrent->left != NULL && carrent->right != NULL){

    swap_node=carrent->left;
    parent_swap_node=carrent;

  /*削除対象ノードより左側にあるノード中で最大値を持つノードを探す*/
    while(swap_node->right != NULL){
      parent_swap_node = swap_node;
      swap_node = swap_node->right;
    }

    /*上で見つけたノードの左側がヌルだった場合*/
    if(swap_node->left == NULL){

      if(strcmp(parent_swap_node->name,swap_node->name) > 0){
	parent_swap_node->left = NULL;
      } else {
	parent_swap_node->right = NULL;
      }

      if(carrent_position == LEFT){    /*親の左につける*/
  
        parent->left = swap_node;
        swap_node->left = carrent->left;
        carrent->left->par = swap_node;
        swap_node->right = carrent->right;
        carrent->right->par = swap_node;
        swap_node->par = parent;

      } else { /*親の右側につける*/

        parent->right = swap_node;
        swap_node->left = carrent->left;
        carrent->left->par = swap_node;
        swap_node->right = carrent->right;
        carrent->right->par = swap_node;
        swap_node->par = parent;

      }

    } else { /*上で見つけたノードの左側がヌルではない場合*/

      if(strcmp(parent_swap_node->name,swap_node->name) > 0)
	parent_swap_node->left = swap_node->left;
      else
	parent_swap_node->right = swap_node->left;

        if(carrent_position){ /*親の左側につける*/

          swap_node->left->par = parent_swap_node;
          parent->left = swap_node;
          swap_node->left = carrent->left;
          carrent->left->par = swap_node;
          swap_node->right = carrent->right;
	  carrent->right->par = swap_node;
          swap_node->par = parent;

	} else { /*親の右側につける*/

          swap_node->left->par = parent_swap_node;
          parent->right = swap_node;
          swap_node->left = carrent->left;
	  carrent->left->par = swap_node;
          swap_node->right = carrent->right;
	  carrent->right->par = swap_node;
	  swap_node->par = parent;

	}
    }
  }
  free(carrent);
  return 0;
}

/*--- 木のデータを出力 ---*/
void printf_node(tree_node *node)
{ 
  if(node == NULL)
    return;

  if(node->left != NULL){
    printf_node(node->left);
  }

  printf("名前:%s",node->name);
  printf("\t電話番号:%s\n",node->call_number);  

  if(node->right != NULL){
     printf_node(node->right);   
  }

  return;
}   

/*--- メモリ解放 ---*/
void free_memori(tree_node *node)
{
  if(node==NULL)
    return;

  free_memori(node->left);
  free_memori(node->right);
  free(node);
}

/*--- 探索 ---*/
tree_node* Nibuntansaku(char *name, tree_node *node)
{
  /* 現在のノードの名前より名前順が後だった場合 */ 
  if(strcmp(name,node->name) > 0){
    if(node->right != NULL){
      return (Nibuntansaku(name,node->right));
    } else {
        return NULL;
    }
    /* 現在のノードの名前より名前順が前だった場合 */
  } else if(strcmp(name,node->name) < 0){
      if(node->left != NULL){
	return (Nibuntansaku(name,node->left));
      } else {
	  return NULL;
      }

  }
  /* 現在のノードが探しているデータだった場合 */
  return node;
}


/*--- ファイルのデータから二分木を作る ---*/
void make_tree(FILE *fin)
{
  char name[SIZE_OF_NAME];
  char call_number[SIZE_OF_CALLNUMBER];

  if(fscanf(fin,"%s",&name)!=-1 && fscanf(fin,"%s",&call_number)!=-1){
    insert_node(name,call_number,tree_root);
    return(make_tree(fin));
  } else {
    return;
  }
}

void printf_deep(tree_node *node)
{
  int left_deep;
  int right_deep;

  if(node->left != NULL)
    printf_deep(node->left);
  
  if(node->right != NULL)
    printf_deep(node->right);

  /*左部分木の高さを求める*/
  if(node->left == NULL)
    left_deep = 0;
  else
    left_deep = deep_tree(node->left,1);

  /*右部分木の高さを求める*/
  if(node->right == NULL)
    right_deep = 0;
  else
    right_deep = deep_tree(node->right,1);
  
  /*左右分木の高さの差を求める*/
  if(left_deep < right_deep)
    printf("%d,",right_deep-left_deep);
  else
    printf("%d,",left_deep-right_deep);

}
  


int main(void)
{
  FILE *fin;
  char name[SIZE_OF_NAME];
  char call_number[SIZE_OF_CALLNUMBER];
  char filename[SIZE_OF_FILENAME];
  int action;
  tree_node *node;

  printf("file name = ");
  scanf("%s", filename);
  if ((fin=fopen(filename, "r"))==NULL) {    /*読取りモードでオープン*/
    printf("ファイルをオープンできません\n");
    return;
  }
  
  make_tree(fin);
  fclose(fin);

  do{
    printf("何を行いますか?\n");
    printf("１：挿入　２：検索　３：削除　４：平衡木　５：データの出力　６：終了\n");
    scanf("%d",&action);

    switch(action){
      case 1:
	printf("挿入するデータを入力してください\n");
        printf("名前:"); scanf("%s",&name);
        printf("電話番号:"); scanf("%s",&call_number);
        insert_node(name,call_number,tree_root);
        printf("データを挿入しました");
        break;

      case 2:       
        printf("検索するデータの名前を入力してください\n");
        printf("名前:"); scanf("%s",&name);
        node = Nibuntansaku(name,tree_root);
        if(node == NULL){
          printf("見つかりませんでした\n");
        } else {
          printf("%sさんの電話番号は%sです\n",name,node->call_number);
	}
        break;

      case 3:
        printf("削除するデータの名前を入力してください\n");
        printf("名前:"); scanf("%s",&name);

        if(delete_node(name, NULL, tree_root, -1) == -1)
          printf("データが見つかりませんでした\n");
        else
          printf("削除しました\n");
        break;

      case 4:

	printf("全てのノードにおける左右分木の高さの差の一覧を出力します\n");
	printf_deep(tree_root);
        printf("\n出力完了\n");

        printf("平衡木作成中\n");
        while(1){
	  suich = 0;
          make_AVLtree(tree_root);
	  if(suich==0)
	    break;
	}
        printf("平衡木作成完了\n");

        printf("全てのノードにおける左右分木の高さの差の一覧を出力します\n");
        printf_deep(tree_root);
        printf("\n出力完了\n");        

        break;
    
      case 5:
        printf("データを出力します\n");
        printf_node(tree_root);
        break;
    }

  }while(action != 6);
  
  free_memori(tree_root);

  return;
}