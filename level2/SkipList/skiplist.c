#include"create.cpp"
#include"insert.cpp"
#include"delete.cpp"
#include"modify.cpp"
#include"search.cpp"
#include"distroy.cpp"
#include<stdio.h>
#include<conio.h>
int main(){
	skip_list* Mylist = skip_list_creat(6);
	int ch;
	printf("input'a'to insert elements,\ninput'b'to modify elements,\ninput'c'to search elements,\ninput'd'to delete elements,input'e'to finish\n");
	while (ch = getch()) 
	{
		
		switch (ch)
		{
			
		   case'a':
		   {
			   int key, value = 0;
			   printf("insert//input key:\n");
			   scanf("%d", &key);
			   printf("input value:\n");
			   scanf("%d", &value);
			   skip_list_insert(Mylist, key, value); 
		   }
		   case'b': {
			   int key, value = 0;
			   printf("modify//input key:\n");
			   scanf("%d", &key);
			   printf("input value:\n");
			   scanf("%d", &value);
			   skip_list_modify(Mylist, key, value);
		   }
		   case'c': {
			   int key, value = 0;
			   printf("search//input key:\n");
			   scanf("%d", &key);
			   printf("input value:\n");
			   scanf("%d", &value);
			   skip_list_search(Mylist, key, value);
		   }
		   case'd': {
			   int key= 0;
			   printf("delete//input key:\n");
			   scanf("%d", &key);
			   skip_list_delete(Mylist, key);
		   }
		   case'e': {
			   printf("destroy!\n");
			   skip_list_destroy(Mylist);
			   printf("Bye")
		   }
		default:
		break;
		    
		}
		
	}
	return 0;
}
