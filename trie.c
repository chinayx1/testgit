#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHILD 26
typedef struct tree
{
	int count;
	struct tree *child[MAX_CHILD];	
} Tree_node, *Trie_node;

Trie_node createNode()
{
	Trie_node n;
	n = (Trie_node) malloc(sizeof(Tree_node));
	memset(n, 0, sizeof(Tree_node));
	return n;
}

int insertNode(Trie_node root, char *str)
{
	Trie_node temp, new_node;
	temp = root;
	char *p = str;
	int child_index;
	while(*p != '\0')
	{
		child_index = *p - 'a';		
		if(temp->child[child_index] != NULL)
		{
			temp = temp->child[child_index];
		}
		else
		{
			new_node = createNode();
			temp->child[child_index] = new_node;
			temp = temp->child[child_index];
		}
		p++;
	}
	temp->count++;
	return 1;
}

int strpos(Trie_node root, char *handle_str)
{
	char *p = handle_str;
	Trie_node temp;
	temp = root;
	int pos = -1;
	int key = 0;
	int child_index;
	int start_key = 0;
	while(p[key] != '\0')		
	{
		child_index = p[key] - 'a';
		if(temp->child[child_index] != NULL)
		{
			if(start_key == 0)
			{
				start_key = key;
			}
			temp = temp->child[child_index];	
		}
		else if(start_key > 0)
		{
			start_key = 0;
			temp = root;
		}	
		key++;
		if(temp->count > 0)
		{
			pos = start_key;
			break;
		}
	}
	return pos;
}

void destroyTrie(Trie_node root)
{
	Trie_node temp;
	temp = root;
	for(int i = 0; i < MAX_CHILD; i++)
	{
		if(temp->child[i])
		{
			destroyTrie(temp->child[i]);
		}
	}
	free(root);
}

int main()
{
	Trie_node root;
	root = createNode();
	char *posstr = "esd";
	insertNode(root, posstr);
	char *handle_str = "afeweasddesd";
	int tpos = strpos(root, handle_str);
	printf("find string pos is %d\n", tpos);
	destroyTrie(root);
	return 0;
}
